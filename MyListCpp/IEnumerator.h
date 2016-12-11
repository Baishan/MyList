/**
 *  Summary: Interface for enumerating over a list
 *  Author: Brian Cullen (brianshan@gmail.com)
 */

#pragma once
#include<mutex>
#include <memory>

namespace MyList{
	namespace Enumerator{

		/**
		 * \brief Interface for enumerating over a list
		 * \tparam T 
		 */
		template<class T>
		class IEnumerator
		{
		public:
			/**
			 * \brief Move enumerator to next position in list.
			 * \return False if at end of list, True otherwise.
			 */
			virtual bool moveNext() = 0;

			/**
			 * \brief Get current item the enumerator is pointing to.
			 * \return T
			 */
			virtual T getCurrent() = 0;

			/**
			 * \brief Get next item in enumerator as atomic transaction.
			 * \param out Reference for output value.
			 * \return False if enumerator at end of list, True otherwise.
			 */
			bool tryGetNext(T & out);

			/**
			 * \brief Clone this enumerator.
			 * \return std::shared_ptr<IEnumerator<T> 
			 */
			virtual std::shared_ptr<IEnumerator<T> > clone() = 0;

			/**
			 * \brief Destructor
			 */
			virtual ~IEnumerator() {};

		private:
			std::mutex mMutex;
		};
	}
}

#include "Enumerator/IEnumerator.tpp"