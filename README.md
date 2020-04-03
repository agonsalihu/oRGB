

<h3 align="center">oRGB</h3>


---

<p align="center"> Changing RGB color space to new oRGB 
    <br> 
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Built Using](#built_using)
- [Authors](#authors)


## 🧐 About <a name = "about"></a>

A new color model, oRGB, that is based on opponentcolor  theory.   Like  HSV,  it  is  designed  specifically  for  computergraphics.  However, it is also designed to work well for computa-tional applications such as color transfer, where HSV falters.

## 🏁 Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See [deployment](#deployment) for notes on how to deploy the project on a live system.



### Prerequisites

What things you need to install the software and how to install them.

- [CMake](https://cmake.org/install/) - Build process Framework
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) - Math Framework
- [OpenCV](https://www.learnopencv.com/install-opencv-4-on-ubuntu-18-04/) - Image Processing Framework
- [GoogleTest](https://github.com/google/googletest) - Test Framework
- [Doxygen](http://www.doxygen.nl/)- Standard tool for generating documentation from annotated C++ sources

### Installing

A step by step series of examples that tell you how to get a development env running.

First clone from GitHub

```
git clone https://github.com/agonsalihu/oRGB.git
```

And then open oRGB dictionary and create new dictionary

```
cd oRGB/
~/oRGB$ mkdir build
```
Create documentation on that dictionary

```
~/oRGB$ doxygen doxyfile
```
And than, go to build and make
```
~/oRGB$ cd build/
~/oRGB/build$ cmake ..
~/oRGB/build$ make
```

End with an example of getting some data out of the system or using it for a little demo.

## 🔧 Running the tests <a name = "tests"></a>
To make and run tests, go to build
```
~/oRGB$ cd build/
~/oRGB/build$ ctest make
```
or, for more detailed tests
```
~/oRGB$ cd build/ctest --verbose
```

### Execute

To execute on terminal in build dictionary write this command

```
~/oRGB/build$ ../build/oRGB_exec
```


## 🎈 Usage <a name="usage"></a>

This projects is used for color adjustement of an image from cool to warm, using oRGB color space 


## ⛏️ Built Using <a name = "built_using"></a>

- [CMake](https://cmake.org/) - Build process Framework
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) - Math Framework
- [OpenCV](https://opencv.org/) - Image Processing Framework
- [GoogleTest](https://github.com/google/googletest) - Test Framework
- [Doxygen](http://www.doxygen.nl/)- Standard tool for generating documentation from annotated C++ sources


## ✍️ Authors <a name = "authors"></a>

- [@agonsalihu](https://github.com/agonsalihu) - Coding
- [@jimmyhalimi](https://github.com/jimmyhalimi) - Supervisor


