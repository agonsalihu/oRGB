/**
 * @file ConvertColorSpace.hpp
 * @author Agon Salihu (agon.salihu99@hotmail.com)
 * @brief Converting RGB image to oRGB
 * @version 0.1
 * @date 2020-03-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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
/**
 * @brief Class for converting image
 * 
 */
class ConvertColorSpace
{
    private:
        /**
         * @brief Basic image
         * 
         */
        cv::Mat img;
        /**
         * @brief matrix for translate to LCC
         * 
         */
        Eigen::Matrix3d transform_matrix{{0.2990,0.5870,0.1140},
                                         {0.5000,0.5000,-1.0000},
                                         {0.8660,-0.8660,0.0000}};
        /**
         * @brief matrix for translate to RGB
         * 
         */
        Eigen::Matrix3d inverse_transform_matrix{{1.0000,0.1140,0.7436},
                                                 {1.0000,0.1140,-0.4111},
                                                 {1.0000,-0.8860,0.1663}};

        /**
         * @brief 64b oRGB image
         * 
         */
        cv::Mat oRGB;
        

    public:
        /**
         * @brief Construct a new Convert Color Space object
         * 
         */
        ConvertColorSpace(void)=default;
        /**
         * @brief Construct a new Convert Color Space object
         * 
         * @param m Construct a new Convert Color Space object intializing image
         */
        ConvertColorSpace(cv::Mat m);
        /**
         * @brief Destroy the Convert Color Space object
         * 
         */
        ~ConvertColorSpace()=default;
        /**
         * @brief Transforming image R'B'G'--> L'C'C'
         * 
         * @param m 
         * @return cv::Mat 
         */
        cv::Mat linearTransform(cv::Mat m);
        /**
         * @brief Rotate image L'C'C --> oRGB
         * 
         * @param m 
         * @return cv::Mat 
         */
        cv::Mat rotateToORGB(cv::Mat m);
        /**
         * @brief Method for Converting colorspace from RGB to oRGB
         * 
         * @param m 
         * @return cv::Mat 
         */
        cv::Mat convertToORGB(cv::Mat m);
        /**
         * @brief Transform from L'C'C to R'G'B
         * 
         * @param m 
         * @return cv::Mat 
         */
        cv::Mat delinearTransform(cv::Mat m);
        /**
         * @brief Rotate from oRGB to L'C'C
         * 
         * @param m 
         * @return cv::Mat 
         */
        cv::Mat rotateToRGB(cv::Mat m);
        /**
         * @brief method for converting color space from oRGB to RGB
         * 
         * @return cv::Mat 
         */
        cv::Mat convertToRGB(cv::Mat oRGB);
        /**
         * @brief method for converting colorspace of a given Image
         * 
         * @return cv::Mat 
         */
        cv::Mat convertToRGB();
        /**
         * @brief Get the oRGB 64b image object
         * 
         * @return cv::Mat 
         */
        cv::Mat getImage64b();
        /**
         * @brief method for showing image turning from 64b to 8b
         * 
         * @param image 
         * @return cv::Mat 
         */
        cv::Mat showImage(cv::Mat image);

};
#endif