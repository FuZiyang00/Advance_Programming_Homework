#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Sparse_Matrix.hpp"

SparseMatrixCSR::SparseMatrixCSR(int rows_n, int cols_n) : rows_n(rows_n), cols_n(cols_n) {
    non_zeros = 0;
    double zeroThreshold = 0.5;
    // chatgpt: random seed to generate different random values each time the program runs
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Use 'unsigned' for better compatibility
    row_idx.push_back(non_zeros); // Initialize row_idx with 0 for the first row

    for (int i = 0; i < rows_n; ++i) {
        for (int j = 0; j < cols_n; ++j) {
            double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
            if (randomValue > zeroThreshold) {
                // Generate a non-zero random double value if we meet the threshold
                values.push_back(1 + (std::rand() % 100)); // +1 because then the range becomes [1,100)
                columns.push_back(j);
                ++non_zeros;
            } 

        }
        row_idx.push_back(non_zeros); // Update row_idx for the current row
    }
}

int SparseMatrixCSR::getrow_n() const { return rows_n; }
int SparseMatrixCSR::getcolumn_n() const { return cols_n; }
int SparseMatrixCSR::getnonzero_n() const { return non_zeros; }

// Read-only operator override 
const double &SparseMatrixCSR::operator() (const int row, const int col) const {
    if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
        throw std::out_of_range("Indices are out of bound"); // Out of bounds error raiser 
    }

    for (int i = row_idx[row]; i < row_idx[row + 1]; i++) {
        if (columns[i] == col) {
            return values[i];
        }
    }
    // If the element is not found in the row, return 0
    static const double default_value = 0.0;
    return default_value;
}


//write operator override 
double &SparseMatrixCSR::operator()(const int row, const int col) { 
    if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
        throw std::out_of_range("Indices are out of bound"); // Out of bounds error raiser 
    }
    int insert_position;

    // Find the appropriate position to insert or locate the value at (row, col)
    for (int i = row_idx[row]; i < row_idx[row + 1]; i++) {
        if (columns[i] == col) {
            return values[i]; // Return the value if it already exists at (row, col)
        }
        else if (columns[i]> col) {
            insert_position = i; // Set the position for new insertion
            break;// Stop the loop once the correct position is found
        }
    }
    for (int i = row + 1; i <= rows_n; i++) {row_idx[i]++;} // Increment row indices for subsequent rows
    columns.insert(columns.begin() + insert_position, col);
    values.insert(values.begin() + insert_position, 0.0);
    return values[insert_position]; // Return the reference to the inserted value
}

// multiplication override 
//ref:https://www.it.uu.se/education/phd_studies/phd_courses/pasc/lecture-1
void SparseMatrixCSR::operator*(const std::vector<double>& vec)const{
    const int c = vec.size(); // Check if the vector dimensions match the matrix
    if (c != cols_n) {
        throw std::out_of_range("Vector does not match"); // Out of bounds error raiser 
    }
    std::cout<< "matrix * vector = ";
    std::cout << "[";
    std::vector<double> result(rows_n,0.0);  // Initialize the result vector to store matrix-vector product
    
    // Multiply the matrix by the vector
    for (int i=0; i<rows_n; ++i){
        double sum = 0;
        for(int j=row_idx[i]; j<row_idx[i+1]; ++j){
            sum += values[j] * vec[columns[j]]; // Perform the dot product of the matrix row and the vector
        }
        result[i] = sum;// Store the resulting value in the result vector
        std::cout << result[i]; // Output the result element
        if (i < rows_n - 1){
            std::cout <<",";
        }
    }
    std::cout << "]" <<std::endl;
  
}

