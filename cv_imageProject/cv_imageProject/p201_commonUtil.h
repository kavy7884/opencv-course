#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
class p201_commonUtil {
 public:
	 p201_commonUtil() = default;
	 ~p201_commonUtil() = default;

	 static bool getFileList(const std::string file_path, std::vector<std::string>& file_list);
	 static bool generateRandomMatrix2D(cv::Mat& buffer);

private:
};

