/**
 *  Summary: Class that represents an immutable list of items. Implemented as linked list.
 *  Author: Brian Cullen (brianshan@gmail.com)
 */

#pragma once

#include<memory>

#include "IEnumerable.h"
#include "Enumerator/IEnumerator.h"
#include "Exception/MyExceptions.h"

namespace MyList{
	using namespace Enumerator;

	/**
	 * \brief Forward declaration
	 * \tparam T 
	 */
	template<class T>
	class IEnumerable;

	/**
	 * \brief Class that represents an immutable list of items.
	 * \tparam T Type of item to be stored in list.
	 */
	template<class T>
	class ImmutableList : public IEnumerable < T >
	{
	private:
		class ListNode;

	public:
		/**
		 * \brief Instantiates an empty list;
		 */
		ImmutableList() : mLength(0), mNode(nullptr) {}

		/**
		 * \brief Initializes new list from array of values.
		 * \param input pointer to input array
		 * \param length length of input array 
		 */
		ImmutableList(const T * input, int length);

		/**
		 * \brief Initializes new list from another IEnumerable
		 * \param list pointer to IEnumerable
		 */
		ImmutableList(const IEnumerable<T> * list);

		/**
		 * \brief Initializes new list from a head and tail list
		 * \param head of the new list
		 * \param tail of the new list
		 */
		ImmutableList(T head, const ImmutableList & tail);

		/**
		 * \brief Get the tail of the list.
		 * \return New Immutable pointing to tail, copy of this if list is empty
		 */
		ImmutableList getTail(){
			if (!mNode) return ImmutableList(*this);
			return ImmutableList(mNode->tail, mLength - 1);
		}

		/**
		 * \brief get the head of the list
		 * \return the head
		 */
		T getHead() const;

		/**
		 * \brief get the length of the list
		 * \return integer length
		 */
		int getLength() const { return mLength; }

		/**
		 * \brief Gets enumerator for the list
		 * \return IEnumerator
		 */
		std::shared_ptr<IEnumerator<T> > getEnumerator() const;

		/**
		 * \brief Prepend value to list
		 * \param value of new head
		 * \return New ImmutableList
		 */
		inline ImmutableList prepend(T value){
			return ImmutableList(value, *this);
		}

		/**
		 * \brief Reverse the list
		 * \return New ImmutableList
		 */
		ImmutableList reverse();

	private:
		int mLength;
		std::shared_ptr<ListNode> mNode;

		/**
		 * \brief Initialize new ImmutableList from internal node.
		 * \param node pointer to a ListNode
		 * \param length of linked list starting at node
		 */
		ImmutableList(const std::shared_ptr<ListNode> & node, int length) : mLength(length), mNode(node){}

		/**
		 * \brief Internal representation of a linked list node.
		 */
		class ListNode
		{
		public:
			/**
			 * \brief Initializes new linked list node
			 * \param head 
			 * \param tail 
			 */
			inline ListNode(T head, const std::shared_ptr<ListNode> & tail) : head(head), tail(tail){ }

			T head;
			std::shared_ptr<ListNode> tail;
		};

		/**
		 * \brief Enumerator for internal linked list
		 */
		class ListNodeEnumerator : public IEnumerator < T >
		{
		public:

			/**
			 * \brief Initializes new ListNodeEnumerator starting from node.
			 * \param node Shared pointer to a node.
			 */
			ListNodeEnumerator(const std::shared_ptr<ListNode> &node) : mNext(node), mCurrent(nullptr) {}

			/**
			 * \brief Copy constructor
			 * \param other ListNodeEnumerator
			 */
			ListNodeEnumerator(const ListNodeEnumerator & other) {
				mNext = other.mNext;
				mCurrent = other.mCurrent;
			}

			/**
			 * \brief Move to enumerator to next position
			 * \return False if enumerator at end of list, Otherwise True
			 */
			bool moveNext() override;

			/**
			 * \brief Get value at current position.
			 * \return Value if Enumerator is valid, otherwise throw exception.
			 */
			T getCurrent() override
			{
				if (!mCurrent) throw Exception::InvalidEnumerator();
				return mCurrent->head;
			}

			/**
			 * \brief Clone enumerator.
			 * \return std::shared_ptr<IEnumerator<T> >
			 */
			std::shared_ptr<IEnumerator<T> > clone() override
			{
				return std::shared_ptr<IEnumerator<T> >(new ListNodeEnumerator(*this));
			}

		private:
			std::shared_ptr<ListNode> mNext;
			std::shared_ptr<ListNode> mCurrent;
		};
	};
}

#include "ImmutableList.tpp"