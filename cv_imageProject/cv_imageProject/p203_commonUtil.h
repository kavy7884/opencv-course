#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
class p203_commonUtil {
public:
	p203_commonUtil() = default;
	~p203_commonUtil() = default;

	static bool bgrToGray(const cv::Mat& bgr_image, cv::Mat& gray_image);

private:
};