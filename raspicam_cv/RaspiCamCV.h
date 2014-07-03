#ifndef __RaspiCamCV__
#define __RaspiCamCV__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _RASPIVID_STATE RASPIVID_STATE;

typedef struct {
	RASPIVID_STATE * pState;
} RaspiCamCvCapture;

typedef struct _IplImage IplImage;

RaspiCamCvCapture * raspiCamCvCreateCameraCapture(int index);
void raspiCamCvReleaseCapture(RaspiCamCvCapture ** capture);
void raspiCamCvSetCaptureProperty(RaspiCamCvCapture * capture, int property_id, double value);
void printEncoder(RaspiCamCvCapture * capture);
IplImage * raspiCamCvQueryFrame(RaspiCamCvCapture * capture);
IplImage * raspiCamCvQueryFrame_New(RaspiCamCvCapture * capture, int mode);
void raspiCamCvQueryFrame_New_Three(RaspiCamCvCapture * capture, IplImage * Y, IplImage * U, IplImage * V);
IplImage * raspiCamCvQueryFrame_New_Final(RaspiCamCvCapture * capture);
/*void raspiCamCvQueryFrame_New_Start(RaspiCamCvCapture * capture);//, Mat& Y, Mat& U, Mat& V);
IplImage * raspiCamCvQueryFrame_New_Y(RaspiCamCvCapture * capture);
IplImage * raspiCamCvQueryFrame_New_U(RaspiCamCvCapture * capture);
IplImage * raspiCamCvQueryFrame_New_V(RaspiCamCvCapture * capture);*/

#ifdef __cplusplus
}
#endif

#endif
