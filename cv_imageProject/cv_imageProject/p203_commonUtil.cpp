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

bool p203_commonUtil::mergeImage(const cv::Mat& image_1, const cv::Mat& image_2, cv::Mat& empty_image) {
	if ((image_1.empty()) || (image_2.empty()) || (!empty_image.empty()))
	  return false;
	if ((image_1.channels() != 3) || (image_2.channels() != 3) || (image_1.channels() != image_2.channels()))
		return false;
	auto size_image_1 = image_1.rows + image_1.cols;
	auto size_image_2 = image_2.rows + image_2.cols;
	cv::Mat temp_image;

	if (size_image_1 >= size_image_2) {
		empty_image = cv::Mat::zeros(image_2.rows, image_2.rows, CV_8UC3);
		cv::resize(image_1, temp_image, cv::Size(image_2.cols, image_2.rows), 0, 0, cv::INTER_LINEAR);
		cv::addWeighted(temp_image, 1, image_2, 1, 0, empty_image);
	} else {
		empty_image = cv::Mat::zeros(image_1.rows, image_1.rows, CV_8UC3);
		cv::resize(image_2, temp_image, cv::Size(image_1.cols, image_1.rows), 0, 0, cv::INTER_LINEAR);
		cv::addWeighted(image_1, 1, temp_image, 1, 0, empty_image);
	}
	return true;
}
