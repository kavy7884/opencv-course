#ifndef P206_COMMON_UTIL_H_
#define P206_COMMON_UTIL_H_
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include "p206_commonVariable.h"
class p206_commonUtil {
public:
	p206_commonUtil() = default;
	~p206_commonUtil() = default;

	static size_t splitContours(const std::string file_path,
	  const size_t height, const size_t width,
	  std::vector<std::pair<int, cv::Mat>> &image_list);

	static std::uint8_t isJPEGwithEXIF(const std::string file_path);

private:
};
#endif

