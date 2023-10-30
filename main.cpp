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
    std::cout<< "You generated a random sparse matrix: "<< std::endl;
    ptr->print();
    std::cout<< "Informations of the matrix: "<< std::endl;
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    std::cout<< "number of columns: "<< ptr->getcolumn_n()<< std::endl;
    std::cout<< "number of non_zero elements: "<< ptr->getnonzero_n()<< std::endl;
    const double read_element = (*ptr)(2,2); // must dereference the ptr before calling the operators
    std::cout << "Your element is " << read_element << std::endl;
    (*ptr)(2, 2) = 8;
    std::cout << "The element has been written to: " << (*ptr) (2, 2) << std::endl;
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

