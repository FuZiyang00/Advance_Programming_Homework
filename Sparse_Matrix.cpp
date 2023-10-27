#include <cmath>
#include <iostream>
#include <vector>
#include <tuple>
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

//write operator override 
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

// //ref:https://www.it.uu.se/education/phd_studies/phd_courses/pasc/lecture-1
std::vector<double> SparseMatrixCSR::operator*(const std::vector<double>& vec)const{
    if (vec.size() != cols_n) {
        throw std::out_of_range("Vector does not match"); // Out of bounds error raiser 
    }
    std::vector<double> result(rows_n,0.0);
    for (int i=0; i<rows_n; ++i){
        for(int j=row_idx[i]; j<row_idx[i+1]; ++j){
             result[i] += values[j] * vec[columns[j]];
        }
    }

    return result;
        
}

std::tuple<std::vector<double>, std::vector<int>,std::vector<int>> SparseMatrixCSR::to_COO()const{
    int nrow =rows_n;
    std::vector<int> rows_csr  = row_idx; //forse const
    std::vector<int> rows_coo;
    int non_zero_row_i;
    for (int i= 0; i < nrow-1; ++i ){
        non_zero_row_i = rows_csr[i+1]-rows_csr[i];
        while (non_zero_row_i>0){
            rows_coo.push_back(i);
            non_zero_row_i-=1;
        }
    }
    return std::make_tuple(values, columns, rows_coo);
   
}
