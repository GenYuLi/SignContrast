#include "Method.h"
using namespace std;
using namespace cv;

int main(int argc,char *argv[])
{
	//string t = { "hi" };
	//while (t != "q")
	//{
	//	cin >> t;
	//	if (t == "q")break;
		vector<vector<Point>> runecontours[6], contours;
		vector<Vec4i> runehierarchy[6], hierarchy;
		Mat imageSource[6], image[6];
		Mat defu;
		imageSource[0] = imread("rune/1.png", CV_8UC1);
		GaussianBlur(imageSource[0], image[0], Size(3, 3), 0);
		Canny(image[0], image[0], 100, 250);
		findContours(image[0], runecontours[0], runehierarchy[0], RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		imageSource[1] = imread("rune/2.png", CV_8UC1);
		GaussianBlur(imageSource[1], image[1], Size(3, 3), 0);
		Canny(image[1], image[1], 100, 250);
		findContours(image[1], runecontours[1], runehierarchy[1], RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		imageSource[2] = imread("rune/3.png", CV_8UC1);
		GaussianBlur(imageSource[2], image[2], Size(3, 3), 0);
		Canny(image[2], image[2], 100, 250);
		findContours(image[2], runecontours[2], runehierarchy[2], RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		imageSource[3] = imread("rune/4.png", CV_8UC1);
		GaussianBlur(imageSource[3], image[3], Size(3, 3), 0);
		Canny(image[3], image[3], 100, 250);
		findContours(image[3], runecontours[3], runehierarchy[3], RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		imageSource[4] = imread("rune/5.png", CV_8UC1);
		GaussianBlur(imageSource[4], image[4], Size(3, 3), 0);
		Canny(image[4], image[4], 100, 250);
		findContours(image[4], runecontours[4], runehierarchy[4], RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		Mat runeContours[5] = { Mat::zeros(image[0].size(), CV_8UC1) ,Mat::zeros(image[1].size(), CV_8UC1) ,Mat::zeros(image[2].size(), CV_8UC1) ,Mat::zeros(image[3].size(), CV_8UC1) ,Mat::zeros(image[4].size(), CV_8UC1) };
		Mat testSource = imread(argv[1], CV_8UC1);
		Mat test;
		GaussianBlur(testSource, test, Size(3, 3), 0);
		Canny(test, test, 100, 250);
		findContours(test, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		//cout << contours.size() << endl;
		Mat imageContours = Mat::zeros(test.size(), CV_8UC1);

		for (int i = 0; i < 5; i++)
		{
			//酶籹近锅
			for (int j = 0; j < runecontours[i].size(); j++)
				drawContours(runeContours[i], runecontours[i], j, Scalar(255), -1, 8, runehierarchy[i]);
		}
		for (int j = 0; j < contours.size(); j++)
			drawContours(imageContours, contours, j, Scalar(255), -1, 8, hierarchy);
		//imshow("test Image Contuours0", imageContours); //近锅
		double Con[5]{ 0,0,0,0,0 };
		int Rune[5]{ -1,-1,-1,-1,-1 }, RuneSize(0);
		//Con[0] = c_method_1(fireSource, imageSource);
		//Con[1] = c_method_1(waterSource, imageSource);
		//Con[2] = c_method_1(goldSource, imageSource);
		//Con[3] = c_method_1(woodSource, imageSource);
		//Con[4] = c_method_1(terraSource, imageSource);
		for (int i = 0; i < 5; i++)
		{
			Con[i] += matchShapes(runeContours[i], imageContours, CONTOURS_MATCH_I1, 0.0);
			Con[i] += matchShapes(runeContours[i], imageContours, CONTOURS_MATCH_I2, 0.0);
			Con[i] += matchShapes(runeContours[i], imageContours, CONTOURS_MATCH_I3, 0.0);
			//Con[i] += matchShapes(image[i], test, CONTOURS_MATCH_I1, 0.0);
			//Con[i] += matchShapes(image[i], test, CONTOURS_MATCH_I2, 0.0);
			//Con[i] += matchShapes(image[i], test, CONTOURS_MATCH_I3, 0.0);
			//Con[i] /= 3;
			//cout << Con[i] << endl;
			if (Con[i] <= 1)
			{
				Rune[RuneSize++] = i;
			}
		}
		int min = Rune[0];
		for (int i = 1; i < RuneSize; i++)
		{
			if (Con[Rune[i]] < Con[min])
			{
				min = Rune[i];
			}
		}
		//for (int i = 0; i < 5; i++)
		//	cout << Con[i]<<endl;
		//int min = 0;
		//for (int i = 0; i < 5; i++)
		//	if (Con[i] < Con[min])min = i;
		defu = imread("Rune/back.jpg", 1);
		switch (min)
		{
		case 0:
			cout << "1";
			//imshow("Rune", runeContours[0]);
			break;
		case 1:
			cout << "2";
			//imshow("Rune", runeContours[1]);
			break;
		case 2:
			cout << "3";
			//imshow("Rune", runeContours[2]);
			break;
		case 3:
			cout << "4";
			//imshow("Rune", runeContours[3]);
			break;
		case 4:
			cout << "5";
			//imshow("Rune", runeContours[4]);
			break;
		default:
			cout << "-1";
			//imshow("礚才ゅ", defu);
			break;
		}
		//for (int i = 0; i < 5; i++)
		//{
		//	char k = '1' + i;
		//	string tmp(1,k);
		//	imshow("Contours Image" +tmp , runeContours[i]); //近锅
		//}
		//imshow("test Image", test);
		//cout << endl;
		//waitKey();
	//}
	return 0;
}

