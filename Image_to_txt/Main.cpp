#include <fstream>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int main()
{
	string folder;
	Mat image;
	string file;
	string path;
	for (int i = 0; i < 10; i++) {
		ofstream out(to_string(i)+".txt");
		string folder = "E:\\CNN_ITMM\\mnist_png\\training\\" + to_string(i) + "\\";
		for (int j = 1; j < 1001; j++) {
			file = " (" + to_string(j) + ").png";
			path = folder + file;
			image = imread(path, IMREAD_GRAYSCALE);
			out << image.rows << ' ' << image.cols << endl;
			for (int i = 0; i < image.rows; i++) {
				for (int j = 0; j < image.cols; j++) {
					if ((int)image.at<uchar>(i, j) == 0) {
						out << -1 << ' ';
					}
					else {
						out << 1 << ' ';
					}
				}
				out << endl;
			}
		}
	}
	return 0;
}
