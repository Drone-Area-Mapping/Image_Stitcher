#pragma once
#include "SocketSlave.h"
#include <playsoundapi.h>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <sys/types.h>
#include <memory>
#include <stdexcept>
#include "json.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"
#include "opencv2/opencv.hpp"

#define clusterSize 94
#define maxImageAmount 300
#define backgroundBlackLevel 15
#define maxItterationSafetyLimit 10

using namespace std;
using namespace cv;

class GAVS
{
private:
	int fullCycleItterator = 0;
	int stitchCounter = 0;
	int totalStitchCounter = 0;
	int clusterCounter = 0;
	String inputBasePath = "";
	String inputPath = "";
	String outputBasePath = "";
	String outputPath = "";
	String tempFiles = "temp\\";
	String inputFileType = ".jpg";
	String fileType = ".jpg";
	int amountOfFiles = 0;
	int totalAmountOfActions;
	bool final = false;
	String errorCode = "";
	String readBuffer = "";
	
	int clusters[maxImageAmount/4+1][clusterSize];

	Mat scan;
	Mat bgra;
	SocketSlave socket;
	
public:
	GAVS();
	int clusteredBuffer[(maxImageAmount / clusterSize) + 1][clusterSize];
	int stitch();
	String executeWinCommand(const char*);
	Mat backgroundRemover(Mat);
	void clearClusters();
	void updateProgress();
		//getters
	String getBasePath();
	String getWorkingPath();
	String getErrorCode();
	int getAmountOfFiles();
	bool getFinal();
	String getSocketLine();
		//setters
	void setInputBasePath(String);
	void setOutputBasePath(String);
	void setInputPath();
	void setOutputPath();
	bool setCluster(vector<int>);
	void setProgressInfo(SocketSlave, int);
};