#include "../include/PageRank.h"
#include "../include/Utils.h"

#include <iostream>
#include <numeric>
#include <algorithm>

PageRank::PageRank(bool dampen) : dampen_(dampen) {}

void PageRank::LoadAdjacencyMatrix(vector<vector<double>> adj_matrix) {
    dimension_ = adj_matrix.size();
    if (dimension_ <= 1) {
        throw std::invalid_argument("Adjacency matrix is too small (<= 1 elements)");
    }

    // Markov matrix is a N*N matrix
    // Initialized as adj_matrix transposed and with inverted weights  
    markov_matrix_ = MatrixXd(dimension_, dimension_);
    for (size_t row = 0; row < dimension_; row++) {
        for (size_t col = 0; col < dimension_; col++) {
            markov_matrix_(col, row) = (adj_matrix[row][col] == 0) ? 0 : 1 / adj_matrix[row][col];
        }
    }

    // Convert weights to proportion (0 <= x <= 1) of outgoing flights
    VectorXd column_sum;
    column_sum.noalias() = markov_matrix_.colwise().sum();
    for (size_t row = 0; row < dimension_; row++) {
        for (size_t col = 0; col < dimension_; col++) {
            if (column_sum[col] == 0) {
                markov_matrix_(row, col) = 1 / double(dimension_);
            }
            else {
                markov_matrix_(row, col) = markov_matrix_(row, col) / column_sum[col];
            }
        }
    }

    // Dampen weights if argument dampen_ is true
    if (dampen_) {
        DampenMarkovMatrix();
    }
}

vector<size_t> PageRank::GenerateRanking() {
    VectorXd page_rank_score = SteadyState();
    vector<double> page_rank_vector (page_rank_score.data(), page_rank_score.data() + page_rank_score.size());
    return Utils::GenerateRanking(page_rank_vector);
}

void PageRank::DampenMarkovMatrix() {
    for (size_t row = 0; row < dimension_; row++) {
        for (size_t col = 0; col < dimension_; col++) {
            markov_matrix_(row, col) =  kDampeningFactor * markov_matrix_(row, col)
                                        + (1 - kDampeningFactor) * (1 / double(dimension_));
        }
    }
}

VectorXd PageRank::SteadyState() {
    // Initialize initial state
    VectorXd state_vector;
    state_vector = VectorXd::Zero(dimension_);
    state_vector(0) = 1;


    // Find steady state through iterations of Markov
    for (size_t i = 0; i < kSteadyIterations; i++) {
        state_vector = markov_matrix_ * state_vector;
    }
    return state_vector;
}