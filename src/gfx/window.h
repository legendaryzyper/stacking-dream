#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef void (*FWindow)(void);

typedef struct Button {
    bool down, pressed, pressed_event;
} Button;

typedef struct Mouse {
    Button buttons[GLFW_MOUSE_BUTTON_LAST + 1];
    vec2s position, delta;
    f32 sensitivity;
    bool not_first;
} Mouse;

typedef struct Keyboard {
    Button keys[GLFW_KEY_LAST + 1];
} Keyboard;

typedef struct Window {
    GLFWwindow *handle;
    Keyboard keyboard;
    Mouse mouse;
    FWindow init, input, tick, update, render, destroy;
    ivec2s size;
    u64 last_second;
    u64 frames, fps, last_frame, frame_delta;
    u64 ticks, tps, tick_remainder;
    u32 tickrate;
} Window;

extern Window window;

void window_init(FWindow init, FWindow input, FWindow tick, FWindow update, FWindow render, FWindow destroy);
void window_loop(void);