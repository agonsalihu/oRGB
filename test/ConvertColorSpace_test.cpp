#include "ConvertColorSpace_test.hpp"



/**
 * @brief Construct a new test f object for Image Set
 * 
 */
TEST_F(ConvertColorSpaceTest, SetImage)
{   
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    EXPECT_TRUE(ccs.setImage(img));
}

/**
 * @brief Construct a new test f object to Get Base Image
 * 
 */
TEST_F(ConvertColorSpaceTest, GetImage)
{
    cv::Mat img =cv::imread(getPath(),cv::IMREAD_COLOR);
    img.convertTo(img, CV_64FC3);
    ccs.setImage(img);
    cv::Mat test = ccs.getImage().clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1;
    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}

/**
 * @brief Construct a new test f object for Linear Transformation
 * 
 */
TEST_F(ConvertColorSpaceTest, LinearTransform)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    Eigen::Matrix3d transform_matrix{{0.2990, 0.5870, 0.1140},
                                     {0.5000, 0.5000, -1.0000},
                                     {0.8660, -0.8660, 0.0000}};

    double gamma = 2.2f;
    double gammaCorrection = 1.0 / gamma;

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
    {

        (*it)[0] = pow((static_cast<double>((*it)[0]) / 255.0), gammaCorrection);
        (*it)[1] = pow((static_cast<double>((*it)[1]) / 255.0), gammaCorrection);
        (*it)[2] = pow((static_cast<double>((*it)[2]) / 255.0), gammaCorrection);

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = transform_matrix * vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];
    }

    test = ccs.linearTransform(test);

    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}

/**
 * @brief Construct a new test f object for Rotate ColorSpace to oRGB
 * 
 */
TEST_F(ConvertColorSpaceTest, Rotate)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    Eigen::Matrix3d rotate_matrix{{1, 0, 0},
                                  {0, 1, 0},
                                  {0, 0, 1}};

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); it++)
    {

        double theta = atan2((*it)[2], (*it)[1]);

        double d = 0.0f;

        if (theta < M_PI / 3.0)
        {

            d = (double)3.0 / 2.0 * theta;
        }
        else if (theta <= M_PI && theta >= M_PI / 3.0)
        {

            d = (M_PI / 2) + 3.0 / 4.0 * (theta - M_PI / 3.0);
        }

        d = d - theta;

        rotate_matrix(1, 1) = cos(d* M_PI/180);
        rotate_matrix(1, 2) = -sin(d* M_PI/180);
        rotate_matrix(2, 1) = sin(d* M_PI/180);
        rotate_matrix(2, 2) = cos(d* M_PI/180);

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = rotate_matrix * vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];
    }

    test = ccs.rotateToORGB(test);

    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {        
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}

/**
 * @brief Construct a new test f object for converting to oRGB
 * 
 */
TEST_F(ConvertColorSpaceTest, ConvertToORGB)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    Eigen::Matrix3d transform_matrix{{0.2990, 0.5870, 0.1140},
                                     {0.5000, 0.5000, -1.0000},
                                     {0.8660, -0.8660, 0.0000}};

    double gamma = 2.2f;
    double gammaCorrection = 1.0 / gamma;

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
    {

        (*it)[0] = pow((static_cast<double>((*it)[0]) / 255.0), gammaCorrection);
        (*it)[1] = pow((static_cast<double>((*it)[1]) / 255.0), gammaCorrection);
        (*it)[2] = pow((static_cast<double>((*it)[2]) / 255.0), gammaCorrection);

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = transform_matrix * vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];
    }

    Eigen::Matrix3d rotate_matrix{{1, 0, 0},
                                  {0, 1, 0},
                                  {0, 0, 1}};

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); it++)
    {

        double theta = atan2((*it)[2], (*it)[1]);

        double d = 0.0f;

        if (theta < M_PI / 3.0)
        {

            d = (double)3.0 / 2.0 * theta;
        }
        else if (theta <= M_PI && theta >= M_PI / 3.0)
        {

            d = (M_PI / 2) + 3.0 / 4.0 * (theta - M_PI / 3.0);
        }

        d = d - theta;

        rotate_matrix(1, 1) = cos(d* M_PI/180);
        rotate_matrix(1, 2) = -sin(d* M_PI/180);
        rotate_matrix(2, 1) = sin(d* M_PI/180);
        rotate_matrix(2, 2) = cos(d* M_PI/180);

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = rotate_matrix * vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];
    }

    test = ccs.linearTransform(test);
    test = ccs.rotateToORGB(test);

    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}

/**
 * @brief Construct a new test f object for rotating image to RGB
 * 
 */
TEST_F(ConvertColorSpaceTest, RotateToRGB)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    Eigen::Matrix3d rotate_matrix{{1, 0, 0},
                                  {0, 1, 0},
                                  {0, 0, 1}};

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); it++)
    {

        double theta = atan2((*it)[2], (*it)[1]);

        double d = 0.0f;

        if (theta < M_PI / 2)
        {

            d = (double)2.0 / 3 * theta;
        }
        else if (theta <= M_PI && theta >= M_PI / 2)
        {

            d = M_PI / 3 + 4.0 / 3 * (theta - M_PI / 2);
        }

        d = d - theta;

        rotate_matrix(1, 1) = cos(d* M_PI/180);
        rotate_matrix(1, 2) = -sin(d* M_PI/180);
        rotate_matrix(2, 1) = sin(d* M_PI/180);
        rotate_matrix(2, 2) = cos(d* M_PI/180);

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = rotate_matrix * vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];
    }

    test = ccs.rotateToRGB(test);

    Eigen::Vector3d imgVec{0, 0, 0}, testVec{0, 0, 0};
    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}
