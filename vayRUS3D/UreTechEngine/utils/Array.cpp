#include "Array.hpp"
#include <corecrt_malloc.h>
#include <vcruntime_string.h>
namespace UreTechEngine {
	Array::Array(size_t _elemSize)
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
			arrPtr = newArrPtr;
			return elemCount - 1;
		}
		else {
			return -1;
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
}
