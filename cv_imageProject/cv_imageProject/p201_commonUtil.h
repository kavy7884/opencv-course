#pragma once
#include <string>
#include <vector>
class p201_commonUtil {
 public:
	 p201_commonUtil() = default;
	 ~p201_commonUtil() = default;

	 static bool getFileList(const std::string file_path, std::vector<std::string>& file_list);

private:
};

