#include "ConvertColorSpace.hpp"
#include "ColorAdjustment.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc,char **argv)
{
    
    std::string path("/home/solaborate/Desktop/oRGB/img/lena.png");

    cv::Mat img=cv::imread(path,cv::IMREAD_COLOR);

    if(!img.data)
        std::cout<<"Image not loaded.Check path: "<<path<<std::endl;
   
    cv::namedWindow("Result",cv::WINDOW_FULLSCREEN);
    cv::imshow("Result",img);
    
    cv::Mat res =  img.clone();
    ConvertColorSpace ccs(img);
    ColorAdjustment ca(img);

    res=ccs.convertToORGB(res);
    
    cv::namedWindow("oRGB",cv::WINDOW_FULLSCREEN);
    cv::imshow("oRGB",res);
    
    res=ccs.filter(Eigen::Vector2d{0,23});

    res=ccs.convertToRGB();

    cv::namedWindow("RGB",cv::WINDOW_FULLSCREEN);
    cv::imshow("RGB",res);
    
    std::cout<<"Press any key to close..."<<std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}