#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP
#include <vector>

class SparseMatrix {
public:
    virtual int getrow_n() const = 0;
    virtual int getcolumn_n() const = 0;
    virtual int getnonzero_n() const = 0;
    virtual const double &operator()(const int row, const int col) const = 0;
    virtual double &operator()(const int row, const int col) = 0;
    //virtual std::vector<double> &operator*(const std::vector<double>& vec);
    virtual void print() const = 0;
    virtual ~SparseMatrix() {} // Virtual destructor
};

class SparseMatrixCSR : public SparseMatrix {
public:
    SparseMatrixCSR(const std::vector<std::vector<double>>& input);
    int getrow_n() const override;
    int getcolumn_n() const override;
    int getnonzero_n() const override;
    const double &operator()(const int row, const int col) const override;
    double &operator()(const int row, const int col) override;
    //std::vector<double> &operator*(const std::vector<double>& vec);
    void print() const override;

    std::tuple<std::vector<double>, std::vector<int>, std::vector<int>> to_COO()const;



private:
    std::vector<std::vector<double>> inputMatrix; // input matrix
    std::vector<double> values;    // Non-zero elements
    std::vector<int> row_idx; // Row pointers
    std::vector<int> columns; // Column indices
    int rows_n;            // Number of rows
    int cols_n;            // Number of columns
    int non_zeros;         // Number of non-zero elements
};

#endif