
#include <iostream>
#include "clases/ToolKit.cpp"
using namespace std;

int main(int argc,char** argv){
    ToolKit tool;
	if( argc!=2 ){
		cout<<"no hay imagen\n";
		return -1;
	}
	Mat image=tool.readImage(argv[1],tool.gray);
    if( !image.data ){
    	cout<<"no imagen data\n";
    	return -1;
    }
    tool.writeImage(image,"hola.jpg");
    tool.createWindow("opencv",tool.normal);
    tool.showWindow("opencv",image);
    tool.pause();
    return 0;
}