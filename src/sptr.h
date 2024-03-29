#pragma once
#include <functional>
#include "optr.h"

namespace hapi
{
#ifdef HAPI_OPAQUE
	template<typename T>
	class sptr final : public optr<T>
	{
		template<typename U>
		friend class sptr;
	public:
		template<typename U>
		sptr(optr<U> const& other)
		{
			this->m_ptr = (T*)other.m_ptr;
		}
		template<typename U>
		sptr(sptr<U> const& other)
		{
			this->m_ptr = (T*)other.m_ptr;
		}
		sptr(optr<T> const& other)
		{
			this->m_ptr = other.m_ptr;
		}
		sptr(sptr<T> const& other)
		{
			this->m_ptr = other.m_ptr;
		}
	public:
		sptr<T>& operator=(sptr<T> const& other)
		{
			this->m_ptr = other.m_ptr;
			return *this;
		}
		void unbind()
		{
			this->m_ptr = nullptr;
		}
		template<typename U>
		void bind(optr<U>& other)
		{
			this->m_ptr = other.m_ptr;
		}
		template<typename U>
		void bind(sptr<U> const& other)
		{
			this->m_ptr = other.m_ptr;
		}
	};
#else
	template<typename T>
	class sptr final
	{
		template<typename U>
		friend class sptr;
	public:
		sptr() = delete;
		template<typename U>
		sptr(sptr<U> const& other) :
			m_ptr((optr<T>*)other.m_ptr)
		{
			if (m_ptr)
			{
				m_ptr->inc_ref_count();
			}
		}
		sptr(sptr<T> const& other) :
			m_ptr(other.m_ptr)
		{
			if (m_ptr)
			{
				m_ptr->inc_ref_count();
			}
		}
		template<typename U>
		sptr(optr<U>& other) :
			m_ptr((optr<T>*)&other)
		{
			if (m_ptr)
			{
				m_ptr->inc_ref_count();
			}
		}
		template<typename U>
		sptr(optr<U>&& other) = delete;
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
		bool operator==(sptr<T> const& other)
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(sptr<T> const& other)
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
			return (T&)m_ptr->operator*();
		}
		T const& operator*() const
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return (T const&)m_ptr->operator*();
		}
		T* operator->()
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return (T*)m_ptr->operator->();
		}
		T const* operator->() const
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return (T const*)m_ptr->operator->();
		}
		template<typename U = T>
		U* get()
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return (T*)m_ptr->get();
		}
		template<typename U = T>
		U const* get() const
		{
			// your sptr isn't bound, loser
			HAPI_ASSERT(m_ptr);
			return (T const*)m_ptr->get();
		}
		void unbind()
		{
			if (m_ptr)
			{
				m_ptr->dec_ref_count();
				m_ptr = nullptr;
			}
		}
		template<typename U>
		void bind(optr<U>& other)
		{
			unbind();
			m_ptr = &other;
			m_ptr->inc_ref_count();
		}
		template<typename U>
		void bind(sptr<U> const& other)
		{
			unbind();
			m_ptr = other.m_ptr;
			m_ptr->inc_ref_count();
		}
		bool is_bound() const
		{
			return m_ptr;
		}
	private:
		optr<T>* m_ptr;
	};
#endif
} // namespace hapi
