#include <cmath>
#include <iostream>
#include <vector>
#include "Sparse_Matrix.hpp"

SparseMatrixCSR::SparseMatrixCSR(const std::vector<std::vector<double>>& input) : inputMatrix(input) {
    rows_n = input.size();
    cols_n = input[0].size();
    non_zeros = 0;

    for (int i = 0; i < rows_n; ++i) {
        for (int j = 0; j < cols_n; ++j) {
            if (input[i][j] != 0) {
                values.push_back(input[i][j]);
                columns.push_back(j);
                ++non_zeros;
            }
        }
        row_idx.push_back(non_zeros);
    }
}

int SparseMatrixCSR::getrow_n() const { return rows_n; }
int SparseMatrixCSR::getcolumn_n() const { return cols_n; }
int SparseMatrixCSR::getnonzero_n() const { return non_zeros; }

// Read-only operator override 
const double &SparseMatrixCSR::operator() (const int row, const int col) const {
    if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
        throw std::out_of_range("Indices are out of bound"); // Out of bounds error raiser 
    }
    return inputMatrix[row][col];
}

// write operator override 
double &SparseMatrixCSR::operator()(const int row, const int col) { 
    if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
        throw std::out_of_range("Indices are out of bound"); // Out of bounds error raiser 
    }
    return inputMatrix[row][col];
}

// Matrix printer 
void SparseMatrixCSR::print() const {
std::cout << "["; // Start of the matrix
for (int i = 0; i < rows_n; ++i) {
    std::cout << "[ "; // Start of the row
    for (int j = 0; j < cols_n; ++j) {
        std::cout << inputMatrix[i][j];
        if (j < cols_n - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]"; // End of the row
    if (i < rows_n - 1) {
        std::cout << "," << std::endl;
    }
}
std::cout << "]" << std::endl; // End of the matrix
}


// no ha senso cosa returno??
// std::tuple<std::vector<double>, std::vector<double>,std::vector<double>> to_COO(const SparseMatrixCSR csr){
//     int nrow =csr.getrow_n();
//     std::vector<double> rows_csr  = csr.row_idx(); //forse const
//     std::vector<double> rows_coo;
//     for (int i= 0; i < nrow-1; ++i ){
//         non_zero_row_i = rows_csr[i+1]-rows_csr[i];
//         while (non_zero_row_i>0){
//             rows_coo.push_back(i);
//             non_zero_row_i-=1;
//         }
//     }
//     return {csr.values(), csr.columns(), rows_coo} 
//     return SparseMatrixCOO(csr.rows_n(), csr.cols_n(), csr.values(), csr.columns(), rows_coo);

// }

