#ifndef SAFELY_LOCKER_ATOMIC_H
# define SAFELY_LOCKER_ATOMIC_H

# include <atomic>
# include <thread>

namespace safely
{
	namespace locker
	{
		class atomic final
		{
		private:
			atomic(const atomic&) = delete;
			atomic& operator=(const atomic&) = delete;

			std::atomic_flag	_flag = ATOMIC_FLAG_INIT;
			std::thread::id		_current_locker = std::thread::id();
			size_t				_n_lock = 0;
		public:
			explicit atomic() noexcept = default;

			inline ~atomic() noexcept {
				while (this->_n_lock > 0)
					this->unlock();
			}

			void		lock() noexcept;
			void		unlock() noexcept;
		};
	}
}

#endif