#pragma once
#include "optr.h"
#include "sptr.h"

namespace hapi
{
	template<typename T>
	class wptr final
	{
	public:
		wptr() = delete;
		explicit wptr(T* const newptr) : m_ptr(newptr) {}
		wptr(wptr<T> const& other) :
			m_ptr(other.m_ptr)
		{}
		wptr(sptr<T>&other) :
			m_ptr(other.get())
		{}
		wptr(optr<T>& other) :
			m_ptr(other.get())
		{}
		wptr(optr<T>&& other) = delete;
		~wptr() {}
	public:
		template<typename OTHER>
		void operator=(OTHER o) = delete;
		bool operator==(const wptr<T>& other)
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(const wptr<T>& other)
		{
			return m_ptr != other.m_ptr;
		}
		operator bool() const
		{
			return m_ptr;
		}
	public:
		T& operator*()
		{
			HAPI_ASSERT(m_ptr);
			return *m_ptr;
		}
		T const& operator*() const
		{
			HAPI_ASSERT(m_ptr);
			return *m_ptr;
		}
		T* operator->()
		{
			HAPI_ASSERT(m_ptr);
			return m_ptr;
		}
		T const* operator->() const
		{
			HAPI_ASSERT(m_ptr);
			return m_ptr;
		}
		T* get()
		{
			return m_ptr;
		}
		T const* get() const
		{
			return m_ptr;
		}
	private:
		T* m_ptr;
	};
}
