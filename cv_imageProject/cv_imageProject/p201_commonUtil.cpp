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
