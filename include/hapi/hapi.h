#pragma once
#ifndef HAPI_OPAQUE
#	define HAPI_ASSERT(x) \
		if (!(x)) __debugbreak();
#else
#	define HAPI_ASSERT(x)
#endif

#include "../../src/optr.h"
#include "../../src/wptr.h"
#include "../../src/sptr.h"
