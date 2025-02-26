#include <time.h>
#include <cstdlib>
#include <iostream>
#include "Matrix.h"

int Matrix::countObjects = 0;

Matrix::Matrix(size_t rows, size_t cols) : m_pdata(new int* [rows]), m_rows(rows), m_cols(cols) // RAII - resource aquire is initialization
{
	for (int i = 0; i < m_rows; i++)
	{
		m_pdata[i] = new int[m_cols];
	}
	countObjects++;
}

Matrix::Matrix(size_t rows, size_t cols, int value) : Matrix(rows, cols)
{
	FillByValue(value);
}

Matrix::Matrix(const Matrix& other) : m_pdata(new int* [other.m_rows]), m_rows(other.m_rows), m_cols(other.m_cols)  //deep copy
{
	for (int i = 0; i < m_rows; i++)
	{
		m_pdata[i] = new int[m_cols];
		for (int j = 0; j < m_cols; j++)
		{
			m_pdata[i][j] = other.m_pdata[i][j];
		}
	}
	countObjects++;
}

Matrix::~Matrix()
{
	Destroy();
	countObjects--;
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

Matrix Matrix::Transponse(bool& bres)
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

Matrix Matrix::operator+(const Matrix& other) const
{
	Matrix result(this->m_rows, this->m_cols);

	if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
	{
		std::cout << "Matrices have different sizes and operation can not be done\n";
	}
	else
	{
		for (int i = 0; i < this->m_rows; ++i)
		{
			for (int j = 0; j < this->m_cols; ++j)
			{
				result.m_pdata[i][j] = this->m_pdata[i][j] + other.m_pdata[i][j];
			}
		}
	}
	return result; //RVO and NRVO
}

Matrix Matrix::operator-(const Matrix& other) const
{
	return *this + other * (-1);
}

Matrix Matrix::operator*(const int multiplier) const
{
	Matrix result(m_rows, m_cols);
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			result.m_pdata[i][j] = m_pdata[i][j] * multiplier;
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix result(m_rows, other.m_cols);
	if (m_cols != other.m_rows)
	{
		std::cout << "Matrices have different sizes and operation can not be done\n";
		result.FillByValue(-1);
	}
	else
	{
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < other.m_cols; j++)
			{
				result.m_pdata[i][j] = 0;
				for (int k = 0; k < m_cols; k++)
				{
					result.m_pdata[i][j] += m_pdata[i][k] * other.m_pdata[k][j];
				}
			}
		}
	}
	return result;
}

bool Matrix::operator==(const Matrix& other) const
{
	if (m_rows != other.m_rows || m_cols != other.m_cols)
	{
		return false;
	}
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			if (m_pdata[i][j] != other.m_pdata[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
	return !((*this) == other);
}

bool Matrix::operator<(const Matrix& other) const
{
	return m_pdata[0][0] < other.m_pdata[0][0];
}

bool Matrix::operator>(const Matrix& other) const
{
	return other < *this;
}

bool Matrix::operator<=(const Matrix& other) const
{
	return ((*this) < other) || ((*this) == other);
}

bool Matrix::operator>=(const Matrix& other) const
{
	return ((*this) > other) || ((*this) == other);
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