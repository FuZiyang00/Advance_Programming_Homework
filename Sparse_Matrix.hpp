#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP
#include <vector>
#include <tuple>

class SparseMatrix {
public:
    virtual int getrow_n() const = 0;
    virtual int getcolumn_n() const = 0;
    virtual int getnonzero_n() const = 0;
    virtual const double &operator()(const int row, const int col) const = 0;
    virtual double &operator()(const int row, const int col) = 0;
    virtual void operator*(const std::vector<double>& vec)const=0;
    virtual void print() const = 0;
    virtual std::vector<std::vector<double>> FormatConverter() const = 0;
    virtual ~SparseMatrix() {} // Virtual destructor
};

class SparseMatrixCSR : public SparseMatrix {
public:
    SparseMatrixCSR(int rows_n, int cols_n);
    int getrow_n() const override;
    int getcolumn_n() const override;
    int getnonzero_n() const override;
    const double &operator()(const int row, const int col) const override;
    double &operator()(const int row, const int col) override;
    void operator*(const std::vector<double>& vec) const override;
    void print() const override;
    std::vector<std::vector<double>> FormatConverter() const override;

private:
    std::vector<double> values;    // Non-zero elements
    std::vector<int> row_idx; // Row pointers
    std::vector<int> columns; // Column indices
    int rows_n;            // Number of rows
    int cols_n;            // Number of columns
    int non_zeros;         // Number of non-zero elements
};

class SparseMatrixCOO : public SparseMatrix {
public:
    SparseMatrixCOO(int rows_n, int cols_n);
    int getrow_n() const override;
    int getcolumn_n() const override;
    int getnonzero_n() const override;
    const double &operator()(const int row, const int col) const override;
    double &operator()(const int row, const int col) override;
    void operator*(const std::vector<double>& vec) const override;
    void print() const override;
    std::vector<std::vector<double>> FormatConverter() const override;

private:
    std::vector<std::vector<double>> inputMatrix; // input matrix
    std::vector<double> values;    // Non-zero elements
    std::vector<int> rows; // Rows indices
    std::vector<int> columns; // Column indices
    int rows_n;            // Number of rows
    int cols_n;            // Number of columns
    int non_zeros;         // Number of non-zero elements
};

#endif