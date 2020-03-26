#include "ConvertColorSpace.hpp"
#include "ColorAdjustment.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc,char **argv)
{
    //Path for image
    std::string path("/home/solaborate/Desktop/2/oRGB/img/pots.jpg");

    //Read image and save in img
    cv::Mat img=cv::imread(path,cv::IMREAD_COLOR);

    //Check if image is loaded
    if(!img.data)
        std::cout<<"Image not loaded.Check path: "<<path<<std::endl;
    
    //Show Original image
    cv::namedWindow("Original",cv::WINDOW_FULLSCREEN);
    cv::imshow("Original",img);
    
    //Creating objects for ConvertColorSpace and ColorAdjustemnt Class
    ConvertColorSpace ccs(img);
    ColorAdjustment ca(img);

    //Convert RGB image to oRGB
    img=ccs.convertToORGB(img);
    
    //Show oRGB image
    cv::namedWindow("oRGB",cv::WINDOW_FULLSCREEN);
    cv::imshow("oRGB",img);
    
    //Filter oRGB image
    img=ccs.filter(Eigen::Vector2d{0,0});

    //Convert back to RGB
    img=ccs.convertToRGB();

    //Show filtered RGB image
    cv::namedWindow("RGB",cv::WINDOW_FULLSCREEN);
    cv::imshow("RGB",img);
    
    //Wait for key and terminate program
    std::cout<<"Press any key to close..."<<std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}