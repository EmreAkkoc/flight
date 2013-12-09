/*
 * Implements the fast, single-disparity stereo alogrithm.
 *
 * Copyright 2013, Andrew Barry <abarry@csail.mit.edu>
 *
 */

#ifndef BARRYMOORE_H
#define BARRYMOORE_H

#include "opencv2/opencv.hpp"
#include <cv.h>
#include <iostream>


using namespace cv;
using namespace std;

struct BarryMooreState
{
    int disparity;
    int zero_dist_disparity;
    int sobelLimit;
    int blockSize;
    int sadThreshold;
    
    // a parameter added to the SAD/sobel division in the denominator
    float sobelAdd;
    
    Mat mapxL;
    
    Mat mapxR;
    
    Mat Q;
    
    bool show_display;
    
    //cv::vector<Point3f> *localHitPoints; // this is an array of cv::vector<Point3f>'s
};

struct BarryMooreStateThreaded
{
    BarryMooreState state;
    
    Mat remapped_left;
    Mat remapped_right;
    
    Mat laplacian_left;
    Mat laplacian_right;
    
    cv::vector<Point3f> *pointVector3d;
    cv::vector<Point3i> *pointVector2d;
    cv::vector<uchar> *pointColors;

    int row_start;
    int row_end;
    
    
};

struct RemapThreadState {
    Mat leftImage;
    Mat rightImage;
    
    Mat sub_remapped_left_image;
    Mat sub_remapped_right_image;
    
    Mat sub_laplacian_left;
    Mat sub_laplacian_right;
    
    Mat submapxL;
    Mat submapxR;
};

void StereoBarryMoore(InputArray _leftImage, InputArray _rightImage, cv::vector<Point3f> *pointVector3d, cv::vector<uchar> *pointColors, cv::vector<Point3i> *pointVector2d, BarryMooreState state);

Mat get_hogdescriptor_visu(Mat& origImg, vector<float>& descriptorValues);

void* StereoBarryMooreThreaded(void *statet);

void* RemapThreaded(void *remap_state);

int GetSAD(Mat leftImage, Mat rightImage, Mat sobelL, Mat sobelR, int pxX, int pxY, BarryMooreState state);

bool CheckHorizontalInvariance(Mat leftImage, Mat rightImage, Mat sobelL, Mat sobelR, int pxX, int pxY, BarryMooreState state);
 
#endif
