# DCP_
This tutorial is used to build an applicaiton program for the enhancement of night time using Dark Channel Prior and OpenCV

The main code is available in this code (test.cpp), so if you want to run the application program make sure that you have installed the opencv in your environment otherwise you will get an error due to the opencv library .

If you have not install the opencv, go in the link below and follow the step to install OpenCV on ubuntu

http://www.codebind.com/linux-tutorials/install-opencv-ubuntu-18-04-lts-c-cpp-linux/ 


After installation of the opencv library you can run the program using the following comand :



1. >$  g++ test.cpp guidedfilter.cpp darkchannel.cpp airlight.cpp dcp.cpp recover.cpp transmission.cpp -o ./dehaze `pkg-config --libs --cflags opencv`


2. >$ ./dehaze


Thank you so much ......

************nambhine1@gmail.com *********
