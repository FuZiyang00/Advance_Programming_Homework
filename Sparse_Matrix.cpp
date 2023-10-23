#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class SparseMartrix{
    virtual ~SparseMatrix() = default;
    
    int getrow_n() const ;
    int getcolumn_n() const ;
    virtual int getnonzero_n() const = 0;
    virtual const double &operator()(int row, int col) const = 0;
    virtual double &operator()(const int &row, const int &col) const = 0;
    virtual vector<double> &operator*(const vector<double>& vec) const = 0;
    virtual void print() const=0;

    //MA KE TIPO DI SENSO ??
    //if (row >= n_row|| col >= n.col()){
    //   throw std::out_of_range("Bad index");
    //return ;}
    
    // :( :(c

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

}; 


>>>>>>> 378c9072cdcc4bba0a6abc275bba773628b357e1
