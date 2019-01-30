#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <Windows.h>
#include "math.h"


using namespace cv;
using namespace std;

int main1(/*int argc, char** argv*/)
{
	int N = 1000;
	Mat img(N, N, CV_8UC1, Scalar(0, 0));
	//cout << new_image << endl;
	//img.at<uchar>(1, 1) = 128;
	namedWindow("mia immagine", WINDOW_AUTOSIZE);
	imshow("mia immagine", img);
	//waitKey(0);
	double dt = 0.05, K = 0.1;
	const int M = 1000;
	double velocità[M][3];
	double posizione[M][3];
	double posizione_new[M][3];
	double dist2;
	for (int i = 0; i < M; i++) {
		posizione[i][0] = posizione_new[i][0] = fRand(N * 3 / 8, N * 5 / 8);
		posizione[i][1] = posizione_new[i][1] = fRand(N * 3 / 8, N * 5 / 8);
		posizione[i][2] = posizione_new[i][2] = fRand(N * 3 / 8, N * 5 / 8);
		dist2 = (posizione[i][1] - N / 2)*(posizione[i][1] - N / 2) + (posizione[i][0] - N / 2)*(posizione[i][0] - N / 2);
		velocità[i][0] = 0 + 0.1 / dist2 * (posizione[i][1] - N / 2);
		velocità[i][1] = 0 - 0.1 / dist2 * (posizione[i][0] - N / 2);
		velocità[i][2] = 0;
	}
	for (double t = 0.0; t < 100000000; t += dt)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
				if (i != j)
				{
					{
						dist2 = (posizione[i][0] - posizione[j][0])*(posizione[i][0] - posizione[j][0]) +
							(posizione[i][1] - posizione[j][1])*(posizione[i][1] - posizione[j][1]) +
							(posizione[i][2] - posizione[j][2])*(posizione[i][2] - posizione[j][2]);
						velocità[i][0] -= dt * K / dist2 * (posizione[i][0] - posizione[j][0]) / sqrt(dist2);
						velocità[i][1] -= dt * K / dist2 * (posizione[i][1] - posizione[j][1]) / sqrt(dist2);
						velocità[i][2] -= dt * K / dist2 * (posizione[i][2] - posizione[j][2]) / sqrt(dist2);
					}
					posizione_new[i][0] += velocità[i][0] * dt;
					posizione_new[i][1] += velocità[i][1] * dt;
					posizione_new[i][2] += velocità[i][2] * dt;
					int x = resize(posizione[i][0], 0, N - 1);
					int y = resize(posizione[i][1], 0, N - 1);
					img.at<uchar>(x, y) = 255;
				}
		}
		imshow("mia immagine", img);
		for (int j = 0; j < M; j++)
		{
			posizione[j][0] = posizione_new[j][0];
			posizione[j][1] = posizione_new[j][1];
			posizione[j][2] = posizione_new[j][2];
		}
		waitKey(1);
		img.setTo(Scalar(0, 0));
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			img.at<uchar>(100 + 40 * cos(0.1*i), 100 + 40 * sin(0.1*i)) = 255;
			//imshow("mia immagine", img);
		}
		imshow("mia immagine", img);
		//waitKey(1);
	}
	waitKey(0);
	return 0;
}