#ifndef P204_COMMON_UTIL_H_
#define P204_COMMON_UTIL_H_
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "p204_commonVariable.h"
class p204_commonUtil {
public:
	p204_commonUtil() = default;
	~p204_commonUtil() = default;

	static std::vector<std::uint32_t> grayscaleHistogram(const cv::Mat& input_image);

private:
};
#endif

