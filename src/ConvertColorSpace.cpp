#include "ConvertColorSpace.hpp"

ConvertColorSpace::ConvertColorSpace(cv::Mat m)
{
    this->img=m;
}

cv::Mat ConvertColorSpace::linearTransform(cv::Mat image)
{

    cv::MatIterator_<cv::Vec3d> it,end;

    double gamma=2.2f;
    double gammaCorrection=1.0/gamma;

    for(it = image.begin<cv::Vec3d>(); it != image.end<cv::Vec3d>(); ++it)
    {

        (*it)[0] = pow((static_cast <double>((*it)[0]) / 255.0 ),gammaCorrection); 
        (*it)[1] = pow((static_cast <double>((*it)[1]) / 255.0 ),gammaCorrection); 
        (*it)[2] = pow((static_cast <double>((*it)[2]) / 255.0 ),gammaCorrection);         
    
        Eigen::Vector3d vec{(*it)[0],(*it)[1],(*it)[2]};
     
        vec = transform_matrix *vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];
       
    }
    
    return image;
    
}

cv::Mat ConvertColorSpace::rotateToORGB(cv::Mat image)
{

    cv::MatIterator_<cv::Vec3d> it,end;

    Eigen::Matrix3d rotate_matrix{{1,0,0},
                                  {0,1,0},
                                  {0,0,1}};
    
    for(it=image.begin<cv::Vec3d>();it!=image.end<cv::Vec3d>();it++)
    {
        
        double theta=atan2((*it)[2],(*it)[1]);

        double d=0.0f;

        if(theta<M_PI/3.0)
        {
            
            d=(double)3.0/2.0*theta;
            
        }else if(theta<=M_PI && theta>=M_PI/3.0 )
        {

            d=(M_PI/2)+3.0/4.0*(theta-M_PI/3.0);

        }
        
        d=d-theta;

        rotate_matrix(1,1) = cos(d);
        rotate_matrix(1,2) = -sin(d);
        rotate_matrix(2,1) = sin(d);
        rotate_matrix(2,2) = cos(d);
        
        Eigen::Vector3d vec{(*it)[0],(*it)[1],(*it)[2]};

        vec=rotate_matrix*vec;
                
        (*it)[0]=vec[0];
        (*it)[1]=vec[1];
        (*it)[2]=vec[2];
        
    }
    
    setImage64b(image);
    
    return image;
}

cv::Mat ConvertColorSpace::showImage(cv::Mat image)
{
    
    cv::MatIterator_<cv::Vec3d> it,end;

    for(it = image.begin<cv::Vec3d>(); it != image.end<cv::Vec3d>(); ++it)
    {
       
        (*it)[0] = (*it)[0] * 255;
        (*it)[1] = (*it)[1] * 255;
        (*it)[2] = (*it)[2] * 255;
        
    }

    image.convertTo(image,CV_8UC3);

    cv::cvtColor(image, image, cv::COLOR_RGB2BGR); 
    
    return image;
}

cv::Mat ConvertColorSpace::convertToORGB(cv::Mat image)
{
    
    cv::cvtColor(image,image, cv::COLOR_BGR2RGB);

    image.convertTo(image,CV_64FC3);
    
    image=linearTransform(image);
    
    image=rotateToORGB(image);

    image=showImage(image);

    return image;

}

cv::Mat ConvertColorSpace::rotateToRGB(cv::Mat image)
{

    cv::MatIterator_<cv::Vec3d> it,end;

    Eigen::Matrix3d rotate_matrix{{1,0,0},
                                  {0,1,0},
                                  {0,0,1}};

    double gamma=2.2;
    double gammaCorrection=1.0/gamma;

    for(it=image.begin<cv::Vec3d>();it!=image.end<cv::Vec3d>();it++)
    {
        
        double theta=atan2((*it)[2],(*it)[1]);

        double d=0.0f;

        if(theta<M_PI/2)
        {
            
            d=(double)2.0/3*theta;
            
        }else if(theta<=M_PI && theta>=M_PI/2 )
        {

            d=M_PI/3+4.0/3*(theta-M_PI/2);

        }
        
        d=d-theta;

        rotate_matrix(1,1) = cos(d);
        rotate_matrix(1,2) = -sin(d);
        rotate_matrix(2,1) = sin(d);
        rotate_matrix(2,2) = cos(d);

        Eigen::Vector3d vec{(*it)[0],(*it)[1],(*it)[2]};

        vec=rotate_matrix*vec;
        
        (*it)[0]=vec[0];
        (*it)[1]=vec[1];
        (*it)[2]=vec[2];

    }

    return image;

}

cv::Mat ConvertColorSpace::delinearTransform(cv::Mat image)
{

    cv::MatIterator_<cv::Vec3d> it,end;

    double gamma=2.2f;
    double gammaCorrection=1/gamma;

    for(it = image.begin<cv::Vec3d>(); it != image.end<cv::Vec3d>(); ++it)
    {
        
        Eigen::Vector3d vec{(*it)[0],(*it)[1],(*it)[2]};
     
        vec = inverse_transform_matrix *vec;

        (*it)[0] = vec[0]*255;
        (*it)[1] = vec[1]*255;
        (*it)[2] = vec[2]*255;

        (*it)[0] = pow((static_cast <double>((*it)[0]) / 255.0 ),gamma)*255; 
        (*it)[1] = pow((static_cast <double>((*it)[1]) / 255.0 ),gamma)*255; 
        (*it)[2] = pow((static_cast <double>((*it)[2]) / 255.0 ),gamma)*255;
        
    }
 
    return image;

}


cv::Mat ConvertColorSpace::convertToRGB()
{
    cv::Mat image=getImage64b();
    
    image=rotateToRGB(image);

    image=delinearTransform(image);
    
    image.convertTo(image,CV_8UC3);

    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
    
    return image;

}

cv::Mat ConvertColorSpace::filter(Eigen::Vector2d vec)
{
    cv::Mat image=getImage64b();
    cv::MatIterator_<cv::Vec3d> it,end;

    for(it = image.begin<cv::Vec3d>(); it != image.end<cv::Vec3d>(); ++it)
    {   
        //(*it)[0]=0;   //L
        //(*it)[1]=0;   //Crg
        //(*it)[2]=0;   //Cby


        (*it)[2] -= vec[0];
        (*it)[1] -= vec[1];
        
    }
    
    return image;

}

void ConvertColorSpace::setImage64b(cv::Mat i)
{
    i.convertTo(i,CV_64FC3);
    this->oRGB=i.clone();
}

cv::Mat ConvertColorSpace::getImage64b()
{
    return this->oRGB;
}

