#include "common.h"

std::string PointPicker::windowName = std::string();
PointPicker::PointPicker(int n) : num_point(n) {}

void PointPicker::mouse_callback(int event, int x, int y, int flags, void *userdata){
    // Cast userdata
    PointPicker* pointPicker = NULL;
    if (userdata != NULL){
        pointPicker = (PointPicker*)userdata;
    }
    if(event == EVENT_LBUTTONDOWN) {
        Point2f p = Point2f(x, y);
        printf("Clicked on Point(%d, %d)\n", x, y);
        pointPicker->points.push_back(p);
        if ((size_t)pointPicker->num_point > pointPicker->points.size()){
            // Draw circle
            Point2f center(x, y);
            circle(pointPicker->display_image, center, 5, Scalar(255, 0, 0), 2);
            // Call function again
            imshow(pointPicker->windowName, pointPicker->display_image);
        } else {

            destroyWindow(pointPicker->windowName);
        }
    }
}

void PointPicker::show(string name, const cv::Mat& display_image){
    windowName = name;
    this->display_image = display_image.clone();
    // Clear old points
    points.clear();
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, display_image);
    setMouseCallback(windowName, mouse_callback, this);
    waitKey(0);

}
