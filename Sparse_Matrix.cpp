#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class SparseMartrix{
    virtual ~SparseMatrix() = default;
<<<<<<< HEAD
    virtual int getrow_n() const = 0;
    virtual int getcolumn_n() const = 0;
=======
    
    int getrow_n() const ;
    int getcolumn_n() const ;
>>>>>>> 5ba0e6217790a1efb4be7c18c1a53ed32df6b46d
    virtual int getnonzero_n() const = 0;
    virtual const double &operator()(const int row, const int col) const = 0;
    virtual double &operator()(const unsigned int &row, const unsigned int &col) const = 0;
    virtual vector<double> &operator*(const vector<double>& vec) const = 0;
    virtual void print() const=0;

};

<<<<<<< HEAD
class SparseMatrixCoo: public SparseMatrix{
    private:
    //const int col_n;
    //const int row_n;
    //vector<int>  col;
	//vector<int>  row;
    vector<vector<double>> mat;
    public:

    SparseMatrixCoo(vector<int>  col,vector<int>  row,vector<double>  v):col(col),row(row),v(v){}
    int getrow_n() const override { return mat.size();}
    int getcolumn_n() const override { return mat(0).size();}
    int getnonzero_n() const override {return (row_n * col_n)-v.size();}
    
};


class SparseMatrixCsr: public SparseMatrix{
    private:
    const int col;
	const int n_row;
    vector<double> v;
    public:
    int getrow_n() const override { return n_row; }
    int getcolumn_n() const override { return n_; }
        
};
=======
class SparseMartrixCOO: public SparseMartrix{
   
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


