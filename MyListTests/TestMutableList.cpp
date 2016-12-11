#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MyListCpp/MutableList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MyList;

namespace MyListTests
{
	TEST_CLASS(TestMutableList)
	{
	public:

		TEST_METHOD(TestEmptyThrowsException)
		{
			MutableList<int> list;
			Assert::ExpectException<Exception::IndexOutOfBounds>([list] { return list.at(0); });
			Assert::AreEqual(0, list.getLength());
		}

		TEST_METHOD(TestEmptyEnumerator)
		{
			MutableList<int> list;
			auto enumerator = list.getEnumerator();
			Assert::AreEqual(false, enumerator->moveNext());
		}

		TEST_METHOD(TestEnumerator)
		{
			int input[] = { 1, 2 };
			MutableList<int> list(input, sizeof(input) / sizeof(int));

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
			MutableList<int> list(input, sizeof(input) / sizeof(int));
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

		TEST_METHOD(TestAppend)
		{
			int input[] = { 1, 2 };
			MutableList<int> list(input, sizeof(input) / sizeof(int));
			list.append(3);

			// Check prepended lists head
			Assert::AreEqual(3, list.at(list.getLength() -1));
			Assert::AreEqual(3, list.getLength());
		}

		TEST_METHOD(TestAssign)
		{
			int input[] = { 1, 2 };
			MutableList<int> list(input, sizeof(input) / sizeof(int));

			list[1] = 3;

			auto enumerator = list.getEnumerator();
			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(1, enumerator->getCurrent());

			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(3, enumerator->getCurrent());
			Assert::AreEqual(false, enumerator->moveNext());
		}

		TEST_METHOD(TestCapacityIncreased)
		{
			int input[] = { 1, 2 };
			MutableList<int> list(input, sizeof(input) / sizeof(int));
			Assert::AreEqual(2, list.getCapacity());
			list.append(3);

			Assert::AreEqual(4, list.getCapacity());
		}

		TEST_METHOD(TestCapacityNotIncreased)
		{
			MutableList<int> list(2);
			list.append(1);
			Assert::AreEqual(2, list.getCapacity());
			list.append(2);
			Assert::AreEqual(2, list.getCapacity());
			list.append(3);
			Assert::AreEqual(4, list.getCapacity());
		}

		TEST_METHOD(TestToMutableList)
		{
			int input[] = { 1, 2, 3, 4 };
			MutableList <int> list(input, sizeof(input) / sizeof(int));

			auto lazyList = list.filter([](int x){return (x % 2) == 0; });
			auto filteredList = lazyList.toMutableList();

			Assert::AreEqual(2, filteredList.getLength());
		}

		TEST_METHOD(TestImmutableListToMutable)
		{
			int input[] = { 1, 2, 3, 4 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));
			auto mutableList = list.toMutableList();
			Assert::AreEqual(2, mutableList[1]);
		}

		TEST_METHOD(TestEmptyToMutableList)
		{
			MutableList<int> list;
			auto lazyList = list.filter([](int x){return (x % 2) == 0; });
			auto filteredList = lazyList.toMutableList();

			Assert::AreEqual(0, filteredList.getLength());
		}
	};
}