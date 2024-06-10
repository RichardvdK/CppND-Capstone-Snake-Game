#include "eagle.h"

void Eagle::Update(){
  // Get the x and y coordinates of the snake
  int snakeX = snake->head_x;
  int snakeY = snake->head_y;

  // Calculate the distance between the eagle and the snake
  int distanceX = snakeX - body_x;
  int distanceY = snakeY - body_y;

  // Move the eagle closer to the snake
  if (distanceX > 0) {
      body_x += GetRelativeSpeed();
  } else if (distanceX < 0) {
      body_x -= GetRelativeSpeed();
  }

  if (distanceY > 0) {
      body_y += GetRelativeSpeed();
  } else if (distanceY < 0) {
      body_y -= GetRelativeSpeed();
  }

// Check if the eagle has caught the snake
if (snake->SnakeCell(static_cast<int>(body_x), static_cast<int>(body_y))) {
    snake_cathed = true;
    std::cout << "The eagle has caught the snake!" << std::endl;
  }

}

void Eagle::SetDifficulty(Difficulty difficulty){
  this->difficulty = difficulty;
  switch (difficulty) {
    case Difficulty::Easy:
      SetRelativeSpeed(snake->speed / 4.0f);
      break;
    case Difficulty::Medium:
      SetRelativeSpeed(snake->speed / 3.0f);
      break;
    case Difficulty::Hard:
      SetRelativeSpeed(snake->speed / 1.5f);
      break;
  }
}
