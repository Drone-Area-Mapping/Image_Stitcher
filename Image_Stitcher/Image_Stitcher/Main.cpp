#include "Main.h"


using namespace std;
using namespace cv;

vector<Mat> imgs;


int main(int argc, char* argv[])
{
    gavs.setInputBasePath("D:\\OneDrive - Avans Hogeschool\\Drone Area Mapping\\10. Example_data\\NDVI\\test3\\test4\\");
    gavs.setOutputBasePath("D:\\Avans\\ProgramOutput\\");
    vector<int> cluster1;
    vector<int> cluster2;
    for (int i = 1; i <= 4; i++)
    {
        cluster1.push_back(i);
        cluster2.push_back(i + 1);
    };
    gavs.setCluster(cluster1);
    gavs.setCluster(cluster2);
    gavs.stitch();
    exit(0);
}

