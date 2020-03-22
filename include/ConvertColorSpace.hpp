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
class ConvertColorSpace{
    private:
        /**
         * @brief Basic image
         * 
         */
        cv::Mat img;
        /**
         * @brief image in LCC color space
         * 
         */
        cv::Mat normalized;
        /**
         * @brief image in RBG color space from LCC
         * 
         */
        cv::Mat denormalizet;
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

    public:
        /**
         * @brief Construct a new Convert Color Space object
         * 
         */
        ConvertColorSpace(void);
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
         * @brief Set the Image object
         * 
         * @param m image
         */
        void setImage(cv::Mat m);
        /**
         * @brief Set the Normalized object
         * 
         * @param m Normalized Image
         */
        void setNormalized(cv::Mat m);
        /**
         * @brief Set the De Normalized object
         * 
         * @param m 
         */
        void setDeNormalized(cv::Mat m);

        /**
         * @brief Get the Image object
         * 
         * @return cv::Mat 
         */
        cv::Mat getImage();
        /**
         * @brief Get the Normalized object
         * 
         * @return cv::Mat 
         */
        cv::Mat getNormalized();
        /**
         * @brief Get the De Normalized object
         * 
         * @return cv::Mat 
         */
        cv::Mat getDeNormalized();
        /**
         * @brief method for converting color space to oRGB
         * 
         * @return cv::Mat 
         */

        cv::Mat convertToORGB();
        /**
         * @brief method for converting color space to RGB
         * 
         * @return cv::Mat 
         */
        cv::Mat convertToRGB();
    
};
#endif