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
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Use 'unsigned' for better compatibility
    //inputMatrix = std::vector<std::vector<double>>(rows_n, std::vector<double>(cols_n));

    row_idx.push_back(non_zeros); // Initialize row_idx with 0 for the first row

    for (int i = 0; i < rows_n; ++i) {
        for (int j = 0; j < cols_n; ++j) {
            double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
            if (randomValue > zeroThreshold) {
                // Generate a non-zero random double value if we meet the threshold
                //inputMatrix[i][j] = 1 + (std::rand() % 100);
                values.push_back(1 + (std::rand() % 100));
                columns.push_back(j);
                ++non_zeros;
            } else {
                //inputMatrix[i][j] = 0.0;
            }
        }
        row_idx.push_back(non_zeros); // Update row_idx for the current row
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

    for (int i = row_idx[row]; i < row_idx[row + 1]; i++) {
            if (columns[i] == col) {
                return values[i];
            }
        }
    // If the element is not found in the row, return 0
    static const double default_value = 0.0;
    return default_value;
}


//write operator override 
double &SparseMatrixCSR::operator()(const int row, const int col) { 
    if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
        throw std::out_of_range("Indices are out of bound"); // Out of bounds error raiser 
    }
    int insert_position = -1;
    for (int i = row_idx[row]; i < row_idx[row + 1]; i++) {
            if (columns[i] == col) {
                return values[i];
            }
            else if (columns[i]> col) {
                insert_position = i;
                break;
            }
        }
    for (int i = row + 1; i <= rows_n; i++) {row_idx[i]++;}
    columns.insert(columns.begin() + insert_position, col);
    values.insert(values.begin() + insert_position, 0.0);
    return values[insert_position];
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
    std::cout << "]" <<std::endl;
  
}

// Matrix printer 
void SparseMatrixCSR::print() const {
    std::cout << "["; // Start of the matrix
    for (int i = 0; i < rows_n; ++i) {
        std::cout << "[ "; // Start of the row
        int row_start = row_idx[i];
        int row_end = row_idx[i + 1];

        for (int j = 0; j < cols_n; ++j) {
            if (row_start < row_end && columns[row_start] == j) {
                // Print the non-zero element if it exists in the CSR data.
                std::cout << values[row_start];
                row_start++;
            } else {
                // Print 0 for missing elements 
                std::cout << 0.0;
            }
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

    std::cout << "The matrix is stored in a CSR format:"<< std::endl;

    // values array printer
    int values_size = values.size();
    std::cout << "Values:"; 
    std::cout << "[ ";
    for (int i = 0; i < values_size; ++i) {
        std::cout << values[i]; 
        if (i < values_size - 1) {
            std::cout << ",";
        }
    }    
    std::cout <<"]" << std::endl;

    // columns indexes printer
    std::cout << "Columns:"; 
    std::cout << "[ ";
    for (int i = 0; i < values_size; ++i) {
        std::cout << columns[i]; 
        if (i < values_size - 1) {
            std::cout << ",";
        }
    }    
    std::cout <<"]" << std::endl;

    // row pointers printer
    int rows_ptr_size = row_idx.size();
    std::cout << "Row_idx:"; 
    std::cout << "[ ";
    for (int i = 0; i < rows_ptr_size; ++i) {
        std::cout << row_idx[i]; 
        if (i < rows_ptr_size - 1) {
            std::cout << ",";
        }
    }    
    std::cout <<"]" << std::endl;
}

std::vector<std::vector<double>> SparseMatrixCSR::FormatConverter() const{

    std::vector<double> coo_values;
    std::vector<double> coo_row_indices;
    std::vector<double> coo_col_indices;
    int rows_size = row_idx.size();

    for (int i = 0; i < rows_size - 1; i++) {
        int row_start = row_idx[i];
        int row_end = row_idx[i + 1];

        for (int j = row_start; j < row_end; j++) {
            coo_values.push_back(static_cast<double>(values[j]));
            coo_row_indices.push_back(i);
            coo_col_indices.push_back(static_cast<double>(columns[j]));
        }
    }

    // Create a vector of vectors to store COO data
    std::vector<std::vector<double>> coo;
    coo.push_back(coo_values);
    coo.push_back(coo_row_indices);
    coo.push_back(coo_col_indices);

    return coo;
}