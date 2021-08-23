using namespace std;

template<typename T>
class ABQ {
public:
	ABQ();
	ABQ(int capacity);
	ABQ(const ABQ& d);
	ABQ& operator=(const ABQ& d);
	~ABQ();
	void enqueue(T data);
	T dequeue();
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

//Default constructor. Maximum capacity shouldbe set to 1, and current size set to 0.
template <typename T>
ABQ<T>::ABQ() {
	size = 0;
	capacity = 1;
	data = nullptr;
}

//Constructor for an ABQ with the specified starting maximum capacity.
template <typename T>
ABQ<T>::ABQ(int capacity) {
	size = 0;
	this->capacity = capacity;
	data = new T[this->capacity];
}

//Copy constructor
template <typename T>
ABQ<T>::ABQ(const ABQ& d) {
	size = d.size;
	capacity = d.capacity;
	data = new T[d.capacity];
	for (int i = 0; i < capacity; i++)
		data[i] = d.data[i];
}

//Assignment operator
template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& d) {
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
ABQ<T>::~ABQ() {
	delete[] data;
}

//Add a new item to end of the queue and resizes if necessary. 
template <typename T>
void ABQ<T>::enqueue(T data) {
	if (size == capacity)
		capacity *= scaleFactor;
	size++;
	T* tempArray = new T[capacity];
	tempArray[0] = data;
	for (int i = 1; i < size; i++)
		tempArray[i] = this->data[i - 1];
	delete[] this->data;
	this->data = tempArray;
}

//Remove the item at front of the queue, resizes if necessary, and return the value removed.
//Throws a runtime error if the queue is empty
template <typename T>
T ABQ<T>::dequeue() {
	if (size == 0)
		throw runtime_error("An error has occurred while dequeuing.");
	else {
		T deqVal = data[size - 1];
		data[size - 1] = 0;
		size--;
		T* tempArray = new T[capacity - 1];
		for (int i = 0; i < size; i++)
			tempArray[i] = this->data[i];
		if (((float)(size) / capacity) < (1.0 / scaleFactor))
			capacity /= (int)scaleFactor;
		delete[] data;
		data = tempArray;
		return deqVal;
	}
}

//Return the value of the item at the front of the queue, without removing it.
//Throws a runtime error if the queue is empty.
template <typename T>
T ABQ<T>::peek() {
	if (size == 0)
		throw runtime_error("An error has occurred while peeking.");
	else
		return data[size - 1];
}

//Returns the current number of items in the ABQ. 
template <typename T>
unsigned int ABQ<T>::getSize() {
	return size;
}

//Returns the current max capacity of the ABQ. 
template <typename T>
unsigned int ABQ<T>::getMaxCapacity() {
	return capacity;
}

//Returns the array representing the queue. 
template<typename T>
T* ABQ<T>::getData() {
	return data;
}