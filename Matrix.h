#pragma once

class Matrix
{
private:
	void Destroy();

	//setter
	void FillByValue(int value);


	int** m_pdata;
	size_t m_rows;
	size_t m_cols;
public:
	Matrix(size_t rows, size_t cols);
	Matrix(size_t rows, size_t, int value);

	~Matrix();

	//getter
	int GetElement(size_t row, size_t col) const;  //Aij
	size_t GetRowsCount() const;
	size_t GetColsCount() const;

	//setter
	void FillByRandom();

	Matrix Add(const Matrix& right, bool& bres);  //Add(Matrix* right)  right == nullptr
	Matrix Subtract(Matrix& right, bool& bres);

	//multiply by number
	bool Multiply(int multplr);  //matrix is left multiplier only

	Matrix Transpose(bool& bres);

	Matrix& operator=(const Matrix& right);

	void Print();
};