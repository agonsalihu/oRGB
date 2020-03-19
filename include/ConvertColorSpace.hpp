#ifndef ___CONVERT_COLOR_SPACE_H____
#define ___CONVERT_COLOR_SPACE_H____

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>
#include <math.h>

class ConvertColorSpace{
    private:
        cv::Mat img;
        cv::Mat normalized;
        cv::Mat denormalizet;
        Eigen::Matrix3d transform_matrix{{0.2990,0.5870,0.1140},
                                         {0.5000,0.5000,-1.0000},
                                         {0.8660,-0.8660,0.0000}};
        Eigen::Matrix3d inverse_transform_matrix{{1.0000,0.1140,0.7436},
                                                 {1.0000,0.1140,-0.4111},
                                                 {1.0000,-0.8860,0.1663}};

    public:
        ConvertColorSpace(void);
        ConvertColorSpace(cv::Mat m);
        ~ConvertColorSpace()=default;

        void setImage(cv::Mat m);
        void setNormalized(cv::Mat m);
        void setDeNormalized(cv::Mat m);

        cv::Mat getImage();
        cv::Mat getNormalized();
        cv::Mat getDeNormalized();

        cv::Mat convertToORGB();
        cv::Mat convertToRGB();
        

};
#endif