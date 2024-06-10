#pragma once

#include <iostream>
#include "SDL.h"

class Eagle {
public:
  enum class FlyDirection { kUp, kDown, kLeft, kRight };

  // Constructor
  Eagle(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        body_x(grid_width / 2),
        body_y(grid_height / 2) {
    std::cout << "Eagle constructor\n";
  }

  void Update();

  // Getter for body_x
  float GetBodyX() const { return body_x;}

  // Setter for body_x
  void SetBodyX(float x) {body_x = x;}

  // Getter for body_y
  float GetBodyY() const { return body_y;}

  // Setter for body_y
  void SetBodyY(float y) {body_y = y;}

  SDL_Point current_cell{
      static_cast<int>(body_x),
      static_cast<int>(body_y)};  // Capture the body's cell after updating.

private:
    int grid_width;
    int grid_height;
    float body_x;
    float body_y;
    SDL_Surface* image;

    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);




  // Add any additional member functions or variables as needed
};
