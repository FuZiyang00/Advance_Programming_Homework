#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Sparse_Matrix.hpp"

SparseMatrixCSR::SparseMatrixCSR(int rows_n, int cols_n) : rows_n(rows_n), cols_n(cols_n) {
    non_zeros = 0;
    double zeroThreshold = 0.5; 
    // chatgpt: random seed to generate different random values each time the program runs
    std::srand(static_cast<unsigned>(std::time(nullptr))); 

    inputMatrix = std::vector<std::vector<double>>(rows_n, std::vector<double>(cols_n));

        for (int i = 0; i < rows_n; i++) {
            row_idx.push_back(non_zeros);
            for (int j = 0; j < cols_n; j++) {
                double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
                if (randomValue < zeroThreshold) {
                    // Set the value to zero if it's below the threshold
                    inputMatrix[i][j] = 0.0;
                } else {
                    // Generate a non-zero random double value
                    inputMatrix[i][j] = std::rand() % 100;
                    values.push_back(inputMatrix[i][j]);
                    columns.push_back(j);
                    ++non_zeros;
                }
            }
        }
        row_idx.push_back(row_idx.back() + 1);
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

// multiplication override 
//ref:https://www.it.uu.se/education/phd_studies/phd_courses/pasc/lecture-1
void SparseMatrixCSR::operator*(const std::vector<double>& vec)const{
    const int c = vec.size();
    if (c != cols_n) {
        throw std::out_of_range("Vector does not match"); // Out of bounds error raiser 
    }
    std::cout<< "matrix * vector = ";
    std::cout << "[";
    std::vector<double> result(rows_n,0.0);
    for (int i=0; i<rows_n; ++i){
        double sum = 0;
        for(int j=row_idx[i]; j<row_idx[i+1]; ++j){
            sum += values[j] * vec[columns[j]];
        }
        result[i] = sum;
        std::cout << result[i];
        if (i < rows_n - 1){
            std::cout <<",";
        }
    }
    std::cout << "]";
  
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



