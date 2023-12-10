#include "p203_commonUtil.h"

bool p203_commonUtil::bgrToGray(const cv::Mat& bgr_image, cv::Mat& gray_image) {
	if ((bgr_image.empty()) ||
		(bgr_image.channels() != 3) ||
		(bgr_image.depth() != CV_8U)) return false;

	if ((gray_image.empty()) ||
		(gray_image.channels() != 1) ||
		(gray_image.depth() != CV_8U)) return false;

	if ((bgr_image.rows != gray_image.rows) ||
		(bgr_image.cols != gray_image.cols)) return false;

	for (int height = 0; height < gray_image.rows; ++height) {
		for (int width = 0; width < gray_image.cols; ++width) {
			auto curr_b = static_cast<double>(bgr_image.at<cv::Vec<std::uint8_t, 3>>(height, width)[0]);
			auto curr_g = static_cast<double>(bgr_image.at<cv::Vec<std::uint8_t, 3>>(height, width)[1]);
			auto curr_r = static_cast<double>(bgr_image.at<cv::Vec<std::uint8_t, 3>>(height, width)[2]);
			auto gray_scale = 0.299 * curr_r + 0.587 * curr_g + 0.114 * curr_b;
			gray_image.at<std::uint8_t>(height, width)
				= static_cast<std::uint8_t>(std::floor(gray_scale));
		}
	}
	return true;
}
