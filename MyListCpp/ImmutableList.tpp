#include "ImmutableList.h"

namespace MyList
{
	template <typename T>
	ImmutableList<T>::ImmutableList(const T * input, int length) : mLength(length), mNode(nullptr)
	{
		// Iterate backwards over array and prepend new head for each value.
		for (int i = length -1; i >= 0; --i){
			mNode.reset(new ListNode(input[i], mNode));
		}
	}

	template <typename T>
	ImmutableList<T>::ImmutableList(const IEnumerable<T> * list) : mLength(0), mNode(nullptr)
	{
		// Iterate over each value in list and append it to the tail.
		auto enumerator = list->getEnumerator();
		T value;

		// Check if at least one value and create a new ListNode
		if (enumerator->tryGetNext(value)){
			mNode.reset(new ListNode(value, mNode));
			auto current = mNode;
			mLength = 1;

			// Foreach value append new listnode to tail.
			while (enumerator->tryGetNext(value))
			{
				// current->tail will always point to empty node at end of list.
				current->tail.reset(new ListNode(value, current->tail));
				current = current->tail;
				mLength++;
			}
		}
	}

	template <typename T>
	ImmutableList<T>::ImmutableList(T head, const ImmutableList & tail){
		// Point this to new head and keep track of length.
		mNode.reset(new ListNode(head, tail.mNode));
		mLength = tail.getLength() + 1;
	}

	template <class T>
	T ImmutableList<T>::getHead() const
	{
		if (!mNode) throw Exception::EmptyListException();
		return mNode->head;
	}

	template <typename T>
	ImmutableList<T> ImmutableList<T>::reverse(){
		// Iterate over list prepending each value to head of new list.
		std::shared_ptr<ListNode> root(nullptr);
		auto enumerator = getEnumerator();
		int length = 0;
		while (enumerator->moveNext()){

			// Point root to new head and keep track of length.
			root.reset(new ListNode(enumerator->getCurrent(), root));
			++length;
		}
		return ImmutableList<T>(root, length);
	}

	template <typename T>
	std::shared_ptr<Enumerator::IEnumerator<T> > ImmutableList<T>::getEnumerator() const {
		// Create new enumerator pointing to head node.
		return std::shared_ptr<IEnumerator<T> >(new ListNodeEnumerator(mNode));
	}

	template <typename T>
	bool ImmutableList<T>::ListNodeEnumerator::moveNext(){
		// Check if at end of list or empty list.
		if (mNext)
		{
			mCurrent = mNext;
			mNext = mCurrent->tail;
			return true;
		}
		return false;
	}
}
