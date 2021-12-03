#include "../include/Utils.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <map>
#include <cmath>

using std::map;

namespace Utils {
    vector<size_t> GenerateRanking(vector<double> to_sort) {
        // Code referenced :
        // https://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
        vector<size_t> indices(to_sort.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::stable_sort(indices.begin(), indices.end(),
            [&to_sort](size_t i1, size_t i2) {return to_sort[i1] > to_sort[i2];});
        return indices;
    }

    double SpearmanCorrelation(vector<size_t> rank1, vector<size_t> rank2) {
        map<size_t, int> rank_diff;
        int dimension = rank1.size();

        for (int i = 0; i < dimension; i++) {
            // If one rank not in map, add to map
            // If one rank already in map, find difference between ranks
            if (rank_diff.find(rank1[i]) == rank_diff.end()) {
                rank_diff[rank1[i]] = i;
            }
            else {
                rank_diff[rank1[i]] = i - rank_diff[rank1[i]];
            }

            if (rank_diff.find(rank2[i]) == rank_diff.end()) {
                rank_diff[rank2[i]] = i;
            }
            else {
                rank_diff[rank2[i]] = i - rank_diff[rank2[i]];
            }
        }

        double sum_diff = 0;
        for (auto it : rank_diff) {
            sum_diff += std::pow(it.second, 2);
        }
        return 1 - ((6 * sum_diff) / (dimension * (std::pow(dimension, 2) - 1)));
    }
}