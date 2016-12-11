#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\MyListCpp\ImmutableList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MyList;

namespace MyListTests
{		
	TEST_CLASS(TestImmutableList)
	{
	public:
		
		TEST_METHOD(TestEmptyThrowsException)
		{
			ImmutableList<int> list;
			Assert::ExpectException<Exception::EmptyListException>([list] { return list.getHead(); });

			Assert::AreEqual(0, list.getLength());
		}

		TEST_METHOD(TestEmptyListTail)
		{
			ImmutableList<int> list;
			Assert::AreEqual(0, list.getTail().getLength());
		}

		TEST_METHOD(TestEmptyEnumerator)
		{
			ImmutableList<int> list;
			auto enumerator = list.getEnumerator();
			Assert::AreEqual(false, enumerator->moveNext());
		}

		TEST_METHOD(TestEnumerator)
		{
			int input[] = { 1, 2 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));

			auto enumerator = list.getEnumerator();
			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(input[0], enumerator->getCurrent());

			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(input[1], enumerator->getCurrent());

			Assert::AreEqual(false, enumerator->moveNext());

			// Should still point to end of list.
			Assert::AreEqual(input[1], enumerator->getCurrent());
		}

		TEST_METHOD(TestReverse)
		{
			int input[] = { 1, 2 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));
			auto reversedList = list.reverse();

			auto enumerator = list.reverse().getEnumerator();
			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(2, enumerator->getCurrent());

			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(1, enumerator->getCurrent());

			Assert::AreEqual(false, enumerator->moveNext());

			// Should still point to end of list.
			Assert::AreEqual(1, enumerator->getCurrent());
		}

		TEST_METHOD(TestPrepend)
		{
			int input[] = { 1, 2 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));
			auto newList = list.prepend(3);

			// Check prepended lists head
			Assert::AreEqual(3, newList.getHead());
			Assert::AreEqual(3, newList.getLength());

			// Check had no effect on old list
			Assert::AreEqual(1, list.getHead());
			Assert::AreEqual(2, list.getLength());
		}

		TEST_METHOD(TestToImmutableList)
		{
			int input[] = { 1, 2, 3, 4 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));
		
			auto lazyList = list.filter([](int x){return (x % 2) == 0; });
			auto filteredList = lazyList.toImmutableList();

			Assert::AreEqual(2, filteredList.getLength());
		}

		TEST_METHOD(TestEmptyToImmutableList)
		{
			ImmutableList<int> list;
			auto lazyList = list.filter([](int x){return (x % 2) == 0; });
			auto filteredList = lazyList.toImmutableList();

			Assert::AreEqual(0, filteredList.getLength());
		}
	};
}