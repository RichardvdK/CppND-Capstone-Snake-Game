#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "eagle.h"
#include <mutex>
#include <condition_variable>
#include <thread>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  std::shared_ptr<Snake> snake;
  Eagle eagle;
  SDL_Point food;
  SDL_Point extra_food;

  std::mutex mtx;
  std::condition_variable cond;
  std::thread ExtraFoodThread;
  bool extra_food_placed{false};

  // Random number generation
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlaceExtraFoodTimer();
  void PlaceExtraFood();

  void Update();
};

#endif
