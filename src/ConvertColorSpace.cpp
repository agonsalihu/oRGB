#include "ConvertColorSpace.hpp"

ConvertColorSpace::ConvertColorSpace(cv::Mat m){
    this->img=m;
}

void ConvertColorSpace::setNormalized(cv::Mat m){
    this->imgoRgb=m;
}

void ConvertColorSpace::setDeNormalized(cv::Mat m){
    this->imgoRgb=m;
}

cv::Mat ConvertColorSpace::getNormalized(){
    return imgoRgb;
}

cv::Mat ConvertColorSpace::getDeNormalized(){
    return imgRgb;
}

cv::Mat ConvertColorSpace::convertToORGB(){
    
    cv::MatIterator_<cv::Vec3d> it;
    
    for(it=img.begin<cv::Vec3d>();it!=img.end<cv::Vec3d>();it++){

        double gamma=2.2;

        (*it)[0]=(pow((float)((*it)[0]/255.0),1/gamma)*255.0f);
        (*it)[1]=(pow((float)((*it)[0]/255.0),1/gamma)*255.0f);
        (*it)[2]=(pow((float)((*it)[0]/255.0),1/gamma)*255.0f);
    
    }

    
    double b,g,r;
    
    for(it=img.begin<cv::Vec3d>();it!=img.end<cv::Vec3d>();it++){
        
        b=(*it)[0];
        g=(*it)[1];
        r=(*it)[2];

        Eigen::Vector3d vec{b,g,r};

        vec=transform_matrix*vec;

        (*it)[0]=vec[0];
        (*it)[1]=vec[1];
        (*it)[2]=vec[2];

    }

    
    return img;
}

void ConvertColorSpace::convertToRGB(){

}