#include "dcp.h"

int main()
{
	IplImage *input = cvLoadImage("/home/namby/Desktop/input.png");
	IplImage *result = cvCreateImage(cvGetSize(input), IPL_DEPTH_8U, 3);
	dehaze(result, input);

	cvSaveImage("result1.bmp", result);
	cvReleaseImage(&result);
	cvReleaseImage(&input);
	return 0;
}
