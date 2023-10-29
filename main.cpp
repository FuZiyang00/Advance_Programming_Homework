#include <cmath>
#include <iostream>
#include <vector>
#include <tuple>
#include "Sparse_Matrix.hpp"

int main() {
    int rows_n, cols_n; 
    rows_n = 5;
    cols_n = 5;
    SparseMatrixCSR* ptr = new SparseMatrixCSR(rows_n, cols_n);
    // tests
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    const double read_element = (*ptr)(0,1); // must dereference the ptr before calling the operators
    std::cout << "constant element " << read_element << std::endl;
    std::cout << "non-constant element written: " << (*ptr) (1, 1) << std::endl;
    (*ptr)(1, 1) = 9;
    std::cout << "non-constant element written to " << (*ptr) (1, 1) << std::endl;
    ptr->print();
    // matrix-vector product tests 
    std::vector<double> v1{1,0,0,0,0}; // base
    std::vector<double> v2{1,1,1,1,1}; 
    (*ptr) * v2;
    
    // converter utility testing 
    std::vector<std::vector<double>> converter = ptr->FormatConverter();
    int iterator = converter[0].size();
    std::cout << "COO Matrix:" << std::endl;
    for (int i = 0; i < iterator; i++) {
        std::cout << "Value: " << converter[0][i]
                  << " Row: " << converter[1][i]
                  << " Column: " << converter[2][i] << std::endl;
    }
    delete ptr;
    return 0;
    }

