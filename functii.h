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


double* makeFilter(int size) {
    double* filter = new double[size * size];
    for (int y = 0; y < size - 1; y++)
        for (int x = 0; x < size - 1; x++)
            filter[y * size + x] = 1 / (double)(size * size);
    return filter;
}

Mat Filtru(Mat frame, int size)
{
    Mat result(frame);
    double* filtru = makeFilter(size);
    double sum;

    for (int y = size / 2; y < frame.cols - size / 2 - 1; y++)
        for (int x = size / 2; x < frame.rows - size / 2 - 1; x++)
        {
            sum = 0;
            for (int i = 0; i < size - 1; i++)
                for (int j = 0; j < size - 1; j++)
                {
                    if ((y - size / 2 + i) > 0 && (y - size / 2 + i) < frame.cols && (x - size / 2 + j) > 0 && (x - size / 2 + j) < frame.rows)
                        sum += frame.at<uchar>(x - size / 2 + j, y - size / 2 + i) * filtru[i * size + j];
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

Mat ScadereMatAbs(Mat mat1, Mat mat2) {
    Mat rez(mat1.rows, mat1.cols, CV_8UC1);
    for (int y = 0; y < rez.cols; y++)
        for (int x = 0; x < rez.rows; x++)
            rez.at<uchar>(x, y) = abs(mat1.at<uchar>(x, y) - mat2.at<uchar>(x, y));
    return rez;
}


Mat Difference(Mat frame, Mat background, int th) {

    Mat rez;

    rez = ScadereMatAbs(frame, background);

    for (int y = 0; y < rez.cols; y++)
        for (int x = 0; x < rez.rows; x++)
            if (rez.at<uchar>(x, y) > th)
                rez.at<uchar>(x, y) = 255;
            else
                rez.at<uchar>(x, y) = 0;

    rez = Filtru(rez, 5);
    // blur(rez, rez, Size(3, 3));

    for (int y = 0; y < rez.cols; y++)
        for (int x = 0; x < rez.rows; x++)
            if (rez.at<uchar>(x, y) > th)
                rez.at<uchar>(x, y) = 255;
            else
                rez.at<uchar>(x, y) = 0;

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

Mat backGroundUpdate(Mat frame, Mat back, int pond) {
    Mat rez(frame.rows, frame.cols, CV_8UC1);
    for (int x = 0; x < frame.rows; x++)
        for (int y = 0; y < frame.cols; y++)
            rez.at<uchar>(x, y) = (pond)*frame.at<uchar>(x, y) + (1 - pond) * back.at<uchar>(x, y);
    return rez;
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