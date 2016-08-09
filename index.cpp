
#include <iostream>
#include <typeinfo>
#include "clases/ToolKitImage.cpp"
#include "clases/ToolKitVideo.cpp"
using namespace std;

int main(int argc,char** argv){
    String filepath="";
    String title="Akasico";
    if(argc>=2) filepath=argv[1];
    //*************************
    if(filepath.compare("")!=0){
        cout << "imagen" << endl;
        ToolKitImage tool;
        Mat src,dst;
        src=tool.readImage(argv[1],tool.unchanged);
        dst=tool.detectFaceFront(src);
        tool.createWindow(title,tool.normal);
        tool.showWindow(title,src);
        tool.pulseExit();
    }
    else{
        cout << "video" << endl;
        ToolKitVideo vd;
        vd.playDetectFaceFrontAndEyes("Mi caracho");
    }
    return 0;
}