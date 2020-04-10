# DCP_

When we take a picture at night from any sensor, we always get an image which is not clear, so we can not identify the information inside the image 

Thats why we use an enhancement algorithm to solve the problem of low contraste and high noise in image or video, in this tutorial : DCP algorithm based dehaze of image is used to enhance the quality of the night input frame, the selection of this algorithm is due to its simplicity, which make the algorithm faster compare to another algorithm.


In this tutorial we build an applicaiton program for the enhancement of night time using Dark Channel Prior and OpenCV running in software means CPU, the elapse output time of the algorithm push us to use  a hardware accelerator to accelerate the speed of processing of the frame.

The main code is available with this tutorial (test.cpp), so if you want to run the application program make sure that you have installed the opencv in your environment otherwise you will get an error due to the opencv library .

If you have not install the opencv, go in the link below and follow the step to install OpenCV on ubuntu

http://www.codebind.com/linux-tutorials/install-opencv-ubuntu-18-04-lts-c-cpp-linux/ 


After installation of the opencv library you can run the program using the following comand :



1. >$  g++ test.cpp guidedfilter.cpp darkchannel.cpp airlight.cpp dcp.cpp recover.cpp transmission.cpp -o ../dehaze ` `pkg-config --libs --cflags opencv``


2. >$ ./dehaze


Thank you so much ......

************nambhine1@gmail.com *********
