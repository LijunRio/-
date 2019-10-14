#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

//RGB TO BGR
//默认图像储存为Mat格式，RGB类型
//在OpenCV读取图片过程中默认的通道顺序是BGR

void RGB_TO_BGR()
{
	Mat img = imread("imori.jpg", IMREAD_COLOR);
	int width = img.cols;
	int height = img.rows;
	Mat img_inv = img.clone();

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			unsigned char tmp = img_inv.at<Vec3b>(i, j)[0];
			img_inv.at<Vec3b>(i, j)[0] = img_inv.at<Vec3b>(i, j)[2];
			img_inv.at<Vec3b>(i, j)[2] = tmp;
		}
	}

	Mat out;
	out.create(height, width * 2, img.type());
	Mat r1 = out(Rect(0, 0, width, height));
	img.copyTo(r1);
	Mat r2 = out(Rect(width, 0, width, height));
	img_inv.copyTo(r2);

	imshow("result", out);
	waitKey(0);
}

class Grayscale
{
public:
	Grayscale() {
		img=imread("imori.jpg", IMREAD_COLOR);
		img_gray = Mat::zeros(img.size(), CV_8UC1);
	}

	//uchar(unsigned char) 是无符号的,8-bit无符号整形数据
	//unsigned char 整数范围为0到255( 0__0xFF )
	void maximum_grayscale() {
		//千万别给我等于啊，脑子不能抽
		for (int i = 0; i < img.cols; i++) {
			for (int j = 0; j < img.rows; j++) {
				uchar b = img.at<Vec3b>(i, j)[0];
				uchar g = img.at<Vec3b>(i, j)[1];
				uchar r = img.at<Vec3b>(i, j)[2];
				uchar max = (b >= g && b >=r)? b : (g >= b & g >= r)? g : r;
				img_gray.at<uchar>(i, j) = max;
			}
		}
		imshow("out", img_gray);
		waitKey(0);
	}


private:
	Mat img;
	Mat img_gray;
	Mat out;
};


int main()
{
	//RGB_TO_BGR();
	Grayscale g1;
	g1.maximum_grayscale();

	waitKey(0);
	system("pause");
}