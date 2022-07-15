//
// Created by enterc on 2022/07/14.
//

#include <thread>
#include <future>
#include <list>
#include <iostream>
#include <opencv2/highgui.hpp>
#include "CameraThread.h"

namespace irmt {
    std::string gstreamerPipeline(int captureWidth, int captureHeight, int displayWidth, int displayHeight, int framerate, int flipMethod) {
        using namespace std;
        return "nvarguscamerasrc ! " \
               "video/x-raw(memory:NVMM), " \
               "width=" + to_string(captureWidth) + ", height=" + to_string(captureHeight) + "," \
               "framerate=(fraction)" + to_string(framerate) + "/1 ! " \
               "nvvidconv flip-method=" + to_string(flipMethod) + " ! " \
               "video/x-raw, width=" + to_string(displayWidth) + ", height=" + to_string(displayHeight) + ", format=(string)GRAY8 ! " \
               "appsink";
    }

    CameraThread::CameraThread() = default;
    CameraThread::~CameraThread() = default;

    void CameraThread::start() {
        using namespace std;
        using namespace cv;

        auto setupExit = promise<void>();
        auto setupCamera = [&](future<void> exitSignal){ // Open camera
            string pipeline = irmt::gstreamerPipeline(1280, 720, 1280, 720, 60, 0);
            this->camera = cv::VideoCapture(pipeline, cv::CAP_GSTREAMER);

            camera.open(pipeline, CAP_GSTREAMER);

            if (!camera.isOpened()) {
                cerr << "failed to open camera id:0" << endl;
                return;
            }

            cout << "trying to capture first frame" << endl;
            while(exitSignal.wait_for(chrono::microseconds(1)) == future_status::timeout) {
                static Mat testFrame;
                bool result = camera.read(testFrame);
                if (result) {
                    cout << "testFrame captured. row:col=" << testFrame.rows << ":" << testFrame.cols << endl;
                    break;
                }
            }
            cout << "exit capture first frame" << endl;
        };

        auto captureExit = promise<void>();
        auto captureFrame = [&camera = this->camera](future<void> exitSignal){ // Capture
            auto buffer = std::list<Mat>();
            Mat captured;

            auto lastTime = chrono::high_resolution_clock::now();
            int frameCount = 0;
            // cuda::GpuMat img_gpu_src, img_gpu_dst;n
            while (exitSignal.wait_for(chrono::microseconds(1)) == future_status::timeout) {
                auto result = camera.read(captured);
                if (result) {
                    if (frameCount % 1 == 0 && !captured.empty()) {
                        frameCount = 0;
                        imshow("Live", captured);
                        if (waitKey(1) >= 0) break;
                    }
                    ++frameCount;
                } else {
                    cout << "capture skipped " << endl;
                }
            }
            cout << "exit capture frame" << endl;
        };

        setupCamera(setupExit.get_future());
        thread th1(captureFrame, captureExit.get_future());

        auto delay = chrono::milliseconds(500);
        for (int i = 0; i < 10; ++i) {
            cout << "current " << i << endl;
            this_thread::sleep_for(delay);
        }
        captureExit.set_value();

        th1.join(); // wait to join th1
        camera.release();
    }
} // irmt