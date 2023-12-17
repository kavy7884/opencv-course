#ifndef P201_COMMON_UTIL_H_
#define P201_COMMON_UTIL_H_
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
class p201_commonUtil {
 public:
	 p201_commonUtil() = default;
	 ~p201_commonUtil() = default;

	 static bool getFileList(const std::string file_path, std::vector<std::string>& file_list);
	 static void lotteNumberGenerator(cv::Vec<uint8_t, 7>& lotteList);
	 static bool generateRandomMatrix2D(cv::Mat& buffer);
	 static bool generateRandomMatrix3D(cv::Mat& buffer);

private:
};
#endif

