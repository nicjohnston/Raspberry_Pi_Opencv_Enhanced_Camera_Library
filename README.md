Raspberry Pi Opencv enhanced Camera Library
===========================================
This is a modification of Emil Valkov's raspicam_cv library available [here](https://github.com/robidouille/robidouille/tree/master/raspicam_cv).
The modification includes the encoder from the original raspivid code in order to provide both an encoded stream and an un-encoded stream in the form of an OpenCV IplImage.

This is a work in progress, and is currently not functioning properly.

Recv.cpp and Send.cpp can be ignored as they only apply to streaming the recieved OpenCV frames over a network using TCP.
