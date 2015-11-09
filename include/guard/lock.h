#ifndef SAFELY_GUARD_LOCK_H
# define SAFELY_GUARD_LOCK_H

# include <thread>

namespace safely
{
	namespace guard
	{
		template <class T>
		class lock
		{
		private:
			lock(const lock&) = delete;
			lock(lock&&) = delete;

			T&				_locker;

		public:
			explicit lock(T& locker) noexcept :
				_locker(locker)
			{
				locker.lock();
			}

			inline ~lock() noexcept {
				this->_locker.unlock();
			}
		};
	}
}

#endif