#include "Method.h"
using namespace cv;
using namespace std;
vector<int> GetHistogram(Mat Image,int &S);
double c_method_1(Mat Image1, Mat Image2)
{
	vector<int> DisA1 , DisA2 ;
	int a, b;
	 DisA1=GetHistogram(Image1,a);
	 DisA2=GetHistogram(Image2,b);
	double t = 0;
	for (int i = 0; i < 50; i++)
	{
		t += abs(DisA1[i] - DisA2[i]);
	}
	t /= DisA1.size();
	return t;
}

class doublecomp
{
public:
	bool operator()(double a, double b)
	{
		return a > b;
	}
};
vector<int> GetHistogram(Mat Image, int& S) 
{
	int Row = Image.rows, Col = Image.cols;
	vector<Point2d> word;
	for (int i = 0; i < Col; i++)
	{
		for (int j = 0; j < Row; j++)
		{
			if (Image.at<uchar>(j, i) == 255)
			{
				word.push_back(Point2d(j, i));
			}
		}
	}
	int Mx(0), My(0),size=word.size();
	for (int i = 0; i < size; i++)
	{
		Mx += word[i].x; My += word[i].y;
	}
	Mx /= size; My /= size;
	Point2d Centroid(Mx,My);
	for (int i = 0; i < size; i++)
		word[i] = word[i] - Centroid;
	vector<double> D;
	D.resize(size);
	for (int i = 0; i < size; i++)
	{
		D[i] = word[i].x * word[i].x + word[i].y * word[i].y;
		D[i] = sqrt(D[i]);
	}
	sort(&D[0],&D[size-1]);
	double Range = D[size - 1] - D[0];
	int leg = D[0];
	vector<int> C;
	C.resize(50);
	for (int i = 0; i < 50; i++)C[i] = 0;
	for (int i = 0; i < size; i++)
	{
		D[i] = D[i] - leg;
		if (D[i] >= Range)
			D[i] = Range;
		D[i] = D[i] / Range;
		D[i] *= 49;
		C[int(D[i])]++;
	}
	S = size;
	return C;
}