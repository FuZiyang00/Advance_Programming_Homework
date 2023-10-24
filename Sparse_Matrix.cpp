#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class SparseMartrix{
    virtual int getrow_n() const = 0;
    virtual int getcolumn_n() const = 0;
    virtual int getnonzero_n() const = 0;
    virtual const double &operator()(const int row, const int col) const = 0;
    virtual double &operator()(const unsigned int &row, const unsigned int &col) const = 0;
    virtual vector<double> &operator*(const vector<double>& vec) const = 0;
    virtual void print() const=0;

    virtual ~SparseMatrix() {
        delete[] array; //Qua ci va tipo l'array in entrata che va distrutto perchè alloca memoria dinamicamente
    }

};

class SparseMatrixCoo: public SparseMatrix{
    private:
        std::vector<std::vector<int>> inputMatrix; // input matrix
        std::vector<int> values;    // Non-zero elements
        std::vector<int> rows; // Rows indices
        std::vector<int> columns; // Column indices
        int rows_n;            // Number of rows
        int cols_n;            // Number of columns
        int non_zeros;          //Number of number of non-zero elements
    
    public:

    SparseMatrixCoo(const std::vector<std::vector<int>>& input) : inputMatrix(input){
        rows_n = input.size();
        cols_n = input[0].size();
        int non_zeros = 0; 

        for (int i=0; i<rows_n; ++i){
            rows.push_back(i);
            for (int j=0; j<cols_n; ++j){
                if (input[i][j] != 0){
                    values.push_back(input[i][j]);
                    columns.push_back(j);
                    ++non_zeros;
                }
            }

        }
    }
    int getrow_n() const override {return rows_n};
    int getcolumn_n() const override {return cols_n};
    int getnonzero_n() const override {return non_zeros};

};


class SparseMartrixCSR: public SparseMartrix{
     private: 
        std::vector<std::vector<int>> inputMatrix; // input matrix
        std::vector<int> values;    // Non-zero elements
        std::vector<int> row_idx; // Row pointers
        std::vector<int> columns; // Column indices
        int rows_n;            // Number of rows
        int cols_n;            // Number of columns
        int non_zeros;          //Number of number of non-zero elements

    public: 
        SparseMartrixCSR(const std::vector<std::vector<int>>& input) : inputMatrix(input) {
            rows_n = input.size();
            cols_n = input[0].size();
            int non_zeros = 0; 

            for (int i=0; i<rows_n; ++i){
                for (int j=0; j<cols_n; ++j){
                    if (input[i][j] != 0){
                        values.push_back(input[i][j]);
                        columns.push_back(j);
                        ++non_zeros;
                    }
                }
                row_idx.push_back(non_zeros);
            }

        }
        int getrow_n() const override {return rows_n};
        int getcolumn_n() const override {return cols_n};
        int getnonzero_n() const override {return non_zeros};
        
}; 


