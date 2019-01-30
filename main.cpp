#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <Windows.h>
#include "math.h"
#include <vector>
#include <conio.h>


using namespace cv;
using namespace std;

const int Dim = 1000;
const int N = 10000;
const double totalMass = 1000, dt = 0.005, K = 1, tMax = +INFINITY;






#include "simulazione.cpp"
int counter = 0;
int main(int argc, char** argv)
{
	//main1();

	Mat img(Dim, Dim, CV_8UC3, Scalar(0, 0, 0));
	VideoWriter video("outcpp.avi", CV_FOURCC('M', 'J', 'P', 'G'), 30, Size(Dim, Dim));


	namedWindow("mia immagine", WINDOW_AUTOSIZE);
	imshow("mia immagine", img);
	
	double v_x[N], v_y[N], v_z[N];
	double p_x[N], p_y[N], p_z[N];
	double p_x_[N], p_y_[N], p_z_[N];


	double dist2;
	for (int i = 0; i < N; i++)
	{
		p_x[i] = p_x_[i] = fRand(Dim / 4, Dim * 3 / 4);
		p_y[i] = p_y_[i] = fRand(Dim / 4, Dim * 3 / 4);
		p_z[i] = p_z_[i] = fRand(Dim / 4, Dim * 3 / 4);

		dist2 = (p_x[i] - Dim / 2)*(p_x[i] - Dim / 2) + (p_y[i] - Dim / 2)*(p_y[i] - Dim / 2);
		v_x[i] = 0 + 300.1 / dist2 * (p_y[i] - Dim / 2);
		v_y[i] = 0 - 300.1 / dist2 * (p_x[i] - Dim / 2);
		v_z[i] = 0;
	}

	double dist_x, dist_y, dist_z;
	for (double t = 0; t < tMax; t += dt)
	{
		for (int n = 0; n < N; n++)
		{
			p_x_[n] = p_x[n];
			p_y_[n] = p_y[n];
			p_z_[n] = p_z[n];
			for (int j = 0; j < N; j++)
			{
				if (n != j)
				{
					dist_x = p_x_[n] - p_x_[j];
					dist2 = dist_x * dist_x;
					dist_y = p_y_[n] - p_y_[j];
					dist2 += dist_y * dist_y;
					dist_z = p_z_[n] - p_z_[j];
					dist2 += dist_z * dist_z;

					v_x[n] -= dist_x / sqrt(dist2) * K / dist2;
					v_y[n] -= dist_y / sqrt(dist2) * K / dist2;
					v_z[n] -= dist_z / sqrt(dist2) * K / dist2;
				}
			}
			p_x[n] += v_x[n] * dt;
			p_y[n] += v_y[n] * dt;
			p_z[n] += v_z[n] * dt;
			int x = resize(p_x[n], 0, Dim - 1);
			int y = resize(p_y[n], 0, Dim - 1);
			img.at<Vec3b>(x, y)[0] += 2;
			img.at<Vec3b>(x, y)[1] += 2;
			img.at<Vec3b>(x, y)[2] += 2;
		}
		
		 if(_kbhit())
		{
			video.release();

			break;
		}
		imshow("mia immagine", img);
		waitKey(1);
		if ((counter % 50) == 0)
		{
			video.write(img);
			img.setTo(Scalar(0, 0, 0));
		}
		counter++;
		//img.setTo(Scalar(0, 0, 0));
		//cout << waitKey(1) << endl;
	}

	return 0;
}