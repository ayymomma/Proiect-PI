#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <cmath>
#include <iostream>


using namespace cv;
using namespace std;

Mat Filtru(Mat frame)
{
    Mat result(frame);
    double sum;
    double filtru[9] = { 1 / 9.0,1 / 9.0,1 / 9.0,
                        1 / 9.0,1 / 9.0,1 / 9.0,
                        1 / 9.0,1 / 9.0,1 / 9.0 };
    int fh = 3;
    int fw = 3;


    for (int y = 1; y < frame.cols - 1; y++)
        for (int x = 1; x < frame.rows - 1; x++)
        {
            sum = 0;
            for (int i = 0; i < fh; i++)
                for (int j = 0; j < fw; j++)
                {
                    sum += frame.at<uchar>(x - fw / 2 + j, y - fh / 2 + i) * filtru[i * fw + j];
                }

            if (sum < 0)
                result.at<uchar>(x, y) = 0;
            else if (sum > 255)
                result.at<uchar>(x, y) = 255;
            else
                result.at<uchar>(x, y) = (unsigned char)sum;

        }
    return result;
}

Mat Difference(Mat frame, Mat background, int th) {

    Mat rez;


    rez = frame - background;

    rez = Filtru(rez);

    for (int y = 0; y < rez.cols; y++)
        for (int x = 0; x < rez.rows; x++)
        {
            if (rez.at<uchar>(x, y) > th)
                rez.at<uchar>(x, y) = 255;
            else
                rez.at<uchar>(x, y) = 0;

        }
    return rez;
}

int countDifferences(Mat frame) {

    int sum = 0;
    for (int x = 0; x < frame.rows; x++)
        for (int y = 0; y < frame.cols; y++)
            if (frame.at<uchar>(x, y) != 0)
                sum++;
    return sum;
}

//Mat DetectDrawRect(Mat frame, Mat difference) {
//    
//    int sum;
//    int xAxis[10], yAxis[10];
//    int xContor = 0, yContor = 0;
//    bool begin = false;
//    for (int x = 0; x < difference.rows; x++)
//        for (int y = 0; y < difference.cols; y++)
//        {
//            if (frame.at<uchar>(x, y) != 0 && begin == false) {
//                xAxis[xContor++] = x;
//                begin = true;
//                break;
//            }
//            else {
//
//            }
//        }
//
//}