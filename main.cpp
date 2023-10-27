#include <cmath>
#include <iostream>
#include <vector>
#include "Sparse_Matrix.hpp"

int main() {
    std::vector<std::vector<double>> array{{0, 2, 5, 5}, 
                                           {9, 7.8, 0, 0},
                                           {10, 0, 0, 0}};

    std::vector<double> v{1,0,0,0};
    SparseMatrix *ptr;
    ptr = new SparseMatrixCSR{array};
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    const double read_element = (*ptr)(0,1); // must dereference the ptr before calling the operators
    std::cout << "constant element " << read_element << std::endl;
    (*ptr) (1, 1) = 9;
    std::cout << "non-constant element written to " << (*ptr) (1, 1) << std::endl;
    ptr->print();
    delete ptr;

    std::vector<std::vector<double>> array1{{1, 0, 3, 5}, 
                                           {9, 7.8, 0, 0},
                                           {10, 0, 0, 0}};
    auto csr2 = SparseMatrixCSR(array1);
    std::vector<double> vsota = csr2*v;
    std::cout << "Vector elements: ";
        for (const double& element : vsota) {
            std::cout << element << ", ";
                }
        std::cout << std::endl;
    //std::tuple< std::vector<double>, std::vector<int>, std::vector<int>> coo=csr.to_COO();

    return 0;
}

//ref:https://unstop.com/blog/how-to-print-a-vector-in-cpps