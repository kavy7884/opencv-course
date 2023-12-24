#include "p204_commonUtil.h"

std::vector<std::uint32_t> p204_commonUtil::grayscaleHistogram(const cv::Mat& input_image) {
	auto histo_list = std::vector<std::uint32_t>(256);
	for (auto &elem : histo_list) elem = 0;
	if (input_image.channels() == 3) {
		cv::Mat gray_image;
		cv::cvtColor(input_image, gray_image, cv::COLOR_BGR2GRAY);
		for (auto it = gray_image.begin<std::uint8_t>(); it != gray_image.end<std::uint8_t>(); ++it)
		  histo_list.at(*it)++;
	}
	return histo_list;
}