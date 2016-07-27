#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
class ToolKit{
public:
	int gray;
	int color;
	int unchanged;
	
	int autosize;
	int normal;
	ToolKit(){
		this->gray=CV_LOAD_IMAGE_GRAYSCALE;
		this->color=CV_LOAD_IMAGE_COLOR;
		this->unchanged=CV_LOAD_IMAGE_UNCHANGED;
		this->autosize=CV_WINDOW_AUTOSIZE;
		this->normal=CV_WINDOW_NORMAL;
	}
	Mat readImage(String pathfile,int tipo){
		return imread(pathfile,tipo);
	}
	void createWindow(String title,int size){
		namedWindow(title,size);
	}
	void showWindow(String title,Mat image){
		imshow(title,image);
	}
	Mat convertToGray(Mat img){
		Mat gray;
		cvtColor(img,gray,CV_BGR2GRAY);
		return gray;
	}
	void writeImage(Mat img,String pathfile){
		imwrite(pathfile,img);
	}
	void pause(){
		waitKey(0);
	}
};