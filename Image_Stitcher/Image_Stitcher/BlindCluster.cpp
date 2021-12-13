#include "BlindCluster.h"
#include <numbers>

BlindCluster::BlindCluster()
{
	cout << "initiating temporary dumb clustering...\n";
}

BlindCluster::~BlindCluster()
{
	cout << "stopping DumbCluster\n";
}
void BlindCluster::cluster()
{
	
	bool clustering = true;
	int currentWorkingLayer = 0;
	float currentLayerClusterAmount;
	int currentLayerImageAmount = totalImages;
	currentLayerClusterAmount = ceil(currentLayerImageAmount / clusterSize);
	totalClusters[0] = currentLayerClusterAmount;
	cout << "New cluster layer: " << currentWorkingLayer << " contains " << currentLayerClusterAmount << " clusters\n";
	/*if ((currentLayerImageAmount % clusterSize) != 0) currentLayerClusterAmount = (currentLayerImageAmount / clusterSize) + 1;
	else currentLayerClusterAmount = (currentLayerImageAmount / clusterSize) + 1;*/
	while(clustering)
	{
		for (int x = 0; x < currentLayerClusterAmount; x++)
		{
			cout << "[";
			for (int i = 1; i < clusterSize+1; i++)
			{
				cout << (x * clusterSize) + i << " ";
				clusters[currentWorkingLayer][x].push_back((x * clusterSize) + i);
			}
			cout << "]\n";
		}
		currentLayerImageAmount = currentLayerClusterAmount;
		if (currentLayerImageAmount > 1)
		{
			currentLayerClusterAmount = ceil(currentLayerImageAmount / clusterSize);
			currentWorkingLayer++;
			cout << "---\nNew cluster layer: " << currentWorkingLayer << " contains " << currentLayerClusterAmount << " clusters \n";
			totalClusters[currentWorkingLayer] = currentLayerClusterAmount;
		}
		else
		{
			totalLayers = currentWorkingLayer + 1;
			cout << "clustering finished after " << totalLayers << " layers!\n";
			cout << "================================\n";
			clustering = false;
		}
	}
	
}
void BlindCluster::nextLayer()
{
	cout << "cluster layer incrementation\n";
	currentLayer++;
	currentCluster = 0;
};

void BlindCluster::setTotalImages(int amount)
{
	totalImages = amount;
};

vector<int> BlindCluster::getCluster()
{
	currentCluster++;
	return clusters[currentLayer][currentCluster - 1];
};
int BlindCluster::getAmountOfClusters()
{
	return totalClusters[currentLayer];
}
int BlindCluster::getAmountOfClusters(int layer)
{
	return totalClusters[layer];
}
int BlindCluster::getAmountOfLayers()
{
	return totalLayers;
}

