namespace MyList{
	namespace Enumerator{

		template<typename T>
		bool IEnumerator<T>::tryGetNext(T & out){

			// Lock the mutex (unlocked when lock goes out of scope, exception safe).
			std::unique_lock<std::mutex> lock(mMutex);

			if (moveNext()){
				out = getCurrent();
				return true;
			}

			return false;
		}
	}
}