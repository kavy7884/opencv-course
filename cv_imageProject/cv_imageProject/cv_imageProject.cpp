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
    case 2: {
        // Test case 2:
        cv::Vec<uint8_t, 7> lotteVector = cv::Vec<uint8_t, 7>::zeros();
        p201_commonUtil::lotteNumberGenerator(lotteVector);

        std::cout << "The selected random number:\t";

        for (int i = 0; i != lotteVector.channels; ++i) {
            std::cout << static_cast<uint32_t>(lotteVector[i]) << "\t";
        }

        std::cout << std::endl;
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
    case 4: {
        // Test case 4:
        bool re{ false };
        int rows{ 0 }, cols{ 0 };
        cv::Mat randomImage, scaledImage;
        std::cout << "Please assign the row size for random image:\t";
        std::cin >> rows;
        std::cout << "Please assign the col size for random image:\t";
        std::cin >> cols;

        randomImage = cv::Mat(rows, cols, CV_64FC3);
        re = p201_commonUtil::generateRandomMatrix3D(randomImage);

        if (re) {
            randomImage.convertTo(scaledImage, CV_8U, 0.5, 1);

            std::cout << "The randomly generated matrix: " << std::endl;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << "{ ";
                    for (int k = 0; k < randomImage.channels(); ++k) {
                        std::cout << randomImage.at<cv::Vec<double, 3>>(i, j)[k] << " -> ";
                        std::cout << static_cast<std::uint16_t>(scaledImage.at<cv::Vec<std::uint8_t, 3>>(i, j)[k]) << ", ";
                    }
                    std::cout << "}\t ";
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cerr << "The matrix can only be the 3D array with CV_64F." << std::endl;
        }

        break;
    }
    case 5: {
        // Test case 5:
        std::string file_name;
        std::cout << "Please input full path of image: ";
        std::cin >> file_name;

        if (cv::haveImageReader(file_name)) {
            cv::Mat image_buffer = cv::imread(file_name);

            if ((image_buffer.data == nullptr) ||
              (image_buffer.empty())) {
                std::cerr << "The file is not readable for OpenCV:\t" << file_name << std::endl;
            }
            else {
                int key;
                std::cout << "The info of image:" << std::endl;
                std::cout << "Hight: " << image_buffer.rows << ", " << std::endl;
                std::cout << "Width: " << image_buffer.cols << ", " << std::endl;
                std::cout << "Depth: " << image_buffer.channels() << ", " << std::endl;
                std::cout << "DataType: " << image_buffer.depth() << ", " << std::endl;
                cv::imshow("Sample image", image_buffer);

                key = cv::waitKey(0);
                if (key == 27) { // Esc
                    cv::destroyAllWindows();
                }
            }
        } else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }

        break;
    }
    case 6: {
        // Test case 6:
        std::string file_name;
        std::cout << "Please input full path of image: ";
        std::cin >> file_name;

        if (cv::haveImageReader(file_name)) {
            cv::Mat image_buffer = cv::imread(file_name);

            if ((image_buffer.data == nullptr) ||
                (image_buffer.empty())) {
                std::cerr << "The file is not readable for OpenCV:\t" << file_name << std::endl;
            }
            else {
                std::string target_path;
                std::cout << "Please assign the directory path storing the cropped images, ended with \"\\\"\: \t";
                std::cin >> target_path;

                int seg_line = static_cast<int>(image_buffer.cols / 2);
                auto now_time = std::time(nullptr);
                auto images_left = image_buffer.colRange(0, seg_line);
                auto images_right = image_buffer.colRange(seg_line, image_buffer.cols);

                std::string path_left = std::string(target_path) + std::string("image_") 
                  + std::to_string(now_time) + std::string("_left.jpeg");
                std::string path_right = std::string(target_path) + std::string("image_")
                    + std::to_string(now_time) + std::string("_right.jpeg");

                std::vector<int> jpeg_options;
                jpeg_options.push_back(cv::IMWRITE_JPEG_QUALITY);
                jpeg_options.push_back(90);
                jpeg_options.push_back(cv::IMWRITE_JPEG_OPTIMIZE);
                jpeg_options.push_back(1);

                cv::imwrite(path_left, images_left, jpeg_options);
                cv::imwrite(path_right, images_right, jpeg_options);

                std::cout << "Image cropping is done! Saved in " << path_left
                  << "and " << path_right << ". " << std::endl;
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }

        break;
    }
    case 7: {
        // Test case 7:
        std::string file_name;
        std::cout << "Please input full path of image: ";
        std::cin >> file_name;

        if (cv::haveImageReader(file_name)) {
            cv::Mat image_buffer = cv::imread(file_name);

            if ((image_buffer.data == nullptr) ||
                (image_buffer.empty())) {
                std::cerr << "The file is not readable for OpenCV:\t" << file_name << std::endl;
            }
            else {
                std::uint8_t range;
                std::vector<cv::Mat> channels, fixed_channels;
                cv::Mat image_buffer_updated;
                std::cout << "The ratio of blue-ray decreased (0 ~ 100):\t";
                std::cin >> range;
                range = 100 - (range % 100);

                cv::split(image_buffer, channels);

                cv::imshow("Original image", image_buffer);
                cv::imshow("Blue-ray channel image", channels[0]);
                cv::imshow("Green-ray channel image", channels[1]);
                cv::imshow("Red-ray channel image", channels[2]);

                for (auto it = channels[0].begin<std::uint8_t>();
                  it != channels[0].end<std::uint8_t>(); ++it) {
                    *it = static_cast<std::uint8_t>(
                      static_cast<double>(*it) * static_cast<double>(range) / 100.0);
                }

                fixed_channels.push_back(channels[0]);
                fixed_channels.push_back(channels[1]);
                fixed_channels.push_back(channels[2]);

                cv::merge(fixed_channels, image_buffer_updated);

                cv::imshow("Blue-ray reduced image", image_buffer_updated);

                cv::waitKey(0);
                cv::destroyAllWindows();
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }

        break;
    }
    case 8: {
        // Test case 8:
        int height{ 0 }, width{ 0 };
        int total_sections = 17;
        std::cout << "Please assign the width of test image:\t";
        std::cin >> width;
        if (width % total_sections == 0) {
            std::cout << "Please assign the height of test image:\t";
            std::cin >> height;
            std::uint8_t current_b{ 0 }, current_g{ 255 };
            auto image = cv::Mat(height, width, CV_8UC3,
              cv::Scalar(current_b, current_g, 255)); // R is 255 forever!
            cv::imshow("Blank yellow", image);
            auto key = cv::waitKey(0);

            if (key == 27) {
                cv::destroyAllWindows();
            }  else {
                cv::destroyAllWindows();
                int column_section = 1;
                int delta = 16; // Eachtime the degree of b += 16 and g -= 16. For this case ONLY!
                bool last_time{ false };

                while ((current_b < 255) && (current_g > 0)) {
                    if (last_time) break;

                    if (current_b > (255 - delta)) {
                        current_b = 255;
                        last_time = true;
                    } else {
                        current_b += delta;
                    }

                    if (current_g < delta) {
                        current_g = 0;
                        last_time = true;
                    }
                    else {
                        current_g -= delta;
                    }

#ifndef NDEBUG
                    std::cout << "colume_section = " << column_section << std::endl;
#endif // !NDEBUG
                    for (int row_id = 0; row_id != image.rows; ++row_id) {
                        auto colume_start = static_cast<int>(column_section * image.cols / total_sections);
                        auto colume_end = static_cast<int>((column_section + 1) * image.cols / total_sections);

#ifndef NDEBUG
                        if (row_id == 0)
                          std::cout << "column_start = " << colume_start << ", column_end = " << colume_end << std::endl;
#endif // !NDEBUG
                        for (int col_id = colume_start; col_id != colume_end; ++col_id) {
                            image.at<cv::Vec<std::uint8_t, 3>>(row_id, col_id)[0] = current_b;
                            image.at<cv::Vec<std::uint8_t, 3>>(row_id, col_id)[1] = current_g;
                        }
                    }
                    column_section++;
                }
                cv::imshow("Hue evolution = " + std::to_string(total_sections), image);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
        } else {
            std::cerr << "The width of test image MUST BE the multiple of " << total_sections << std::endl;
        }
    }
    case 9: {
        // Test case 9:
        std::string file_name;
        std::cout << "Please input full path of image: ";
        std::cin >> file_name;

        if (cv::haveImageReader(file_name)) {
            cv::Mat image_buffer = cv::imread(file_name);

            if ((image_buffer.data == nullptr) ||
                (image_buffer.empty())) {
                std::cerr << "The file is not readable for OpenCV:\t" << file_name << std::endl;
            }
            else {
                std::uint32_t transp;
                std::vector<cv::Mat> channels, fixed_channels;
                std::string export_path, export_dir;
                
                std::cout << "The ratio of transparency (0 ~ 255):\t";
                std::cin >> transp;

                if ((transp < 0) || (transp > 255)) {
                    std::cerr << "The value is not valid:\t" << transp << " ." << std::endl;
                } else {
                    cv::Mat transparency_channel, image_buffer_updated;
                    cv::split(image_buffer, channels);
                    transparency_channel = cv::Mat(image_buffer.rows, image_buffer.cols, CV_8UC1, cv::Scalar(transp));

                    fixed_channels.push_back(channels[0]);
                    fixed_channels.push_back(channels[1]);
                    fixed_channels.push_back(channels[2]);
                    fixed_channels.push_back(transparency_channel);

                    cv::merge(fixed_channels, image_buffer_updated);
                    std::cout << "Please assign the directory for exporting the image file (end with \\):\t";
                    std::cin >> export_dir;

                    export_path = export_dir + "Test_" + std::to_string(transp) + ".png";
                    cv::imwrite(export_path, image_buffer_updated);
                    std::cout << "The transparent image file is saved to " << export_path << std::endl;
                }
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }

        break;
    }
    default:
        break;
    }
}