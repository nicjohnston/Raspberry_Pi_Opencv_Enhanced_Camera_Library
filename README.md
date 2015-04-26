Raspberry Pi Opencv enhanced Camera Library
===========================================
This is a modification of Emil Valkov's raspicam_cv library available [here](https://github.com/robidouille/robidouille/tree/master/raspicam_cv).
The modification includes the encoder from the original raspivid code in order to provide both an encoded stream and an un-encoded stream in the form of an OpenCV IplImage.

This is a work in progress, and is currently not functioning properly.

The raspicam_cv folder replaces the folder (of the same name) that is created in the install process explained [here](https://github.com/robidouille/robidouille/blob/master/raspicam_cv/README).

Test.cpp can be compiled using the following command:

    g++-4.7 -W -O2 -Wall -std=c++11 -c -Wno-multichar -g -I/home/pi/git/robidouille/raspicam_cv -I/usr/include/opencv -I/home/pi/git/raspberrypi/userland/host_applic/linulibs/bcm_host -I/home/pi/git/raspberrypi/userland/host_applications/linux/apps/raspicam -I/home/pi/git/raspberrypi/userland -I/home/pi/git/raspberrypi/userland/interface/vcos/pthreads -I/home/pi/git/raspberrypi/userland/interface/vmcs_host/linux -I/home/pi/git/raspberrypi/userland/interface/mmal  -MD Test.cpp -o objs/Test.o && g++-4.7 -O2 -Wall objs/Test.o /home/pi/git/robidouille/raspicam_cv/libraspicamcv.a -lopencv_highgui -lopencv_core -lopencv_legacy -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_imgproc -L/home/pi/git/raspberrypi/userland/build/lib -L/home/pi/git/robidouille/raspicam_cv -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host -lX11 -lXext -lrt -lstdc++ -L. -lraspicamcv -lm -pthread -o Test -W

run.sh will remake raspicam_cv and recompile the test program.  If you want the test program to automaticly run when run.sh is executed, just uncomment line 7.

Recv.cpp and Send.cpp can be ignored because they only apply to streaming the recieved OpenCV frames over a network using TCP.

A functioning revision of this library can be found at https://github.com/6by9/Raspberry_Pi_Opencv_Enhanced_Camera_Library.

Update 4-26-2015:
When I tested this library last December it failed with multiple errors, however I should be able to resume work on this library in mid May.
