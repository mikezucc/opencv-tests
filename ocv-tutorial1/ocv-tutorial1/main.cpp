#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>

using namespace cv;
using namespace std;

void salt(cv::Mat &image, int n) {
	for (int k = 0; k<n; k++) {      // rand() is the MFC random number generator      
		// try qrand() with Qt      
		int i = rand() % image.cols;
		int j = rand() % image.rows;

		image.at<uchar>(j, i) = 255;
	}
}

void createStereo() {
	Mat img1, img2, g1, g2;
	Mat disp, disp8;

	img1 = imread("imgLeft.jpg");
	img2 = imread("imgRight.jpg");

	cvtColor(img1, g1, CV_BGR2GRAY);
	cvtColor(img2, g2, CV_BGR2GRAY);

	StereoBM sbm;
	sbm.state->SADWindowSize = 9;
	sbm.state->numberOfDisparities = 112;
	sbm.state->preFilterSize = 5;
	sbm.state->preFilterCap = 61;
	sbm.state->minDisparity = -39;
	sbm.state->textureThreshold = 507;
	sbm.state->uniquenessRatio = 0;
	sbm.state->speckleWindowSize = 0;
	sbm.state->speckleRange = 8;
	sbm.state->disp12MaxDiff = 1;

	sbm(g1, g2, disp);
	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

	imshow("left", img1);
	imshow("right", img2);
	imshow("disp", disp8);
}

int main() {
	//read the image
	createStereo();
	waitKey(0);

    return 0;
}