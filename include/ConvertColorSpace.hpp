#ifndef ___CONVERT_COLOR_SPACE_H____
#define ___CONVERT_COLOR_SPACE_H____

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>

class ConvertColorSpace{
    private:
        cv::Mat img;
        cv::Mat imgoRgb;
        cv::Mat imgRgb;
        Eigen::Matrix3d transform_matrix{{0.299,0.587,0.114},
                                         {0.500,0.500,-1.00},
                                         {0.866,-0.866,0.00}};
        Eigen::Matrix3d inverse_transform_matrix{{1.000,0.1140,0.7436},
                                                 {1.000,0.1140,-0.4111},
                                                 {1.000,-0.8860,0.1663}};

    public:
        ConvertColorSpace(void);
        ConvertColorSpace(cv::Mat m);
        ~ConvertColorSpace()=default;

        void setNormalized(cv::Mat m);
        void setDeNormalized(cv::Mat m);

        cv::Mat getNormalized();
        cv::Mat getDeNormalized();

        cv::Mat convertToORGB();
        void convertToRGB();

};
#endif