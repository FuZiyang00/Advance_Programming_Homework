#include <cmath>
#include <iostream>
#include <vector>
#include <tuple>
#include "Sparse_Matrix.hpp"

int main() {
    int rows_n, cols_n;
    std::cout<< "Select number of rows: "<< std::endl;
    std::cin>>rows_n;
    std::cout<< "Select number of cloumns: "<< std::endl;
    std::cin>>cols_n;
    
    SparseMatrixCSR* ptr = new SparseMatrixCSR(rows_n, cols_n);

    // tests
    std::cout<< "You generated a random sparse matrix: "<< std::endl;
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    std::cout<< "number of non_zero elements: "<< ptr->getnonzero_n()<< std::endl;
    const double read_element = (*ptr)(0,1); // must dereference the ptr before calling the operators
    std::cout << "constant element " << read_element << std::endl;
    std::cout << "non-constant element written: " << (*ptr) (1, 1) << std::endl;
    (*ptr)(1, 1) = 9;
    
    std::cout << "non-constant element written to " << (*ptr) (1, 1) << std::endl;
    ptr->print();
    
    // matrix-vector product tests 
    std::vector<double> v1(cols_n,0.0);
    v1[0]=1.0; // base e0 
    std::vector<double> v2(cols_n,1.0); 
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

