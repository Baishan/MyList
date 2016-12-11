#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\MyListCpp\ImmutableList.h"
#include "StubEnumerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MyList;

namespace MyListTests
{
	TEST_CLASS(TestMapEnumerator)
	{
	public:

		TEST_METHOD(TestMapApplied)
		{
			auto stub = std::make_shared<StubEnumerator<int>>(true, 2);
			MapEnumerator<int, char> map(stub, [](int x){return static_cast<char>(x + '0'); });

			Assert::AreEqual(true, map.moveNext());
			Assert::AreEqual('2', map.getCurrent());
		}

		TEST_METHOD(TestEndList)
		{
			auto stub = std::make_shared<StubEnumerator<int>>(false, 2);
			MapEnumerator<int, char> map(stub, [](int x){return static_cast<char>(x + '0'); });

			Assert::AreEqual(false, map.moveNext());
			Assert::AreEqual('2', map.getCurrent());
		}
	};

	TEST_CLASS(TestMap)
	{
	public:
		TEST_METHOD(TestMapResult)
		{
			int input[] = { 1, 2 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));
			auto map = list.map<int>([](int x){return x * 3; });

			auto enumerator = map.getEnumerator();

			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(input[0] * 3, enumerator->getCurrent());

			Assert::AreEqual(true, enumerator->moveNext());
			Assert::AreEqual(input[1] * 3, enumerator->getCurrent());

			Assert::AreEqual(false, enumerator->moveNext());

			// Should still point to end of list.
			Assert::AreEqual(input[1] * 3, enumerator->getCurrent());
		}

		TEST_METHOD(TestMapEmptyList)
		{
			ImmutableList<int> list;
			auto map = list.map<int>([](int x){return x * 3; });

			auto enumerator = map.getEnumerator();
			Assert::AreEqual(false, enumerator->moveNext());
		}
	};
}