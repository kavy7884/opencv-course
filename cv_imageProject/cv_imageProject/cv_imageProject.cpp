﻿#include <iostream>
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
    case 3: {
        // Test case 3:
        bool re{false};
        int rows{ 0 }, cols{ 0 };
        cv::Mat randomImage;
        std::cout << "Please assign the row size for random image:\t";
        std::cin >> rows;
        std::cout << "Please assign the col size for random image:\t";
        std::cin >> cols;

        randomImage = cv::Mat(rows, cols, CV_64FC1);
        re = p201_commonUtil::generateRandomMatrix2D(randomImage);
        
        if (re) {
            std::cout << "The randomly generated matrix: " << std::endl;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << static_cast<uint64_t>(randomImage.at<double>(i, j)) << "\t";
                }
                std::cout << std::endl;
            }

            std::cout << "The generation of identity matrix: " << std::endl;

            cv::Mat unit_matrix = randomImage * randomImage.inv();
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << static_cast<uint64_t>(unit_matrix.at<double>(i, j)) << "\t";
                }
                std::cout << std::endl;
            }
        } else {
            std::cerr << "The matrix can only be the 2D array with CV_64F." << std::endl;
        }

        break;
    }
    default:
        break;
    }

    
}