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

  void Render(const Snake& snake, Eagle const eagle, SDL_Point const &food, SDL_Point const &extra_food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window* sdl_window; // The window we'll be rendering to
  SDL_Renderer* sdl_renderer; // The window renderer we'll be rendering to
  SDL_Surface* sdl_imageSurface; // The image surface to be rendered
  SDL_Texture* sdl_imageTexture; // The image texture to be rendered

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
