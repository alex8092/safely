#include "safely/locker/atomic.h"

using safely::locker::atomic;

void atomic::lock() noexcept
{
	auto tid = std::this_thread::get_id();
	if (tid == this->_current_locker) {
		++this->_n_lock;
		return ;
	}
	while(this->_flag.test_and_set(std::memory_order_acquire));
	this->_current_locker = tid;
	++this->_n_lock;
}

void atomic::unlock() noexcept
{
	--this->_n_lock;
	if (this->_n_lock == 0) {
		this->_current_locker = std::thread::id();
		this->_flag.clear(std::memory_order_release);
	}
}