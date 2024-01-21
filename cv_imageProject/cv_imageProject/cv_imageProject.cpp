#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/face/facerec.hpp>
#include <TinyEXIF.h>
#include "p201_commonUtil.h"
#include "p203_commonUtil.h"
#include "p204_commonUtil.h"
#include "p206_commonUtil.h"
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
                std::cout << "Please assign the directory path storing the cropped images, ended with \"\\\":\t";
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
    case 10: {
        // Test case 10:
        bool re{ false };
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
                cv::Mat gray_scale_image = cv::Mat(image_buffer.rows, image_buffer.cols, CV_8UC1);
                re = p203_commonUtil::bgrToGray(image_buffer, gray_scale_image);

                if (re) {
                    cv::imshow("Grayscale of " + file_name, gray_scale_image);
                    cv::waitKey(0);
                    cv::destroyAllWindows();
                } else {
                    std::cerr << "Grayscale image generation failed for " << file_name << std::endl;
                }
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 11: {
        // Test case 11:
        bool re{ false };
        std::string file_name_1, file_name_2;
        std::cout << "Please input full path of 1st image: ";
        std::cin >> file_name_1;
        std::cout << "Please input full path of 2nd image: ";
        std::cin >> file_name_2;

        std::cout << cv::haveImageReader(file_name_1) << std::endl;
        std::cout << cv::haveImageReader(file_name_2) << std::endl;

        if (cv::haveImageReader(file_name_1) && cv::haveImageReader(file_name_2)) {
            cv::Mat image_buffer_1 = cv::imread(file_name_1);
            cv::Mat image_buffer_2 = cv::imread(file_name_2);
            if ((image_buffer_1.data == nullptr) ||
              (image_buffer_1.empty()) ||
              (image_buffer_2.data == nullptr) ||
              (image_buffer_2.empty())) {
                std::cerr << "At least one file is not parsable for OpenCV. Bye" << std::endl;
            } else {
                cv::Mat merged_image;
                re = p203_commonUtil::mergeImage(image_buffer_1, image_buffer_2, merged_image);
                if (re) {
                    cv::imshow("Merged image", merged_image);
                    cv::waitKey(0);
                    cv::destroyAllWindows();
                } else {
                    std::cerr << "Merging image failled for " << file_name_1 << " and " << file_name_2 << std::endl;
                }
            }
        }
        else {
            std::cerr << "At least one file is not parsable for OpenCV. Bye" << std::endl;
        }
        break;
    }
    case 12: {
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
                cv::Mat nagative_image;
                cv::bitwise_not(image_buffer, nagative_image);
                cv::imshow("Nagative image", nagative_image);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 13: {
        std::uint16_t r, g, b;
        const int& cols{ 1 }, rows{ 1 };
        cv::Mat pixel, hsv_array;

        std::cout << "Please assign the degree of Red (0 ~ 255):\t";
        std::cin >> r;
        std::cout << "Please assign the degree of Green (0 ~ 255):\t";
        std::cin >> g;
        std::cout << "Please assign the degree of Blue (0 ~ 255):\t";
        std::cin >> b;
        pixel = cv::Mat(rows, cols, CV_8UC3, cv::Scalar(b, g, r));
        cv::cvtColor(pixel, hsv_array, cv::COLOR_BGR2HSV_FULL);
        std::cout << "The info of HSV image: depth = " << hsv_array.depth()
          << ", channel size = " << hsv_array.channels() << std::endl;
        for (int i = 0; i < hsv_array.rows; i++) {
            for (int j = 0; j < hsv_array.cols; j++) {
                std::cout << "pixel item:\t {H = " << static_cast<std::uint16_t>(
                    hsv_array.at<cv::Vec<std::uint8_t, 3>>(i, j)[0]) * 360 / 256;
                std::cout << ", S = " << (static_cast<double>(hsv_array.at<cv::Vec<std::uint8_t, 3>>(i, j)[1]) + 1) / 256.0 * 100.0;
                std::cout << "%, V = " << (static_cast<double>(hsv_array.at<cv::Vec<std::uint8_t, 3>>(i, j)[2]) + 1) / 256.0 * 100.0 << "%}." << std::endl;;
            }
        }
    }
    case 14: {
        // Test case 14:
        bool re{ false };
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
                cv::Mat gray_scale_image = cv::Mat(image_buffer.rows, image_buffer.cols, CV_8UC1);
                cv::cvtColor(image_buffer, gray_scale_image, cv::COLOR_BGR2GRAY);
                std::cout << "The info of gray scaled image: depth = " << gray_scale_image.depth()
                    << ", channel size = " << gray_scale_image.channels() << std::endl;
                cv::imshow("Grayscale of " + file_name, gray_scale_image);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 15: {
        // Test case 15:
        bool re{ false };
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
                std::uint32_t angle;
                cv::Mat rotated_image;
                std::cout << "Please assign the angle to be rotated counter-wise (90, 270, 180 otherwise): ";
                std::cin >> angle;
                switch (angle) {
                case 90:
                    cv::rotate(image_buffer, rotated_image, cv::ROTATE_90_CLOCKWISE);
                    break;
                case 270:
                    cv::rotate(image_buffer, rotated_image, cv::ROTATE_90_COUNTERCLOCKWISE);
                    break;
                default:
                    cv::rotate(image_buffer, rotated_image, cv::ROTATE_180);
                    break;
                }

                cv::imshow("Grayscale of " + file_name, rotated_image);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 16: {
        // Test case 16:
        bool re{ false };
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
                using PointType = cv::Point_<float>;
                std::vector<PointType> src_edge, dst_edge;
                cv::Mat mapping_matrix, calibrated_buffer;
                std::time_t now_time = std::time(nullptr);
                std::string target_dir, file_name_calibrated;
                std::cout << "Please assign the dir/path storing the calibrated images, ended with \"\\\":\t";
                std::cin >> target_dir;

                file_name_calibrated = std::string(target_dir) + std::string("calibrated_")
                    + std::to_string(now_time) + std::string(".jpg");

                if ((image_buffer.cols != P204_DEFAULT_CARLABEL_SIZE_WIDTH) 
                    || (image_buffer.rows != P204_DEFAULT_CARLABEL_SIZE_HEIGHT)) {
                    cv::resize(image_buffer, image_buffer, cv::Size(
                      P204_DEFAULT_CARLABEL_SIZE_WIDTH, P204_DEFAULT_CARLABEL_SIZE_HEIGHT));
                }

                src_edge.push_back(PointType(30.0, 95.0));
                src_edge.push_back(PointType(86.0, 311.0));
                src_edge.push_back(PointType(450.0, 175.0));
                src_edge.push_back(PointType(426.0, 11.0));
                dst_edge.push_back(PointType(56.0, 50.0));
                dst_edge.push_back(PointType(56.0, 273.0));
                dst_edge.push_back(PointType(444.0, 273.0));
                dst_edge.push_back(PointType(444.0, 50.0));

                mapping_matrix = cv::getPerspectiveTransform(src_edge, dst_edge);
                cv::warpPerspective(image_buffer, calibrated_buffer, mapping_matrix,
                  cv::Size(image_buffer.cols, image_buffer.rows));
                cv::imshow("Skewed image: " + file_name, image_buffer);
                cv::waitKey(0);
                cv::imshow("Calibrated image of: " + file_name, calibrated_buffer);
                cv::waitKey(0);
                cv::destroyAllWindows();
                cv::imwrite(file_name_calibrated, calibrated_buffer);
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 17: {
        // Test case 17:
        bool re{ false };
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
                using PointType = cv::Point_<float>;
                std::vector<PointType> src_edge, dst_edge;
                cv::Mat cropped_buffer, gray_scale_buffer, boolean_buffer;
                std::time_t now_time = std::time(nullptr);
                std::string target_dir, file_name_boolean;
                std::cout << "Please assign the dir/path storing the cropped images, ended with \"\\\":\t";
                std::cin >> target_dir;

                file_name_boolean = std::string(target_dir) + std::string("boolean_")
                    + std::to_string(now_time) + std::string(".jpg");

                if ((image_buffer.cols != P204_DEFAULT_CARLABEL_SIZE_WIDTH)
                    || (image_buffer.rows != P204_DEFAULT_CARLABEL_SIZE_HEIGHT)) {
                    cv::resize(image_buffer, image_buffer, cv::Size(
                        P204_DEFAULT_CARLABEL_SIZE_WIDTH, P204_DEFAULT_CARLABEL_SIZE_HEIGHT));
                }

                cropped_buffer = image_buffer.colRange(56, 444).rowRange(50, 273);
                cv::cvtColor(cropped_buffer, gray_scale_buffer, cv::COLOR_BGR2GRAY);
                boolean_buffer = cv::Mat::zeros(cropped_buffer.rows, cropped_buffer.cols, CV_8UC1);

                for (int i = 0; i < gray_scale_buffer.rows; i++) {
                    for (int j = 0; j < gray_scale_buffer.cols; j++) {
                        if (gray_scale_buffer.at<std::uint8_t>(i, j) <= 128) {
                            boolean_buffer.at<std::uint8_t>(i, j) = 255;
                        } else {
                            boolean_buffer.at<std::uint8_t>(i, j) = 0;
                        }
                    }
                }
                cv::imshow("Grayscale image: " + file_name, gray_scale_buffer);
                cv::waitKey(0);
                cv::imshow("Boolean image: " + file_name, boolean_buffer);
                cv::waitKey(0);
                cv::destroyAllWindows();
                cv::imwrite(file_name_boolean, boolean_buffer);
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 18: {
        // Test case 18:
        bool re{ false };
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
                auto histogram = p204_commonUtil::grayscaleHistogram(image_buffer);
                std::ofstream ofs;
                std::string target_dir, csv_path;
                time_t now_time = std::time(nullptr);
                std::cout << "Please assign the dir/path storing the cropped images, ended with \"\\\":\t";
                std::cin >> target_dir;

                csv_path = std::string(target_dir) + std::string("histo_")
                  + std::to_string(now_time) + std::string(".csv");
                ofs.open(csv_path);
                for (size_t i = 0; i < histogram.size(); i++)
                  ofs << "\"" << i << "\",\"" << histogram[i] << "\"" << std::endl;
                ofs.close();
                std::cout << "Histogram data generate to " << csv_path << " done!" << std::endl;
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 19: {
        // Test case 19:
        bool re{ false };
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
                cv::Mat eroded_buffer;
                std::uint16_t morph_size{ 1 };
                std::cout << "Please assign the size of kernel for eroding operations (1 or 2):\t";
                std::cin >> morph_size;

                if ((morph_size != 1) && (morph_size != 2))
                {
                    std::cerr << "Not supported morph_size generating the eroding/dilating kernel." << std::endl;
                }
                else
                {
                    cv::Mat erode_kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2 * morph_size + 1, 2 * morph_size + 1));
                    uint16_t morph_type = 0;
                    std::cout << "Please assign the type of morphology operation (0 = erode, 1 = dilate, 2 = open, 3 = close, 4 = tophat, 5 = blackhat, gredient otherwise):\t";
                    std::cin >> morph_type;

                    cv::imshow("The original image", image_buffer);
                    cv::waitKey(0);

                    switch (morph_type)
                    {
                    case 0:
                        cv::erode(image_buffer, eroded_buffer, erode_kernel);
                        cv::imshow("The eroded image", eroded_buffer);
                        break;
                    case 1:
                        cv::dilate(image_buffer, eroded_buffer, erode_kernel);
                        cv::imshow("The dilated image", eroded_buffer);
                        break;
                    case 2:
                        cv::morphologyEx(image_buffer, eroded_buffer, cv::MORPH_OPEN, erode_kernel);
                        cv::imshow("The opened image", eroded_buffer);
                        break;
                    case 3:
                        cv::morphologyEx(image_buffer, eroded_buffer, cv::MORPH_CLOSE, erode_kernel);
                        cv::imshow("The closed image", eroded_buffer);
                        break;
                    case 4:
                        cv::morphologyEx(image_buffer, eroded_buffer, cv::MORPH_TOPHAT, erode_kernel);
                        cv::imshow("The tophated image", eroded_buffer);
                        break;
                    case 5:
                        cv::morphologyEx(image_buffer, eroded_buffer, cv::MORPH_BLACKHAT, erode_kernel);
                        cv::imshow("The blackhated image", eroded_buffer);
                        break;
                    default:
                        cv::morphologyEx(image_buffer, eroded_buffer, cv::MORPH_GRADIENT, erode_kernel);
                        cv::imshow("The gradiented image", eroded_buffer);
                        break;
                    }

                    cv::waitKey(0);
                    cv::destroyAllWindows();
                }
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 20: {
        // Test case 20:
        bool re{ false };
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
                std::uint32_t kernel_size;
                cv::Mat cropped_buffer, blur_buffer, grayscale_buffer, boolean_buffer;
                std::string target_dir, out_path;
                time_t now_time = std::time(nullptr);
                std::cout << "Please assign the dir/path storing the (smoothed and) booleanized images, ended with \"\\\":\t";
                std::cin >> target_dir;
                out_path = std::string(target_dir) + std::string("smoothboolean_")
                    + std::to_string(now_time) + std::string(".jpg");

                std::cout << "Please assign the kernel size for blurring by media of pixels (3, 5, 7, 9, min(width, hight) otherwise): \t";
                std::cin >> kernel_size;

                if ((kernel_size != 3) && (kernel_size != 5) && (kernel_size != 7) && (kernel_size != 9)) {
                    if (image_buffer.cols > image_buffer.rows) {
                        kernel_size = image_buffer.rows;
                    } else {
                        kernel_size = image_buffer.cols;
                    }

                    if (kernel_size % 2 == 0) {
                        kernel_size--;
                    }
                }

                cv::imshow("Original image", image_buffer);
                cv::waitKey(0);
                cropped_buffer = image_buffer.colRange(56, 444).rowRange(50, 273);
                cv::medianBlur(cropped_buffer, blur_buffer, kernel_size);
                cv::imshow("Blurred image", blur_buffer);
                cv::waitKey(0);
                cv::cvtColor(blur_buffer, grayscale_buffer, cv::COLOR_BGR2GRAY);
                cv::threshold(grayscale_buffer, boolean_buffer, 128, 255, cv::THRESH_BINARY_INV);
                cv::imshow("Improved boolean image", boolean_buffer);
                cv::waitKey(0);
                cv::destroyAllWindows();
                cv::imwrite(out_path, boolean_buffer);
                std::cout << "image generate to " << out_path << " done!" << std::endl;
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 21: {
        // Test case 21:
        bool re{ false };
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
                std::uint32_t kernel_size{5};
                cv::Mat grayscale_buffer, blur_buffer, edge_buffer;
                std::string target_dir, out_path;
                time_t now_time = std::time(nullptr);
                std::cout << "Please assign the dir/path storing the edge images, ended with \"\\\":\t";
                std::cin >> target_dir;
                out_path = std::string(target_dir) + std::string("edge_")
                    + std::to_string(now_time) + std::string(".jpg");

                cv::imshow("Original image", image_buffer);
                cv::waitKey(0);
                cv::cvtColor(image_buffer, grayscale_buffer, cv::COLOR_BGR2GRAY);
                cv::GaussianBlur(grayscale_buffer, blur_buffer, cv::Size(kernel_size, kernel_size), 0.0, 0.0);
                cv::imshow("Blurred image", blur_buffer);
                cv::waitKey(0);
                cv::Canny(blur_buffer, edge_buffer, 210, 70);
                cv::imshow("Edged image", edge_buffer);
                cv::waitKey(0);
                cv::destroyAllWindows();
                cv::imwrite(out_path, edge_buffer);
                std::cout << "image generate to " << out_path << " done!" << std::endl;
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 22: {
        // Test case 22:
        bool re{ false };
        std::string first_file_name;
        std::cout << "Please input full path of first image: ";
        std::cin >> first_file_name;
        std::string second_file_name;
        std::cout << "Please input full path of second image: ";
        std::cin >> second_file_name;

        if (cv::haveImageReader(first_file_name) && cv::haveImageReader(second_file_name)) {
            cv::Mat image_buffer_01 = cv::imread(first_file_name);
            cv::Mat image_buffer_02 = cv::imread(second_file_name);

            if ((image_buffer_01.data == nullptr) ||
                (image_buffer_01.empty()) || 
                (image_buffer_02.data == nullptr) ||
                (image_buffer_02.empty())) {
                std::cerr << "The file is not readable for OpenCV!\t" << std::endl;
            }
            else {
                std::vector<std::pair<std::string, cv::Mat>> image_list;
                std::vector<double> blur_measurement;
                image_list.push_back(std::make_pair(first_file_name, image_buffer_01));
                image_list.push_back(std::make_pair(first_file_name, image_buffer_02));
                for (size_t i = 0; i < image_list.size(); i++) {
                    cv::Mat grayscale_buffer, lap_buffer, mean_buffer, stdev_buffer;
                    cv::cvtColor(image_list[i].second, grayscale_buffer, cv::COLOR_BGR2GRAY);
                    cv::Laplacian(grayscale_buffer, lap_buffer, CV_64F);
                    cv::meanStdDev(lap_buffer, mean_buffer, stdev_buffer);
                    auto blur_value = stdev_buffer.at<double>(0, 0);

                    std::cout << "The degree of blur:\t" << blur_value << "for " << image_list[i].first << "." << std::endl;
                    blur_measurement.push_back(blur_value);
                }

                if (blur_measurement[0] > blur_measurement[1]) {
                    std::cout << "The file is more blur:\t" << image_list[1].first << "." << std::endl;
                    cv::imshow("Original image", image_list[1].second);
                    cv::waitKey(0);
                } else {
                    std::cout << "The file is more blur:\t" << image_list[0].first << "." << std::endl;
                    cv::imshow("Original image", image_list[0].second);
                    cv::waitKey(0);
                }
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV" << std::endl;
        }
        break;
    }
    case 23: {
        // Test case 23:
        bool re{ false };
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
                std::uint32_t kernel_size{ 5 };
                cv::Mat grayscale_buffer, boolean_buffer;
                std::string target_dir, out_path;
                std::vector<std::vector<cv::Point_<int>>> contours;
                std::vector<cv::Vec<int, 4>> hierarchy;
                time_t now_time = std::time(nullptr);
                char filled;
                std::cout << "Please assign the dir/path storing the countour images, ended with \"\\\":\t";
                std::cin >> target_dir;
                out_path = std::string(target_dir) + std::string("countour_")
                    + std::to_string(now_time) + std::string(".jpg");
                std::cout << "Do you want the detected countour to be filled with predefined color? (Y for filled. Otherwise draw with thin line:\t";
                std::cin >> filled;
                cv::Mat dst_buffer = cv::Mat::zeros(image_buffer.rows, image_buffer.cols, CV_8UC3);

                cv::cvtColor(image_buffer, grayscale_buffer, cv::COLOR_BGR2GRAY);
                cv::threshold(grayscale_buffer, boolean_buffer, 128, 255, cv::THRESH_BINARY_INV);
                cv::findContours(boolean_buffer, contours, hierarchy, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_NONE);
                
                cv::imshow("Original image", image_buffer);
                cv::waitKey(0);

                if ((filled == 'Y') || (filled == 'y')) {
                    cv::drawContours(dst_buffer, contours, -1, cv::Scalar(255.0, 0.0, 255.0),
                      cv::LineTypes::FILLED, cv::LineTypes::LINE_AA, hierarchy);
                } else {
                    cv::drawContours(dst_buffer, contours, -1, cv::Scalar(255.0, 0.0, 255.0),
                        1, cv::LineTypes::LINE_AA, hierarchy);
                }

#ifndef NDEBUG
                for (auto c_it = contours.begin(); c_it != contours.end(); ++c_it) {
                    for (auto p_it = c_it->begin(); p_it != c_it->end(); ++p_it) {
                        std::cout << "The point:\t(" << p_it->x << ", " << p_it->y << ")" << std::endl;
                    }
                }
#endif // !NDEBUG

                cv::imshow("Contour image", dst_buffer);
                cv::waitKey(0);
                cv::imwrite(out_path, dst_buffer);
                std::cout << "image generate to " << out_path << " done!" << std::endl;
            }
        }
        else {
            std::cerr << "The file is not parsable for OpenCV:\t" << file_name << std::endl;
        }
        break;
    }
    case 24: {
        // Test case 24:

        std::string file_name;
        std::cout << "Please input full path of image file to be read for contour separation: \t";
        std::cin >> file_name;

        std::vector<std::pair<int, cv::Mat>> image_list;

        auto image_size = p206_commonUtil::splitContours(file_name, 40, 40, image_list);

        if (image_size > 0) {
            for (auto image : image_list) {
                cv::imshow("Extracted component", image.second);
                cv::waitKey(0);
                cv::destroyAllWindows();
            }
        }
        
        break;
    }
    case 25: {
        // Test case 25:

        std::string file_name;
        std::cout << "Please input full path of image file for extracting the EXIF metadata: \t";
        std::cin >> file_name;

        auto ret = p206_commonUtil::isJPEGwithEXIF(file_name);

        if (ret == ERRNO_EXIF_OK) {
            std::cout << "The file is EXIF-embedded JPEG file:\t" << file_name << std::endl;
        }
        break;
    }
    case 26: {
        // Test case 26:

        std::string file_name;
        std::cout << "Please input full path of image file for extracting the EXIF metadata: \t";
        std::cin >> file_name;

        auto ret = p206_commonUtil::isJPEGwithEXIF(file_name);

        if (ret == ERRNO_EXIF_OK) {
            std::ifstream binary_stream(file_name, std::ifstream::binary);
            auto image_exif = TinyEXIF::EXIFInfo(binary_stream);

            if (image_exif.Fields) {
                std::cout << "The resolution:\t" << image_exif.ImageWidth << " x " << image_exif.ImageHeight << "." << std::endl;
                std::cout << "The camera info:\t" << image_exif.Make << " " << image_exif.Model << "." << std::endl;

                if (image_exif.GeoLocation.hasLatLon()) {
                    std::cout << "The GEO location:\t" << image_exif.GeoLocation.Latitude << ", " << image_exif.GeoLocation.Longitude << "." << std::endl;
                } else {
                    std::cout << "The GEO location is NOT available" << std::endl;
                }
            }

            binary_stream.close();
        }
        break;
    }
    case 28: {
        // Test case 28:

        std::string file_name;
        std::cout << "Please input full path of vedio file for extracting the profile: \t";
        std::cin >> file_name;

        cv::VideoCapture video_obj(file_name, cv::CAP_ANY);

        if (video_obj.isOpened()) {
            auto w = video_obj.get(cv::CAP_PROP_FRAME_WIDTH);
            auto h = video_obj.get(cv::CAP_PROP_FRAME_HEIGHT);
            auto c = video_obj.get(cv::CAP_PROP_FRAME_COUNT);
            auto fps = video_obj.get(cv::CAP_PROP_FPS);
            auto frame_time = 1000.0 / fps;
            auto total_second = static_cast<std::uint32_t>(c / fps);

            std::cout << "The file name is opened as video:\t" << file_name << ":" << std::endl;
            std::cout << "\tThe backend decoding the video:\t" << video_obj.getBackendName() << "." << std::endl;
            std::cout << "\tThe resolution of the video:\t" << w << "X" << h << " pixels." << std::endl;
            std::cout << "\tThe length of the video:\t" << total_second / 60 << " mins and " << total_second %60 << " secs. Each frame spent "
              << frame_time << " ms." << std::endl;
        } else {
            std::cerr << "The specified file cannot be opened as video:\t" << file_name << "." << std::endl;
        }
        video_obj.release();
        break;
    }
    case 29: {
        // Test case 29:

        std::string file_name;
        std::cout << "Please input full path of vedio file for extracting the frame: \t";
        std::cin >> file_name;

        cv::VideoCapture video_obj(file_name, cv::CAP_ANY);

        if (video_obj.isOpened()) {
            auto c = video_obj.get(cv::CAP_PROP_FRAME_COUNT);
            auto fps = video_obj.get(cv::CAP_PROP_FPS);
            auto total_second = static_cast<std::uint32_t>(c / fps);
            std::uint32_t location{ 0 };
            cv::Mat current_frame;

            std::cout << "Please assign the location of frame to be extracted ( 0s to " << total_second - 1 << "s ):\t";
            std::cin >> location;

            if (location >= total_second) {
                std::cerr << "Oops! Invalid location of video:\t" << location << "s." << std::endl;
            } else {
                video_obj.set(cv::CAP_PROP_POS_FRAMES, location* fps);

                if (video_obj.read(current_frame)) {
                    cv::imshow("The specified frame", current_frame);
                    cv::waitKey(0);
                    video_obj.release();
                    cv::destroyAllWindows();
                }
                else {
                    std::cerr << "Oops! Error extracting the frame from the location of video!" << std::endl;
                }
            }
            
        }
        else {
            std::cerr << "The specified file cannot be opened as video:\t" << file_name << "." << std::endl;
        }
        video_obj.release();
        break;
    }
    case 30: {
        // Test case 30:
        std::uint32_t fps;
        std::uint32_t frame_time_multipler{ 1 };
        bool re{ true };

        std::string file_name;
        std::cout << "Please input full path of vedio file for play: \t";
        std::cin >> file_name;

        cv::VideoCapture video_obj(file_name, cv::CAP_ANY);

        if (video_obj.isOpened()) {
            fps = static_cast<std::uint32_t>(video_obj.get(cv::CAP_PROP_FPS));

            std::cout << "Please assign the speed playing the video (2=0.5 speed, 4=0.25 speed, mormal speed otherwise):\t";
            std::cin >> frame_time_multipler;

            if ((frame_time_multipler != 2) && (frame_time_multipler != 4)) {
                frame_time_multipler = 1;
            }
            
        }
        else {
            std::cerr << "The specified file cannot be opened as video:\t" << file_name << "." << std::endl;
        }

        while (video_obj.isOpened()) {
            cv::Mat current_frame;
            int current_key;
            re = video_obj.read(current_frame);

            if (re) {
                cv::imshow("Playing now", current_frame);
                current_key = cv::waitKey(1000 * frame_time_multipler / fps);

                if (current_key == 0x1b) break;
            } else {
                std::cerr << "Oops! Error extracting the frame from the location of video!" << std::endl;
            }
        }
        cv::destroyAllWindows();
        video_obj.release();
        break;
    }
    case 31: {
        // Test case 31:
        cv::VideoCapture video_read_obj;
        cv::VideoWriter video_write_obj;
        int api_preference = cv::CAP_FFMPEG;
        int fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
        std::time_t now_time = std::time(nullptr);
        double fps{ 0.0 };
        cv::Size frame_size;
        std::string file_path, target_dir, out_path;

        std::cout << "Please input full path of vedio file for cropping:\t";
        std::cin >> file_path;
        std::cout << "Please assign the directory for exporting the image file (end with \\):\t";
        std::cin >> target_dir;
        out_path = std::string(target_dir) + std::string("cropped_video_")
            + std::to_string(now_time) + std::string(".avi");
        video_read_obj = cv::VideoCapture(file_path, cv::CAP_ANY);
        fps = video_read_obj.get(cv::CAP_PROP_FPS);
        frame_size = cv::Size(static_cast<std::int32_t>(video_read_obj.get(cv::CAP_PROP_FRAME_WIDTH)),
          static_cast<std::int32_t>(video_read_obj.get(cv::CAP_PROP_FRAME_HEIGHT)));
        video_write_obj = cv::VideoWriter(out_path, api_preference, fourcc, fps, frame_size);

        if (video_read_obj.isOpened() && video_write_obj.isOpened()) {
            auto c = video_read_obj.get(cv::CAP_PROP_FRAME_COUNT);
            auto total_second = static_cast<std::uint32_t>(c / fps);
            std::uint32_t location{ 0 }, until{ 0 };
            cv::Mat current_frame;

            std::cout << "FPS rate = " << fps << "." << std::endl;

            std::cout << "Please assign the start frame to be copied ( 0s to " << total_second - 1 << "s ):\t";
            std::cin >> location;

            if (location >= total_second)
              location = 0;

            std::cout << "Please assign the end frame to be copied ( 0s to " << total_second - 1 << "s ):\t";
            std::cin >> until;

            if ((until >= total_second) || (until < total_second))
              until = total_second - 1;

            auto start_frame = static_cast<std::int32_t>(static_cast<double>(location) * fps);
            auto end_frame = static_cast<std::int32_t>(static_cast<double>(until) * fps);
            auto copy_iters = end_frame - start_frame;

            std::cout << "start_frame = " << start_frame << ", end_frame = " << end_frame << ", copy_iters = " << copy_iters << "." << std::endl;

            video_read_obj.set(cv::CAP_PROP_POS_FRAMES, start_frame);
            for (int i = 0; i < copy_iters; i++) {
                auto re = video_read_obj.read(current_frame);

                if (re) {
                    video_write_obj.write(current_frame);
                } else {
                    break;
                }
            }
            std::cout << "Totally " << copy_iters << " frames copied to " << out_path << "." << std::endl;
        } else {
            std::cerr << "At least video I/O stream can not be created!" << std::endl;
        }
        video_read_obj.release();
        video_write_obj.release();
        break;
    }
    case 32: {
        // Test case 32:
        std::string file_path, model_path;

        std::cout << "Please input full path of image file for face detection:\t";
        std::cin >> file_path;
        std::cout << "Please input full path for importing the pre-defined face detection model:\t";
        std::cin >> model_path;

        cv::CascadeClassifier x;

        if (x.load(model_path)) {
            if (cv::haveImageReader(file_path)) {
                cv::Mat image_buffer = cv::imread(file_path);

                if ((image_buffer.data == nullptr) ||
                    (image_buffer.empty())) {
                    std::cerr << "The file is not readable for OpenCV:\t" << file_path << std::endl;
                }
                else {
                    cv::Mat grayscale_buffer;
                    double scale_factor = 1.02;
                    int min_neighbor = 3;
                    int size_ceiling = 40;

                    std::cout << "Please define the scale factor:\t";
                    std::cin >> scale_factor;
                    std::cout << "Please define the min neighbor:\t";
                    std::cin >> min_neighbor;
                    std::cout << "Please define the minimum width of rect considered as NOISE:\t";
                    std::cin >> size_ceiling;

                    std::vector<cv::Rect> faces;
                    cv::cvtColor(image_buffer, grayscale_buffer, cv::COLOR_BGR2GRAY);
                    x.detectMultiScale(grayscale_buffer, faces, scale_factor, min_neighbor, 0,
                        cv::Size(size_ceiling, size_ceiling),
                        cv::Size(image_buffer.cols / 3, image_buffer.cols / 3));

                    for (auto it = faces.begin(); it != faces.end(); ++it)
                        cv::rectangle(image_buffer, *it, cv::Scalar(255, 0, 255), 2, cv::LINE_AA);

                    cv::imshow("finfing faces", image_buffer);
                    cv::waitKey(0);
                    cv::destroyAllWindows();
                    std::cout << "totally " << faces.size() << " faced detected. Bye" << std::endl;
                }
            }
        }
        break;
    }
    case 33: {
        // Test case 33:
        bool dataCollected = true;
        std::string sourceDir0, sourceDir1;
        std::vector<std::string> fileList0;
        std::vector<std::string> fileList1;

        std::vector<std::string> sourceDirs = { sourceDir0 , sourceDir1 };
        std::vector< std::vector<std::string> > fileLists = { fileList0, fileList1 };
        std::vector<cv::Mat> trainingSample;
        std::vector<int> trainingLabel;

        for (int i = 0; i != sourceDirs.size(); ++i) {
            bool ret;
            std::cout << "Please assign the " << i << "-th directory for exporting the image file (end with \"\\\"):\t";
            std::cin >> sourceDirs[i];
            ret = p201_commonUtil::getFileList(sourceDirs[i], fileLists[i]);

            if (!ret) {
                std::cerr << "Getting sample list failed from " << sourceDirs[i] << ".Bye~" << std::endl;
                dataCollected = false;
                break;
            }
            else {
                for (auto it = fileLists[i].begin(); it != fileLists[i].end(); ++it) {
                    std::cout << "Reading raw data from " << *it << std::endl;

                    if (!cv::haveImageReader(*it)) {
                        std::cerr << "The file is not parsable for openCV:\t" << *it << std::endl;
                    }
                    else {
                        cv::Mat image_buffer = cv::imread(*it);

                        if ((image_buffer.data == nullptr) || (image_buffer.empty())) {
                            std::cerr << "The file is not readable for openCV:\t" << *it << std::endl;
                        }
                        else {
                            cv::Mat grayscale_buffer;
                            cv::cvtColor(image_buffer, grayscale_buffer, cv::COLOR_BGR2GRAY);
                            trainingSample.push_back(grayscale_buffer);
                            trainingLabel.push_back(i);
                        }
                    }
                }
            }
        }

        if (dataCollected) {
            std::string modelDir, modelPath;
            std::time_t nowTime = std::time(nullptr);
#ifdef _DEBUG
            for (int j = 0; j != trainingLabel.size(); ++j) {
                std::cout << trainingLabel[j] << " -> ";
            }
            std::cout << std::endl;
#endif // _DEBUG

            std::cout << "Please assign the directory saving the trained face recognition model (end with \"\\\"):\t";
            std::cin >> modelDir;

            modelPath = std::string(modelDir) + std::string("facemodel_") + std::to_string(nowTime) + std::string(".xml");

            auto face_detecter_model = cv::face::LBPHFaceRecognizer::create();
            face_detecter_model->train(trainingSample, trainingLabel);
            face_detecter_model->write(modelPath);
            std::cout << "FACE Prediction model had been generated and saved to " << modelPath << "." << std::endl;
        }
        else {
            std::cerr << "FACE Prediction model generation failed owing to the data collection failed." << std::endl;
        }

        break;
    }
    case 34: {
        // Test case 34:
        std::string fileName, modelPath;
        std::cout << "Please assign the full path of image file for face detection:\t";
        std::cin >> fileName;
        std::cout << "Please assign the full path for importing the pre-defined face recognition model (end with *.modelFile):\t";
        std::cin >> modelPath;

        if (!cv::haveImageReader(fileName)) {
            std::cerr << "The file is not parsable for openCV:\t" << fileName << std::endl;
        }
        else {
            cv::Mat image_buffer = cv::imread(fileName);

            if ((image_buffer.data == nullptr) || (image_buffer.empty())) {
                std::cerr << "The file is not readable for openCV:\t" << fileName << std::endl;
            }
            else {
                cv::Mat grayscale_buffer;
                int prediction_label = 0;
                double prediction_confidence = 0.0;

                cv::cvtColor(image_buffer, grayscale_buffer, cv::COLOR_BGR2GRAY);

                auto face_detector_model = cv::face::LBPHFaceRecognizer::create();
                face_detector_model->read(modelPath);
                face_detector_model->predict(grayscale_buffer, prediction_label, prediction_confidence);

                std::cout << "My prediction:\tClass " << prediction_label << ". Confidence level = " << prediction_confidence << "." << std::endl;
            }
        }

        break;
    }
    default:
        break;
    }
}