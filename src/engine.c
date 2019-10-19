#include <stdlib.h>
#include <libguile.h>
#include <SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;

SCM hello () {
  return scm_from_locale_string("Hello");
}

void init_engine () {
  scm_c_define_gsubr("hello", 0, 0, 0, hello);
}
