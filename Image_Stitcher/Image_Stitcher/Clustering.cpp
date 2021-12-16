#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <fstream>

#include "Clustering.h"

void Clustering::readPoints(std::string filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw "File couldn't be open.";
    }

    while (!file.eof()) {
        std::string x_str, y_str;

        std::getline(file, x_str, ',');
        std::getline(file, y_str, '\n');

        this->points.push_back({ std::stod(x_str), std::stod(x_str) });
    }
}

void Clustering::findClusters() {
    std::map<int, point> working_set;

    for (int i = 0, n = this->points.size(); i < n; i++)
        working_set[i] = this->points[i];

    while (working_set.size() > 0) {
        int n = working_set.size();

        // Calculate the relative distances

        std::map<double, int> distance_map;
        auto it = working_set.begin(), it_ = working_set.begin();

        for (int i = 0, n_ = working_set.size(); i < n_; i++, it_++) {
            double ax = it->second.first, ay = it->second.second,
                bx = it_->second.first, by = it_->second.second;
            double distance = sqrt(pow(bx - ax, 2) + pow(by - ay, 2));
            distance_map.insert({ distance, it_->first });
        }

        // Append the cluster and restrict the working set

        cluster cluster;

        std::for_each_n(distance_map.begin(), std::min(n, CHUNK_MAXSIZE), [&distance_map, &working_set, &cluster](auto pair) {
            cluster.push_back(pair.second);
            working_set.erase(pair.second);
            });

        this->clusters.push_back(cluster);
    }
}

cluster_list Clustering::getClusters() {
    return this->clusters;
}