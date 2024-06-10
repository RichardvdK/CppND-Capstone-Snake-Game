#pragma once

#include <iostream>
#include "SDL.h"
#include "snake.h"
#include <memory>

class Eagle {
public:
  enum class Difficulty {Easy, Medium, Hard};

  // Constructor
  Eagle(std::shared_ptr<const Snake> snake)
      : grid_width(snake->GetGridSize().first),
        grid_height(snake->GetGridSize().second),
        body_x(grid_width / 2),
        body_y(grid_height / 2),
        snake(snake){
        SetDifficulty(difficulty);
  }

  void Update();

  // Getters and setters
  float GetRelativeSpeed() const {return relative_speed;}
  void SetRelativeSpeed(const float& speed);

  // Change the difficulty of the game
  void SetDifficulty(const Difficulty& difficulty);
  Difficulty GetDifficulty() const {return difficulty;}

  float body_x;
  float body_y;

  // Check if the eagle has caught the snake
  bool snake_cathed{false};

private:
    SDL_Surface* image; // The image surface to be rendered
    std::shared_ptr<const Snake> snake;
    int grid_width;
    int grid_height;
    float relative_speed{1};
    Difficulty difficulty{Difficulty::Medium};
};