// Matrix printer 
void SparseMatrixCSR::print() const {
    std::cout << "["; // Start of the matrix
    for (int i = 0; i < rows_n; ++i) {
        std::cout << "[ "; // Start of the row
        int row_start = row_idx[i];
        int row_end = row_idx[i + 1];

        for (int j = 0; j < cols_n; ++j) {
            if (row_start < row_end && columns[row_start] == j) {
                // Print the non-zero element if it exists in the CSR data.
                std::cout << values[row_start];
                row_start++;
            } else {
                // Print 0 for missing elements 
                std::cout << 0.0;
            }
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
    std::cout << "The matrix is stored in a CSR format:"<< std::endl;

    // values array printer
    int values_size = values.size();
    std::cout << "Values:"; 
    std::cout << "[ ";
    for (int i = 0; i < values_size; ++i) {
        std::cout << values[i]; 
        if (i < values_size - 1) {
            std::cout << ",";
        }
    }    
    std::cout <<"]" << std::endl;

    // columns indexes printer
    std::cout << "Columns:"; 
    std::cout << "[ ";
    for (int i = 0; i < values_size; ++i) {
        std::cout << columns[i]; 
        if (i < values_size - 1) {
            std::cout << ",";
        }
    }    
    std::cout <<"]" << std::endl;

    // row pointers printer
    int rows_ptr_size = row_idx.size();
    std::cout << "Row_idx:"; 
    std::cout << "[ ";
    for (int i = 0; i < rows_ptr_size; ++i) {
        std::cout << row_idx[i]; 
        if (i < rows_ptr_size - 1) {
            std::cout << ",";
        }
    }    
    std::cout <<"]" << std::endl;
}

std::vector<std::vector<double>> SparseMatrixCSR::FormatConverter() const{
    // Initialize vectors to store COO format data
    std::vector<double> coo_values;
    std::vector<double> coo_row_indices;
    std::vector<double> coo_col_indices;
    int rows_size = row_idx.size();

    // Traverse the CSR matrix to convert it into COO format
    for (int i = 0; i < rows_size - 1; i++) {
        int row_start = row_idx[i];
        int row_end = row_idx[i + 1];

        // Iterate through non-zero elements within the current row
        for (int j = row_start; j < row_end; j++) {
            coo_values.push_back(static_cast<double>(values[j]));
            coo_row_indices.push_back(i);
            coo_col_indices.push_back(static_cast<double>(columns[j]));
        }
    }

    // Create a vector of vectors to store COO data
    std::vector<std::vector<double>> coo;
    coo.push_back(coo_values);
    coo.push_back(coo_row_indices);
    coo.push_back(coo_col_indices);

    return coo;
}


SparseMatrixCOO::SparseMatrixCOO(int rows_n, int cols_n) : rows_n(rows_n), cols_n(cols_n) {
    non_zeros = 0;
    double zeroThreshold = 0.5; // Threshold for zero or non-zero value determination

    // Use 'std::srand' to seed and generate different random values each time
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Use 'unsigned' for better compatibility

    // Generating random sparse matrix
    for (int i = 0; i < rows_n; ++i) {
        for (int j = 0; j < cols_n; ++j) {
            // Generate random value and check if it surpasses the zero threshold
            double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
            if (randomValue > zeroThreshold) {
                // Store non-zero values along with their respective row and column indices
                values.push_back(std::rand() % 100); // Assign a random non-zero value
                columns.push_back(j); // Store column index
                rows.push_back(i); // Store row index
                ++non_zeros; // Increment the count of non-zero elements
            }
        }
    }
}


int SparseMatrixCOO::getrow_n() const { return rows_n; }
int SparseMatrixCOO::getcolumn_n() const { return cols_n; }
int SparseMatrixCOO::getnonzero_n() const { return non_zeros; }

// Read-only operator override - Accesses elements in COO format
const double &SparseMatrixCOO::operator() (const int row, const int col) const {
    if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
        throw std::out_of_range("Indices are out of bound"); // Error when indices are out of range
    }

    // Search for the element at given row and column indices
    for (int i = 0; i < non_zeros ; i++) {
        if (row == rows[i] && col == columns[i]){
            return values[i]; // Return the found value at the specific indices
        }
    }
    // If the element is not found in the row, return 0 as default
    static const double default_value = 0.0;
    return default_value;
}


// Write operator override - Modifies or inserts elements in COO format
double &SparseMatrixCOO::operator()(const int row, const int col) {
    if (row < 0 || row >= rows_n || col < 0 || col >= cols_n) {
        throw std::out_of_range("Indices are out of bound"); // Error when indices are out of range
    }

    // Using lower_bound to locate or insert new elements at specified row and column
    auto it = std::lower_bound(rows.begin(), rows.end(), row);
    auto pos = it - rows.begin();

    // If the element already exists, return its value
    if (it != rows.end() && *it == row && columns[pos] == col) {
        return values[pos];
    }

    // If the element doesn't exist, insert a new value at the appropriate position
    rows.insert(it, row);
    columns.insert(columns.begin() + pos, col);
    values.insert(values.begin() + pos, 0.0); // Insert default value 0.0

    return values[pos]; // Return reference to the inserted value
}


// Multiplication override - Performs matrix-vector multiplication in COO format
void SparseMatrixCOO::operator*(const std::vector<double>& vec) const {
    const int c = vec.size();
    if (c != cols_n) {
        throw std::out_of_range("Vector does not match"); // Error if vector dimensions don't match matrix
    }
    std::cout << "matrix * vector = ";
    std::cout << "[";
    std::vector<double> result(rows_n); // Initialize the resulting vector

    // Perform matrix-vector multiplication
    for(int i = 0; i < non_zeros; i++){
        result[rows[i]] += values[i] * vec[columns[i]];
    }

    // Output the resulting vector
    for (int i = 0; i < c; i++) {
        std::cout << result[i];
        if (i < c - 1) {
            std::cout << ",";
        }
    }

    std::cout << "]" << std::endl;
}


// Matrix printer - Display the matrix stored in COO format along with the separate arrays
void SparseMatrixCOO::print() const {
    std::cout << "["; // Start of the matrix
    // Printing the matrix in a more readable format
    for (int i = 0; i < rows_n; ++i) {
        std::cout << "[ "; // Start of the row
        for (int j = 0; j < cols_n; ++j) {
            bool isChanged = false; // Check if a value is changed to print correctly
            for (int k = 0; k < non_zeros; ++k) {
                if (rows[k] == i && columns[k] == j) {
                    std::cout << values[k] << " "; // Print the value if present in COO format
                    isChanged = true;
                    break;
                }
            }
            if (!isChanged) {
                std::cout << "0 "; // Print '0' for missing elements in the COO format
            }
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

    // Display the matrix values, columns, and rows separately
    std::cout << "The matrix is stored in a COO format:" << std::endl;

    std::cout << "Values: [ "; // Display the stored values
    for (int i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i < values.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;

    // Display the stored columns and rows separately
    std::cout << "Columns: [ ";
    for (int i = 0; i < values.size(); ++i) {
        std::cout << columns[i];
        if (i < values.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;

    std::cout << "Rows: [ ";
    for (int i = 0; i < rows.size(); ++i) {
        std::cout << rows[i];
        if (i < rows.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}


// COO to CSR format conversion
std::vector<std::vector<double>> SparseMatrixCOO::FormatConverter() const {
    std::vector<double> csr_values(non_zeros, 0.);
    std::vector<double> csr_columns(non_zeros, 0.);
    std::vector<double> csr_row(rows_n + 1, 0.);

    // Convert COO format to CSR format
    for (int i = 0; i < non_zeros; i++) {
        csr_values[i] = values[i]; // Assign values to CSR format
        csr_columns[i] = columns[i]; // Assign columns to CSR format
        csr_row[rows[i] + 1]++; // Calculate row pointers for CSR format
    }
    for (int i = 0; i < rows_n; i++) {
        csr_row[i + 1] += csr_row[i]; // Update row pointers for CSR format
    }

    // Create a vector of vectors to store CSR data
    std::vector<std::vector<double>> csr;
    csr.push_back(csr_values);
    csr.push_back(csr_columns);
    csr.push_back(csr_row);

    return csr; // Return the CSR-formatted matrix
}
