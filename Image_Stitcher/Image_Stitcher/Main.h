#pragma once

#include "SocketSlave.h"
#include "GAVS.h"
#include "BlindCluster.h"

#include <chrono>
#include <thread>
#include "json.hpp"


bool idle = true;
string inputPath = "";
string outputPath = "";
string readBuffer = "";
int progress = 0;
int totalAmountOfActions = 0;
