#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;
namespace Utils {
    /**
     * Produces a ranking of indices based on a vector of scores
     * @param to_sort A vector of scores
     * @return A ranking such that the first value represents the index of the maximum value in to_sort
     */
    vector<size_t> GenerateRanking(vector<double> to_sort);

    /**
     * Given two rankings of the same size, return the Spearman correlation coefficient
     * @param rank1 The first ranking
     * @param rank2 The second ranking
     * @return A value between 0 (Inverse correlation) and 1 (Perfect correlation)
     */
    double SpearmanCorrelation(vector<size_t> rank1, vector<size_t> rank2);
}
