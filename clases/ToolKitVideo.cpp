#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <sstream>
using namespace std;
using namespace cv;
class ToolKitVideo : public ToolKitImage {
private:
	String filepath;
	double fps;
	int delay;
	VideoCapture v;
public:
	double getFps(){return this->fps;}
	int getDelay(){return this->delay;}

	ToolKitVideo() : ToolKitImage(){
	}
	void streamFile(String filepath){
		VideoCapture vc(filepath);
		this->v=vc;
		this->fps=vc.get(CV_CAP_PROP_FPS);
		this->delay=1000/fps;
	}
	void streamCam(int device){
		VideoCapture vc(device);
		this->v=vc;
		this->fps=vc.get(CV_CAP_PROP_FPS);
		this->delay=1000/fps;
	}
	bool loadVideo(VideoCapture vc){
		return vc.isOpened();
	}
	void playDetectFaceFront(String title){
		namedWindow(title,CV_WINDOW_NORMAL);
		VideoCapture v;
		CascadeClassifier detector;
		if( !v.open(0) ) cout << "no camara";
		if( !detector.load("clasificadores/haarcascade_frontalface_alt2.xml") ) cout << "not found";
		while(true){
			Mat frame,gray,dst;
			v.read(frame);
			cvtColor(frame,gray,CV_BGR2GRAY);
			equalizeHist(gray,dst);
			vector<Rect> rect;
			int linelong=30;
			detector.detectMultiScale( dst,rect,1.2,3,0,Size(60,60) );
			for(size_t i=0;i<rect.size();i++){
			    drawMarker( frame,rect,i,30,"frontal" );
    		}
			imshow(title,frame);
			if(waitKey(50)>=0) break;
		}
	}
	void playDetectFaceFrontAndEyes(String title){
		float eye_sx=0.16f;
		float eye_sy=0.26f;
		float eye_sw=0.30f;
		float eye_sh=0.28f;
		namedWindow(title,CV_WINDOW_NORMAL);
		VideoCapture v;
		CascadeClassifier detector,dteyes;
		if( !v.open(0) ) cout << "no camara";
		if( !detector.load("clasificadores/lbpcascade_frontalface.xml") ) cout << "not found";
		if( !dteyes.load("clasificadores/haarcascade_eye.xml") ) cout << "nodetector eyes";
		while(true){
			Mat frame,gray,dst;
			v.read(frame);
			cvtColor(frame,gray,CV_BGR2GRAY);
			equalizeHist(gray,dst);
			vector<Rect> rect;
			detector.detectMultiScale( dst,rect,1.2,3,0,Size(60,60) );
			for(size_t i=0;i<rect.size();i++){
			   drawMarker( frame,rect,i,30,title );
    		}
    		if( rect.size()>0 ){
			Mat face=dst(rect[0]).clone();
			vector<Rect> leye,reye;
			int leftx=cvRound(face.cols*eye_sx);
			int topy=cvRound(face.rows*eye_sy);
			int widthx=cvRound(face.cols*eye_sw);
			int heighty=cvRound(face.rows*eye_sh);
			int rigthx= cvRound(face.cols*(1.0-eye_sx-eye_sw));
			
			Mat topleftofface=face(Rect(leftx,topy,widthx,heighty));
			Mat toprigthofface=face(Rect(rigthx,topy,widthx,heighty));
			
			dteyes.detectMultiScale(topleftofface,leye);
			dteyes.detectMultiScale(toprigthofface,reye);
			cout << "left" << (int)leye.size() << endl;
			if( (int)leye.size()>0 ){
				cout << "ojo izquierdo" << endl;
				rectangle(frame, 
				Point(leye[0].x + leftx + rect[0].x, leye[0].y + topy + rect[0].y), 
				Point(leye[0].width + widthx + rect[0].x + 5, leye[0].height + heighty + rect[0].y), 
				CV_RGB(0,255,0), 2);
			}
			if( (int)reye.size()>0 ){
				rectangle(frame, 
				Point(reye[0].x + rigthx + leftx + rect[0].x, reye[0].y + topy + rect[0].y), 
				Point(reye[0].width + widthx + rect[0].x + 5, reye[0].height + heighty + rect[0].y), 
				CV_RGB(0,255,0), 2);
			}
			}
			imshow(title,frame);
			if(waitKey(50)>=0) break;
		}
	}
	void play(String title){
		while(true){
			Mat frame;
			this->v.read(frame);
			namedWindow(title,CV_WINDOW_NORMAL);
			Mat t=detectFaceFront(frame);
			imshow(title,t);
			if(waitKey(50)>=0) break;
		}
	}
	void playRecord(String filepath){
		VideoWriter wtr( filepath,CV_FOURCC('M','J','P','G'),30,Size(640,480) );
		while(true){
			Mat frame;
			this->v.read(frame);
			wtr.write(frame);
			namedWindow("webcam",CV_WINDOW_NORMAL);
			imshow("webcam",frame);
			if(waitKey(50)>=0) break;
		}
		wtr.release();
	}
	void playCanny(String title){
		while(true){
			Mat frame,gray,blur,edge;
			this->v.read(frame);
			cvtColor(frame,gray,CV_BGR2GRAY);
			GaussianBlur(gray,blur,Size(7,7),1.5,1.5);
			Canny(blur,edge,0,20,3);
			namedWindow(title,CV_WINDOW_NORMAL);
			imshow(title,edge);
			if(waitKey(50)>=0) break;
		}
	}


};