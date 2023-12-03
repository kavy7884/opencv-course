#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "p201_commonUtil.h"
int main() {
    // Greeting
    std::cout << "Hello OpenCV World!\n";
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    
    // Define
    unsigned int index{ 0 };
    
    std::cout << "Please input your test case index: ";
    std::cin >> index;

    switch (index) {
    case 0: {
        // Test case 0: 
        std::string test_image_path;
        cv::Mat test_image;
        std::cout << "Please input test image path: ";
        std::cin >> test_image_path;
        std::cout << "Your image path is: " << test_image_path << std::endl;

        try {
            test_image = cv::imread(test_image_path);
            cv::imshow("Selected file image", test_image);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
        catch (std::exception e) {
            std::cerr << "Exception get: \t" << e.what() << std::endl;
        }
    }
    case 1: {
        // Test case 1:
        std::string test_dir;
        std::cout << "Please assign the test directory to be listed: ";
        std::cin >> test_dir;

        bool re{ false };
        auto file_list = std::vector<std::string>();
        re = p201_commonUtil::getFileList(test_dir, file_list);

        if (re) {
            for (const auto& f : file_list) {
                std::cout << f << std::endl;
            }

            std::cout << "Done! " << file_list.size() << " files was found!" << std::endl;
        }
        break;
    }
    default:
        break;
    }

    
}