#include "Array.hpp"
#include <corecrt_malloc.h>
#include <vcruntime_string.h>
namespace UreTechEngine {
	Array::Array(size_t _elemSize)
	{
		elemSize = _elemSize;
	}

	Array::Array()
	{
	}

	void Array::setElemSize(size_t _elemSize)
	{
		elemSize = _elemSize;
	}

	unsigned int Array::addElement(void* toAddPtr)
	{
		char* newArrPtr = nullptr;
		if (toAddPtr != nullptr) {
			if (arrPtr != nullptr) {
				newArrPtr = (char*)malloc(elemSize * (elemCount + 1));
				memcpy(newArrPtr, arrPtr, elemSize * elemCount);
				memcpy((newArrPtr + elemSize * elemCount), toAddPtr, elemSize);
				elemCount++;
			}
			else {
				newArrPtr = (char*)malloc(elemSize);
				memcpy(newArrPtr, toAddPtr, elemSize);
				elemCount++;
			}
			free(arrPtr);
			arrPtr = newArrPtr;
			return elemCount - 1;
		}
		else {
			return -1;
		}
	}
	void Array::removeIndex(unsigned int _index)
	{
		char* newArrPtr = nullptr;
		char* firstPartOfArray = nullptr;
		char* lastPartOfArray = nullptr;
		size_t firstSize, lastSize;
		if (arrPtr != nullptr) {
			if (_index < elemCount) {
				newArrPtr = (char*)malloc(elemSize * (elemCount - 1));

				firstSize = elemSize * (_index);
				lastSize = elemCount - (_index + 1);

				memcpy(newArrPtr, arrPtr, firstSize);
				memcpy((newArrPtr + firstSize), (arrPtr + firstSize), lastSize);
				elemCount--;
				free(arrPtr);
				arrPtr = newArrPtr;
			}
		}
	}
	void* Array::getIndex(unsigned int index)
	{
		if ((arrPtr + (elemSize * index)) != nullptr) {
			return (arrPtr + (elemSize * index));
		}
		else {
			return nullptr;
		}
	}
	unsigned int Array::size()
	{
		return elemCount;
	}
}
