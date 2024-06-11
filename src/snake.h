#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  // Create a getter for the grid size
  std::pair<int, int> GetGridSize() const { return {grid_width, grid_height}; }

  void GrowBody();
  bool SnakeCell(int x, int y) const;

  // Getters and setters
  float GetHeadX() const {return head_x;}
  void SetHeadX(float x){head_x = x;}

  float GetHeadY() const {return head_y;}
  void SetHeadY(float y){head_y = y;}

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  float head_x;
  float head_y;
};

#endif
