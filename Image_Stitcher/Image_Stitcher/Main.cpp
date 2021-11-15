#include "Main.h"


using namespace std;
using namespace cv;

vector<Mat> imgs;


int main(int argc, char* argv[])
{
    gavs.setInputBasePath("D:\\OneDrive - Avans Hogeschool\\Drone Area Mapping\\10. Example_data\\NDVI\\test3\\test4\\");
    gavs.setOutputBasePath("D:\\Avans\\ProgramOutput\\");
    gavs.stitch();
    exit(0);
}

