#pragma once

#include "../render/render.h"
#include "../input_config/input_config.h"
#include "../input/input.h"
#include "../time/time.h"

typedef struct global {
    Render_State render;
    Config_State config;
    Input_State input;
    Time_State time;
} Global;

extern Global global;