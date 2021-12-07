#include "Main.h"
#define DEBUG

using namespace std;
using namespace cv;

vector<Mat> imgs;
//atomic<bool> exitProgram(false); // Declare atomic variable for multi-thread communication

int main(int argc, char* argv[])
{
    SocketSlave socket;
    JSONParser json;
    
    
    while (!socket.initialize())
    {
        cout << "establishing socket connection.....\n";
        this_thread::sleep_for(500ms);
    }


    while (true)
    {
        GAVS gavs;
        BlindCluster cluster;
        //--!!Code between this for testing purposes only!!--
        gavs.setInputBasePath("D:\\OneDrive - Avans Hogeschool\\Drone Area Mapping\\10. Example_data\\example_images4\\RGB\\");
        gavs.setOutputBasePath("D:\\Avans\\ProgramOutput\\");
        //--!!Code between this for testing purposes only!!--

        while (idle)
        {

            readBuffer = socket.returnline();
            if (readBuffer != "")
            {
                cout << readBuffer;
                cout << json.getDataTitle(readBuffer).c_str() << ":" << json.getDataValue(readBuffer).c_str() << "\n";
                if (json.getDataTitle(readBuffer) == "startProcessing")
                {
                    cout << "Initiating stitch!!!\n";
                    idle = false;
                    cluster.setTotalImages(15);
                    cluster.cluster();
                }
            }

        }
        while (!idle)
        {
            cout << "stitching " << cluster.getAmountOfClusters() << " clusters\n";
            //send back to gui status percentage: (currentCluster * (currentLayer + 1))/(totalClusters*(TotalLayers+1))
            for (int i = 0; i < cluster.getAmountOfClusters(); i++)
            {
                cout << "...\n";
                gavs.setCluster(cluster.getCluster());
            }
            if (cluster.getAmountOfClusters() == 1)
            {
                cout << "Final stitch detected!\n";
                idle = true;
            }
            else
            {
                cluster.nextLayer();
            }
            gavs.stitch();
            gavs.clearClusters();
            if (idle)cout << "Shouldn't loop again\n";
        }
    }
    

#ifdef DEBUG
    //exit(0);
#endif
}