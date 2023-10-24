#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class SparseMartrix{
    virtual ~SparseMatrix() = default;
    virtual int getrow_n() const = 0;
    virtual int getcolumn_n() const = 0;
    virtual int getnonzero_n() const = 0;
    virtual const double &operator()(const int row, const int col) const = 0;
    virtual double &operator()(const unsigned int row, const unsigned int col) const = 0;
    virtual vector<double> &operator*(const vector<double>& vec) const = 0;
    virtual void print() const=0;

};

class SparseMatrixCoo: public SparseMatrix{
    private:
        std::vector<std::vector<int>> inputMatrix; // input matrix
        std::vector<int> values;    // Non-zero elements
        std::vector<int> rows; // Rows indices
        std::vector<int> columns; // Column indices
        int rows_n;            // Number of rows
        int cols_n;            // Number of columns
    
    public:

    SparseMatrixCoo(const std::vector<std::vector<int>>& input) : inputMatrix(input){
        rows_n = input.size();
        cols_n = input[0].size();
        int non_zeros = 0; 

        for (int i=0; i<rows_n; ++i){
            for (int j=0, j<cols_n; ++j){
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
    double &operator()(const unsigned int &row, const unsigned int &col) const {
    }

};


class SparseMartrixCSR: public SparseMartrix{
     private: 
        std::vector<std::vector<int>> inputMatrix; // input matrix
        std::vector<int> values;    // Non-zero elements
        std::vector<int> row_idx; // Row pointers
        std::vector<int> columns; // Column indices
        int rows_n;            // Number of rows
        int cols_n;            // Number of columns

    public: 
        SparseMartrixCSR(const std::vector<std::vector<int>>& input) : inputMatrix(input) {
            rows_n = input.size();
            cols_n = input[0].size();
            int non_zeros = 0; 

            for (int i=0; i<rows_n; ++i){
                // aspetto di capire come aggiornare il row_idx
                for (int j=0, j<cols_n; ++j){
                    if (input[i][j] != 0){
                        values.push_back(input[i][j]);
                        colums.push_back(j);
                        ++non_zeros;
                    }
                }

            }

        }
        int getrow_n() const override {return rows_n};
        int getcolumn_n() const override {return cols_n};
        int getnonzero_n() const override {return non_zeros};
        
}; 


