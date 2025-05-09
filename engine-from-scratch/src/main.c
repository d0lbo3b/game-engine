#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <linmath.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/global/global.h"
#include "engine/input/input.h"
#include "engine/input_config/input_config.h"
#include "engine/time/time.h"

#define VELOCITY 500

static bool should_quit = false;
static vec2 pos;

static void input_handle(void){
    if (global.input.left == KS_PRESSED || global.input.left == KS_HELD){
        pos[0] -= VELOCITY*global.time.delta;
    } 
    if (global.input.right == KS_PRESSED || global.input.right == KS_HELD){
        pos[0] += VELOCITY*global.time.delta;
    } 
    if (global.input.up == KS_PRESSED || global.input.up == KS_HELD){
        pos[1] += VELOCITY*global.time.delta;
    } 
    if (global.input.down == KS_PRESSED || global.input.down == KS_HELD){
        pos[1] -= VELOCITY*global.time.delta;
    } 
    if (global.input.escape == KS_PRESSED || global.input.escape == KS_HELD){
        should_quit = true;
    }
}

int main(int argc, char **argv){
    time_init(180);
    config_init();
    render_init();

    pos[0] = global.render.width*0.5;
    pos[1] = global.render.height*0.5;

    while (!should_quit){
        time_update();
        SDL_Event event;

        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:{
                should_quit = true;
            } break;
            default:
                break;
            }
        }

        input_update();
        input_handle();

        render_begin();

        render_quad(
            (vec2){pos[0], pos[1]},
            (vec2){100, 100},
            (vec4){1, 0, 0, 1}
        );

        render_end();
        time_update_late();
    }

    return 0;
}