#ifndef DYNAMICARRAY_
#define DYNAMICARRAY_

#include <stdexcept>

template <class T>
class DynamicArray {
private:
	T* items;
	bool isEmpty;
	int size;
public:
	DynamicArray() {
		items = nullptr;
		isEmpty = true;
		size = 0;
	}
	DynamicArray(const int size) : size(size) {
		if (size < 0) throw std::length_error("negative size");

		items = new T[size];
		isEmpty = true;
	}
	DynamicArray(const T* data, const int size) : DynamicArray(size) {
		for (int i = 0; i < size; ++i)
			items[i] = data[i];

		isEmpty = false;
	}
	DynamicArray(const DynamicArray<T>& array) {
		items = new T[array.size];
		isEmpty = array.isEmpty;
		size = array.size;

		for (int i = 0; i < array.size; ++i)
			items[i] = array.items[i];
	}
	~DynamicArray() {
		delete[] items;
		size = 0;
	}

	int getSize() const { return size; }
	T get(const int index) const {
		if (index < 0 || index >= size || isEmpty)
			throw std::out_of_range("out of range");

		return items[index];
	}
	void set(const int index, const T value) {
		if (index < 0 || index >= size)
			throw std::out_of_range("out of range");;

		this->items[index] = value;
		isEmpty = false;
	}
	void removeAt(const int index) {
		if (index < 0 || index >= size || isEmpty)
			throw std::out_of_range("out of range");
		if (size < 1) throw  std::length_error("size is 0");

		T* tempItems = new T[this->size];
		for (int i = 0; i < size; ++i) {
			tempItems[i] = items[i];
		}

		delete[] items;
		items = new T[size - 1];

		for (int i = 0; i < index ; ++i) {
			items[i] = tempItems[i];
		}
		for (int i = index; i < size-1; ++i) {
			items[i] = tempItems[i + 1];
		}

		delete[] tempItems;
		size--;
	}
	void resize(const int newSize) {
		if (newSize < 0) throw std::length_error("negative size");


		T* newItems = new T[newSize];

		for (int i = 0; i < (size > newSize ? newSize : size); ++i)
			newItems[i] = items[i];

		delete[] items;
		items = newItems;
		size = newSize;
	}
	/*DynamicArray<T> operator+(const DynamicArray<T>& array) const {
		if (this->size != array.size)
			throw std::length_error("unequal sizes");
		
		T* tempItems = new T[size];

		for (int i = 0; i < size; ++i) {
			tempItems[i] = items[i] + array.items[i];
		}

		DynamicArray<T> newArray(tempItems, size);
		delete[] tempItems;
		return newArray;
	}*/
};
#endif