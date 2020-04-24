# OpenCV Windows Setup 

## setup

1. Install OpenCV - https://github.com/opencv/opencv/releases/tag/4.3.0
2. Add OpenCV to Path = ..\opencv\build\x64\bin
3. Create project and add opencv
   * Create console app
   * Set platform to x64
   * Add Include Directory - opencv/build/include
   * Add Library - /library
   * Add linker additional dependency `.lib` file for `opencv_worldXYZ.lib` where XYZ is the library version

## credit

Setup found in this blog: https://medium.com/@subwaymatch/opencv-410-with-vs-2019-3d0bc0c81d96

Updated to CV 4.3.0.