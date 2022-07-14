//
// Created by enterc on 2022/07/14.
//

#ifndef IR_MARKER_TRACKER_CAMERATHREAD_H
#define IR_MARKER_TRACKER_CAMERATHREAD_H

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"

namespace irmt {

    class CameraThread {
        public:
        CameraThread();
        ~CameraThread();
        void start();
        private:
        cv::VideoCapture camera;
        std::string gstreamerPipeline();
    };

    extern std::string gstreamerPipeline(int captureWidth,
                                         int captureHeight,
                                         int displayWidth,
                                         int displayHeight,
                                         int framerate,
                                         int flipMethod);
} // irmt

#endif //IR_MARKER_TRACKER_CAMERATHREAD_H
