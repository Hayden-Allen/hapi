#pragma once
#include <functional>
#include "optr.h"
#include "sptr.h"

namespace hapi
{
#ifdef HAPI_OPAQUE
	template<typename T>
	class wptr final : public optr<T>
	{
	public:
		wptr(T* const ptr)
		{
			this->m_ptr = ptr;
		}
		wptr(wptr<T> const& other)
		{
			this->m_ptr = other.m_ptr;
		}
		wptr(sptr<T> const& other)
		{
			this->m_ptr = other.m_ptr;
		}
	public:
		wptr<T>& operator=(wptr<T> const& other)
		{
			this->m_ptr = other.m_ptr;
			return *this;
		}
	};
#else
	template<typename T>
	class wptr final
	{
	public:
		wptr() = delete;
		explicit wptr(T* const newptr) :
			m_ptr(newptr) {}
		wptr(wptr<T> const& other) :
			m_ptr(other.m_ptr)
		{}
		wptr(sptr<T> other) :
			m_ptr(other.get())
		{}
		wptr(optr<T> other) :
			m_ptr(other.get())
		{}
		wptr(optr<T>&& other) = delete;
		~wptr() {}
	public:
		bool operator==(wptr<T> const& other)
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(wptr<T> const& other)
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
		template<typename U = T>
		U* get()
		{
			return (U*)m_ptr;
		}
		template<typename U = T>
		U const* get() const
		{
			return (U const*)m_ptr;
		}
	private:
		T* m_ptr;
	};
#endif
} // namespace hapi
