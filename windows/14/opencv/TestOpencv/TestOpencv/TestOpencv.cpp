// TestOpencv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <opencv2\opencv.hpp>
#include <sstream>
using namespace std;

#ifdef _DEBUG

#pragma comment(lib, "opencv_highgui342d.lib")
#pragma comment(lib, "opencv_imgcodecs342d.lib")
#pragma comment(lib, "opencv_imgproc342d.lib")
#pragma comment(lib, "opencv_core342d.lib")
#else
#pragma comment(lib, "opencv_highgui342.lib")
#pragma comment(lib, "opencv_imgcodecs342.lib")
#pragma comment(lib, "opencv_imgproc342.lib")
#pragma comment(lib, "opencv_core342.lib")
#endif

//寻找最佳匹配位置的方法
//参数1:	源图像
//参数2:	模板图像
//返回:	得到的最佳匹配点
//
int MatchTemplate(string soucreFile, string templateFile)
{
	cv::Mat imageSource = cv::imread(soucreFile.c_str(),
		cv::IMREAD_UNCHANGED);
	cv::Mat imageTemplate = cv::imread(templateFile.c_str(),
		cv::IMREAD_UNCHANGED);
	cv::Mat imageMatched;

	////模板匹配
	cv::matchTemplate(imageSource, imageTemplate, imageMatched,
		cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//寻找最佳匹配位置
	cv::minMaxLoc(imageMatched, &minVal, &maxVal, &minLoc, &maxLoc);

	//cv::Mat imageColor;
	//cv::cvtColor(imageSource, imageColor, CV_BGR2BGRA);
	//cv::rectangle(imageColor, cv::Point(maxLoc.x, maxLoc.y),
	//	cv::Point(maxLoc.x + imageTemplate.cols, maxLoc.y + imageTemplate.rows),
	//	(7, 249, 151), 2);

	////创建一个新窗口
	//std::string windowName = "TestOpencv";
	////将图像显示都新创建的窗口中
	//cv::namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	//cv::imshow(windowName, imageSource);
	//cv::imshow(windowName, imageMatched);
	//cv::imshow(windowName, imageColor);
	//qDebug() << "maxLoc.x = " << maxLoc.x << ",maxLoc.y = " << maxLoc.y << endl;
	
	stringstream ss;
	ss << "maxLoc.x = " << maxLoc.x << ",maxLoc.y = " << maxLoc.y << endl;
	
	return 1;
}

int main()
{
	MatchTemplate("D:\\1.png", "D:\\3.png");

	system("pause");
    return 0;
}

