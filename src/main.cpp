#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    {
        using namespace std;
        using namespace cv;
        Mat frame;
        VideoCapture cap;
        cap.open(0, cv::CAP_ANY);

        if (!cap.isOpened()) {
            cerr << "failed to open camera id:0" << endl;
            return -1;
        }

        for(;;) {
            cap.read(frame);

            if(!frame.empty()) {
                imshow("Live", frame);
                if (waitKey(5) >= 0) break;
            }
        }
    }

    return 0;
}
