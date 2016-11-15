#include <QApplication>
#include <QString>
#include <QObject>
#include <QFileDialog>
#include <string>
#include <stdio.h>
#include <vector>
#include <opencv.hpp>
#include "common.h"

using namespace std;
using namespace cv;

class GeometricTransform {
public:
    cv::Mat perspectiveTransformEstimate(std::vector<cv::Point2f> inputs, std::vector<cv::Point2f> targets);
    void forwardTransform(const cv::Mat& src, cv::Mat& output, const cv::Mat& transformMatrix);
};

cv::Mat GeometricTransform::perspectiveTransformEstimate(std::vector<cv::Point2f> inputs, std::vector<cv::Point2f> targets){
    return getPerspectiveTransform(inputs, targets);
}

void GeometricTransform::forwardTransform(const Mat& src, Mat& output, const Mat& transformMatrix) {
    Mat dst = Mat::zeros(src.size(), src.type());
    typedef cv::Point3_<uchar> Pixel;
    int i, j;
    for (i = 0; i < src.rows; ++i) {
        const Pixel* ptr = src.ptr<Pixel>(i);
        for ( j = 0; j < src.cols; ++j) {
            Mat p1 = (Mat_<double>(3,1) << i , j , 1);
            //cout << p1 << endl;
            //cout << "Matrix size " << endl << transformMatrix.size() << endl;
            Mat p2 = transformMatrix * p1;
            double x = p2.at<double>(0,0);
            double y = p2.at<double>(1,0);
            double w = p2.at<double>(2,0);
            x /= w; y /=w;
            int _x = cvRound(x);
            int _y = cvRound(y);
            // Check bound
            if(_x >= 0 && _x < dst.rows && _y >= 0 && _y < dst.cols){
            // Set pixel _x, _y
                dst.at<Pixel>(_x, _y) = ptr[j];
            }
        }
    }
    src.forEach<Pixel>([](const Pixel& p, const int* idx) -> void {

    });
    output = dst;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QString fileName = QFileDialog::getOpenFileName(nullptr, QObject::tr("Open File"),
                                                    "/home/bbphuc/Downloads",
                                                    QObject::tr("Images (*.png *.xpm *.jpg)"));

    std::string filename = fileName.toStdString();
    auto src = imread(filename, IMREAD_COLOR);

    if (src.empty()){
        printf("Some thing wrong?\n");
    }

    GeometricTransform geoTransform;
    std::vector<Point2f> targets = {Point2f(0,0), Point2f(300, 0), Point2f(300, 300), Point(0, 300)};
    PointPicker pp(4);



    pp.show("p", src);
    std::vector<Point2f> inputs = pp.getPoints();
    Mat transformMatrix = geoTransform.perspectiveTransformEstimate(inputs, targets);
    cout << transformMatrix << endl;
    Mat output;
    geoTransform.forwardTransform(src, output, transformMatrix);
    imshow("Output" , output);
    waitKey();
    return 0;
}
