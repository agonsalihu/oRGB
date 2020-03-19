#include "ConvertColorSpace.hpp"

ConvertColorSpace::ConvertColorSpace(cv::Mat m){
    this->img=m;
}

void ConvertColorSpace::setImage(cv::Mat m){
    this->img=m;
}

void ConvertColorSpace::setNormalized(cv::Mat m){
    this->normalized=m;
}

void ConvertColorSpace::setDeNormalized(cv::Mat m){
    this->denormalizet=m;
}

cv::Mat ConvertColorSpace::getImage(){
    return img;
}

cv::Mat ConvertColorSpace::getNormalized(){
    return normalized;
}

cv::Mat ConvertColorSpace::getDeNormalized(){
    return denormalizet;
}

cv::Mat ConvertColorSpace::convertToORGB(){
    
    img.convertTo(img,CV_64FC3);
    
    cv::MatIterator_<cv::Vec3d> it,end;

    float gamma=2.2f;
    float gammaCorrection=1/gamma;

    for(it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
    {
        
        (*it)[0] = pow((static_cast <double>((*it)[0]) / 255.0 ),gammaCorrection) * 255.0; 
        (*it)[1] = pow((static_cast <double>((*it)[1]) / 255.0 ),gammaCorrection) * 255.0; 
        (*it)[2] = pow((static_cast <double>((*it)[2]) / 255.0 ),gammaCorrection) * 255.0; 

    }
    
    double b,g,r;

    for(it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
    {

        (*it)[0] = pow((static_cast <double>((*it)[0]) / 255.0 ),gammaCorrection); 
        (*it)[1] = pow((static_cast <double>((*it)[1]) / 255.0 ),gammaCorrection); 
        (*it)[2] = pow((static_cast <double>((*it)[2]) / 255.0 ),gammaCorrection);         

        b = (*it)[0];
        g = (*it)[1];
        r = (*it)[2];
        
        Eigen::Vector3d vec{b,g,r};
     
        vec = transform_matrix *vec;

        (*it)[0] = vec[0] * 255.0;
        (*it)[1] = vec[1] * 255.0;
        (*it)[2] = vec[2] * 255.0;
       
    }

    

    /*

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
    
    img.convertTo(img,CV_8UC3);

    */
    
    Eigen::Matrix3d rotate_matrix{{1,0,0},
                                  {0,1,0},
                                  {0,0,1}};

    for(it=img.begin<cv::Vec3d>();it!=img.end<cv::Vec3d>();it++){
        
        double theta=atan2((*it)[2],(*it)[1]);

        double d{0};

        if(theta<M_PI/3){

            d=(static_cast<double>(3)/2)*theta;

        }else if(theta<=M_PI && theta>=M_PI/3 ){

            d=M_PI/2+3/4*(theta-M_PI/3);

        }
        
        //d=d-theta;

        rotate_matrix(0,0) = cos(d);
        rotate_matrix(0,1) = sin(d);
        rotate_matrix(1,0) = -sin(d);
        rotate_matrix(1,1) = cos(d);

        Eigen::Vector3d vec{(*it)[0],(*it)[1],(*it)[2]};

        vec=rotate_matrix*vec;
        
        (*it)[0]=vec[0]*255;
        (*it)[1]=vec[1]*255;
        (*it)[2]=vec[2]*255;


    }

    img.convertTo(img,CV_8UC3);
    return img;
}

void ConvertColorSpace::convertToRGB(){

}