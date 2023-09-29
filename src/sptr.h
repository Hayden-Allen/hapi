#pragma once
#include "optr.h"

namespace hapi
{
	template<typename T>
	class sptr final
	{
	public:
		sptr() = delete;
		sptr(sptr<T> const& other) :
			m_ptr(other.m_ptr)
		{
			if (m_ptr)
			{
				m_ptr->inc_ref_count();
			}
		}
		sptr(optr<T>& other) :
			m_ptr(&other)
		{
			if (m_ptr)
			{
				m_ptr->inc_ref_count();
			}
		}
		sptr(optr<T>&& other) = delete;
		~sptr()
		{
			if (m_ptr)
			{
				m_ptr->dec_ref_count();
			}
		}
	public:
		template<typename OTHER>
		void operator=(OTHER o) = delete;
		bool operator==(const sptr<T>& other)
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(const sptr<T>& other)
		{
			return m_ptr != other.m_ptr;
		}
		operator bool() const
		{
			return m_ptr && m_ptr->operator bool();
		}
	public:
		T& operator*()
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return m_ptr->operator*();
		}
		T const& operator*() const
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return m_ptr->operator*();
		}
		T* operator->()
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return m_ptr->operator->();
		}
		T const* operator->() const
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return m_ptr->operator->();
		}
		T* get()
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return m_ptr->get();
		}
		T const* get() const
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return m_ptr->get();
		}
		void unbind()
		{
			if (m_ptr)
			{
				m_ptr->dec_ref_count();
				m_ptr = nullptr;
			}
		}
		void bind(optr<T>& other)
		{
			unbind();
			m_ptr = &other;
			m_ptr->inc_ref_count();
		}
		bool is_bound() const
		{
			return m_ptr;
		}
	private:
		optr<T>* m_ptr;
	};
}
