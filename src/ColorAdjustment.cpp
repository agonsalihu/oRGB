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