/*
TEST_F(ConvertColorSpaceTest, DeLinearTransform)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    double gamma = 2.2f;
    double gammaCorrection = 1 / gamma;

    Eigen::Matrix3d inverse_transform_matrix{{1.0000, 0.1140, 0.7436},
                                             {1.0000, 0.1140, -0.4111},
                                             {1.0000, -0.8860, 0.1663}};

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
    {

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = inverse_transform_matrix * vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];

        (*it)[0] = pow((static_cast<double>((*it)[0])), gamma) * 255;
        (*it)[1] = pow((static_cast<double>((*it)[1])), gamma) * 255;
        (*it)[2] = pow((static_cast<double>((*it)[2])), gamma) * 255;
    }

    test=ccs.delinearTransform(test);

    Eigen::Vector3d imgVec{0, 0, 0}, testVec{0, 0, 0};
    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 1000.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 1000.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 1000.01);
    }
}


TEST_F(ConvertColorSpaceTest, Convert_To_RGB)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    Eigen::Matrix3d rotate_matrix{{1, 0, 0},
                                  {0, 1, 0},
                                  {0, 0, 1}};

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); it++)
    {

        double theta = atan2((*it)[2], (*it)[1]);

        double d = 0.0f;

        if (theta < M_PI / 2)
        {

            d = (double)2.0 / 3 * theta;
        }
        else if (theta <= M_PI && theta >= M_PI / 2)
        {

            d = M_PI / 3 + 4.0 / 3 * (theta - M_PI / 2);
        }

        d = d - theta;

        rotate_matrix(1, 1) = cos(d);
        rotate_matrix(1, 2) = -sin(d);
        rotate_matrix(2, 1) = sin(d);
        rotate_matrix(2, 2) = cos(d);

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = rotate_matrix * vec;

        (*it)[0] = vec[0];
        (*it)[1] = vec[1];
        (*it)[2] = vec[2];
    }

    double gamma = 2.2f;
    double gammaCorrection = 1 / gamma;

    Eigen::Matrix3d inverse_transform_matrix{{1.0000, 0.1140, 0.7436},
                                             {1.0000, 0.1140, -0.4111},
                                             {1.0000, -0.8860, 0.1663}};

    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
    {

        Eigen::Vector3d vec{(*it)[0], (*it)[1], (*it)[2]};

        vec = inverse_transform_matrix * vec;

        (*it)[0] = vec[0] * 255;
        (*it)[1] = vec[1] * 255;
        (*it)[2] = vec[2] * 255;

        (*it)[0] = pow((static_cast<double>((*it)[0]) / 255.0), gamma) * 255;
        (*it)[1] = pow((static_cast<double>((*it)[1]) / 255.0), gamma) * 255;
        (*it)[2] = pow((static_cast<double>((*it)[2]) / 255.0), gamma) * 255;
    }

    test = ccs.rotateToRGB(test);
    test = ccs.delinearTransform(test);

    Eigen::Vector3d imgVec{0, 0, 0}, testVec{0, 0, 0};
    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}
*/

/**
 * @brief Construct a new test f object for Filter oRGB 
 * 
 */
TEST_F(ConvertColorSpaceTest, Filter)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    Eigen::Vector2d vec{0, 0.3};
    
    for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
    {

        if ((*it)[2] - vec[0] < -1)
        {

            (*it)[2] = (-1.0);
        }
        else if ((*it)[2] - vec[0] > 1)
        {

            (*it)[2] = 1.0;
        }
        else
        {

            (*it)[2] = vec[0];
        }

        if ((*it)[1] - vec[1] < -1)
        {

            (*it)[1] = (-1.0);
        }
        else if ((*it)[1] - vec[1] < -1)
        {

            (*it)[1] = 1.0;
        }
        else
        {

            (*it)[1] -= vec[1];
        }
    }
    
    test = ccs.filter(test, vec);

    Eigen::Vector3d imgVec{0, 0, 0}, testVec{0, 0, 0};
    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}

/**
 * @brief Construct a new test f object for extracting color from oRGB image
 * 
 */
TEST_F(ConvertColorSpaceTest, Extract)
{
    cv::Mat img = cv::imread(getPath(), cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    img.convertTo(img, CV_64FC3);
    cv::Mat test = img.clone();
    test.convertTo(test, CV_64FC3);

    cv::MatIterator_<cv::Vec3d> it, it1, end;

    enum Color
    {
        L = 0,
        Crg = 1,
        Cyb = 2
    };

    switch (Crg)
    {
    case Crg:
        for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
        {
            //(*it)[0] = 0; //L
            (*it)[1] = 0; //Crg
            //(*it)[2]=0;   //Cby
        }
        break;

    case Cyb:
        for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
        {
            //(*it)[0] = 0; //L
            //(*it)[1] = 0; //Crg
            (*it)[2] = 0; //Cby
        }
        break;
    case L:
        for (it = img.begin<cv::Vec3d>(); it != img.end<cv::Vec3d>(); ++it)
        {
            //(*it)[0] = 0; //L
            (*it)[1] = 0; //Crg
            (*it)[2] = 0; //Cby
        }
        break;
    default:
        break;
    }

    test = ccs.extract(test, ConvertColorSpace::Crg);

    Eigen::Vector3d imgVec{0, 0, 0}, testVec{0, 0, 0};
    for (it = img.begin<cv::Vec3d>(),it1=test.begin<cv::Vec3d>();
         it != img.end<cv::Vec3d>() && it1!=test.end<cv::Vec3d>();
         ++it,++it1)
    {
        EXPECT_NEAR((*it)[0], (*it1)[0], 0.01);
        EXPECT_NEAR((*it)[1], (*it1)[1], 0.01);
        EXPECT_NEAR((*it)[2], (*it1)[2], 0.01);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}