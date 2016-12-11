#pragma once
#include<mutex>

namespace MyList{
	namespace Enumerator{

		template<class T>
		class IEnumerator
		{
		private:
			std::mutex mMutex;

		public:
			virtual bool moveNext() = 0;
			virtual T getCurrent() = 0;

			bool tryGetNext(T & out);

			virtual std::shared_ptr<IEnumerator<T> > clone() = 0;
		};
	}
}

#include "IEnumerator.tpp"