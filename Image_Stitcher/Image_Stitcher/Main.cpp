#include "Main.h"
#define DEBUG

using namespace std;
using namespace cv;

vector<Mat> imgs;


int main(int argc, char* argv[])
{
    gavs.setInputBasePath("D:\\OneDrive - Avans Hogeschool\\Drone Area Mapping\\10. Example_data\\example_images4\\RGB2\\");
    gavs.setOutputBasePath("D:\\Avans\\ProgramOutput\\");
    SocketClient socket;
    // Initialize threads
    thread inputThread(socket.getinput);
    thread outputThread(socket.getoutput);
    // Wait for the threads to shutdown after losing connection
    inputThread.join();
    outputThread.detach(); // Blocking thread, using detach to terminate the thread! This doesnt matter because main exits anyway.

    printf("[Main]: Closing connection with the server . . .");

    // cleanup
    // shutdown the connection since no more data will be sent
    socket.iResult = shutdown(ConnectSocket, SD_BOTH);
    if (socket.iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        //return 1;
    }
    closesocket(ConnectSocket);
    WSACleanup();
    //socket.logic();
#ifdef DEBUG
    vector<int> cluster1;
    vector<int> cluster2;
    vector<int> cluster3;
    
    //for (int i = 1; i <= 4; i++)
    //{
    //    cluster1.push_back(i);
    //    cluster2.push_back(i + 5);
    //    cluster3.push_back(i + 10);

    //};
    //cluster1.push_back(0);
    //cluster1.push_back(1);
    //cluster1.push_back(2);
    //gavs.setCluster(cluster1);
    //gavs.setCluster(cluster2);
    //gavs.setCluster(cluster3);
    //gavs.stitch();
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

