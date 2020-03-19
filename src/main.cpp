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
    ConvertColorSpace ccs(res);
    cv::cvtColor(res, res, cv::COLOR_BGR2RGB);
    res=ccs.convertToORGB();
    cv::cvtColor(res, res, cv::COLOR_RGB2BGR);

    cv::namedWindow("oRGB",cv::WINDOW_FULLSCREEN);
    cv::imshow("oRGB",res);


    cv::Mat res1=res.clone();
    cv::cvtColor(res1, res1, cv::COLOR_BGR2RGB);
    ConvertColorSpace ccs1(res1);
    res1=ccs1.convertToRGB();
    cv::cvtColor(res1, res1, cv::COLOR_RGB2BGR);
    

    cv::namedWindow("RGB",cv::WINDOW_FULLSCREEN);
    cv::imshow("RGB",res1);

    std::cout<<"Press any key to close..."<<std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}