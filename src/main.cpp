#include <iostream>
#include <list>
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudaarithm.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "CameraThread.h"

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
    std::cout << "Hello, IR marker tracker!" << std::endl;

    {
        irmt::CameraThread camera;
        camera.start();

        // if (buffer.size() >= N) {
        //     output.forEach<uchar>([&](uchar &p, const int* position) -> void {
        //         p = 0; // clear previous output
        //         int i = 0;
        //         for (const auto &item: buffer) {
        //             p += (double)item.at<int>(position) * An[i];
        //             ++i;
        //             if (i > N) break;
        //         }
        //     });
        //     buffer.pop_back();
        // } else {
        //     cout << "buffering... " << buffer.size() << endl;
        // }

        // Cuda test
        // try {
        //     img_gpu_src.upload(capBuffer);
        //     cv::cuda::threshold(img_gpu_src, img_gpu_dst, 128, 255, THRESH_BINARY);
        //     // cv::cuda::bilateralFilter(img_gpu_src, img_gpu_dst, 3, 1 , 1);
        //     img_gpu_dst.download(output);
        // } catch (const cv::Exception &ex) {
        //     cout << "Error: " << ex.what() << endl;
        // }
        //
        // // Calculate time
        // auto end = chrono::high_resolution_clock::now();
        // cout << "fps:" << 1.0 / (chrono::duration_cast<chrono::nanoseconds>(end - lastTime).count() / 1000000000.0)
        //      << endl;
        // lastTime = end;
    }

    return 0;
}

