#include <libguile.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define CYAN {100,200,255}
#define AMBER {255,200,100}
#define BLACK {0,0,0}

#define WIN_W 640
#define WIN_H 480

#define CHRS 256

#define TICKS_PER_SECOND 20
#define SKIP_TICKS (1000 / TICKS_PER_SECOND)

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *textures[CHRS];

int font_w;
int font_h;

SCM initw(SCM s_font_file, SCM s_font_w, SCM s_font_h) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WIN_W, WIN_H, 0, &window, &renderer);

  font_w = scm_to_int(s_font_w);
  font_h = scm_to_int(s_font_h);

  char *font_file = scm_to_locale_string(s_font_file);
  
  TTF_Init();
  TTF_Font *font = TTF_OpenFont(font_file, font_h);

  free(font_file);
  
  SDL_Surface *text_surface;
  SDL_Color color = AMBER;
  for (int i = 0; i < CHRS; i++) {
    char c[1] = { i };
    text_surface = TTF_RenderText_Solid(font, c, color); 
    textures[i] = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
  }
  
  TTF_CloseFont(font);
  TTF_Quit();

  return SCM_BOOL_T;
}

SCM clearw() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);

  return SCM_BOOL_T;
}

SCM printw(SCM s_x, SCM s_y, SCM s_str) {
  int x = scm_to_int(s_x);
  int y = scm_to_int(s_y);
  
  char *str = scm_to_locale_string(s_str);
  SDL_Rect src = { 0, 0, font_w, font_h };
  
  for (int i = 0; i < strlen(str); i++) {
    SDL_Rect dest = { (x + i) * font_w, y * font_h, font_w, font_h };
    SDL_RenderCopy(renderer, textures[str[i]], &src, &dest);
  }
  free(str);
  
  return SCM_BOOL_T;
}

SCM refreshw() {
  SDL_RenderPresent(renderer);

  return SCM_BOOL_T;
}

SCM delayw(SCM s_ms) {
  Uint32 ms = scm_to_uint32(s_ms);
  SDL_Delay(ms);
  
  return SCM_BOOL_T;
}

SCM exitw() {
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return SCM_BOOL_T;
}

void init_ascii () {
  scm_c_define_gsubr("initw", 3, 0, 0, initw);
  scm_c_define_gsubr("clearw", 0, 0, 0, clearw);
  scm_c_define_gsubr("printw", 3, 0, 0, printw);
  scm_c_define_gsubr("refreshw", 0, 0, 0, refreshw);
  scm_c_define_gsubr("delayw", 1, 0, 0, delayw);
  scm_c_define_gsubr("exitw", 0, 0, 0, exitw);
}

