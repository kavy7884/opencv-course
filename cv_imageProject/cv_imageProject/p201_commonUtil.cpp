#include "p201_commonUtil.h"
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <cmath>
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

void p201_commonUtil::lotteNumberGenerator(cv::Vec<uint8_t, 7>& lotteList) {
	std::unordered_set<std::uint8_t>::const_iterator it;
	std::unordered_set<std::uint8_t> lotteSet = std::unordered_set<uint8_t>();
	cv::RNG prng = cv::RNG(static_cast<uint64_t>(time(nullptr)));
	int jt = 0;

	while (lotteSet.size() < lotteList.channels) {
		lotteSet.insert(prng.uniform(1, 48));
	}

	for (it = lotteSet.begin(); it != lotteSet.end(); ++it) {
		if (jt < lotteList.channels) {
		lotteList[jt++] = *it;
		}
		else {
			break;
		}
	}
	return;
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

bool p201_commonUtil::generateRandomMatrix3D(cv::Mat& buffer) {
	using VectorType = cv::Vec<double, 3>;

	if ((buffer.channels() != 3) || (buffer.depth() != CV_64F))
		return false;

	auto prng = cv::RNG(static_cast<uint64_t>(time(nullptr)));

	for (auto it = buffer.begin<VectorType>(); it != buffer.end<VectorType>(); ++it) {
		for (int k = 0; k < (*it).channels; ++k) {
			(*it)[k] = floor(prng.uniform(0.0, 256.0));
		}
	}
	return true;
}