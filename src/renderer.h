#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "snake.h"
#include "eagle.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, Eagle const eagle, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window* sdl_window;
  SDL_Renderer* sdl_renderer;
  SDL_Surface* sdl_imageSurface;
  SDL_Texture* sdl_imageTexture;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
