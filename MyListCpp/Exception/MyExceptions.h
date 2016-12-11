/**
 *  Summary: A few useful exceptions.
 *  Author: Brian Cullen (brianshan@gmail.com)
 */

#pragma once
#include <exception>

namespace MyList{
	namespace Exception
	{
		/**
		 * \brief Exception to be thrown if user trys to get value from empty list.
		 */
		class EmptyListException : std::exception
		{
		public:
			const char * what() const throw() override
			{
				return "Cannot get value from empty list.";
			}
		};

		/**
		* \brief Exception to be thrown if user trys to access out of bounds element.
		*/
		class IndexOutOfBounds : std::exception
		{
		public:
			const char * what() const throw() override
			{
				return "Index out of bounds";
			}
		};

		/**
		 * \brief Exception to be thrown if enumerator attempts to get value from empty or before movenext is called.
		 */
		class InvalidEnumerator : std::exception
		{
		public:
			const char * what() const throw() override
			{
				return "Enumerator not pointing to value.";
			}
		};
	}
}

