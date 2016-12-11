/**
 *  Summary: Class that represents a lazy evaluated list from an Enumerator.
 *  Author: Brian Cullen (brianshan@gmail.com)
 */

#pragma once
#include<memory>

#include "Enumerator/IEnumerator.h"

namespace MyList{
	using namespace Enumerator;

	template<class T>
	class IEnumerable;

	/**
	 * \brief Class that represents a lazy evaluated list from an Enumerator.
	 * \tparam T Type of items
	 */
	template<class T>
	class LazyList : public IEnumerable < T >
	{
	public:
		/**
		 * \brief Initializes lazy evaluated list from enumerator.
		 * \param enumerator Shared pointer to enumerator.
		 */
		LazyList(const std::shared_ptr<IEnumerator<T> > & enumerator) : mEnumerator(enumerator){}

		/**
		 * \brief Get new enumerator for this list.
		 * \return std::shared_ptr < IEnumerator<T> >
		 */
		std::shared_ptr < IEnumerator<T> > getEnumerator() const {
			return mEnumerator->clone();
		}

	private:
		std::shared_ptr<IEnumerator<T> > mEnumerator;
	};
}
