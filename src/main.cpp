#include "ConvertColorSpace.hpp"
#include "ColorAdjustment.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char **argv)
{
  //Path for image
  std::string path("../img/pots.jpg");

  //Read image and save in img
  cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);

  //Read image from command line argument
  if (argc > 1)
  {
    path = argv[1]; // take image path as argument
  }

  //Check if image is loaded
  if (!img.data)
    std::cout << "Image not loaded.Check path: " << path << std::endl;

  //Show Original image
  cv::namedWindow("Original", cv::WINDOW_FULLSCREEN);
  cv::imshow("Original", img);

  //Creating objects for ConvertColorSpace and ColorAdjustemnt Class
  ConvertColorSpace ccs(img);
  ColorAdjustment ca(img);

  //Convert RGB image to oRGB
  img = ccs.convertToORGB(img);

  //Show oRGB imageLinear Blend
  cv::namedWindow("oRGB", cv::WINDOW_FULLSCREEN);
  cv::imshow("oRGB", img);

  //Extract method
  //img=ccs.extract(ccs.getImage64b(),ConvertColorSpace::Crg);

  //Filter oRGB image
  img = ccs.filter(ccs.getImage64b(), Eigen::Vector2d{0, 0});

  //Convert back to RGB
  img = ccs.convertToRGB();

  //Show filtered RGB image
  cv::namedWindow("RGB", cv::WINDOW_FULLSCREEN);
  cv::imshow("RGB", img);

  //To function trackbar Uncoment this comment block,
  //comment applied method filter in line 38
  /*
    cv::namedWindow("Trackbar", cv::WINDOW_FULLSCREEN);
    int crgValue = 0;
    cv::createTrackbar("Crg", "Trackbar", &crgValue, 100.0);
    cv::setTrackbarMin("Crg","Trackbar",-100.0);

    int cybValue = 0;
    cv::createTrackbar("Cyb", "Trackbar", &cybValue, 100.0);
    cv::setTrackbarMin("Cyb","Trackbar",-100.0);
    
    while(cv::waitKey(1)!=27){
      double rg = cv::getTrackbarPos("Crg","Trackbar") / 100.0; 
      double yb = cv::getTrackbarPos("Cyb","Trackbar") / 100.0;

      img=ccs.filter(Eigen::Vector2d{rg,yb});
      img=ccs.convertToRGB();

      cv::imshow("Trackbar", img);
    }
    */

  //Wait for key and terminate program
  std::cout << "Press any key to close..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}