
#include<opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;
const char* output = "histogram image";
int main(int argc, char* argv)
{
	Mat src, dst, dst1;
	src = imread("D:\\11.jpeg");
	if (src.empty())return -1;
	char input[] = "input image";
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow(input, src);
	vector<Mat>channels;
	split(src, channels);
	Mat blue, green, red;
	blue = channels.at(0);
	green = channels.at(1);
	red = channels.at(2);
	int histsize = 256;
	float range[] = { 0,256 };
	const float* histRanges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&channels[0], 1, 0, Mat(), b_hist, 1, &histsize, &histRanges, true, false);
	calcHist(&channels[1], 1, 0, Mat(), g_hist, 1, &histsize, &histRanges, true, false);
	calcHist(&channels[2], 1, 0, Mat(), r_hist, 1, &histsize, &histRanges, true, false);
	int hist_h = 400;
	int hist_w = 512;
	int bin_w = hist_w / histsize;
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	for (int i = 1;i < histsize;i++)
	{
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))), Point((i)* bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2);
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))), Point((i)* bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2);
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))), Point((i)* bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2);
	}
	imshow(output, histImage);
	waitKey(0);
	return 0;
}