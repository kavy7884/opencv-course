#include "p206_commonUtil.h"

bool comparePairs(const std::pair<int, cv::Mat>& a, const std::pair<int, cv::Mat>& b) {
    return a.first < b.first;
}

size_t p206_commonUtil::splitContours(const std::string file_path,
  const size_t height, const size_t width, std::vector<std::pair<int, cv::Mat>>& image_list) {
    if (cv::haveImageReader(file_path)) {
        cv::Mat image_buffer = cv::imread(file_path);
        if ((image_buffer.data == nullptr) || (image_buffer.empty())) {
            std::cerr << "[" << __func__ << ":" << __LINE__ << "]\tThe file is not parsable for OpenCV:\t" << file_path << std::endl;
        } else {
            cv::Mat grayscale_buffer, boolean_buffer;
            std::vector<std::vector<cv::Point_<int>>> contours;
            std::vector<cv::Vec<int, 4>> hierarchy;
            cv::cvtColor(image_buffer, grayscale_buffer, cv::COLOR_BGR2GRAY);
            cv::threshold(grayscale_buffer, boolean_buffer, 128, 255, cv::THRESH_BINARY_INV);
            cv::findContours(boolean_buffer, contours, hierarchy, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_NONE);

            for (const auto& contour : contours) {
                cv::Rect region = cv::boundingRect(contour);
                auto contour_part = boolean_buffer.rowRange(region.y, region.y + region.height)
                  .colRange(region.x, region.x + region.width);

                if ((width != 0) && (height != 0)) {
                    size_t part_size = static_cast<size_t>(contour_part.rows) + static_cast<size_t>(contour_part.cols);
                    size_t all_size = static_cast<size_t>(boolean_buffer.rows) + static_cast<size_t>(boolean_buffer.cols);
                    if ((part_size >= CONTOUR_SIZE_MULTIPLE_CEIL * (width + height)) && (part_size < CONTOUR_SIZE_MULTIPLE_ROOF * (all_size))) {
                        cv::Mat contour_resized;
                        cv::resize(contour_part, contour_resized,
                          cv::Size(static_cast<int>(width), static_cast<int>(height)));
                        image_list.push_back(std::make_pair(region.x, contour_resized));
                    }
                } else {
                    image_list.push_back(std::make_pair(region.x, contour_part));
                }

                std::sort(image_list.begin(), image_list.end(), comparePairs);
            }
        }
    } else {
        std::cerr << "[" << __func__ << ":" << __LINE__ << "]\tThe file is not parsable for OpenCV:\t" << file_path << std::endl;
    }
    return image_list.size();
}

std::uint8_t p206_commonUtil::isJPEGwithEXIF(const std::string file_path)
{
    const int parse_range = 10;
    char ipeg_header[parse_range];
    std::uint8_t ret{ ERRNO_EXIF_OK };
    std::ifstream ifs;
    ifs.open(file_path, std::ios::binary);

    if (ifs.fail()) {
        std::cerr << "[" << __func__ << ":" << __LINE__ << "]\tOpen the file failed:\t" << file_path << std::endl;
    }
    ifs.read(ipeg_header, parse_range);
    ifs.close();

#ifndef NDEBUG
    for (size_t i = 0; i < parse_range; i++) {
        std::cout << "[" << i << "]\t0x" << std::setw(2) << std::setfill('0') << std::hex;
        std::cout << static_cast<std::int16_t>(static_cast<std::uint8_t>(ipeg_header[i])) << std::dec << std::endl;
    }
#endif // !NDEBUG

    if ((static_cast<std::uint8_t>(ipeg_header[0]) != static_cast<std::uint8_t>(0xff)) ||
        (static_cast<std::uint8_t>(ipeg_header[1]) != static_cast<std::uint8_t>(0xd8))) {
        std::cerr << "[" << __func__ << ":" << __LINE__ << "]\tThe file is Not JPEG file:\t" << file_path << std::endl;
        return ERROR_EXIF_NOT_JPEG;
    }

    if ((static_cast<std::uint8_t>(ipeg_header[2]) != static_cast<std::uint8_t>(0xff)) ||
      (static_cast<std::uint8_t>(ipeg_header[3]) != static_cast<std::uint8_t>(0xe1)) ||
      (static_cast<std::uint8_t>(ipeg_header[6]) != static_cast<std::uint8_t>(0x45)) ||
      (static_cast<std::uint8_t>(ipeg_header[7]) != static_cast<std::uint8_t>(0x78)) ||
      (static_cast<std::uint8_t>(ipeg_header[8]) != static_cast<std::uint8_t>(0x69)) ||
      (static_cast<std::uint8_t>(ipeg_header[9]) != static_cast<std::uint8_t>(0x66))) {
        std::cerr << "[" << __func__ << ":" << __LINE__ << "]\tThe file is Not contain EXIF:\t" << file_path << std::endl;
        return ERROR_EXIF_NO_EXIF_IN_JPG;
    }

    return ret;
}
