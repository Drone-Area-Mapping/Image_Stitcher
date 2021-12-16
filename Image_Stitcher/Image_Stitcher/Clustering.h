#pragma once

#include <vector>
#include <utility>
#include <string>

using cluster = std::vector<int>;
using cluster_list = std::vector<cluster>;
using point = std::pair<double, double>;
using point_list = std::vector<point>;

constexpr int CHUNK_MAXSIZE = 4;

class Clustering
{
private:
	cluster_list clusters;
	point_list points;

public:
	Clustering() : clusters(), points() {}
	void readPoints(std::string filepath);
	void findClusters();
	cluster_list getClusters();
};