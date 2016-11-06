#include <iostream>
#include <utility>
#include <stdexcept>

#ifndef SPTR_HPP
#define SPTR_HPP

template<typename T>
class shared_ptr {
public:
	shared_ptr() noexcept; 
	explicit shared_ptr(T * ptr); 
	shared_ptr(const shared_ptr& r);  
	shared_ptr(shared_ptr&& r); 
	auto operator =(const shared_ptr& x)->shared_ptr &;  
	auto operator =(shared_ptr&& x)->shared_ptr&;  
	~shared_ptr(); /*noexcept*/
	auto reset() noexcept -> void; 
	auto swap(shared_ptr& s) noexcept -> void; 
	auto get() const noexcept->T *; 
	auto use_count() const noexcept->size_t; 
	auto unique() const noexcept -> bool; 
	auto operator*() const;
	auto operator->() const;
	explicit operator bool() const noexcept; 
private:
	T * ptr_;
	size_t * count_;
};

template <class T, class... Args>
shared_ptr<T> make_shared(Args&& ...args);

#include "shared_ptr.cpp"

#endif
