#include "Method.h"
using namespace cv;
void Draw()
{
	namedWindow("Water", WINDOW_AUTOSIZE);
	moveWindow("Water", 960, 540);
	waitKey();
	Mat Image = Mat::zeros(Size(1920, 1080), CV_8UC1);
	imshow("Water", Image);
	resizeWindow("Water", Size(800, 600));
	waitKey();
	moveWindow("Water", 0, 0);
	waitKey();
}
MouseCallback;