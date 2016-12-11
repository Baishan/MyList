#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\MyListCpp\ImmutableList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MyList;

namespace MyListTests
{
	TEST_CLASS(TestMap)
	{
	public:
		TEST_METHOD(TestMapResult)
		{
			int input[] = { 1, 2 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));
			int sum = list.foldLeft<int>(0, ([](int a, int x){return a + x; }));
			Assert::AreEqual(3, sum);
		}
	};
}