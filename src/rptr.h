#pragma once
#include "optr.h"
#include "wptr.h"

namespace hapi
{
	template<typename T>
	class rptr final
	{
	public:
		rptr() : m_ptr(nullptr) {}
		explicit rptr(T* const newptr) : m_ptr(newptr) {}
		explicit rptr(T const* const newptr) : m_ptr(newptr) {}
		rptr(wptr<T> const& other) :
			m_ptr(other.get())
		{}
		rptr(optr<T> const& other) :
			m_ptr(other.get())
		{}
		rptr(optr<T>&& other) = delete;
		~rptr() {}
	public:
		template<typename OTHER>
		void operator=(OTHER o) = delete;
		bool operator==(const rptr<T>& other)
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(const rptr<T>& other)
		{
			return m_ptr != other.m_ptr;
		}
	public:
		T const& operator*() const
		{
			return *m_ptr;
		}
		T const* operator->() const
		{
			return m_ptr;
		}
		T const* get() const
		{
			return m_ptr;
		}
	private:
		T const* m_ptr;
	};
}
