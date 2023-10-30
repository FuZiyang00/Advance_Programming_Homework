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
    std::cout<< "Informations of the matrix: "<< std::endl;
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    std::cout<< "number of columns: "<< ptr->getcolumn_n()<< std::endl;
    std::cout<< "number of non_zero elements: "<< ptr->getnonzero_n()<< std::endl;
    std::cout<< "Choose an element of the matrix i j: ";
    int i,j;
    std::cin>>i >> j;
    const double read_element = (*ptr)(i,j); // must dereference the ptr before calling the operators
    std::cout << "Your element is " << read_element << std::endl;
    std::cout << "Change element to (select number):";
    int number;
    std::cin>>number;
    (*ptr)(i, j) = number;
    
    std::cout << "The element was written to: " << (*ptr) (1, 1) << std::endl;
    ptr->print();
    ptr->print();
    
    // matrix-vector product tests 
    std::cout << "Matrix-vector product tests : " << std::endl;
    std::vector<double> v2(cols_n,1.0); 
    std::cout << "For vector={1,1,...,1}; ";
    (*ptr) * v2;
    std::cout << "Choose an idex of the base vector ei where i=(0,...,n_col-1); i= ";
    int index;
    std::cin>>index;
    std::vector<double> v1(cols_n,0.0);
    v1[index]=1.0; // base ei
    std::cout << "For vector=ei: ";
    (*ptr) * v1;
  
    
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

