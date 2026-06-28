#pragma once

#include "../gfx/gfx.h"

#include "types.h"

#define NS_PER_SECOND 1000000000
#define NS_PER_MS 1000000

#define NOW() ((u64)(glfwGetTime() * NS_PER_SECOND))