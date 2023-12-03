#include "p201_commonUtil.h"
#include <iostream>
#include <filesystem>
bool p201_commonUtil::getFileList(const std::string file_path, std::vector<std::string>& file_list) {
	using namespace std::filesystem;
	bool re{ false };

	try {
		auto file_name_set = directory_iterator(file_path);
		for (directory_entry curr_item : file_name_set) {
			if (curr_item.is_regular_file()) {
				file_list.push_back(curr_item.path().string());
			}
		}
		re = true;
	}
	catch (const std::exception& e) {
		std::cerr << __func__ << "\tException get:\t" << e.what() << std::endl;
	}

	return re;
}

bool p201_commonUtil::generateRandomMatrix2D(cv::Mat& buffer) {
	if ((buffer.channels() > 1) || (buffer.depth() != CV_64F))
		return false;

	auto prng = cv::RNG(static_cast<uint64_t>(time(nullptr)));

	for (int i = 0; i < buffer.rows; ++i) {
		for (int j = 0; j < buffer.cols; ++j) {
			buffer.at<double>(i, j) = floor(prng.uniform(0.0, 256.0));
		}
	}
	return true;
}
