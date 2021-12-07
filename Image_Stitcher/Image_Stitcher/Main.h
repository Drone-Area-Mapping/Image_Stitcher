#include "SocketSlave.h"
#include "GAVS.h"
#include "JSONParser.h"
#include "BlindCluster.h"
#include <chrono>
#include <thread>


bool idle = true;
string inputPath = "";
string outputPath = "";
string readBuffer = "";
