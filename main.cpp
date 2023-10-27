#include <cmath>
#include <iostream>
#include <vector>
#include <tuple>
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


std::cout << "*************************** "<<std::endl;
///matrix prova
    std::vector<std::vector<double>> array1{{1, 0, 3, 5}, 
                                           {9, 7.8, 0, 0},
                                           {10, 0, 0, 0}};
    auto csr2 = SparseMatrixCSR(array1);
csr2.print();
//multi prova
    std::vector<double> vsota = csr2*v;
    std::cout << "CSR*v: ";
        for (const double& element : vsota) {
            std::cout << element << ", ";
                }
        std::cout << std::endl;
//to COO prova
    std::tuple< std::vector<double>, std::vector<int>, std::vector<int>> coo=csr2.to_COO();
    std::cout << "convert to COO: ";
        std::cout << "values_COO: ";
        int size= std::get<0>(coo).size();
        for (const double& element : std::get<0>(coo)) {
            std::cout << element;
            if (size != 1){
                std::cout << ", ";
                size -=1;
                }
            }    
        std::cout << std::endl;

        std::cout << "columns_COO: ";
        int size_c= std::get<1>(coo).size();
        for (const int& element : std::get<1>(coo)) {
            std::cout << element;
            if (size_c != 1){
                std::cout << ", ";
                size_c -=1;
            }
        }
        std::cout << std::endl;

        std::cout << "rows_COO: ";
        int size_r= std::get<2>(coo).size();
        for (const int& element : std::get<2>(coo)) {
            std::cout << element;
            if (size_r != 1){
                std::cout << ", ";
                size_r -=1;
            }
        }
        std::cout << std::endl;
        
        
    return 0;
    }


//ref:https://unstop.com/blog/how-to-print-a-vector-in-cpps