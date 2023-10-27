#include <cmath>
#include <iostream>
#include <vector>
#include "Sparse_Matrix.hpp"

int main() {
    std::vector<std::vector<double>> array{{0, 2, 5, 5}, 
                                           {9, 7.8, 0, 0},
                                           {10, 0, 0, 0}};
    
    SparseMatrix *ptr;
    ptr = new SparseMatrixCSR{array};
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    //SparseMatrixCSR csr2(array);
    //SparseMatrix* ptr2 =&csr2;
    //std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> ptr2->to_COO();
    const double read_element = (*ptr)(0,1); // must dereference the ptr before calling the operators
    std::cout << "constant element " << read_element << std::endl;
    (*ptr) (1, 1) = 9;
    std::cout << "non-constant element written to " << (*ptr) (1, 1) << std::endl;
    ptr->print();
    delete ptr;
    return 0;
}