#ifndef LISTSEQUENCE_
#define LISTSEQUENCE_
#include "LinkedList.h"
#include "Sequence.hpp"
#include <stdexcept>

template <class T>
class ListSequence: public Sequence<T> {
private:
	LinkedList<T>* items;
	int size;
public:
	ListSequence() {
		items = new LinkedList<T>();
		size = 0;
	}
	ListSequence(T* items, const int size) {
		if (size < 0) throw std::length_error("negative size");

		this->items = new LinkedList<T>(items, size);
		this->size = size;
	}
	ListSequence(const ListSequence<T>& list) {
		this->items = new LinkedList<T>(*list.items);
		this->size = list.size;
	}
	ListSequence(LinkedList<T>& list) {
		this->items = new LinkedList<T>(list);
		this->size = list.getSize();
	}
	virtual ~ListSequence() {
		delete items;
		size = 0;
	}
	virtual T getFirst() const override {
		if (size < 1) throw  std::length_error("size is 0");
		
		return items->getFirst();
	}
	virtual T getLast() const override {
		if (size < 1) throw  std::length_error("size is 0");

		return items->getLast();
	}
	virtual T get(const int index) const override {
		if (index < 0 || index >= size)
			throw std::out_of_range("out of range");
		if (size < 1) throw  std::length_error("size is 0");

		return items->get(index);
	}
	virtual void set(const int index, const T& item) override {
		if (index < 0 || index >= size) throw std::out_of_range("out of range");
		if (size < 1) throw  std::length_error("size is 0");

		items->set(index, item);
	}
	virtual Sequence<T>* getSubsequence(const int stind, const int endind) const override {
		if (stind < 0 || stind >= size) throw std::out_of_range("out of range");
		if (endind < 0 || endind >= size) throw std::out_of_range("out of range");
		if (stind > endind) throw std::logic_error("end index must be not less than start index");
		if (size < 1) throw  std::length_error("size is 0");

		LinkedList<T>* subList = items->getSubList(stind,endind) ;

		ListSequence<T>* subSequence = new ListSequence<T>(*subList);

		return subSequence;
	}
	virtual int getSize() const override
	{ return size; }
	virtual void append(const T& value) override {
		items->append(value);
		size++;
	}
	virtual void prepend(const T& value) override {
		items->prepend(value);
		size++;
	}
	virtual void insertAt(const int index, const T& value) override {
		if (index < 0 || index >= size)
			throw std::out_of_range("out of range");

		items->insertAt(index, value);
		size++;
	}
	virtual void removeAt(const int index) override {
		if (index < 0 || index >= size)
			throw std::out_of_range("out of range");

		items->removeAt(index);
		size--;
	}
	virtual Sequence<T>* concat(const Sequence<T>& other) override {
		int sumSize = size + other.getSize();
		T* tempItems = new T[sumSize];
	
		for (int i = 0; i < size; i++)
			tempItems[i] = this->get(i);
	
		for (int i = 0; i < other.getSize();++i)
			tempItems[i+size] = other.get(i);

		ListSequence<T>* newSeq = new ListSequence<T>(tempItems,sumSize);
		delete[] tempItems;
		return newSeq;
	}
	void print() {
		items->print();
	}
};
#endif