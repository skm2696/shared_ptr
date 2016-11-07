#include <iostream>
#include <utility>
#include <stdexcept>

#ifndef SPTR_HPP
#define SPTR_HPP
template<typename T>
class shared_ptr {
public:
	shared_ptr() noexcept; /*noexcept*/
	explicit shared_ptr(T * ptr); /*strong*/
	shared_ptr(const shared_ptr& r); /*strong*/
	shared_ptr(shared_ptr&& r); /*noexcept*/
	auto operator =(const shared_ptr& x)->shared_ptr &; /*strong*/
	auto operator =(shared_ptr&& x)->shared_ptr&; /*noexcept*/
	~shared_ptr(); /*noexcept*/
	auto reset() noexcept -> void; /*noexcept*/
	auto swap(shared_ptr& s) noexcept -> void; /*noexcept*/
	auto get() const noexcept->T *; /*noexcept*/
	auto use_count() const noexcept->size_t; /*noexcept*/
	auto unique() const noexcept -> bool; /*noexcept*/
	auto operator*() const -> T&; /*strong*/
	auto operator->() const -> T*; /*strong*/
	explicit operator bool() const noexcept; /*noexcept*/
private:
	T * ptr_;
	size_t * count_;
};
template <class T, class... Args>
shared_ptr<T> make_shared(Args&& ...args);

#include "shared_ptr.cpp"

#endif
