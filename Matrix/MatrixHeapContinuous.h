#pragma once

#include "Matrix/Matrix.h"
#include "Array/Array.h"

namespace Structures {

	template <typename T>
	class MatrixHeapContinous : public Matrix<T> {
	public:
		MatrixHeapContinous(uint32_t, uint32_t);
		MatrixHeapContinous(const MatrixHeapContinous<T>&);
		MatrixHeapContinous(MatrixHeapContinous<T>&&);
		~MatrixHeapContinous();

		MatrixHeapContinous<T>& operator=(const MatrixHeapContinous<T>&);
		Matrix<T>& operator=(const Matrix<T>&) override;
		Structure* clone() const override;

		T* operator [](const uint32_t) override;

		const T get(uint32_t, uint32_t) const override;
		void set(uint32_t, uint32_t, const T&) override;

		Matrix<T>* multiply(const Matrix<T>&) const override;

	private:
		uint32_t mapFunction(uint32_t r, uint32_t c) const;

	private:
		T* matrix;
	};

	template<typename T>
	MatrixHeapContinous<T>::MatrixHeapContinous(uint32_t r, uint32_t c) : Matrix<T>(r,c), matrix(new T[r * c]) {

	}

	template<typename T>
	MatrixHeapContinous<T>::MatrixHeapContinous(const MatrixHeapContinous<T>& other) : Matrix<T>(other.rows, other.columns),
	matrix(new T[other.rows * other.columns]) {
		std::memcpy(this->matrix, other.matrix, other.rows * other.columns * sizeof(T));
	}

	template<typename T>
	MatrixHeapContinous<T>::MatrixHeapContinous(MatrixHeapContinous<T>&& other) : Matrix<T>(other.rows, other.columns), matrix(other.matrix) {
		other.matrix = nullptr;
		other.rows = 0;
		other.columns = 0;
	}

	template<typename T>
	MatrixHeapContinous<T>::~MatrixHeapContinous() {
		delete[] this->matrix;
		this->matrix = nullptr;
		this->rows = 0;
		this->columns = 0;
	}

	template<typename T>
	MatrixHeapContinous<T>& MatrixHeapContinous<T>::operator=(const MatrixHeapContinous<T>& other) {
		if (this != &other) {
			if (this->rows != other.rows || this->columns != other.columns) {
				delete[] this->matrix;
				this->rows = other.rows;
				this->columns = other.columns;
				this->matrix = new T[this->rows * this->columns * sizeof(T)];
			}
			std::memcpy(this->matrix, other.matrix, other.rows * other.columns * sizeof(T));
		}
		return *this;
	}

