#include <time.h>
#include <cstdlib>
#include <iostream>
#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t cols) : m_pdata(new int* [rows]), m_rows(rows), m_cols(cols) // RAII - resource aquire is initialization
{
	for (int i = 0; i < m_rows; i++)
	{
		m_pdata[i] = new int[m_cols];
	}
}

Matrix::Matrix(size_t rows, size_t cols, int value) : Matrix(rows, cols)
{
	FillByValue(value);
}

Matrix::~Matrix()
{
	Destroy();
}

int Matrix::GetElement(size_t row, size_t col) const
{
	return m_pdata[row][col];
}

size_t Matrix::GetRowsCount() const
{
	return m_rows;
}

size_t Matrix::GetColsCount() const
{
	return m_cols;
}

void Matrix::FillByRandom()
{
	srand(static_cast<unsigned int>(time(NULL)));
	size_t size = m_cols * m_rows;
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_pdata[i][j] = rand() % (size - 1) + 1;
		}
	}
}

Matrix Matrix::Add(const Matrix& right, bool& bres)
{
	Matrix result(this->m_rows, this->m_cols);

	if (this->m_rows != right.m_rows || this->m_cols != right.m_cols)
	{
		std::cout << "Matrices have different sizes and operation can not be done\n";
		bres = false;
	}
	else
	{
		for (int i = 0; i < this->m_rows; ++i)
		{
			for (int j = 0; j < this->m_cols; ++j)
			{
				result.m_pdata[i][j] = this->m_pdata[i][j] + right.m_pdata[i][j];
			}
		}
		bres = true;
	}
	return result;
}

Matrix Matrix::Subtract(Matrix& right, bool& bres)
{
	right.Multiply(-1);  //A * (-1)
	return Add(right, bres);  // A - B = A + B * (-1)
}

bool Matrix::Multiply(int multplr)
{
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_pdata[i][j] *= multplr;
		}
	}
	return true;
}

void Matrix::FillByValue(int value)
{
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			m_pdata[i][j] = value;
		}
	}
}

Matrix Matrix::Transpose(bool& bres)
{
	Matrix result(m_cols, m_rows);

	for (int i = 0; i < result.m_rows; ++i)
	{
		for (int j = 0; j < result.m_cols; ++j)
		{
			result.m_pdata[i][j] = m_pdata[j][i];
		}
	}
	bres = true;
	return result;
}

Matrix& Matrix::operator=(const Matrix& right)
{
	if (this == &right)
	{
		return *this;
	}

	Destroy();

	m_rows = right.m_rows;
	m_cols = right.m_cols;

	m_pdata = new int* [m_rows];
	for (size_t i = 0; i < m_rows; ++i)
	{
		m_pdata[i] = new int[m_cols];
		for (size_t j = 0; j < m_cols; ++j)
		{
			m_pdata[i][j] = right.m_pdata[i][j];
		}
	}

	return *this;
}


void Matrix::Print()
{
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			std::cout << m_pdata[i][j] << "       ";
		}
		std::cout << '\n';
	}
}

void Matrix::Destroy()
{
	for (int i = 0; i < m_rows; ++i)
	{
		delete[] m_pdata[i];
		m_pdata[i] = nullptr;
	}
	delete[] m_pdata;
	m_pdata = nullptr;
}