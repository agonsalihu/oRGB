#ifndef ___WRAPPER_H____
#define ___WRAPPER_H____

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>

class Wrapper{

    private:

        Eigen::Matrix3d matrix_;
        Eigen::Matrix3d translate_matrix_;
        Eigen::Matrix3d rotate_matrix_;
        Eigen::Matrix3d multiply_matrix_;
        Eigen::Matrix3d scale_matrix_;
        Eigen::Matrix3d shearX_matrix_;
        Eigen::Matrix3d shearY_matrix_;
        Eigen::Matrix3d reflectO_matrix_;
        Eigen::Matrix3d reflectX_matrix_;
        Eigen::Matrix3d reflectY_matrix_;
    
    public:
        Wrapper(void)=default;

        Wrapper(Eigen::Matrix3d mat);     

        bool setBaseMatrix(Eigen::Matrix3d mat);

        Eigen::Matrix3d translate(Eigen::Vector2d vec);

        Eigen::Matrix3d rotate(double angle);

        Eigen::Vector3d multiply(Eigen::Matrix3d m,Eigen::Vector3d v);

        Eigen::Matrix3d getMatrix3d();

        bool setTranslateMatrix(Eigen::Vector2d v);

        Eigen::Matrix3d getTranslateMatrix();

        bool setRotateMatrix(double d);

        Eigen::Matrix3d getRotateMatrix();

        bool setMultiplyMatrix(Eigen::Matrix3d m);

        Eigen::Matrix3d getMultiplyMatrix();

        ~Wrapper() = default;

};

#endif