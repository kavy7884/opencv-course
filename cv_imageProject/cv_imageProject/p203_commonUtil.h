#ifndef P203_COMMON_UTIL_H_
#define P203_COMMON_UTIL_H_
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
class p203_commonUtil {
public:
	p203_commonUtil() = default;
	~p203_commonUtil() = default;

	static bool bgrToGray(const cv::Mat& bgr_image, cv::Mat& gray_image);
	static bool mergeImage(const cv::Mat& image_1, const cv::Mat& image_2, cv::Mat& empty_image);

private:
};
#endif