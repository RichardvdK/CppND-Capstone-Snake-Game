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
  float GetBodyX() const { return body_x;}
  void SetBodyX(float x) {body_x = x;}
  float GetBodyY() const { return body_y;}
  void SetBodyY(float y) {body_y = y;}
  float GetRelativeSpeed() const {return relative_speed;}
  void SetRelativeSpeed(float speed) {
    relative_speed = speed;
    std::cout << "Speed: " << relative_speed << "\n";
  }

  // Change the difficulty of the game
  void SetDifficulty(Difficulty difficulty);
  Difficulty GetDifficulty() const {return difficulty;}

  SDL_Point current_cell{
      static_cast<int>(body_x),
      static_cast<int>(body_y)};  // Capture the body's cell after updating.

private:
    SDL_Surface* image;
    std::shared_ptr<const Snake> snake;
    float relative_speed{snake.get()->speed / 4.0};
    int grid_width;
    int grid_height;
    float body_x;
    float body_y;
    bool cathed{false};
    Difficulty difficulty{Difficulty::Medium};

    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);




  // Add any additional member functions or variables as needed
};
