/*!
 * @file lsd_matrix.hpp
 *
 * @author David Losteiner
 * @date 2014.08.13.
 *
 * This implements a template matrix class with basic operations.
 *
 * The base comes from:
 * 	http://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File
 *
 */

#pragma once

/// @todo: This should not use STL datatype
#include <vector>

#include "lsd/core/lsd_types.hpp"
#include "lsd/core/lsd_assert.hpp"

namespace lsd
{
	/*!
	 * @class TMatrix
	 * @brief Templated 2D matrix class.
	 *
	 * TMatrix class implements a static size 2D array for matrices and vectors.
	 * 	The basic operators and functions (transpose, invert, determinant, eye) are implemented here.
	 *
	 * @warning The row/column size is a constant uint16_t in the current implementation.
	 *
	 * @tparam T	Type of the matrix element values
	 */
	template <typename T>
	class TMatrix
	{

		private:
			/// @todo: vector data type should be replaced with an own type.
			std::vector<std::vector<T> > m_matStorage_t; ///< Storage vector for data elements
			uint16_t m_rows_u16;	///< Number of rows in matrix
			uint16_t m_cols_u16;	///< Number of columns in matrix

		public:

			/// C'tor
			TMatrix(uint16_t f_RowNum_u16, uint16_t f_ColNum_u16):
				m_rows_u16(f_RowNum_u16),
				m_cols_u16(f_ColNum_u16)
			{
				m_matStorage_t.resize(f_RowNum_u16);
				for (unsigned i=0; i<m_matStorage_t.size(); i++)
				{
					m_matStorage_t[i].resize(f_ColNum_u16, static_cast<T>(0));
				}

			};

			/// Copy constructor
			TMatrix(const TMatrix<T>& f_rhs_r)
			{
				m_matStorage_t = f_rhs_r.m_matStorage_t;
				m_rows_u16 = f_rhs_r.getRows();
				m_cols_u16 = f_rhs_r.getCols();
			};

			/// Virtual destructor
			virtual ~TMatrix() {};

			/// Get the number of rows of the matrix
			uint16_t getRows() const { return this->m_rows_u16; }

			/// Get the number of columns of the matrix
			uint16_t getCols() const { return this->m_cols_u16; }

			/// Write access to matrix element (row,col)
			T& operator()(const uint16_t& f_row_ru16, const uint16_t& f_col_ru16);
			/// Read access to matrix element (row,col)
			const T& operator()(const uint16_t& f_row_ru16, const uint16_t& f_col_ru16) const;

			/// Assignment operator overload
			TMatrix<T>& operator=(const TMatrix<T>& f_rhs_r);

			// --- Matrix operators ---
			TMatrix<T>	operator+(	const TMatrix<T>& f_rhs_r);
			TMatrix<T>&	operator+=(	const TMatrix<T>& f_rhs_r);
			TMatrix<T>	operator-(	const TMatrix<T>& f_rhs_r);
			TMatrix<T>&	operator-=(	const TMatrix<T>& f_rhs_r);
			TMatrix<T>	operator*(	const TMatrix<T>& f_rhs_r);
			TMatrix<T>&	operator*=(	const TMatrix<T>& f_rhs_r);

			/// @todo: identity implementation
			/// @todo: dot product
			/// @todo: transpone
			/// @todo: determinant
			/// @todo: inverse (divide)

	};

	/// @todo: Vector typedef

	/////////////////  IMPLEMENTATION  //////////////////////////////



	/// Write access to matrix element (row,col)
	template<typename T>
	T& TMatrix<T>::operator()(const uint16_t& f_row_ru16, const uint16_t& f_col_ru16)
	{
		LSD_ASSERT( ((f_row_ru16 < m_rows_u16) && (f_col_ru16 < m_cols_u16)),
				"[TMatrix] Index is out of range: ("<<f_row_ru16 << ","<<f_col_ru16<<")" );

		return this->m_matStorage_t[f_row_ru16][f_col_ru16];
	}

	/// Read access to matrix element (row,col)
	template<typename T>
	const T& TMatrix<T>::operator()(const uint16_t& f_row_ru16, const uint16_t& f_col_ru16) const
	{
		LSD_ASSERT( ((f_row_ru16 < m_rows_u16) && (f_col_ru16 < m_cols_u16)),
				"[TMatrix const] Index is out of range: ("<<f_row_ru16 << ","<<f_col_ru16<<")" );

		return this->m_matStorage_t[f_row_ru16][f_col_ru16];
	}




