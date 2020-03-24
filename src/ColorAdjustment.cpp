#include "ColorAdjustment.hpp"

ColorAdjustment::ColorAdjustment(cv::Mat m)
{
    ColorAdjustment::setImage(m);
}

void ColorAdjustment::setImage(cv::Mat m)
{
    this->img=m;
}

cv::Mat ColorAdjustment::getImage()
{
    return this->img;
}

cv::Mat ColorAdjustment::filter(cv::Mat image,Eigen::Vector2d vec)
{

    cv::MatIterator_<cv::Vec3d> it,end;

    for(it = image.begin<cv::Vec3d>(); it != image.end<cv::Vec3d>(); ++it)
    {   
        //std::cout<<(*it)[1]<<" "<<(*it)[2]<<std::endl;
    
        (*it)[1] -= vec[0];
        (*it)[2] -= vec[1];
        
    }

    return image;

}