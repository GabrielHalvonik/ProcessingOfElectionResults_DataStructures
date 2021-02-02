#pragma once

#include "Matrix.h"
#include <cstring>

namespace Structures {

	template <uint32_t r, uint32_t c, typename T>
	class MatrixStack : public Matrix<T>/*, public IMatrixUtility<MatrixStack<r,c,T>>*/ {
	public:
		MatrixStack();
		MatrixStack(const MatrixStack&);

		MatrixStack<r,c,T>& operator=(const MatrixStack<r,c,T>&);
		Matrix<T>& operator=(const Matrix<T>&) override;

		T* operator[](const uint32_t) override;

		const T get(uint32_t, uint32_t) const override;
		void set(uint32_t, uint32_t, const T&) override;

		Structure* clone() const override;

		Matrix<T>* multiply(const Matrix<T>&) const override;
//		MatrixStack<r,c,T> operator*(const MatrixStack<r,c,T>&);
//		MatrixStack<r,c,T> operator*(const MatrixStack<r,c,T>*);
//		template <uint32_t R, uint32_t C, typename E>
//		friend MatrixStack<R,C,E> operator*(const MatrixStack<R,C,E>&, const MatrixStack<R,C,E>&);
//		template <uint32_t R, uint32_t C, typename E>
//		friend MatrixStack<R,C,E> operator*(const MatrixStack<R,C,E>*, const MatrixStack<R,C,E>*);
	private:
		T matrix[r][c];
	};

	template<uint32_t r, uint32_t c, typename T>
	MatrixStack<r,c,T>::MatrixStack() : Matrix<T>(r, c) {
		std::memset(this->matrix, 0, this->size() * sizeof(T));
	}

	template<uint32_t r, uint32_t c, typename T>
	MatrixStack<r,c,T>::MatrixStack(const MatrixStack& other) : Matrix<T>(other.rows, other.columns) {
		std::memcpy(this->matrix, other.matrix, this->size() * sizeof(T));
	}

	template<uint32_t r, uint32_t c, typename T>
	MatrixStack<r,c,T>& MatrixStack<r, c, T>::operator=(const MatrixStack<r,c,T>& other) {
		if (this != &other && this->rows == other.rows && this->columns == other.columns) {
			std::memcpy(this->matrix, other.matrix, this->rows * this->columns * sizeof(T));
		}
		return *this;
	}

	template<uint32_t r, uint32_t c, typename T>
	Matrix<T>& MatrixStack<r,c,T>::operator=(const Matrix<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

	template<uint32_t r, uint32_t c, typename T>
	Structure* MatrixStack<r,c,T>::clone() const {
		return new MatrixStack<r,c,T>(*this);
	}

	template<uint32_t r, uint32_t c, typename T>
	Matrix<T>* MatrixStack<r,c,T>::multiply(const Matrix<T>& matrix) const {
//		if (this->rows != second.columns) {
////			return nullptr;
//		}
		const MatrixStack<r,c,T> second = dynamic_cast<const MatrixStack<r,c,T>&>(matrix);
		MatrixStack<r,c,T>* result = new MatrixStack<r,c,T>;
		for (uint32_t i = 0; i < result->rows; i++) {
			for (uint32_t k = 0; k < result->columns; k++) {
				for (uint32_t j = 0; j < second.columns; j++) {
					result->matrix[i][j] += (this->matrix[i][k] * second.matrix[k][j]);
				}
			}
		}
		return result;
	}

//	template<uint32_t r, uint32_t c, typename T>
//	MatrixStack<r,c,T> MatrixStack<r,c,T>::operator*(const MatrixStack<r,c,T>& second) {
//		return this->multiply(second);
//	}

//	template<uint32_t r, uint32_t c, typename T>
//	MatrixStack<r,c,T> MatrixStack<r,c,T>::operator*(const MatrixStack<r,c,T>* second) {
//		return this->multiply(*second);
//	}

	template<uint32_t r, uint32_t c, typename T>
	const T MatrixStack<r,c,T>::get(uint32_t row, uint32_t column) const {
		return this->matrix[row][column];
	}

	template<uint32_t r, uint32_t c, typename T>
	void MatrixStack<r,c,T>::set(uint32_t row, uint32_t column, const T& data) {
		this->matrix[row][column] = data;
	}

	template<uint32_t r, uint32_t c, typename T>
	T* MatrixStack<r,c,T>::operator[](const uint32_t index) {
		return this->matrix[index];
	}

//	template<uint32_t r, uint32_t c, typename T>
//	MatrixStack<r,c,T> operator*(const MatrixStack<r,c,T>& first, const MatrixStack<r,c,T>& second) {
//		if (first.rows != second.columns) {
////			return nullptr;
//		}

//		MatrixStack<r,c,T> result;
//		for (uint32_t i = 0; i < result.rows; i++) {
//			for (uint32_t k = 0; k < result.columns; k++) {
//				for (uint32_t j = 0; j < second.columns; j++) {
//					result.matrix[i][j] += (first.matrix[i][k] * second.matrix[k][j]);
//				}
//			}
//		}
//		return result;
//	}

//	template<uint32_t r, uint32_t c, typename T>
//	MatrixStack<r,c,T> operator*(const MatrixStack<r,c,T>* first, const MatrixStack<r,c,T>* second) {
//		return operator*(*first, *second);
//	}

}

