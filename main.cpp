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
    
    std::cout<<"Let's test before the COO Sparse Matrix"<<std::endl;
    SparseMatrixCOO* aaa = new SparseMatrixCOO(rows_n,cols_n);

    //Preliminary test of COO features:
    std::cout<< "You generated a random sparse matrix: "<< std::endl;
    aaa->print();
    std::cout<< "Informations of the matrix: "<< std::endl;
    std::cout<< "number of rows: "<< aaa->getrow_n()<< std::endl;
    std::cout<< "number of columns: "<< aaa->getcolumn_n()<< std::endl;
    std::cout<< "number of non_zero elements: "<< aaa->getnonzero_n()<< std::endl;
    std::cout<< "Choose an element of the matrix i j: ";
    int i,j;
    std::cin>>i >> j;
    const double read_element = (*aaa)(i,j); // must dereference the aa before calling the operators
    std::cout << "Your element is " << read_element << std::endl;
    std::cout << "Change element to (select number):";
    int number;
    std::cin>>number;
    (*aaa)(i, j) = number;
    std::cout << "The element was written to: " << (*aaa) (i, j) << std::endl;
    aaa->print();

    // matrix-vector product tests for COO 
    std::cout << "Matrix-vector product tests : " << std::endl;
    std::vector<double> v2(cols_n,1.0); 
    std::cout << "For vector={1,1,...,1}; ";
    (*aaa) * v2;
    std::cout << "Choose an idex of the base vector ei where i=(0,...,n_col-1); i= ";
    int index;
    std::cin>>index;
    std::vector<double> v1(cols_n,0.0);
    v1[index]=1.0; // base ei
    std::cout << "For vector=ei: ";
    (*aaa) * v1;

    //Convert from COO to CSR test
    std::vector<std::vector<double>> converter = aaa->FormatConverter();
    int iterator = converter[0].size();
    int iterator1= converter[2].size();
    std::cout << "CSR Matrix:" << std::endl;
    for (int i = 0; i < iterator; i++) {
        std::cout << "Value: " << converter[0][i]
                  << " Column: " << converter[1][i];
        if (i<iterator1)
        {
            std::cout <<" Row Cumulative: " << converter[2][i] << std::endl;
        }
        else
        {
           std::cout<<std::endl;
        }
        
    }

    delete aaa;

    // SPARSE MATRIX WITH CSR

    std::cout<<"Let's test now with CSR Sparse Matrix"<<std::endl;
    SparseMatrixCSR* ptr = new SparseMatrixCSR(rows_n, cols_n);

    //Preliminary test of CSR features:
    std::cout<< "You generated a random sparse matrix: "<< std::endl;
    ptr->print();
    std::cout<< "Informations of the matrix: "<< std::endl;
    std::cout<< "number of rows: "<< ptr->getrow_n()<< std::endl;
    std::cout<< "number of columns: "<< ptr->getcolumn_n()<< std::endl;
    std::cout<< "number of non_zero elements: "<< ptr->getnonzero_n()<< std::endl;
    std::cout<< "Choose an element of the matrix i j: ";
    std::cin>>i >> j;
    const double read_element1 = (*ptr)(i,j); // must dereference the ptr before calling the operators
    std::cout << "Your element is " << read_element1 << std::endl;
    std::cout << "Change element to (select number):";
    std::cin>>number;
    (*ptr)(i, j) = number;
    std::cout << "The element was written to: " << (*ptr) (1, 1) << std::endl;
    ptr->print();

    // matrix-vector product tests for CSR
    std::cout << "Matrix-vector product tests : " << std::endl;
    std::vector<double> vv2(cols_n,1.0); 
    std::cout << "For vector={1,1,...,1}; ";
    (*ptr) * vv2;
    std::cout << "Choose an idex of the base vector ei where i=(0,...,n_col-1); i= ";
    std::cin>>index;
    std::vector<double> vv1(cols_n,0.0);
    vv1[index]=1.0; // base ei
    std::cout << "For vector=ei: ";
    (*ptr) * vv1;

    // converter from CSR to COO test 
    std::vector<std::vector<double>> converter1 = ptr->FormatConverter();
    iterator = converter1[0].size();
    std::cout << "COO Matrix:" << std::endl;
    for (int i = 0; i < iterator; i++) {
        std::cout << "Value: " << converter1[0][i]
                  << " Row: " << converter1[1][i]
                  << " Column: " << converter1[2][i] << std::endl;
    }
    delete ptr;


    return 0;
    }

