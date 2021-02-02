#pragma once

#include "Structure.h"

namespace Structures {

	template <typename T>
	class Matrix : public Structure/*, virtual public IMatrixUtility<Matrix<T>>*/ {
	public:
		virtual ~Matrix() {}

		Structure& operator=(const Structure& other) override;
		size_t size() const override;
		inline uint32_t getRows() const { return rows; }
		inline uint32_t getColumns() const { return columns; }

		virtual Structure* clone() const override = 0;

		virtual Matrix<T>& operator=(const Matrix<T>&) = 0;
		virtual T* operator[](const uint32_t) = 0;

		virtual const T get(uint32_t, uint32_t) const = 0;
		virtual void set(uint32_t, uint32_t, const T&) = 0;


		virtual Matrix<T>* operator*(const Matrix<T>&);

		virtual Matrix<T>* multiply(const Matrix<T>&) const = 0;

	protected:
		Matrix(uint32_t, uint32_t);
		uint32_t rows;
		uint32_t columns;
	};

	template<typename T>
	inline Structure& Matrix<T>::operator=(const Structure& other) {
		if (this != &other) {
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Matrix<T>::Matrix(uint32_t r, uint32_t c) : Structure(), rows(r), columns(c) {
	}

	template<typename T>
	size_t Matrix<T>::size() const {
		return rows * columns;
	}

	template<typename T>
	Matrix<T>* Matrix<T>::operator*(const Matrix<T>& second) {
		return multiply(second);
	}

}