	/// Assignment Operator
	template<typename T>
	TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& f_rhs_r)
	{
		LSD_ASSERT( ((f_rhs_r.getRows() == this->getRows()) && (f_rhs_r.getCols() == this->getCols())), "[TMatrix =] Matrix dimensions are different!" );

		if (&f_rhs_r == this)
		  return *this;

		for (uint16_t i=0; i<m_rows_u16; i++)
		{
			for (uint16_t j=0; j<m_cols_u16; j++)
			{
				m_matStorage_t[i][j] = f_rhs_r(i, j);
			}
		}

		return *this;
	}


	////////////////////////////////////////////////////
	// --- Matrix operators ---

	template<typename T>
	TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& f_rhs_r)
	{
		LSD_ASSERT( ((f_rhs_r.getRows() == this->getRows()) && (f_rhs_r.getCols() == this->getCols())), "[TMatrix +] Matrix dimensions are different!" );

		typename TMatrix<T>::TMatrix l_result_t(this->m_rows_u16, this->m_cols_u16);

		for (uint16_t i=0; i<m_rows_u16; i++)
		{
			for (uint16_t j=0; j<m_cols_u16; j++)
			{
				l_result_t(i,j) = this->m_matStorage_t[i][j] + f_rhs_r(i,j);
			}
		}

		return l_result_t;
	}


	template<typename T>
	TMatrix<T>& TMatrix<T>::operator+=(const TMatrix<T>& f_rhs_r)
	{
		LSD_ASSERT( ((f_rhs_r.getRows() == this->getRows()) && (f_rhs_r.getCols() == this->getCols())), "[TMatrix +=] Matrix dimensions are different!" );

		for (uint16_t i=0; i<m_rows_u16; i++)
		{
			for (uint16_t j=0; j<m_cols_u16; j++)
			{
				this->m_matStorage_t[i][j] += f_rhs_r(i,j);
			}
		}

		return *this;
	}


	template<typename T>
	TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& f_rhs_r)
	{
		LSD_ASSERT( ((f_rhs_r.getRows() == this->getRows()) && (f_rhs_r.getCols() == this->getCols())), "[TMatrix -] Matrix dimensions are different!" );

		typename TMatrix<T>::TMatrix l_result_t(this->m_rows_u16, this->m_cols_u16);

		for (uint16_t i=0; i<m_rows_u16; i++)
		{
			for (uint16_t j=0; j<m_cols_u16; j++)
			{
				l_result_t(i,j) = this->m_matStorage_t[i][j] - f_rhs_r(i,j);
			}
		}

		return l_result_t;
	}

	// Cumulative subtraction of this matrix and another
	template<typename T>
	TMatrix<T>& TMatrix<T>::operator-=(const TMatrix<T>& f_rhs_r)
	{
		LSD_ASSERT( ((f_rhs_r.getRows() == this->getRows()) && (f_rhs_r.getCols() == this->getCols())), "[TMatrix -=] Matrix dimensions are different!" );

		for (uint16_t i=0; i<m_rows_u16; i++)
		{
			for (uint16_t j=0; j<m_cols_u16; j++)
			{
				this->m_matStorage_t[i][j] -= f_rhs_r(i,j);
			}
		}

		return *this;
	}


	template<typename T>
	TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& f_rhs_r)
	{
		/// @todo: Assert is missing from operator*
		/// @warning: Multiplication can be matrix-matrix and matrix-vector
		typename TMatrix<T>::TMatrix l_result_t(this->m_rows_u16, f_rhs_r.getCols());

		for (uint16_t i=0; i<f_rhs_r.getRows(); i++)
		{
			for (uint16_t j=0; j<f_rhs_r.getCols(); j++)
			{
				for (uint16_t k=0; k<m_rows_u16; k++)
				{
					l_result_t(i,j) += this->m_matStorage_t[i][k] * f_rhs_r(k,j);
				}
			}
		}

		return l_result_t;
	}



	template<typename T>
	TMatrix<T>& TMatrix<T>::operator*=(const TMatrix<T>& f_rhs_r)
	{
		/// @todo: Assert is missing from operator*=
		typename TMatrix<T>::TMatrix l_result_t = (*this) * f_rhs_r;
		(*this) = l_result_t;
		return *this;
	}


}
