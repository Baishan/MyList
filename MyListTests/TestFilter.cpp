#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\MyListCpp\ImmutableList.h"
#include "StubEnumerator.h"
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MyList;

namespace MyListTests
{
	TEST_CLASS(TestFilterEnumerator)
	{
	public:

		TEST_METHOD(TestFilterTrue)
		{
			auto stub = std::make_shared<StubEnumerator<int>>(true, 2);
			// Test even number
			FilterEnumerator<int> filter(stub, [](int x){return (x % 2) == 0; });

			Assert::AreEqual(true, filter.moveNext());
			Assert::AreEqual(2, filter.getCurrent());
		}

		TEST_METHOD(TestEndList)
		{
			auto stub = std::make_shared<StubEnumerator<int>>(false, 2);
			FilterEnumerator<int> filter(stub, [](int x){return (x % 2) == 0; });

			Assert::AreEqual(false, filter.moveNext());
		}
	};

	TEST_CLASS(TestFilter)
	{
	public:
		TEST_METHOD(TestFilterResult)
		{
			int input[] = { 1, 2, 3, 4};
			ImmutableList<int> list(input, sizeof(input)/sizeof(int));
			auto filter = list.filter([](int x){return (x % 2) == 0; });

			auto enumerator = filter.getEnumerator();

			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(2, enumerator->getCurrent());

			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(4, enumerator->getCurrent());

			Assert::AreEqual(false, enumerator->moveNext());

			// Should still point to end of list.
			Assert::AreEqual(4, enumerator->getCurrent());
		}

		TEST_METHOD(TestEmptyListFilter)
		{
			ImmutableList<int> list;
			auto filter = list.filter([](int x){return (x % 2) == 0; });

			auto enumerator = filter.getEnumerator();
			Assert::AreEqual(false, enumerator->moveNext());
		}
	};
}