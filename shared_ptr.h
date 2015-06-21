/*
 * shared_ptr.h
 *
 *  Created on: 12/01/2009
 *      Author: Strulovich
 */

#ifndef SHARED_PTR_H_
#define SHARED_PTR_H_
#include <cassert>
#include <iostream>
#include <typeinfo>

namespace mtm {

template<typename T>
class shared_ptr 
{
private:
	T* data;
	int* counter;

	typedef T element_type;

	void checkInvariant() const 
	{
		assert((data && counter && (*counter)>0) ||
				(!data && !counter));
	}

	void increaseCount() const 
	{
		checkInvariant();
		if (counter) {
			(*counter)++;
		}
	}

	void decreaseCount() 
	{
		checkInvariant();
		if(counter && !--*counter) 
		{
			delete counter;
			delete data;
			counter = NULL;
			data = NULL;
		}
	}

	/*!
	 * Ensures we don't have memory leaks in case bad_alloc or similiar
	 */
    static int* allocateCounter(T* ptr) 
	{
    	try 
		{
    		return ptr ? new int(1) : NULL;
    	} catch (...) 
		{
    		delete ptr;
    		throw; // re-throw the exception caught
    	}
    }

public:
    explicit shared_ptr(T* ptr = NULL) :
    	data(ptr), counter(allocateCounter(ptr)) {}

	shared_ptr(const shared_ptr<T>& other) :
		data(other.data),
		counter(data ? other.counter : NULL) 
		{
			increaseCount();
			checkInvariant();
		}

	template <typename S> friend class shared_ptr;
	template <typename S> shared_ptr(const shared_ptr<S>& other) :
		data(other.data),
		counter(data ? other.counter : NULL) 
		{
			increaseCount();
			checkInvariant();
		}

	~shared_ptr() 
	{
		checkInvariant();
		decreaseCount();
		checkInvariant();
	}

	T& operator*() const 
	{
		checkInvariant();
		assert(data != NULL);
		return *data;
	}

	T* operator->() const 
	{
		checkInvariant();
		assert(data != NULL);
		return data;
	}

	T* get() const 
	{
		checkInvariant();
		return data;
	}

	shared_ptr<T>& operator=(const shared_ptr<T>& other) 
	{
		checkInvariant();
		other.increaseCount();
		decreaseCount();
		counter = other.counter;
		data = other.data;
		checkInvariant();
		return *this;
	}

	template<typename S> shared_ptr<T>& operator=(const shared_ptr<S>& other) 
	{
		checkInvariant();
		other.increaseCount();
		decreaseCount();
		counter = other.counter;
		data = other.data;
		checkInvariant();
		return *this;
	}

	operator bool() const 
	{
		checkInvariant();
		return data;
	}

	void reset() 
	{
		decreaseCount();
		data = NULL;
		counter = NULL;
	}

	friend std::ostream& operator<<(std::ostream& os, const shared_ptr<T>& ptr) 
	{
		os << "[shared_ptr";
		os << ", data = " << ptr.get();
		if (ptr.get()) {
			os << " of " << typeid(*(ptr.get())).name();
			os << ", count = " << *ptr.counter;
		}
		os << "]" ;
		return os;
	}
};

template <typename T, typename S>
inline bool operator==(const shared_ptr<T>& first,const  shared_ptr<S>& second) 
{
	return first.get() == second.get();
}

template <typename T, typename S>
inline bool operator!=(const shared_ptr<T>& first,const  shared_ptr<S>& second) 
{
	return !(first==second);
}

template <typename T, typename S>
inline bool operator<(const shared_ptr<T>& first, const shared_ptr<S>& second) 
{
	return first.get() < second.get();
}

} // namespace mtm

#endif /* SHARED_PTR_H_ */
