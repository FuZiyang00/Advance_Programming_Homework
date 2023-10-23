#include <cmath>
#include <iostream>
#include <vecctor>
using namespace std;

class SparseMartrix{
    virtual ~SparseMatrix() = default;
    
    const int n_col;
	const int n_row;
    vector<double> v;

    virtual int getrow_n() const = 0;
    virtual int getcolumn_n() const = 0;
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