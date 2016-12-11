/**
 *  Summary: Class that represents an mutable list of items. Allows O(1) random access and assignment.
 *  Warning: Not safe to write to list while reading.
 *  Author: Brian Cullen (brianshan@gmail.com)
 */

#pragma once

#include "IEnumerable.h"
#include "Enumerator/IEnumerator.h"
#include "Exception/MyExceptions.h"

#define DEFAULT_CAPACITY 16

namespace MyList{
	using namespace Enumerator;

	/**
	* \brief Forward declaration
	* \tparam T
	*/
	template<class T>
	class IEnumerable;

	/**
	* \brief Class that represents an mutable list of items. Allows random access and assignment.
	* \tparam T Type of item to be stored in list.
	*/
	template<class T>
	class MutableList : public IEnumerable < T >
	{
	public:

		/**
		 * \brief Create list with default capacity
		 */
		MutableList() : MutableList(DEFAULT_CAPACITY) {}

		/**
		 * \brief Create list with given capacity.
		 * \param capacity 
		 */
		MutableList(int capacity);

		/**
		 * \brief Create list from array of items
		 * \param input Array
		 * \param length Length of input array
		 */
		MutableList(const T * input, int length);

		/**
		 * \brief Copy constructor, deep copy array items.
		 * \param other MutableList
		 */
		MutableList(const MutableList & other);

		/**
		 * \brief Move constructor
		 * \param other MutableList 
		 */
		MutableList(MutableList && other);

		/**
		 * \brief Create a list from other IEnumerable
		 * \param input 
		 */
		MutableList(const IEnumerable<T> * input);

		/**
		* \brief Append item to list
		* \param value
		*/
		void append(const T & value);

		/**
		 * \brief Get item at index.
		 * \param i index
		 * \return Item
		 */
		T at(unsigned int i) const;

		/**
		 * \brief Get the length of the list
		 * \return Length
		 */
		int getLength() const { return mLength; }

		/**
		 * \brief Get capacity of internal buffer.
		 * \return capacity
		 */
		int getCapacity() const
		{
			return mCapacity;
		}

		/**
		 * \brief Remove last item from list
		 * \return 
		 */
		T pop();

		/**
		 * \brief Random access to item in list, read or assign.
		 * \param i index
		 * \return Reference to item.
		 */
		T & operator[](unsigned int i);

		/**
		 * \brief Reverse the list
		 * \return New list with reversed items.
		 */
		MutableList reverse();

		/**
		 * \brief Sets new capacity for the list.
		 * \param newCapacity must be greater than length of list.
		 */
		void setCapacity(int newCapacity);

		/**
		 * \brief Get enumerator for the list.
		 * \return std::shared_ptr<IEnumerator<T>
		 */
		std::shared_ptr<IEnumerator<T>> getEnumerator() const override{
			return std::shared_ptr<IEnumerator<T>>(new MutableListEnumerator(this));
		}

		/**
		 * \brief Destructor
		 */
		~MutableList() override{
		}

	private:

		/**
		 * \brief Allocates capacity in the internal buffer
		 * \param capacity 
		 */
		void allocateCapacity(int capacity);

		/**
		 * \brief Ensure capacity is great enough to insert new item. Doubles capacity if not.
		 */
		void ensureCapacity();

		/**
		 * \brief Reverse contents in place.
		 */
		void reverseInPlace();

		/**
		 * \brief Capacity of internal buffer.
		 */
		int mCapacity;

		/**
		 * \brief Shared pointer to buffer. Allows transfer of ownership to enumerators.
		 */
		std::shared_ptr<T> mBuffer;

		/**
		 * \brief Length of list.
		 */
		int mLength;

		/**
		* \brief Enumerator for internal buffer
		*/
		class MutableListEnumerator : public IEnumerator < T >
		{
		public:
			/**
			* \brief Create enumerator from list
			* \param list that will share its buffer.
			*/
			MutableListEnumerator(const MutableList * list) : mIndex(-1), mBuffer(list->mBuffer), mLength(list->mLength){};

			/**
			 * \brief Copy constructor shares buffer
			 * \param other MutableListEnumerator
			 */
			MutableListEnumerator(const MutableListEnumerator & other) : mIndex(-1), mBuffer(other.mBuffer), mLength(other.mLength){};

			/**
			* \brief Move to enumerator to next position
			* \return False if enumerator at end of list, Otherwise True
			*/
			bool moveNext() override
			{
				if ((mIndex + 1) == mLength)
				{
					return false;
				}
				mIndex++;
				return true;
			}

			/**
			* \brief Get value at current position.
			* \return Value if Enumerator is valid, otherwise throw exception.
			*/
			T getCurrent() override
			{
				if (mIndex < 0) throw Exception::InvalidEnumerator();
				return mBuffer.get()[mIndex];
			}

			/**
			* \brief Clone enumerator.
			* \return std::shared_ptr<IEnumerator<T> >
			*/
			std::shared_ptr<IEnumerator<T> > clone() override
			{
				return std::shared_ptr<IEnumerator<T> >(new MutableListEnumerator(*this));
			}

			/**
			 * \brief Destructor
			 */
			virtual ~MutableListEnumerator()
			{
			}

		private:
			int mIndex;

			std::shared_ptr<T> mBuffer;

			int mLength;
		};
	};
}

#include "MutableList.tpp"