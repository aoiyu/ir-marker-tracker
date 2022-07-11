#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <list>

const static int N = 13;
const static double An[N] = {
        -1.009102304854209e-01 ,
        3.898171832519375e-17 ,
        1.513653457281314e-01 ,
        -3.469446951953614e-17 ,
        -1.870978567577278e-01 ,
        0.000000000000000e+00 ,
        2.000000000000000e-01 ,
        0.000000000000000e+00 ,
        -1.870978567577278e-01 ,
        -3.469446951953614e-17 ,
        1.513653457281314e-01 ,
        3.898171832519375e-17 ,
        -1.009102304854209e-01
//        3.382710778154774e-17 ,
//        -4.466739185417679e-02 ,
//        -4.792173602385930e-17 ,
//        5.294696238906402e-02 ,
//        1.214306433183765e-17 ,
//        -6.054613829125259e-02 ,
//        -7.806255641895632e-17 ,
//        6.718948146708566e-02 ,
//        -3.122502256758253e-17 ,
//        -7.263270379186808e-02 ,
//        -4.163336342344337e-17 ,
//        7.667347858597003e-02 ,
//        2.775557561562891e-17 ,
//        -7.916044967850472e-02 ,
//        0.000000000000000e+00 ,
//        8.000000000000002e-02 ,
//        0.000000000000000e+00 ,
//        -7.916044967850472e-02 ,
//        2.775557561562891e-17 ,
//        7.667347858597003e-02 ,
//        -4.163336342344337e-17 ,
//        -7.263270379186808e-02 ,
//        -3.122502256758253e-17 ,
//        6.718948146708566e-02 ,
//        -7.806255641895632e-17 ,
//        -6.054613829125259e-02 ,
//        1.214306433183765e-17 ,
//        5.294696238906402e-02 ,
//        -4.792173602385930e-17 ,
//        -4.466739185417679e-02 ,
//        3.382710778154774e-17
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    {
        using namespace std;
        using namespace cv;
        Mat capBuffer;
        VideoCapture cap;
        cap.set(CAP_PROP_FRAME_WIDTH, 1280);
        cap.set(CAP_PROP_FRAME_HEIGHT, 720);
        cap.set(CAP_PROP_FPS, 60);

        cap.open(0, cv::CAP_ANY);

        if (!cap.isOpened()) {
            cerr << "failed to open camera id:0" << endl;
            return -1;
        }

        auto buffer = std::list<Mat>();
        Mat output;
        while(!cap.read(output)) {
            cout << "loading first frame" << endl;
        }

        for (;;) {
            auto result = cap.read(capBuffer);

            if (result) {
                auto begin = chrono::high_resolution_clock::now();

                cv::cvtColor(capBuffer, output, COLOR_BGR2GRAY);
                //auto frame = capBuffer.clone();
                buffer.push_front(output);

                if (buffer.size() >= N) {
                    output.forEach<uchar>([&](uchar &p, const int* position) -> void {
                        // p = 0; // clear previous output
                        int i = 0;
                        for (const auto &item: buffer) {
                            p += (double)item.at<int>(position) * An[i];
                            ++i;
                            if (i > N) break;
                        }
                    });
                    buffer.pop_back();
                } else {
                    cout << "buffering... " << buffer.size() << endl;
                }

                auto end = chrono::high_resolution_clock::now();
                // cout << "time elapsed " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;
            } else {
                cout << "capBuffer skipped " << endl;
            }

            if (!output.empty()) {
                // imshow("Live", capBuffer);
                imshow("Output", output);
                if (waitKey(1) >= 0) break;
            }
        }
    }

    return 0;
}

