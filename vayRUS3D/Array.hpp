#ifndef Array_hpp
#define Array_hpp
namespace UreTechEngine {
	class Array {
	public:
		Array(size_t _elemSize);
		unsigned int addElement(void* toAddPtr);
		void* getIndex(unsigned int index);
	private:
		size_t elemSize = 0;
		char* arrPtr = nullptr;
		unsigned int elemCount = 0;
	};
}
#endif // !Array_hpp
