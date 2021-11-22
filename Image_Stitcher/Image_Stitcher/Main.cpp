#include "Main.h"
#define DEBUG

using namespace std;
using namespace cv;

vector<Mat> imgs;


int main(int argc, char* argv[])
{
    gavs.setInputBasePath("D:\\OneDrive - Avans Hogeschool\\Drone Area Mapping\\10. Example_data\\example_images4\\RGB\\");
    gavs.setOutputBasePath("D:\\Avans\\ProgramOutput\\");

#ifdef DEBUG
    vector<int> cluster1;
    vector<int> cluster2;
    vector<int> cluster3;
    for (int i = 1; i <= 4; i++)
    {
        cluster1.push_back(i);
        cluster2.push_back(i + 5);
        cluster3.push_back(i + 10);

    };
    gavs.setCluster(cluster1);
    gavs.setCluster(cluster2);
    gavs.setCluster(cluster3);
    gavs.stitch();
    exit(0);
#endif

#ifndef DEBUG
    while (!gavs.getFinal())
    {
        bool fillingClusterBuffers = true;
        while (fillingClusterBuffers)
        {
            //fillingClusterBuffers = gavs.setCluster([INSERT GETCLUSTER FUNCTION HERE])
        }
        gavs.stitch();
        //INSERT CLUSTERFUNCTION.NEXTPHASE HERE
    }
#endif


    
    
}