	template<typename T>
	Matrix<T>& MatrixHeapContinous<T>::operator=(const Matrix<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	Structure* MatrixHeapContinous<T>::clone() const {
		return new MatrixHeapContinous<T>(*this);
	}

	template<typename T>
	T* MatrixHeapContinous<T>::operator[](const uint32_t r) {
		return &(this->matrix)[r * this->columns];
	}

	template<typename T>
	const T MatrixHeapContinous<T>::get(uint32_t r, uint32_t c) const {
		return this->matrix[(r * this->columns) + c];
	}

	template<typename T>
	void MatrixHeapContinous<T>::set(uint32_t r, uint32_t c, const T& data) {
		this->matrix[(r * this->columns) + c] = data;
	}

	template<typename T>
	Matrix<T>* MatrixHeapContinous<T>::multiply(const Matrix<T>& matrix) const {
//		if (this->rows != second.getColumns()) {
////			return;
//		}

		const MatrixHeapContinous<T> second = dynamic_cast<const MatrixHeapContinous<T>&>(matrix);
		MatrixHeapContinous<T>* result = new MatrixHeapContinous<T>(this->rows, second.columns);

		for (uint32_t i = 0; i < result->rows; i++) {
			for (uint32_t k = 0; k < result->columns; k++) {
				for (uint32_t j = 0; j < second.columns; j++) {
					result->matrix[i * result->columns + j] += ((this->matrix[i * result->columns + k]
															* second.matrix[k * result->columns + j]));
				}
			}
		}

		return result;
	}

	template<typename T>
	uint32_t MatrixHeapContinous<T>::mapFunction(uint32_t r, uint32_t c) const {
		return (r * this->columns) + c;
	}

}

//#pragma once

//#include "Matrix/Matrix.h"
//#include "Array/Array.h"

//namespace Structures {

//	template <typename T>
//	class MatrixHeapContinous : public Matrix<T> {
//	public:
//		MatrixHeapContinous(uint32_t, uint32_t);
//		MatrixHeapContinous(const MatrixHeapContinous<T>&);
//		~MatrixHeapContinous();

//		MatrixHeapContinous<T>& operator=(const MatrixHeapContinous<T>&);
//		Matrix<T>& operator=(const Matrix<T>&) override;
//		Structure* clone() const override;

//		T* operator [](const uint32_t) override;

//		const T get(uint32_t, uint32_t) const override;
//		void set(uint32_t, uint32_t, const T&) override;

//		Matrix<T>* multiply(const Matrix<T>&) const override;

//	private:
//		uint32_t mapFunction(uint32_t r, uint32_t c) const;

//	private:
//		Array<T>* matrix;
//	};

//	template<typename T>
//	MatrixHeapContinous<T>::MatrixHeapContinous(uint32_t r, uint32_t c) : Matrix<T>(r,c), matrix(new Array<T>(r * c)) {

//	}

//	template<typename T>
//	MatrixHeapContinous<T>::MatrixHeapContinous(const MatrixHeapContinous<T>& other) : Matrix<T>(other.rows, other.columns),
//	matrix(new Array<T>(*other.matrix)) {

//	}

//	template<typename T>
//	MatrixHeapContinous<T>::~MatrixHeapContinous() {
//		delete this->matrix;
//		this->matrix = nullptr;
//		this->rows = 0;
//		this->columns = 0;
//	}

//	template<typename T>
//	MatrixHeapContinous<T>& MatrixHeapContinous<T>::operator=(const MatrixHeapContinous<T>& other) {
//		if (this != &other) {
//			if (this->rows == other.rows && this->columns == other.columns) {
//				*matrix = *(other.matrix);
//			} else {
//				delete this->matrix;
//				this->rows = other.rows;
//				this->columns = other.columns;
//				this->matrix = new Array<T>(*(other.matrix));
//			}
//		}
//		return *this;
//	}

//	template<typename T>
//	Matrix<T>& MatrixHeapContinous<T>::operator=(const Matrix<T>& other) {
//		if (this != &other) {
//			*this = dynamic_cast<const Matrix<T>&>(other);
//		}
//		return *this;
//	}

//	template<typename T>
//	Structure* MatrixHeapContinous<T>::clone() const {
//		return new MatrixHeapContinous<T>(*this);
//	}

//	template<typename T>
//	T* MatrixHeapContinous<T>::operator[](const uint32_t r) {
//		return &(*this->matrix)[r * this->columns];
//	}

//	template<typename T>
//	const T MatrixHeapContinous<T>::get(uint32_t r, uint32_t c) const {
//		return (*this->matrix)[this->mapFunction(r,c)];
//	}

//	template<typename T>
//	void MatrixHeapContinous<T>::set(uint32_t r, uint32_t c, const T& data) {
//		(*this->matrix)[this->mapFunction(r,c)] = data;
//	}

//	template<typename T>
//	Matrix<T>* MatrixHeapContinous<T>::multiply(const Matrix<T>& matrix) const {
////		if (this->rows != second.getColumns()) {
//////			return;
////		}

//		const MatrixHeapContinous<T> second = dynamic_cast<const MatrixHeapContinous<T>&>(matrix);
//		MatrixHeapContinous<T>* result = new MatrixHeapContinous<T>(this->rows, second.columns);

//		for (uint32_t i = 0; i < result->rows; i++) {
//			for (uint32_t k = 0; k < result->columns; k++) {
//				for (uint32_t j = 0; j < second.columns; j++) {
//					(*result)[i][j] += ((this->get(i,k)) * second.get(k,j));
//				}
//			}
//		}

//		return result;
//	}

//	template<typename T>
//	uint32_t MatrixHeapContinous<T>::mapFunction(uint32_t r, uint32_t c) const {
//		return (r * this->columns) + c;
//	}

//}

