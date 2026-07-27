#include <iostream>
#include "server/OriginServer.h"
using namespace std;
int main()
{
    OriginServer origin;

    origin.addFile(File("image1.jpg",1200,"image"));
    origin.addFile(File("video.mp4",54000,"video"));
    origin.addFile(File("style.css",40,"css"));

    origin.displayFiles();
    cout << origin.hasFile("video.mp4") << endl;
    File f = origin.getFile("style.css");
    cout << f.name << endl;

    return 0;
}