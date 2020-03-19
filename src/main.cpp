#include "wrapper.hpp"
#include "ConvertColorSpace.hpp"

#include <iostream>


int main(int argc,char **argv){
    
    std::string path("/home/solaborate/Desktop/oRGB/img/lena.png");

    cv::Mat img=cv::imread(path,cv::IMREAD_COLOR);

    if(!img.data)
        std::cout<<"Image not loaded.Check path: "<<path<<std::endl;
    
    cv::namedWindow("Result",cv::WINDOW_FULLSCREEN);
    cv::imshow("Result",img);
    
    cv::Mat res =  img.clone();
    cv::cvtColor(res, res, cv::COLOR_BGR2RGB);

    ConvertColorSpace ccs(res);
    res=ccs.convertToORGB();
    
    cv::cvtColor(res, res, cv::COLOR_RGB2BGR);
    
    cv::namedWindow("oRGB",cv::WINDOW_FULLSCREEN);
    cv::imshow("oRGB",res);

    std::cout<<"Press any key to close..."<<std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}