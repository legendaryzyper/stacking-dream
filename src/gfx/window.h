#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef void (*FWindow)();

typedef struct Window {
    GLFWwindow *handle;
    FWindow init, tick, update, render, destroy;
    ivec2s size;
} Window;

extern Window window;

void window_init(FWindow init, FWindow tick, FWindow update, FWindow render, FWindow destroy);
void window_loop(void);
