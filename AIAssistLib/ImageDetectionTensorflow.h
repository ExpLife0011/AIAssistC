#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<cmath>
#include <windows.h>
#include <Tlhelp32.h>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

#include "include/cppflow/cppflow.h"

#include "AssistConfig.h"
#include "ImageDetection.h"

using namespace cv;
using namespace std;
using namespace cuda;


// 基于Tensorflow的图像检测类
// 图像对象检查封装类，使用AI模型截取屏幕对象进行对象检测
class ImageDetectionTensorflow
{
public:
    ImageDetectionTensorflow();
    ~ImageDetectionTensorflow();
    void ReInit();

    void getScreenshot();
    DETECTRESULTS detectImg();
    cv::Mat getImg();

private:
    void initImg(); //初始化图像资源
    void releaseImg(); //释放图像资源

    void initDnn(); //初始化DNN资源

private:
    static AssistConfig* m_AssistConfig;

    //截屏图像数据相关属性
    HDC m_screenDC;
    HDC m_memDC;
    HBITMAP m_hBitmap;
    BITMAPINFO* m_Bitmapinfo = NULL;

    //存放图像数据的mat对象
    //注意opencv的函数使用这个对象时会自动调用create函数创建数据存放数组
    //在其他地方使用时，需要手动调用create申请内存创建数组；重复执行create函数不会导致重复创建数据存放数组；
    cv::Mat m_mat_src; //存放bitmap中获取的源图
    cv::Mat m_mat_3; //存放转换为3通道的图像

    cv::Mat img_mat;//模型检测图像数据


    //AI网络相关属性
    /*
    const string ConfigFile = "../../Data/model/mobilenet/ssd_mobilenet_v3_small.pbtxt";
    const string ModelFile = "../../Data/model/mobilenet/ssd_mobilenet_v3_small.pb";
    const string LabelFile = "../../Data/model/mobilenet/coco.names";
    */

    //模型目录
    const string ModelFile = "../../Data/model/tensorflow/efficientdet-lite0/";
    const string LabelFile = "../../Data/model/mobilenet/coco.names";

    /*
    const string ConfigFile = "../../Data/model/efficientdet/d0.pbtxt";
    const string ModelFile = "../../Data/model/efficientdet/d0.pb";
    const string LabelFile = "../../Data/model/efficientdet/coco.names";
    */

    vector<string> m_classLabels; //类标签
    const float MinConfidence = 0.60; //最小置信度
    const int PersonClassId = 1; //分类标签列表中 人类 的classid
    //cv::dnn::Net m_net;
    //使用专门的对象检测模型类
    cppflow::model* m_net = NULL;

};

