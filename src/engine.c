#include <stdlib.h>
#include <libguile.h>
#include <SDL.h>

#define WIN_W 640
#define WIN_H 480

#define CHAR_W 8
#define CHAR_H 8

#define COLS_H (WIN_W / CHAR_W)
#define COLS_V (WIN_H / CHAR_H)

#define CHARSET_FILE "assets/charset.bmp"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *charset;

static SCM init () {
  SDL_Init(SDL_INIT_VIDEO);
  int x = SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &window, &renderer);

  SDL_Surface *surface = SDL_LoadBMP(CHARSET_FILE);
  charset = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  return scm_from_int(x);
}

static void clear () {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

static SCM get_ticks () {
  Uint32 ticks = SDL_GetTicks();
  return scm_from_uint32(ticks);
}

static SCM poke (SCM addr, SCM s_chr) {
  int c_addr = scm_to_int(addr);
  int col_y = c_addr / COLS_H;
  int col_x = c_addr % COLS_H;

  char chr = scm_to_char(s_chr);
  int chr_y = chr / 16;
  int chr_x = chr % 16;
  
  clear();
  
  SDL_Rect src = { chr_x * CHAR_W, chr_y * CHAR_H, CHAR_W, CHAR_H };
  SDL_Rect dst = { col_x * CHAR_W, col_y * CHAR_H, CHAR_W, CHAR_H };
  SDL_RenderCopy(renderer, charset, &src, &dst);
  SDL_RenderPresent(renderer);
  return scm_from_int(c_addr);
}

static SCM delay (SCM s_ms) {
  Uint32 ms = scm_to_uint32(s_ms);
  SDL_Delay(ms);
  return SCM_BOOL_T;
}

static void inner_main (void *data, int argc, char **argv) {
  scm_c_define_gsubr("sys-init", 0, 0, 0, init);
  scm_c_define_gsubr("sys-get-ticks", 0, 0, 0, get_ticks);
  scm_c_define_gsubr("sys-poke", 2, 0, 0, poke);
  scm_c_define_gsubr("sys-delay", 1, 0, 0, delay);
  scm_shell(argc, argv);
}

int main (int argc, char **argv) {
  scm_boot_guile(argc, argv, inner_main, 0);
  return 0;
}
