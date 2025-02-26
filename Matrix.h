#pragma once

class Matrix  //struct Matrix
{
private:
	void Destroy();

	//setter
	static int countObjects;
	
	int** m_pdata;
	size_t m_rows;
	size_t m_cols;
public:
	Matrix(size_t, size_t);
	Matrix(size_t, size_t, int);
	Matrix(const Matrix&);

	~Matrix();

	//getter
	int GetElement(size_t, size_t) const;  //Aij
	size_t GetRowsCount() const;
	size_t GetColsCount() const;

	//setter
	void FillByRandom();
	void FillByValue(int);

	//static

	Matrix Transponse(bool& bres);

	void Print();

	//operators oveloading

	//arithmetic operators:
	Matrix operator+(const Matrix&) const; //A += B <=> A = A + B
	Matrix operator-(const Matrix&) const;


	//multiply by number
	Matrix operator*(const int) const;  //A 
	//multiply by matrix
	Matrix operator*(const Matrix&) const; //

	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;

	//A > B if A11 > B11
	bool operator<(const Matrix&) const;
	bool operator>(const Matrix&) const;
	bool operator<=(const Matrix&) const;
	bool operator>=(const Matrix&) const;

	//assignment operator overloading
	Matrix& operator=(const Matrix& right);

	//friend functions

};