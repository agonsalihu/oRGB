#include "wrapper.hpp"
#include "ConvertColorSpace.hpp"

#include <iostream>


int main(int argc,char **argv){
    
    Wrapper mat(Eigen::Matrix3d::Identity());

    mat.setTranslateMatrix(Eigen::Vector2d(2,3));

    Eigen::Matrix3d translate_matrix=mat.getTranslateMatrix();

    std::cout<<translate_matrix<<std::endl;

    std::string path("/home/solaborate/Desktop/oRGB/img/lena.png");

    cv::Mat img=cv::imread(path,cv::IMREAD_COLOR);

    if(!img.data)
        std::cout<<"Image not loaded.Check path: "<<path<<std::endl;
    
    cv::namedWindow("Result",cv::WINDOW_FULLSCREEN);
    cv::imshow("Result",img);

    cv::Mat res =  img.clone();

    //ConvertColorSpace ccs(res);

    //res=ccs.convertToORGB();

    /*cv::MatIterator_<cv::Vec3b> it;

    double b1,g1,r1;
    for(it = res.begin<cv::Vec3b>(); it != res.end<cv::Vec3b>(); ++it)
    {
        
        b1=(*it)[0];
        g1=(*it)[1];
        r1=(*it)[2];

        Eigen::Vector3d color1(b1,g1,r1);

        color1 = mat.multiply(translate_matrix,color1);
        
        (*it)[0] =mat.multiply(translate_matrix,color1)[0];
        (*it)[1] =mat.multiply(translate_matrix,color1)[1];
        (*it)[2] =mat.multiply(translate_matrix,color1)[2];
    }*/

    //cv::namedWindow("Iterator",cv::WINDOW_FULLSCREEN);
    //cv::imshow("Iterator",res);

    std::cout<<"Press any key to close..."<<std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}