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
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[1024];
	struct sockaddr_in serv_addr, cli_addr;
	int n = 0;
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			 sizeof(serv_addr)) < 0) 
			 error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 
				(struct sockaddr *) &cli_addr, 
				&clilen);
	if (newsockfd < 0) 
		 error("ERROR on accept");
	bzero(buffer,1024);

	Mat  img = Mat::zeros(480, 640, CV_8UC3);
	//Mat  img = Mat::zeros(960, 1280, CV_8UC3);
	int  imgSize = img.total()*img.elemSize();

	Mat  img2 = Mat::zeros(480, 640, CV_8UC3);
	//Mat  img = Mat::zeros(960, 1280, CV_8UC3);
	int  imgSize2 = img2.total()*img2.elemSize();
	uchar sockData[imgSize];

	namedWindow( "Server" );// Create a window for display.
	Mat test = imread("Recv.bmp");;
	imshow( "Server", test );
	int ptr = 0;
	cout << "Ready" << endl;
	char buf [8];
	//int ln = 0;
	//Receive data here
	do {
		for (int i = 0; i < imgSize; i += n) {
			if ((n = recv(newsockfd, sockData +i, imgSize  - i, 0)) == -1) {
				error("recv failed");
			}
		}

		// Assign pixel value to img

		ptr = 0;
		for (int i = 0;  i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {									
				img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
				ptr=ptr+3;
			}
		}
		//namedWindow( "Server", WINDOW_OPENGL );// Create a window for display.
		//cout << "sent" << endl;
		cvtColor(img,img2,CV_YCrCb2RGB);
		imshow( "Server", img2 );
		waitKey(5);
		//cout << "sent2" << endl;
		//sprintf (buf, "%d.bmp", ln);
		//imwrite(buf,img);
		//cout << "Recv" << endl;
		//ln++;
	//} while (cvWaitKey(10) < 0);
	} while (1);
	//imwrite("Recv.bmp",img);
	close(newsockfd);
	close(sockfd);
	waitKey(0);
	return 0; 
}



/*
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
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[1024];
	struct sockaddr_in serv_addr, cli_addr;
	int n = 0;
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			 sizeof(serv_addr)) < 0) 
			 error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 
				(struct sockaddr *) &cli_addr, 
				&clilen);
	if (newsockfd < 0) 
		 error("ERROR on accept");
	bzero(buffer,1024);

	Mat  img = Mat::zeros(960, 1280, CV_8UC3);
	int  imgSize = img.total()*img.elemSize();
	uchar sockData[imgSize];

	//Receive data here

	for (int i = 0; i < imgSize; i += n) {
		if ((n = recv(newsockfd, sockData +i, imgSize  - i, 0)) == -1) {
			error("recv failed");
		}
	}

	// Assign pixel value to img

	int ptr=0;
	for (int i = 0;  i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {									
			img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
			ptr=ptr+3;
		}
	}
	imwrite("Recv1.bmp",img);
	//close(newsockfd);
	//close(sockfd);

	namedWindow( "Server1", WINDOW_OPENGL );// Create a window for display.
	imshow( "Server1", img );  
	//waitKey(0);

	//Receive data here

	for (int i = 0; i < imgSize; i += n) {
		if ((n = recv(newsockfd, sockData +i, imgSize  - i, 0)) == -1) {
			error("recv failed");
		}
	}

	// Assign pixel value to img

	ptr=0;
	for (int i = 0;  i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {									
			img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
			ptr=ptr+3;
		}
	}
	imwrite("Recv2.bmp",img);
	//close(newsockfd);
	//close(sockfd);

	namedWindow( "Server2", WINDOW_OPENGL );// Create a window for display.
	imshow( "Server2", img );  
	//waitKey(0);

	//Receive data here

	for (int i = 0; i < imgSize; i += n) {
		if ((n = recv(newsockfd, sockData +i, imgSize  - i, 0)) == -1) {
			error("recv failed");
		}
	}

	// Assign pixel value to img

	ptr=0;
	for (int i = 0;  i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {									
			img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
			ptr=ptr+3;
		}
	}
	imwrite("Recv3.bmp",img);
	//close(newsockfd);
	//close(sockfd);

	namedWindow( "Server3", WINDOW_OPENGL );// Create a window for display.
	imshow( "Server3", img );  
	waitKey(0);
	return 0; 
}
*/
