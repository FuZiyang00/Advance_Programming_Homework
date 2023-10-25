#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class SparseMatrix {
    // Getter Functions
    virtual int getrow_n() const = 0;
    virtual int getcolumn_n() const = 0;
    virtual int getnonzero_n() const = 0;
    // Operator assignments
    virtual const double &operator()(const int row, const int col) const = 0;
    virtual double &operator()(const int row, const int col) = 0;
    // Matrix printer 
    virtual void print() const = 0;
    // Destructor
};

class SparseMatrixCSR : public SparseMatrix {
private:
    std::vector<std::vector<double>> inputMatrix; // input matrix
    std::vector<double> values;    // Non-zero elements
    std::vector<int> row_idx; // Row pointers
    std::vector<int> columns; // Column indices
    int rows_n;            // Number of rows
    int cols_n;            // Number of columns
    int non_zeros;         // Number of non-zero elements

public:
    SparseMatrixCSR(const std::vector<std::vector<double>>& input) : inputMatrix(input) {
        rows_n = input.size();
        cols_n = input[0].size();
        non_zeros = 0;

        for (int i = 0; i < rows_n; ++i) {
            for (int j = 0; j < cols_n; ++j) {
                if (input[i][j] != 0) {
                    values.push_back(input[i][j]);
                    columns.push_back(j);
                    ++non_zeros;
                }
            }
            row_idx.push_back(non_zeros);
        }
    }

    virtual int getrow_n() const override { return rows_n; }
    virtual int getcolumn_n() const override { return cols_n; }
    virtual int getnonzero_n() const override { return non_zeros; }
    // Read-only operator override 
    virtual const double &operator() (const int row, const int col) const override {
        if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
            throw std::out_of_range("Indices are out of bound"); // Out of bounds error raiser 
        }
        return inputMatrix[row][col];
    }
    // write operator override 
    virtual double &operator()(const int row, const int col) override { 
        if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
            throw std::out_of_range("Indices are out of bound"); // Out of bounds error raiser 
        }
        return inputMatrix[row][col];
    }
    
    // Matrix printer 
    virtual void print() const override {
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
};

int main() {
    std::vector<std::vector<double>> array{{0, 2, 5, 5}, 
                                           {9, 7.8, 0, 0},
                                           {10, 0, 0, 0}};

    SparseMatrixCSR matrix(array);
    int rows = matrix.getrow_n();
    std::cout << "number of rows: " << rows << std::endl;
    const double n = matrix(1, 1);
    std::cout << "constant element " << n << std::endl;
    matrix(1, 1) = 9;
    std::cout << "non-constant element " << matrix(1, 1) << std::endl;
    matrix.print();
    return 0;
}
