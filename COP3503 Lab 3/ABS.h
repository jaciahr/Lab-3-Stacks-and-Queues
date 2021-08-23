#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class ABS {
public:
	ABS();
	ABS(int capacity);
	ABS(const ABS& d);
	ABS& operator=(const ABS& d);
	~ABS();
	void push(T data);
	T pop();
	T peek();
	unsigned int getSize();
	unsigned int getMaxCapacity();
	T* getData();
private:
	int size;
	int capacity;
	T* data;
	float scaleFactor = 2.0f;
};

//Default constructor. Maximum capacity should be set to 1, and current size set to 0.
template <typename T>
ABS<T>::ABS() {
	size = 0;
	capacity = 1;
	data = nullptr;
}

//Constructor for an ABS with the specified starting maximum capacity. 
template <typename T>
ABS<T>::ABS(int capacity) {
	size = 0;
	this->capacity = capacity;
	data = new T[this->capacity];
}

//Copy constructor
template <typename T>
ABS<T>::ABS(const ABS& d) {
	size = d.size;
	capacity = d.capacity;
	data = new T[d.capacity];
	for (int i = 0; i < size; i++)
		data[i] = d.data[i];
}

//Assignment operator
template <typename T>
ABS<T>& ABS<T>::operator=(const ABS& d) {
	size = d.size;
	capacity = d.capacity;
	delete[] data;
	T* tempData = new T[capacity];
	for (int i = 0; i < size; i++)
		tempData[i] = d.data[i];
	return *this;
}

//Destructor
template <typename T>
ABS<T>::~ABS() {
	delete[] data;
}

//Add a new item to the top of the stack and resize if necessary. 
template <typename T>
void ABS<T>::push(T data) {
	if (this->data == nullptr) {
		this->data = new T[1];
		this->data[0] = data;
		size = 1;
		capacity = 1;
	}
	else if (size == capacity) {
		T* tempArray = new T[(int)(capacity * scaleFactor)];
		for (int i = 0; i < size; i++)
			tempArray[i] = this->data[i];
		tempArray[size] = data;
		size++;
		capacity = (int)(capacity * scaleFactor);
		delete[] this->data;
		this->data = tempArray;
	}
	else if (size < capacity) {
		this->data[size] = data;
		size++;
	}
}

//Remove the item at the top of the stack, resizes if necessary, and return the value removed.
//Throws a runtime error if the stack is empty. 
template <typename T>
T ABS<T>::pop() {
	if (size == 0)
		throw runtime_error("An error has occurred when popping.");
	else {
		T popVal = data[size - 1];
		data[size - 1] = 0;
		size--;
		T* tempArray = new T[capacity - 1];
		for (int i = 0; i < size; i++)
			tempArray[i] = data[i];
		if (((float)(size) / capacity) < (1.0 / scaleFactor))
			capacity /= (int)(scaleFactor);
		delete[] data;
		data = tempArray;
		return popVal;
	}
}

//Return the value of the item at the top of the stack, without removing it.
//Throws a runtime error if the stack is empty
template <typename T>
T ABS<T>::peek() {
	if (size == 0)
		throw runtime_error("An error has occurred when peeking.");
	else
		return data[size - 1];
}

//Returns the current number of items in the ABS.
template <typename T>
unsigned int ABS<T>::getSize() {
	return size;
}

//Returns the current max capacity of the ABS. 
template <typename T>
unsigned int ABS<T>::getMaxCapacity() {
	return capacity;
}

//Returns the array representing the stack. 
template <typename T>
T* ABS<T>::getData() {
	return data;
}