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
			lock& operator=(const lock&) = delete;
			lock& operator=(lock&&) = delete;

			T&				_locker;

		public:
			explicit lock(T& locker) noexcept :
				_locker(locker)
			{
				locker.lock();
			}
			lock(lock&&) = default;

			inline ~lock() noexcept {
				this->_locker.unlock();
			}
		};

		template <typename Locker>
		static inline auto make_lock(Locker& l) noexcept {
			return lock<Locker>(l);
		}
	}
}

#endif