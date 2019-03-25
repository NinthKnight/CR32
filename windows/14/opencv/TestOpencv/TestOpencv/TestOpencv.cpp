// TestOpencv.cpp : �������̨Ӧ�ó������ڵ㡣
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

//Ѱ�����ƥ��λ�õķ���
//����1:	Դͼ��
//����2:	ģ��ͼ��
//����:	�õ������ƥ���
//
int MatchTemplate(string soucreFile, string templateFile)
{
	cv::Mat imageSource = cv::imread(soucreFile.c_str(),
		cv::IMREAD_UNCHANGED);
	cv::Mat imageTemplate = cv::imread(templateFile.c_str(),
		cv::IMREAD_UNCHANGED);
	cv::Mat imageMatched;

	////ģ��ƥ��
	cv::matchTemplate(imageSource, imageTemplate, imageMatched,
		cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//Ѱ�����ƥ��λ��
	cv::minMaxLoc(imageMatched, &minVal, &maxVal, &minLoc, &maxLoc);

	//cv::Mat imageColor;
	//cv::cvtColor(imageSource, imageColor, CV_BGR2BGRA);
	//cv::rectangle(imageColor, cv::Point(maxLoc.x, maxLoc.y),
	//	cv::Point(maxLoc.x + imageTemplate.cols, maxLoc.y + imageTemplate.rows),
	//	(7, 249, 151), 2);

	////����һ���´���
	//std::string windowName = "TestOpencv";
	////��ͼ����ʾ���´����Ĵ�����
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

