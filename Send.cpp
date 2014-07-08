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
	int sockfd, portno;
	int n = 0;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];
	if (argc < 3) {
	   fprintf(stderr,"usage %s hostname port\n", argv[0]);
	   exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		error("ERROR connecting");
	}

	RaspiCamCvCapture * capture = raspiCamCvCreateCameraCapture(0);
	/*IplImage* image;*/
	Mat frame;
	int imgSize = 0;
	//int ln = 0;
	cout << "test" << endl;
	long double waitTime = atof(argv[3]);
	cout << waitTime << endl;
	int mode = atof(argv[4]);
	cout << mode << endl;
	do {
		/*image = raspiCamCvQueryFrame(capture);
		//frame = Mat(image, true);
		Mat frame(image);
		//imwrite("Sent.bmp",frame);
		frame = (frame.reshape(0,1)); // to make it continuous

		imgSize = frame.total()*frame.elemSize();

		cout << "sent" << endl;
		// Send data here
		n = send(sockfd, frame.data, imgSize, 0);*/
		
		
		//frame = raspiCamCvQueryFrame_New(capture, mode);
		//frame = (frame.reshape(0,1)); // to make it continuous
		//imgSize = frame.total()*frame.elemSize();
		//n = send(sockfd, frame.data, imgSize, 0);
		printEncoder(capture);
		
		
		//delay(waitTime);
		usleep(waitTime);
		//ln++;
	} while (cvWaitKey(10) < 0);
	close(sockfd);
	raspiCamCvReleaseCapture(&capture);

	//namedWindow( "Client", CV_WINDOW_AUTOSIZE );// Create a window for display.
	//imshow( "Client", img);  
	waitKey(0);
	return 0;
}
