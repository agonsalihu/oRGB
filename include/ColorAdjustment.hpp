/**
 * @file ColorAdjustment.hpp
 * @author Agon Salihu (agon.salihu99@hotmail.com)
 * @brief Color Shading warm to cool
 * @version 0.1
 * @date 2020-03-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef ___COLOR_ADJUSTMENT_H____
#define ___COLOR_ADJUSTMENT_H____

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>

/**
 * @brief Class for Color Shading and Adjustment
 * 
 */
class ColorAdjustment{
    private:
        /**
         * @brief Basic image
         * 
         */
        cv::Mat img;

    public:
        /**
         * @brief Construct a new Color Adjustment object
         * 
         */
        ColorAdjustment(void)=default;
       
        /**
         * @brief Construct a new Color Adjustment object
         * 
         * @param m sets image for color adjusting
         */
        ColorAdjustment(cv::Mat m);
        
        /**
         * @brief Destroy the Color Adjustment object
         * 
         */
        ~ColorAdjustment()=default;
        
        /**
         * @brief Set the Image object
         * 
         * @param m basic image
         */
        void setImage(cv::Mat m);
        /**
         * @brief Get the Image object
         * 
         * @return cv::Mat basic image
         */
        cv::Mat getImage();
        
};
#endif