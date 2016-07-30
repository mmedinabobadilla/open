
#include <iostream>
#include "clases/ToolKitImage.cpp"
#include "clases/ToolKitVideo.cpp"
using namespace std;

int main(int argc,char** argv){
    String path="";
    if(argc!=2){
        path=argv[1];
    }else return -1;
    ToolKitVideo video;
    String title="matias";
    cout << path <<endl;
    return 0;
}