#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <chrono>
#include <string>

#include "Timer.h"
#include "ThreadSpool.h"
#include <Windows.h>

const int ARRAY_SIZE = 1000000;
const int MAX_VALUE = 1000000;

ThreadSpool * threadSpool = &ThreadSpool::getInstance();

// print results of current array
void print(std::vector<int> & array, int arraySize)
{
	for (size_t i = 0; i < arraySize; i++)
	{
		std::cout << array[i] << ",";
	}
	std::cout << "\n";
}

int section(std::vector<int>& array, const int left, const int right) {
	// get a mid point in the array
	const int mid = left + (right - left) / 2;
	const int pivotPtr = array[mid];
	// move the mid point value to the front of the array.
	std::swap(array[mid], array[left]);
	int i_left = left + 1;
	int j_right = right;
	// loop through section between leftPtr and rightPtr to find pivots correct placing
	// while swapping  < and > values in array to pivot with each other 

//#pragma omp parallel for 
	while (i_left <= j_right) {
		// find next element from left  that is more then pivotPtr
		/// NOTE: checking for i_left and j_right are still valid
		while (i_left <= j_right && array[i_left] <= pivotPtr) {
			i_left = i_left + 1;
		}
		// find next element for far right which is smaller then pivot
		while (i_left <= j_right && array[j_right] > pivotPtr) {
			j_right = j_right - 1;
		}
		// double check if the left ptr is < right ptr. then swap
		if (i_left < j_right) {
			std::swap(array[i_left], array[j_right]);
		}
	}
	// swap original left with 
	std::swap(array[i_left - 1], array[left]);
	// return new mid point
	return i_left - 1;
}

void quicksort(std::vector<int> &array, const int left, const int right, const int arraySize) {
	// check if left and right ad still valid values
	if (left >= right)
		return;
	// get the new midpoint
	int midPtr = section(array, left, right);

	/// TODO: IMPLEMENT TREADSPOOL and CO.!!!
	/// first 8 are threaded
	/// after that make Fibers and insert them into current thread
	/// GGGGGGGGZZZYYYYYYYYY
	//ThreadScheduler * threadPtr = nullptr;
	if (auto threadPtr0 = threadSpool->getAvaliable())
	{
		//threadPtr = ;
		threadPtr0->addFiber(Fiber([&array,left,arraySize, midPtr]() { quicksort(array, left, midPtr - 1, arraySize); }));

		//if (auto threadPtr1 = threadSpool->getAvaliable())
			//threadPtr0->addFiber(Fiber([&array, right, arraySize, midPtr]() { quicksort(array, midPtr + 1, right, arraySize); }));

		quicksort(array, midPtr + 1, right, arraySize);
	}
	else
	{
		quicksort(array, left, midPtr - 1, arraySize);
		quicksort(array, midPtr + 1, right, arraySize);
	}

	
}

int main() {
	// Vector of ints, as vector is on the heap not on the heap and threadsafe.
	std::vector<int> * array = new std::vector<int>();
	for (size_t i = 0; i < ARRAY_SIZE; i++)
	{
		array->push_back((rand() % MAX_VALUE) + 1);
	}
	size_t arraySize = array->size();


	std::cout << "Array size: " << std::to_string(ARRAY_SIZE) << std::endl;
	std::cout << "Values: [1 - " << std::to_string(MAX_VALUE) << "]" << std::endl;

	addStartTime("Threaded Quicksort Elapsed: ");
	quicksort(*array, 0, arraySize - 1, arraySize);
	addFinishTime("Threaded Quicksort Elapsed: ");

	printFinalTimeSheet();
	print(*array, arraySize);
	return 0;
}