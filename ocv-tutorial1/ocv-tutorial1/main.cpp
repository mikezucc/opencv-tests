#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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

int main() {
	//read the image
	Mat image;
	image = imread("loafy.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if (!image.data)                              // Check for invalid input
	{
		return -1;
	}

	salt(image, 10000);

	namedWindow("My Window", WINDOW_AUTOSIZE);
	imshow("My Window", image);
	// Wait for a keystroke in the window
	waitKey(0);

    return 0;
}