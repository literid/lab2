#ifndef LINKEDLIST_
#define LINKEDLIST_

#include <iostream>
#include <stdexcept>

template <class T>
class LinkedList {
private:
	struct Node {
		T data;
		Node* next;
		Node(T data = T(), Node* pnext = nullptr) : data(data), next(pnext) {}
	};

	Node* head;
	int size;
public:
	LinkedList() : head(nullptr), size(0) {}
	LinkedList(T* items, int count)  {
		if (count < 0) throw  std::length_error("negative size");

		head = new Node;
		head->data = items[0];
		Node* ptr = head;
		int i = 0;
		while (i < count-1) {
			++i;
			ptr->next = new Node(items[i], nullptr);
			ptr = ptr->next;
		}
		size = count;
	}
	LinkedList(const LinkedList<T>& list) {
		head = new Node;
		Node* oldPtr = list.head;
		Node* newPtr = head;
		newPtr->data = oldPtr->data;

		for (int i = 0; i < list.size - 1; ++i) {
			newPtr->next = new Node((oldPtr->next)->data, nullptr);
			newPtr = newPtr->next;
			oldPtr = oldPtr->next;
		}
		size = list.size;
	}
	~LinkedList() {
		while (size) {
			pop_front();
		}
	}
	T getFirst() const {
		if (size == 0) throw std::length_error("size is 0");

		return head->data;
	}
	T getLast() const {
		if (size == 0) throw std::length_error("size is 0");

		Node* ptr = head;

		while (ptr->next != nullptr) 
			ptr = ptr->next;

		return ptr->data;
	}
	T get(const int index) const {
		if (index < 0 || index >= size)
			throw  std::out_of_range("out of range");

		Node* ptr = head;
			
		for (int i = 0; i < index; ++i)
			ptr = ptr->next;

		return ptr->data;
	}
	void set(const int index , const T& item) {
		if (index < 0 || index >= this->size)
			throw std::out_of_range("out of range");

		Node* ptr = head;

			for (int i = 0; i < index; i++, ptr = ptr->next);

		ptr->data = item;
	}
	LinkedList<T>* getSubList(int stind, int endind) const {
		if (size == 0) throw std::length_error("size is 0");
		if (stind < 0 || stind >= size) throw std::out_of_range("out of range");
		if (endind < 0 || endind >= size) throw std::out_of_range("out of range");
		if (stind > endind) throw std::logic_error("end index must be not less than start index");

		Node* ptr = head;
		int n = endind - stind;
		T* tarray = new T[n];
		for (int i = 0; i < endind; i++, ptr = ptr->next) {
			if (i >= stind) {
				tarray[i] = ptr->data;
			}
		}
		
		LinkedList<T>* newList = new LinkedList<T>(tarray,n);
		delete[] tarray;
		return newList;
	}
	int getSize() const { return size; }
	void append(const T& item) {
		Node* ptr = head;

		while (ptr->next != nullptr) {
			ptr = ptr->next;
			std::cout << 1 << std::endl;
		}
		ptr->next = new Node(item, nullptr);
		size++;
	}
	void prepend(const T& item) {
		Node* ptr = new Node(item,head);
		head = ptr;
		size++;
	}
	void removeAt(const int ind) {
		if (ind < 0 || ind >= size)
			throw  std::out_of_range("out of range");

		Node* ptr = head;
		if (ind != 0) {
			for (int i = 0; i < ind - 1; ++i)
				ptr = ptr->next;
			
			Node* tempptr = (ptr->next)->next;
			delete ptr->next;
			ptr->next = tempptr;
		}
		else {
			Node* ptr = head->next;
			delete head;
			head = ptr;
		}
		size--;
	}
	void insertAt(const int ind, const T& item) {
		if (ind < 0 || ind >= size)
			throw  std::out_of_range("out of range");
		
		Node* ptr = head;

		for (int i = 0; i < ind-1; ++i) 
			ptr = ptr->next;
		
		Node* tempptr = ptr->next;
		ptr->next = new Node(item, tempptr);
		size++;
	}
	LinkedList<T>* concat(const LinkedList<T>* list) {
		int sumSize = size + list->size;
		T* tempItems = new T[sumSize];
		Node* ptr = head;

		for (int i = 0; i < size; ++i, ptr = ptr->next) 
			tempItems[i] = ptr->data;

		ptr = list->head;

		for (int i = size; i < sumSize; ++i, ptr = ptr->next) 
			tempItems[i] = ptr->data;

		LinkedList<T>* list_ptr = new LinkedList<T>(tempItems, sumSize);
		delete[] tempItems;

		return  list_ptr;
	}
	void pop_front() {
			Node* ptr = head;
			head = head->next;
			delete ptr;
			size--;
	}
	void print() {
		Node* ptr = head;
		while (ptr != nullptr) {
			std::cout << ptr->data << ' ';
			ptr = ptr->next;
		}
		std::cout << std::endl;
	}	
};
#endif
