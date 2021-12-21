#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

#define clusterSize 94

using namespace std;

class BlindCluster
{
public:
	BlindCluster();
	~BlindCluster();
	void setTotalImages(int);
	vector<int> getCluster();
	int getAmountOfClusters();
	int getAmountOfClusters(int);
	int getAmountOfLayers();
	void nextLayer();
	void cluster();
	void reset();

private:
	int totalImages;
	int totalLayers;
	int totalClusters[10];
	int currentCluster = 0;
	int currentLayer = 0;
	vector<int> clusters[10][75];
	
};

