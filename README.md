# DCP_

When we take a picture at night from any sensor, we always get an image which is not clear, so we can not identify the information inside the image 

Thats why we use an enhancement algorithm to solve this problem of low contraste and high noise in image or video, in this tutorial : DCP algorithm is used to enhance the quality of the night input frame, the selection of this algorithm is due to its simplicity, which make the algorithm faster compare to another algorithm.


1. In this tutorial we build an applicaiton program for the enhancement of night time using Dark Channel Prior and OpenCV running in software means CPU the elapse output time of the algorithm push us to use  a hardware accelerator to accelerate the speed of processing of the frame.

2. And DCP algorithm implemented on FPGA using alveo board u200 as platform

The main code is available with this tutorial (test.cpp) for the software, so if you want to run the application program make sure that you have installed the opencv in your environment otherwise you will get an error due to the opencv library .

If you have not install the opencv, go in the link below and follow the step to install OpenCV on ubuntu

http://www.codebind.com/linux-tutorials/install-opencv-ubuntu-18-04-lts-c-cpp-linux/ 


After installation of the opencv library you can run the program using the following comand  :



1. >$  g++ test.cpp transmission.cpp recover.cpp guidedfilter.cpp darkchannel.cpp airlight.cpp dcp.cpp  -o ./ehaze `pkg-config --libs --cflags opencv`


2. >$ ./dehaze


For the hardware make sure that you install the vitis software and interconnect your host with alveo board, so you can runn the application program on hardware using the DCP_source code .

Thank you so much ......

************nambhine1@gmail.com *********
