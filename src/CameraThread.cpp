//
// Created by enterc on 2022/07/14.
//

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
               // "videoconvert ! " \
               // "video/x-raw, format=(string)GRAY8 ! " \
               //           "nv3dsink";
               "appsink";
    }

    CameraThread::CameraThread() = default;
    CameraThread::~CameraThread() = default;

    void CameraThread::start() {
        using namespace std;
        using namespace cv;

        { // Open camera
            string pipeline = irmt::gstreamerPipeline(1280, 720, 1280, 720, 60, 0);
            this->camera = cv::VideoCapture(pipeline, cv::CAP_GSTREAMER);

            camera.open(pipeline, CAP_GSTREAMER);

            if (!camera.isOpened()) {
                cerr << "failed to open camera id:0" << endl;
                return;
            }
        }

        { // Capture
            auto buffer = std::list<Mat>();
            Mat captured, output;
            while(!camera.read(output)) {
                cout << "loading first frame" << endl;
            }

            cout << "row:col " << output.rows << ":" << output.cols << endl;

            auto lastTime = chrono::high_resolution_clock::now();
            int frameCount = 0;
            // cuda::GpuMat img_gpu_src, img_gpu_dst;
            for (;;) {
                auto result = camera.read(captured);
                if (result) {
                    if (frameCount % 10 == 0 && !output.empty()) {
                        frameCount = 0;
                        imshow("Live", captured);
                        // imshow("Output", output);
                        //if (waitKey(1) >= 0) break;
                    }

                    ++frameCount;
                } else {
                    cout << "capture skipped " << endl;
                }
            }
        }
    }
} // irmt