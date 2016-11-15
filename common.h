#include <string>
#include <stdio.h>
#include <vector>
#include <opencv.hpp>

#ifndef COMMON_H
#define COMMON_H

using namespace std;
using namespace cv;


class PointPicker {
private:
    int num_point;
    static std::string windowName;
    cv::Mat display_image;
    std::vector<Point2f> points;
public:
    PointPicker(int n);
    static void mouse_callback(int event, int x, int y, int flags, void* userdata);
    void show(std::string name,const cv::Mat& display_image);
    inline std::vector<Point2f> getPoints() const
    { return points; }
};

#endif // COMMON_H
