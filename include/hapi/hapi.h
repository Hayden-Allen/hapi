#pragma once
#include "../../src/optr.h"
#include "../../src/wptr.h"
#include "../../src/rptr.h"

namespace hapi
{
	template<typename T>
	static bool operator==(const optr<T>& a, const wptr<T>& b)
	{
		return a.get() == b.get();
	}
	template<typename T>
	static bool operator==(const optr<T>& a, const rptr<T>& b)
	{
		return a.get() == b.get();
	}
	template<typename T>
	static bool operator==(const wptr<T>& a, const rptr<T>& b)
	{
		return a.get() == b.get();
	}
	template<typename T>
	static bool operator!=(const optr<T>& a, const wptr<T>& b)
	{
		return a.get() != b.get();
	}
	template<typename T>
	static bool operator!=(const optr<T>& a, const rptr<T>& b)
	{
		return a.get() != b.get();
	}
	template<typename T>
	static bool operator!=(const wptr<T>& a, const rptr<T>& b)
	{
		return a.get() != b.get();
	}
}
