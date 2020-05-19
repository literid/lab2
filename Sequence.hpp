#ifndef SEQUENCE_
#define SEQUENCE_

template <class T>
class Sequence
{
public:
	virtual T getFirst() const = 0;
	virtual T getLast() const = 0;
	virtual T get(const int index) const = 0;
	virtual void set(const int index, const T& item) = 0;
	virtual Sequence<T>* getSubsequence(const int start, const int end) const = 0;
public:
	virtual int getSize() const = 0;
	virtual void append(const T& value) = 0;
	virtual void prepend(const T& value) = 0;
	virtual void insertAt(const int index, const T& value) = 0;
	virtual void removeAt(const int index) = 0;
	virtual Sequence<T>* concat(const Sequence<T>& other) = 0;
public:
	virtual ~Sequence(){}
};
#endif
