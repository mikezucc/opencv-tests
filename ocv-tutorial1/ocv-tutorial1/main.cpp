#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {

	//read the image
	cv::Mat image = cv::imread("loafy.jpeg");
	cv::namedWindow("My Window");
	cv::imshow("My Window", image);
	cv::waitKey(5000);

	return 1;
}