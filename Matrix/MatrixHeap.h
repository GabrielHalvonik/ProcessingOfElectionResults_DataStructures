#pragma once

#include "Matrix.h"
#include "cstring"

namespace Structures {

	template <typename T>
	class MatrixHeap : public Matrix<T>/*, virtual public IMatrixUtility<MatrixHeap<T>> */{
	public:
		MatrixHeap(uint32_t, uint32_t);
		MatrixHeap(const MatrixHeap<T>&);
		~MatrixHeap();

		MatrixHeap<T>& operator=(const MatrixHeap<T>&);
		Matrix<T>& operator=(const Matrix<T>&) override;

		Structure* clone() const override;

		T* operator [](const uint32_t) override;

		const T get(uint32_t, uint32_t) const override;
		void set(uint32_t, uint32_t, const T&) override;

		Matrix<T>* multiply(const Matrix<T>&) const override;
	private:
//		Array<Array<T>*>* array;
		T** matrix;
	};


	template<typename T>
	MatrixHeap<T>::MatrixHeap(uint32_t r, uint32_t c) : Matrix<T>(r, c), matrix(new T*[r]) {
		for (size_t i = 0; i < this->rows; ++i) {
			matrix[i] = new T[this->columns] {0};
		}
	}

	template<typename T>
	MatrixHeap<T>::MatrixHeap(const MatrixHeap<T>& other) : Matrix<T>(other.rows, other.columns), matrix(new T*[other.rows]) {
		for (size_t i = 0; i < this->rows; ++i) {
			this->matrix[i] = new T[this->columns] {};
			std::memcpy(this->matrix[i], other.matrix[i], this->columns * sizeof(T));
		}
	}

	template<typename T>
	MatrixHeap<T>::~MatrixHeap() {
		for (size_t i = 0; i < this->rows; ++i) {
			delete[] this->matrix[i];
			this->matrix[i] = nullptr;
		}
		delete[] this->matrix;
		this->matrix = nullptr;
		this->rows = 0;
		this->columns = 0;
	}

	template<typename T>
	MatrixHeap<T>& MatrixHeap<T>::operator=(const MatrixHeap<T>& other) {
		if (this != &other && this->rows == other.rows && this->columns == other.columns) {
			for (size_t i = 0; i < this->rows; i++) {
				std::memcpy(this->matrix[i], other.matrix[i], this->columns * sizeof(T));
			}
//			this->rows = other.rows;
//			this->columns = other.columns;
//			for (int i = 0; i < this->rows; ++i) {
//				delete[] this->matrix[i];
//			}
//			delete[] this->matrix;

//			this->matrix = new T*[this->rows];
//			for (int i = 0; i < this->rows; ++i) {
//				this->matrix[i] = new T[this->columns];
//			}
		}

		return *this;
	}

	template<typename T>
	Matrix<T>& MatrixHeap<T>::operator=(const Matrix<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	Structure* MatrixHeap<T>::clone() const {
		return new MatrixHeap<T>(*this);
	}

	template<typename T>
	T* MatrixHeap<T>::operator[](const uint32_t r) {
		return this->matrix[r];
	}

	template<typename T>
	const T MatrixHeap<T>::get(uint32_t r, uint32_t c) const {
		return this->matrix[r][c];
	}

	template<typename T>
	void MatrixHeap<T>::set(uint32_t r, uint32_t c, const T& data) {
		this->matrix[r][c] = data;
	}

	template<typename T>
	Matrix<T>* MatrixHeap<T>::multiply(const Matrix<T>& matrix) const {
//		if (this->rows != second.getColumns()) {
////			return;
//		}

		const MatrixHeap<T> second = dynamic_cast<const MatrixHeap<T>&>(matrix);
		MatrixHeap<T>* result = new MatrixHeap<T>(this->rows, second.columns);

		for (uint32_t i = 0; i < result->rows; i++) {
			for (uint32_t k = 0; k < result->columns; k++) {
				for (uint32_t j = 0; j < second.columns; j++) {
					result->matrix[i][j] += (this->matrix[i][k] * second.matrix[k][j]);
				}
			}
		}

		return result;
	}

}

