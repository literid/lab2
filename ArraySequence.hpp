#ifndef ARRAYSEQUENCE_
#define ARRAYSEQUENCE_

#include "Sequence.hpp"
#include "DynamicArray.hpp"
#include <stdexcept>


template <class T>
class ArraySequence :public Sequence<T> {
private:
	DynamicArray<T> *items;
	int size;
public:
	ArraySequence() {
		items = new DynamicArray<T>();
		size = 0;	
	}
	ArraySequence(const int size): size(size) {
		if (size < 0) throw std::length_error("negative size");
		
		items = new DynamicArray<T>(size);
	}
	ArraySequence(const T* items,const int size) {
		if (size < 0) throw std::length_error("negative size");

		this->items = new DynamicArray<T>(items,size);
		this->size = size;
	}
	ArraySequence(const ArraySequence<T>& other) {
		items = new DynamicArray<T>(*other.items);
		this->size = other.size;
	}
	ArraySequence(const DynamicArray<T>& array) {
			items = new DynamicArray<T>(array);
			size = array.getSize();
	}
	virtual ~ArraySequence() {
		delete items;
		size = 0;
	}
	virtual T getFirst() const override {
		if (size < 1) throw  std::length_error("size is 0");
		
		return items->get(0);
	}
	virtual T getLast() const override {
		if (size < 1) throw  std::length_error("size is 0");

		return items->get(size - 1);
	}
	virtual T get(const int ind) const override {
		if (ind < 0 || ind >= size)
			throw std::out_of_range("out of range");
		if (size < 1) throw  std::length_error("size is 0");

		return items->get(ind);
	}
	virtual void set(const int index, const T& item) override {
		if (index < 0 || index >= size) throw std::out_of_range("out of range");
		if (size < 1) throw  std::length_error("size is 0");

		items->set(index,item);
	}
	virtual Sequence<T>* getSubsequence(const int stind, const int endind) const override {
		if (stind < 0 || stind >= size) throw std::out_of_range("out of range");
		if (endind < 0 || endind >= size) throw std::out_of_range("out of range");
		if (stind > endind) throw std::logic_error("end index must be not less than start index");
		if (size < 1) throw  std::length_error("size is 0");

		T* subArray = new T[endind - stind];
		for (int i = 0; i < endind; i++) {
			if (i >= stind) 
				subArray[i] = items->get(i);		
		}

		ArraySequence<T>* subSequence = new ArraySequence<T>(subArray, endind - stind);

		delete[] subArray;

		return subSequence;
	}
	virtual int getSize() const override {
		return size;
	}
	virtual void append(const T& value) override {
		items->resize(size + 1);
		items->set(size, value);
		size++;
	}
	virtual void prepend(const T& value) override {
		items->resize(size + 1);
		T t1 = items->get(0);
		T t2;

		for (int i = 0; i < size; ++i) {
			t2 = t1;
			t1 = items->get(i + 1);
			items->set(i + 1,t2);
		}
		items->set(0,value);

		size++;
	}
	virtual void insertAt(const int index, const T& value) override {
		if (index < 0 || index >= size) throw std::out_of_range("out of range");
		
		items->resize(size + 1);
		T t1 = items->get(index);
		T t2;

		for (int i = index; i < size; i++) {
			t2 = t1;
			t1 = items->get(i + 1);
			items->set(i + 1, t2);
		}

		items->set(index,value);
		size++;
	}
	virtual void removeAt(const int index) override {
		if (index < 0 || index >= size) throw std::out_of_range("out of range");

		items->removeAt(index);
		size--;
	}
	virtual Sequence<T>* concat(const Sequence<T>& other) override {
		DynamicArray<T> array = DynamicArray<T>(size + other.getSize());
		ArraySequence<T>* newSeq = new ArraySequence<T>(array);
		
		for (int i = 0; i < this->size; i++)
			newSeq->set(i,this->get(i));

		for (int i = 0; i < other.getSize(); i++)
			newSeq->set(i + size,other.get(i));

		return newSeq;
	}
	/*void print() {
		for (int i = 0; i < size; ++i) 
			std::cout << items->get(i) << ' ';
		std::cout << std::endl;
	}
	ArraySequence<T> operator+(const ArraySequence<T>& array) const {
		if (this->size != array.size)
			throw std::length_error("unequal sizes");

		DynamicArray<T> tempArray = *items + *array.items;
		ArraySequence<T> newArray(tempArray);
		return newArray;
	}*/
};
#endif 