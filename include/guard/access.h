#ifndef SAFELY_GUARD_ACCESS_H
# define SAFELY_GUARD_ACCESS_H

# include "guard/safecall.h"

namespace safely
{
	namespace guard
	{
		template <typename Locker, typename T>
		struct access
		{
		private:
			T		_object;
			Locker	_locker;

		public:
			access() noexcept :
				_object(T())
			{

			}
			access(T&& object) noexcept :
				_object(std::move(object))
			{

			}

			template <typename toCall>
			auto get(const toCall& t) {
				return safecall(this->_locker, [&]() {
					return t(this->_object);
				});
			}

			template <typename toCall>
			void call(const toCall& t) {
				safecall(this->_locker, [&]() {
					t(this->_object);
				});
			}
		};
	}
}

#endif