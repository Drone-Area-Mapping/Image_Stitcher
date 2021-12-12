#include "Main.h"
#define DEBUG

using namespace std;
using namespace cv;
using json = nlohmann::json;

vector<Mat> imgs;
json progressJson;
//atomic<bool> exitProgram(false); // Declare atomic variable for multi-thread communication

int main(int argc, char* argv[])
{
    SocketSlave socket;
    //JSONParser json;
    
    
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
        //gavs.setInputBasePath("D:\\OneDrive - Avans Hogeschool\\Drone Area Mapping\\10. Example_data\\example_images4\\RGB\\");
        //gavs.setOutputBasePath("D:\\Avans\\ProgramOutput\\");
        //--!!Code between this for testing purposes only!!--

        while (idle)
        {

            readBuffer = socket.returnline();
            if (readBuffer != "")
            {
                cout << readBuffer;
                json j_complete = json::parse(readBuffer);
                cout << j_complete["name"];
                //cout << json.getDataTitle(readBuffer).c_str() << ":" << json.getDataValue(readBuffer).c_str() << "\n";
                if (j_complete["name"] == "startProcessing")
                {
                    cout << "Initiating stitch!!!\n";
                    gavs.setInputBasePath(j_complete["value"]["import"]);
                    gavs.setOutputBasePath(j_complete["value"]["export"]);
                    idle = false;
                    cluster.setTotalImages(15);
                    cluster.cluster();
                }
            }

        }
        while (!idle)
        {
            
            cout << "stitching " << cluster.getAmountOfClusters() << " clusters\n";
            cout << "stitching " << cluster.getAmountOfLayers() << " layers\n";
            tempDumbProgress++;
            progress = (tempDumbProgress/cluster.getAmountOfLayers())*100;
            progressJson["stitchProgress"] = progress;
            socket.write_line(progressJson.dump());
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
                tempDumbProgress = 0;
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