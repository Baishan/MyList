#include "MutableList.h"

namespace MyList
{

	template<class T>
	MutableList<T>::MutableList(int capacity) : mCapacity(capacity), mBuffer(nullptr), mLength(0)
	{
		allocateCapacity(mCapacity);
	}

	template<class T>
	MutableList<T>::MutableList(const T * input, int length) : mCapacity(length), mBuffer(nullptr), mLength(length)
	{
		allocateCapacity(mCapacity);

		// Copy contents of array.
		memcpy(mBuffer.get(), input, length * sizeof(T));
	}

	template<class T>
	MutableList<T>::MutableList(const MutableList & other) : mCapacity(other.mLength), mBuffer(nullptr), mLength(other.mLength)
	{
		allocateCapacity(mCapacity);

		// Copy length items from other buffer.
		memcpy(mBuffer.get(), other.mBuffer.get(), mLength * sizeof(T));
	}

	template<class T>
	MutableList<T>::MutableList(MutableList && other) : mCapacity(other.mLength), mBuffer(other.mBuffer), mLength(other.mLength)
	{
		// Transfer ownership of buffer.
	}

	template<class T>
	MutableList<T>::MutableList(const IEnumerable<T> * input) : MutableList()
	{
		// Enumerate and append every value.
		auto enumerator = input->getEnumerator();
		T value;
		while (enumerator->tryGetNext(value))
		{
			append(value);
		}
	}

	template<class T>
	void MutableList<T>::append(const T & value)
	{
		// Make sure buffer is large enough.
		ensureCapacity();
		mBuffer.get()[mLength++] = value;
	}

	template<class T>
	T MutableList<T>::pop()
	{
		// Cant pop from empty list
		if (mLength == 0) throw Exception::EmptyListException();
		return mBuffer.get()[mLength--];
	}

	template<class T>
	T & MutableList<T>::operator[](unsigned int i)
	{
		if (i >= mLength)
		{
			throw Exception::IndexOutOfBounds();
		}
		return mBuffer.get()[i];
	}

	template<class T>
	T MutableList<T>::at(unsigned int i) const
	{
		return (const_cast<MutableList<T>*>(this))->operator[](i);
	}

	template<class T>
	MutableList<T> MutableList<T>::reverse()
	{
		// Create copy of this list
		MutableList<T> reversedList(*this);
		reversedList.reverseInPlace();

		// return with move constructor (prevent another copy)
		return std::move(reversedList);
	}

	template<class T>
	void MutableList<T>::setCapacity(int newCapacity)
	{
		// Ignore request for too small capacity
		if (newCapacity >= mLength)
		{
			// Double buffer size.
			T * newBuffer = new T[newCapacity];
			memcpy(newBuffer, mBuffer.get(), mLength * sizeof(T));
			T * temp = mBuffer.get();

			// Smart pointer will destroy old buffer if its not owned by some enumerator.
			mBuffer.reset(newBuffer, std::default_delete<T[]>());
			mCapacity = newCapacity;
		}
	}

	template<class T>
	void MutableList<T>::allocateCapacity(int capacity)
	{
		// Make sure capacity is at least one. 
		if (capacity <= 0) capacity = 1;
		mCapacity = capacity;
		mBuffer.reset(new T[mCapacity], std::default_delete<T[]>());
	}

	template<class T>
	void MutableList<T>::ensureCapacity()
	{
		if (mLength == mCapacity)
		{
			// Double buffer size and copy items
			auto newCapacity = mCapacity * 2;
			setCapacity(newCapacity);
		}
	}

	template<class T>
	void MutableList<T>::reverseInPlace()
	{
		T * startPtr = mBuffer.get();
		T * endPtr = mBuffer.get() + mLength - 1;
		while (startPtr < endPtr)
		{
			// Swap values;
			T temp = *startPtr;
			*startPtr = *endPtr;
			*endPtr = temp;
			++startPtr;
			--endPtr;
		}
	}

}