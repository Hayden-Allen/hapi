#pragma once
#include <functional>

namespace hapi
{
	template<typename T>
	class sptr;
#ifdef HAPI_OPAQUE
	template<typename T>
	class sptr;
#endif

	template<typename T>
#ifdef HAPI_OPAQUE
	class optr
	{
		template<typename U>
		friend class sptr;
		template<typename U>
		friend class wptr;
	public:
		template<typename U>
		optr(optr<U> const& other) :
			m_ptr(other.m_ptr)
		{}
#else
	class optr final
	{
		friend class sptr<T>;
	public:
		optr(optr<T> const& other) = delete;
#endif
	public:
		optr() :
			m_ptr(nullptr) {}
		explicit optr(T* const newptr) :
			m_ptr(newptr) {}
		template<typename... ARGS>
		explicit optr(ARGS&&... args) :
			m_ptr(new T(std::move(args...)))
		{}
		optr(optr<T>&& other) noexcept :
			m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}
		virtual ~optr()
		{
			// you still have sptrs that reference this optr, loser
			HAPI_ASSERT(m_ref_count == 0);
			// you forgot to call free(), loser
			HAPI_ASSERT(!m_ptr);
		}
	public:
		void operator=(optr<T> const& other) = delete;
		void operator=(optr<T>&& other)
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		void operator=(T* const newptr)
		{
			set(newptr);
		}
		bool operator==(optr<T> const& other)
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(optr<T> const& other)
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
			return (U*)m_ptr;
		}
		void set(T* const newptr)
		{
			if (m_ptr != newptr)
			{
				delete m_ptr;
				m_ptr = newptr;
			}
		}
		void free()
		{
			// you still have sptrs that reference this optr, loser
			HAPI_ASSERT(m_ref_count == 0);
			delete m_ptr;
			m_ptr = nullptr;
		}
	private:
		T* m_ptr;
#ifndef HAPI_OPAQUE
		uint64_t m_ref_count = 0;
	private:
		void dec_ref_count()
		{
			HAPI_ASSERT(m_ref_count != 0);
			m_ref_count--;
		}
		void inc_ref_count()
		{
			m_ref_count++;
		}
#endif
	};
} // namespace hapi
