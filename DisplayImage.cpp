#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc,char** argv){
	if( argc!=2 ){
		cout<<"no hay imagen\n";
		return -1;
	}
	Mat image;
    image = imread( argv[1], 1 );
    if( !image.data ){
    	cout<<"no imagen data\n";
    	return -1;
    }
    namedWindow("Display Image",CV_WINDOW_AUTOSIZE);
    imshow("Display Image",image);
    waitKey(0);
    return 0;
}