#include "wrapper.hpp"

Wrapper::Wrapper(Eigen::Matrix3d mat){
    this-setBaseMatrix(mat);
}

bool Wrapper::setBaseMatrix(Eigen::Matrix3d mat){
    this->matrix_=mat;
    return true;
}

bool Wrapper::setTranslateMatrix(Eigen::Vector2d v){
    this->translate_matrix_=this->matrix_;
    translate_matrix_(0,2) += v(0);
    translate_matrix_(1,2) += v(1);
    return true;
}

bool Wrapper::setRotateMatrix(double d)
{
  this->rotate_matrix_= this->matrix_;

  double angle=(d*M_PI)/180;

  rotate_matrix_(0,0)=cos(angle);
  rotate_matrix_(0,1)=sin(angle);
  rotate_matrix_(1,0)=-sin(angle);
  rotate_matrix_(1,1)=cos(angle);

  return true;
}

Eigen::Matrix3d Wrapper::getMatrix3d()
{
  return this->matrix_;
}

Eigen::Matrix3d Wrapper::getTranslateMatrix()
{
  return this->translate_matrix_;
}

Eigen::Matrix3d Wrapper::getRotateMatrix()
{
  return this->rotate_matrix_;
}

Eigen::Matrix3d Wrapper::translate(Eigen::Vector2d vec)
{
  Eigen::Matrix3d _local_matrix = getMatrix3d();

  _local_matrix(0,2) += vec(0);
  _local_matrix(1,2) += vec(1);

  return _local_matrix;
}

Eigen::Matrix3d Wrapper::rotate(double angle)
{
  Eigen::Matrix3d test = getMatrix3d();

  test(0,0) =  cos(angle * M_PI / 180);
  test(0,1) = sin(angle * M_PI / 180);
  test(1,0) = -sin(angle * M_PI / 180);
  test(1,1) =  cos(angle * M_PI / 180);

  return test;
}

Eigen::Vector3d Wrapper::multiply(Eigen::Matrix3d m,Eigen::Vector3d v){
    return m*v;
}


