#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <sys/types.h>
#include <memory>
#include <stdexcept>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"
#include "opencv2/opencv.hpp"

#define clusterSize 4
#define maxImageAmount 300

using namespace std;
using namespace cv;

class GAVS
{
private:
	int fullCycleItterator = 0;
	int stitchCounter = 0;
	String inputBasePath = "";
	String inputPath = "";
	String outputBasePath = "";
	String outputPath = "";
	String tempFiles = "temp\\";
	String fileType = ".png";
	int amountOfFiles = 0;
	bool final = false;
	String errorCode = "";
	vector<Mat> imgs;
	Mat scan;
	
	
public:
	GAVS();
	int clusteredBuffer[(maxImageAmount / clusterSize) + 1][clusterSize];
	int stitch();
	String executeWinCommand(const char*);
		//getters
	String getBasePath();
	String getWorkingPath();
	String getErrorCode();
	int getAmountOfFiles();
		//setters
	void setInputBasePath(String);
	void setOutputBasePath(String);
	void setInputPath();
	void setOutputPath();
	void setNextLevel();

};