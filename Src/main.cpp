/**
 * @file main.cpp
 * @date 2022/2/18
 * @author L.S.
 * */
 
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
  const string input_image_path = "../Source/Image/input_image.jpg";
  const string output_image_path = "../Result/Image/output_image.jpg";
  const cv::Mat input_image = cv::imread(input_image_path);
  cv::Mat output_image;
  cv::Mat image_temp;
  cv::Mat image_erode, image_dilate, image_open, image_close, image_gradient, image_tophat, image_blackhat;
  cv::Mat image_kernel = getStructuringElement(MORPH_RECT, cv::Size(4, 4)); // 获取卷积核

  // 膨胀操作
  cv::dilate(input_image, image_dilate, image_kernel); // 膨胀操作

  // 腐蚀操作
  cv::erode(input_image, image_erode, image_kernel); // 腐蚀操作

  // 开运算：先腐蚀再膨胀，用来消除小物体
  cv::erode(input_image, image_temp, image_kernel); // 腐蚀操作
  cv::dilate(image_temp, image_open, image_kernel); // 膨胀操作
  cv::morphologyEx(input_image, image_open, MORPH_OPEN, image_kernel);

  // 闭运算：先膨胀再腐蚀，用于排除小型黑洞
  cv::dilate(input_image, image_temp, image_kernel); // 膨胀操作
  cv::erode(image_temp, image_close, image_kernel); // 腐蚀操作
  cv::morphologyEx(input_image, image_close, MORPH_CLOSE, image_kernel);

  cv::morphologyEx(input_image, image_gradient, MORPH_GRADIENT, image_kernel); // 梯度运算: 膨胀图与腐蚀图之差(轮廓描边)
  cv::morphologyEx(input_image, image_tophat, MORPH_TOPHAT, image_kernel); // 顶帽运算: 原图与开运算之差
  cv::morphologyEx(input_image, image_blackhat, MORPH_BLACKHAT, image_kernel); // 黑帽运算: 闭运算与原图之差

  output_image = image_gradient.clone();
  cv::imwrite(output_image_path, output_image);

  return 0;
}