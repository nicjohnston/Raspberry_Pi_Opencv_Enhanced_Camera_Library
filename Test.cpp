#include "RaspiCamCV.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
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
	/*IplImage* image;*/
	Mat frame;
	int imgSize = 0;
	//int ln = 0;
	//cout << "test" << endl;
	long double waitTime = 1;
	//cout << waitTime << endl;
	int mode = 2;
	//cout << mode << endl;
	while (1) {
		/*image = raspiCamCvQueryFrame(capture);
		//frame = Mat(image, true);
		Mat frame(image);
		//imwrite("Sent.bmp",frame);
		frame = (frame.reshape(0,1)); // to make it continuous

		imgSize = frame.total()*frame.elemSize();

		cout << "sent" << endl;
		// Send data here
		n = send(sockfd, frame.data, imgSize, 0);*/


		frame = raspiCamCvQueryFrame_New(capture, mode);  // this grabs a frame in YUV format
		//printEncoder(capture);  // this should print the H264 encoded stream to the terminal
		
		usleep(waitTime);
	}
	raspiCamCvReleaseCapture(&capture);
	waitKey(0);
	return 0;
}
