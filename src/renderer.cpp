#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize SDL_image for the eagle texture
  if (IMG_Init(IMG_INIT_PNG) == 0) {
      std::cerr << "IMG_Init Error: " << IMG_GetError() << "\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Load the Eagle image
  std::string imagePath = "../src/eagle_small.png";
  sdl_imageSurface = IMG_Load(imagePath.c_str());
    if (nullptr == sdl_imageSurface) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

  // Create a texture from the surface and free the surface afterwards to save memory
  sdl_imageTexture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_imageSurface);
  SDL_FreeSurface(sdl_imageSurface);
  if (nullptr == sdl_imageTexture) {
      std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyTexture(sdl_imageTexture);
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(const Snake& snake, Eagle const eagle, SDL_Point const &food, SDL_Point const &extra_food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render extra food if it is placed
  SDL_Rect extra_block;
  extra_block.w = screen_width / grid_width;
  extra_block.h = screen_height / grid_height;

  // create a green extra food block
  // std::cout << "extra_food.x: " << extra_food.x << " extra_food.y: " << extra_food.y << std::endl;
  if (extra_food.x != -1 && extra_food.y != -1) {

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
    block.x = extra_food.x * block.w;
    block.y = extra_food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render the eagle texture on the screen at the eagle's position
  block.x = static_cast<int>(eagle.body_x) * block.w;
  block.y = static_cast<int>(eagle.body_y) * block.h;
  SDL_RenderCopy(sdl_renderer, sdl_imageTexture, NULL, &block);

  // Render snake's head
  block.x = static_cast<int>(snake.GetHeadX()) * block.w;
  block.y = static_cast<int>(snake.GetHeadY()) * block.h;
  if (snake.alive && !eagle.snake_cathed) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
