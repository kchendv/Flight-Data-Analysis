#pragma once

#include <string>
#include <vector>
#include "Eigen/Core"

using std::string;
using std::vector;
using namespace Eigen;

class PageRank {
    public:
        /**
         * Constructor for PageRank generator
         *
         * @param dampen True if weight dampening should be applied
         */
        PageRank(bool dampen = true);

        /**
         * Loads the adjacency matrix for PageRank analysis
         *
         * @param adj_matrix A n*n Adjacency matrix
         */
        void LoadAdjacencyMatrix(vector<vector<double>> adj_matrix);

        /**
         * Generates the Page Rank ranking
         *
         * @return A vector of indices
         * sorted from highest to lowest Page Rank score
         */
        vector<size_t> GenerateRanking();

    private:
        const double kDampeningFactor = 0.85;
        const size_t kSteadyIterations = 100;
        bool dampen_;
        size_t dimension_;
        MatrixXd markov_matrix_;

        /**
         * Applies dampening to the stored Markov matrix
         */
        void DampenMarkovMatrix();

        /**
         * Calculates the steady state vector based on the stored Markov matrix
         *
         * @return The steady state vector
         */
        VectorXd SteadyState();
};