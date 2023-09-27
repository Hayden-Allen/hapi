#pragma once

namespace hapi
{
	template<typename T>
	class optr final
	{
	public:
		optr() : m_ptr(nullptr) {}
		explicit optr(T* const newptr) : m_ptr(newptr) {}
		template<typename ... ARGS>
		explicit optr(ARGS&& ... args) : m_ptr(new T(std::move(args...))) {}
		optr(optr<T> const& other) = delete;
		optr(optr<T>&& other) noexcept :
			m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}
		~optr()
		{
			// you forgot to call free() loser
			if (m_ptr)
				abort();
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
		bool operator==(const optr<T>& other)
		{
			return m_ptr == other.m_ptr;
		}
		bool operator!=(const optr<T>& other)
		{
			return m_ptr != other.m_ptr;
		}
	public:
		T& operator*()
		{
			return *m_ptr;
		}
		T const& operator*() const
		{
			return *m_ptr;
		}
		T* operator->()
		{
			return m_ptr;
		}
		T const* operator->() const
		{
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
			delete m_ptr;
			m_ptr = nullptr;
		}
	private:
		T* m_ptr;
	};
}
