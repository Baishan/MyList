#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\MyListCpp\ImmutableList.h"
#include "../MyListCpp/MutableList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MyList;

namespace MyListTests
{
	TEST_CLASS(TestChain)
	{
	public:
		TEST_METHOD(TestFilterMapReverseFoldChain)
		{
			int input[] = { 1, 2, 3, 4 };
			ImmutableList<int> list(input, sizeof(input) / sizeof(int));

			std::string result = list.filter([](int x){return (x % 2) == 0; })
			.map<char>([](int x){return static_cast<char>(x + '0'); })
			.toImmutableList()
			.reverse()
			.foldLeft<std::string>(std::string(), [](std::string a, char c){return a + c; });

			Assert::AreEqual(std::string("42"), result);
		}

		TEST_METHOD(TestMutableFilterMapReverseFoldChain)
		{
			int input[] = { 1, 2, 3, 4 };
			MutableList<int> list(input, sizeof(input) / sizeof(int));

			std::string result = list.filter([](int x){return (x % 2) == 0; })
				.map<char>([](int x){return static_cast<char>(x + '0'); })
				.toImmutableList()
				.reverse()
				.foldLeft<std::string>(std::string(), [](std::string a, char c){return a + c; });

			Assert::AreEqual(std::string("42"), result);
		}
	};
}