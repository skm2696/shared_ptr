#include "shared_ptr.h"

#ifndef SPTR_CPP
#define SPTR_CPP

template<typename T> 
shared_ptr<T>::shared_ptr() noexcept : ptr_(nullptr), count_(nullptr) 
{ }

template<typename T> 
shared_ptr<T>::shared_ptr(T * ptr) : ptr_(ptr), count_(new size_t(1)) 
{ }

template<typename T> 
shared_ptr<T>::shared_ptr(const shared_ptr & r) : ptr_(r.ptr_), counter_(r.count_) 
{
	if (r.count_) 
	{
		(*r.count_)++;
	}
}

template<typename T> 
shared_ptr<T>::shared_ptr(shared_ptr && r) : ptr_(std::move(r.ptr_)), count_(std::move(r.count_)) 
{
	r.ptr_ = nullptr;
	r.count_ = nullptr;
}

template<typename T> 
auto shared_ptr<T>::operator =(const shared_ptr & x) -> shared_ptr & 
{
	if (this != &x) 
	{
		(shared_ptr<T>(x)).swap(this);
	}
	return *this;
}

template<typename T> 
auto shared_ptr<T>::operator =(shared_ptr && x) -> shared_ptr & 
{
	if (this != &x) 
	{
		swap(x);
	}
	return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() 
{
	if (count_) 
	{
		if (*count_ == 1) 
		{
			delete count_;
			delete ptr_;
		}
		else (*count_)--;
	}
}

template<typename T> 
auto shared_ptr<T>::reset() noexcept -> void 
{
	~shared_ptr();
	ptr_ = nullptr;
	count_ = nullptr;
}

template<typename T> 
auto shared_ptr<T>::swap(shared_ptr & s) noexcept -> void 
{
	std::swap(ptr_, s.ptr_);
	std::swap(count_, s.count_);
}

template<typename T> 
auto shared_ptr<T>::get() const noexcept -> T * 
{
	return ptr_;
}

template<typename T> 
inline auto shared_ptr<T>::use_count() const noexcept -> size_t 
{
	return (count_ != nullptr ? *count_ : 0);
}

template<typename T> 
auto shared_ptr<T>::unique() const noexcept -> bool 
{
	return (use_count() == 1);
}

template<typename T> 
auto shared_ptr<T>::operator*() const -> T & 
{
	if (ptr_ == nullptr) 
	{
		throw std::logic_error("ptr_ = nullptr");
	}
	return *ptr_;
}

template<typename T> 
auto shared_ptr<T>::operator->() const -> T * 
{
	if (ptr_ == nullptr) 
	{
		throw std::logic_error("ptr_ = nullptr");
	}
	return ptr_;
}

template<typename T> /*noexcept*/
shared_ptr<T>::operator bool() const noexcept 
{
	return (ptr_ != nullptr);
}

template<class T, class ...Args>
shared_ptr<T> make_shared(Args && ...args) 
{
	return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif
