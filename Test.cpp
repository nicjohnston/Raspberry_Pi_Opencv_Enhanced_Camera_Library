#include "RaspiCamCV.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

void delay(long double time) {
	usleep(1000000*time);
}

int main(int argc, char *argv[])
{
	RaspiCamCvCapture * capture = raspiCamCvCreateCameraCapture(0);
	Mat frame;
	long double waitTime = 1;
	int mode = 2;
	while (1) {
		frame = raspiCamCvQueryFrame_New(capture, mode);  // this grabs a frame in YUV format
		//printEncoder(capture);  // this should print the H264 encoded stream to the terminal
		usleep(waitTime);
	}
	raspiCamCvReleaseCapture(&capture);
	waitKey(0);
	return 0;
}
