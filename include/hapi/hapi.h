#pragma once
#define HAPI_ASSERT(x) \
	if (!(x)) __debugbreak();

#include "../../src/optr.h"
#include "../../src/wptr.h"
#include "../../src/sptr.h"
