#include <stdlib.h>
#include <libguile.h>
#include <SDL.h>

#define WIN_W 640
#define WIN_H 480

#define CHAR_W 5
#define CHAR_H 7

#define COLS_H (WIN_W / CHAR_W)
#define COLS_V (WIN_H / CHAR_H)

SDL_Window *window;
SDL_Renderer *renderer;

static SCM init () {
  SDL_Init(SDL_INIT_VIDEO);
  int x = SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  return scm_from_int(x);
}

static SCM poke (SCM addr) {
  int c_addr = scm_to_int(addr);
  int col_y = c_addr / COLS_H;
  int col_x = c_addr % COLS_H;

  SDL_Rect rect = { col_x * CHAR_W, col_y * CHAR_H, CHAR_W, CHAR_H };
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
  SDL_RenderPresent(renderer);
  return scm_from_int(c_addr);
}

static void inner_main (void *data, int argc, char **argv) {
  scm_c_define_gsubr("video-init", 0, 0, 0, init);
  scm_c_define_gsubr("video-poke", 1, 0, 0, poke);
  scm_shell(argc, argv);
}

int main (int argc, char **argv) {
  scm_boot_guile(argc, argv, inner_main, 0);
  return 0;
}
