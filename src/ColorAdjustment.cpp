#include "ColorAdjustment.hpp"

ColorAdjustment::ColorAdjustment(cv::Mat m){
    ColorAdjustment::setImage(m);
}

void ColorAdjustment::setImage(cv::Mat m){
    this->img=m;
}

cv::Mat ColorAdjustment::getImage(){
    return this->img;
}

cv::Mat ColorAdjustment::filter(Eigen::Vector2d vec){
    
    img-=cv::Scalar(0,vec[0],vec[1]);

    return img;

}