#ifndef VECTOR_
#define VECTOR_

#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include <stdexcept>
#include <cmath>
#include <typeinfo>
#include <complex>
#include <iostream>



template <class T>
class Vector {
private:
	Sequence<T>* coefs;
	int size;
public:
	Vector() {
		coefs = new ArraySequence<T>();
		size = 0;
	}
	Vector(const T* items, const int size) : size(size) {
		if (size < 0) throw std::length_error("negative size");

		coefs = new ArraySequence<T>(items, size);
	}
	Vector(const Vector<T>& vector) {
		T* tempItems = new T[vector.size];

		for (int i = 0; i < vector.size; ++i) 
			tempItems[i] = vector.coefs->get(i);

		coefs = new ArraySequence<T>(tempItems, vector.size);
		size = vector.size;
		delete[] tempItems;
	}
	Vector(const ArraySequence<T>& array) {
		coefs = new ArraySequence<T>(array);
		size = array.getSize();
	}
	~Vector() {
		delete coefs;
		size = 0;
	}
	T get(const int index) const {
		if (index < 0 || index >= size)
			throw std::out_of_range("out of range");
		return coefs->get(index);
	}
	void set(const int index, const T value) {
		coefs->set(index, value);
	}
	int getSize() const {
		return coefs->getSize();
	}
	double getNorm() const {
		if (size < 1) throw std::length_error("zero size");

		T sum = T();

		if (typeid(T) == typeid(int)) {
			for (int i = 0; i < size; ++i)
				sum += (coefs->get(i)) * (coefs->get(i));

			return sqrt(sum);
		}
	}
	std::complex<double> getCompNorm() const {
		if (size < 1) throw std::length_error("zero size");

		std::complex<double> compSum(0, 0);

		for (int i = 0; i < size; ++i)
			compSum += (coefs->get(i)) * (coefs->get(i));
		std::cout << compSum;
		
		compSum.real(sqrt(compSum.real()));
		compSum.imag(sqrt(compSum.imag()));
		return compSum;
	}
	template<typename T1>
	T1 scalarMult(const Vector<T1>& vector) const {
		if (this->size != vector.size)
			throw std::length_error("unequal sizes");
		if (size < 1) throw std::length_error("zero size");

		T1 sum = T1();

		for (int i = 0; i < size; ++i)
			sum += (coefs->get(i)) * (vector.coefs->get(i));

		return sum;
	}
	std::complex<int> scalarMult(const Vector<std::complex<int>>& vector) const {
		if (this->size != vector.size)
			throw std::length_error("unequal sizes");
		if (size < 1) throw std::length_error("zero size");

		std::complex<int> sum(0, 0);

		for (int i = 0; i < size; ++i)
			sum += coefs->get(i) * std::conj(vector.coefs->get(i));

		return sum;
	}
	Vector<T>& operator=(const Vector<T>& vector)  {
		delete coefs;

		coefs = new ArraySequence<T>(vector.coefs);
		size = vector.size;
	}
	Vector<T> operator+(const Vector<T>& vector) const {
		if (this->size != vector.size)
			throw std::length_error("unequal sizes");

		T* tempItems = new T[size];

		for (int i = 0; i < size; ++i) 
			tempItems[i] = coefs->get(i) + vector.coefs->get(i);
		
		Vector<T> result(tempItems,size);
		delete[] tempItems;

		return result;
	}
	Vector<T> operator-(const Vector<T>& vector) const {
		if (this->size != vector.size)
			throw std::length_error("unequal sizes");

		T* tempItems = new T[size];

		for (int i = 0; i < size; ++i)
			tempItems[i] = coefs->get(i) - vector.coefs->get(i);

		Vector<T> result(tempItems, size);
		delete[] tempItems;

		return result;
	}
	Vector<T> operator*(const T number) const {
		if (size < 1) throw std::length_error("zero size");

		T* tempItems = new T[size];

		for (int i = 0; i < size; ++i)
			tempItems[i] = number*(coefs->get(i));
		
		Vector<T> result(tempItems, size);
		delete[] tempItems;
		
		return result;
	}
	bool operator==(const Vector<T>& vector) const {
		if (size != vector.getSize()) return false;

		for (int i = 0; i < size; ++i) 
			if ((this->get(i)) != vector.get(i)) return false;
		
		return true;
	}
};	
template<class T>
Vector<T> operator*(const T number, const Vector<T>& vector) {
	if (vector.getSize() < 1) throw std::length_error("zero size");

	Vector<T> result = vector.operator*(number);

	return result;
}
#endif