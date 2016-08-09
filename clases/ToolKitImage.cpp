#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
class ToolKitImage{
/*
canales:
  CV_8UC3  {8 bits 3 canales}
  CV_8SC3,CV_16UC3,CV_16SC3,CV_32SC3,CV_32FC3,CV_64FC3

*/
public:
	int gray;
	int color;
	int unchanged;
	int autosize;
	int normal;
	ToolKitImage(){
		this->gray=CV_LOAD_IMAGE_GRAYSCALE;
		this->color=CV_LOAD_IMAGE_COLOR;
		this->unchanged=CV_LOAD_IMAGE_UNCHANGED;
		//*************************
		this->autosize=CV_WINDOW_AUTOSIZE;
		this->normal=CV_WINDOW_NORMAL;
		//*************************
	}
	//crear lienzo 
	Mat createImage(int cols,int rows,Scalar rgb){
		Mat img(cols,rows,CV_64FC3,rgb);
		return img;
	}//thickness=grozor
	//dibujar texto
	void drawText(Mat img,String text,int p_x,int p_y,int tpg,int size,Scalar color,int thickness){
		switch(tpg){
			case 2:
				putText( img,text,Point(p_x,p_y),FONT_HERSHEY_PLAIN,size,color,thickness );
			case 3:
				putText( img,text,Point(p_x,p_y),FONT_HERSHEY_DUPLEX,size,color,thickness );
			break;
			case 4:
				putText( img,text,Point(p_x,p_y),FONT_HERSHEY_COMPLEX,size,color,thickness );
			break;
			case 5:
				putText( img,text,Point(p_x,p_y),FONT_HERSHEY_TRIPLEX,size,color,thickness );
			break;
			case 6:
				putText( img,text,Point(p_x,p_y),FONT_HERSHEY_COMPLEX_SMALL,size,color,thickness );
			break;
			case 7:
				putText( img,text,Point(p_x,p_y),FONT_HERSHEY_SCRIPT_SIMPLEX,size,color,thickness );
			break;
			case 8:
				putText( img,text,Point(p_x,p_y),FONT_HERSHEY_SCRIPT_COMPLEX,size,color,thickness );
			break;
			default:
					putText( img,text,Point(p_x,p_y),FONT_HERSHEY_SIMPLEX,size,color,thickness );
			break;
		}
	}//dibujar circulo
	void drawCircle(Mat img,int pos_x,int pos_y,double radio,Scalar color,int thickness){
		circle( img,Point(pos_x,pos_y),radio,color,thickness );
	}
	//obtener color bgr
	Scalar getColor(int b,int g,int r){
		return Scalar(b,g,r);
	}//funcion sobrecarda para obtener color bgr
	Scalar getColor(int bgr){
		return Scalar::all(bgr);
	}
	//leer fichero tipo = color | gray | unchanged 
	Mat readImage(String pathfile,int tipo){
		return imread(pathfile,tipo);
	}
	//crear titulo de ventana y tamaño
	void createWindow(String title,int size){
		namedWindow(title,size);
	}
	//destruir ventana para liberar recursos
	void destroyWindow(String title){
		destroyWindow(title);
	}
	//mostrar ventana definidida pro titulo e imagen que mostrar
	void showWindow(String title,Mat image){
		imshow(title,image);
	}//convertir a gris imagen
	Mat convertToGray(Mat img){
		Mat gray;
		cvtColor(img,gray,CV_BGR2GRAY);
		return gray;
	}//escribir imagen en fichero
	void writeImage(Mat img,String pathfile){
		imwrite(pathfile,img);
	}//esperar pulsacion para cerrar ventana
	void pulseExit(){
		waitKey(0);
	}//difuminar x ey = impar positivo
	Mat gaussianBlur(Mat src,int x, int y,int desviacionX){
		Mat dst;
		GaussianBlur(src,dst,Point(x,y),desviacionX);
		return dst;
	}
	//desv = >1 e impar
	Mat medBlur(Mat src,int desv){
		Mat dst;
		medianBlur(src,dst,desv);
		return dst;
	}
	Mat erosion(Mat src,int krl){
		Mat dst;
		erode(src,dst,krl);
		return dst;
	}
	Mat dilatar(Mat src,int krl){
		Mat dst;
		dilate(src,dst,krl);
		return dst;
	}
	int countFace;
	Mat drawMarker(Mat src,vector<Rect> rect,int i,int linelong,String title="Marcador"){
		line( src,Point(rect[i].x,rect[i].y),Point(rect[i].x,rect[i].y+linelong),CV_RGB(0,255,0),3 );
    	line( src,Point(rect[i].x,rect[i].y),Point(rect[i].x+linelong,rect[i].y),CV_RGB(0,255,0),3 );
    		
    	line( src,Point(rect[i].x+rect[i].width,rect[i].y),Point(rect[i].x+rect[i].width,rect[i].y+linelong),CV_RGB(0,255,0),3 );
    	line( src,Point(rect[i].x+rect[i].width,rect[i].y),Point(rect[i].x+rect[i].width-linelong,rect[i].y),CV_RGB(0,255,0),3 );
    
    	line( src,Point(rect[i].x,rect[i].y+rect[i].height),Point(rect[i].x,rect[i].y+rect[i].height-linelong),CV_RGB(0,255,0),3 );	
    	line( src,Point(rect[i].x,rect[i].y+rect[i].height),Point(rect[i].x+linelong,rect[i].y+rect[i].height),CV_RGB(0,255,0),3 );	
    		
    	line( src,Point(rect[i].x+rect[i].width,rect[i].y+rect[i].height),Point(rect[i].x+rect[i].width-linelong,rect[i].y+rect[i].height),CV_RGB(0,255,0),3 );	     
    	line( src,Point(rect[i].x+rect[i].width,rect[i].y+rect[i].height),Point(rect[i].x+rect[i].width,rect[i].y+rect[i].height-linelong),CV_RGB(0,255,0),3 );	     
		int font= FONT_HERSHEY_DUPLEX;
    	Size s=getTextSize(title,font,1,1,0);
    	int x= (src.cols-s.width)/2;
    	int y=rect[i].y+s.height+5;
    	putText( src,title,Point(rect[i].x,rect[i].y-s.height),font,1,CV_RGB(0,255,0),1,CV_AA );
    	return src;
	}
	Mat detectFaceFront(Mat src){
		this->countFace=0;
		Mat gray,dst;
		gray=this->convertToGray(src);
		CascadeClassifier detector;
		if( !detector.load("clasificadores/lbpcascade_frontalface.xml") ) cout << "clasificador no existe"; 
		equalizeHist(gray,dst);	
		vector<Rect> rect;
		detector.detectMultiScale(dst,rect);
		int linelong=30;
		for(size_t i=0;i<rect.size();i++){
			this->countFace++;
		    //rectangle( src,Point(rect[i].x,rect[i].y),Point(rect[i].x+rect[i].width,rect[i].y+rect[i].height),CV_RGB(255,0,0),2 ); 
    		this->drawMarker( src,rect,i,15,"" );
		}
    	return src;
	}
	Mat detectEyes(Mat src){
		float eye_sx=0.16f;
		float eye_sy=0.26f;
		float eye_sw=0.30f;
		float eye_sh=0.28f;
		Mat gray,dst;
		CascadeClassifier dtface,dteyes;
		if( !dtface.load("clasificadores/haarcascade_frontalface_alt2.xml") ) cout << "no detector face";
		if( !dteyes.load("clasificadores/haarcascade_eye.xml") ) cout << "nodetector eyes";
		cvtColor(src,gray,CV_BGR2GRAY);
		equalizeHist(gray,dst);
		vector<Rect> rect;
		dtface.detectMultiScale(dst,rect,1.2,3,0,Size(60,60));
		for(size_t i=0;i<rect.size();i++){
		    cout <<"valor rect "<< rect[i]<< endl;
		   rectangle( src,Point(rect[i].x,rect[i].y),Point(rect[i].x+rect[i].width,rect[i].y+rect[i].height),CV_RGB(0,255,0),5 ); 
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
				rectangle(src, 
				Point(leye[0].x + leftx + rect[0].x, leye[0].y + topy + rect[0].y), 
				Point(leye[0].width + widthx + rect[0].x - 5, leye[0].height + heighty + rect[0].y), 
				CV_RGB(0,0,255), 2);
			}
			if( (int)reye.size()>0 ){
				rectangle(src, 
				Point(reye[0].x + rigthx + leftx + rect[0].x, reye[0].y + topy + rect[0].y), 
				Point(reye[0].width + widthx + rect[0].x + 5, reye[0].height + heighty + rect[0].y), 
				CV_RGB(0,0,255), 2);
			}
			return src;
		}
	}
	
};