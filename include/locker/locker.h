#ifndef SAFELY_LOCKER_LOCKER_H
# define SAFELY_LOCKER_LOCKER_H

# include "guard/lock.h"

namespace safely
{
	namespace locker
	{
		template <typename TypeLock>
		class Locker final
		{
		private:
			TypeLock	_lock;

			Locker(const Locker&) = delete;
			Locker&	operator=(const Locker&) = delete;

		public:
			explicit Locker() noexcept = default;
			~Locker() noexcept = default;
			Locker(Locker&&) noexcept = default;
			Locker& operator=(Locker&&) noexcept = default;

			guard::lock<TypeLock>	lock() noexcept {
				return guard::lock<TypeLock>(this->_lock);
			}

		};
	}
}

#endif