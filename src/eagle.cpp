#include "eagle.h"

void Eagle::Update(){
  // Get the x and y coordinates of the snake
  int snakeX = snake.get()->head_x;
  int snakeY = snake.get()->head_y;

  // Calculate the distance between the eagle and the snake
  int distanceX = snakeX - body_x;
  int distanceY = snakeY - body_y;

  // Check the difficulty
  // SetDifficulty(difficulty);

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
if (snake.get()->SnakeCell(static_cast<int>(body_x), static_cast<int>(body_y))) {
    snake_cathed = true;
    std::cout << "The eagle has caught the snake!" << std::endl;
  }

}

void Eagle::SetDifficulty(Difficulty difficulty){
  this->difficulty = difficulty;
  switch (difficulty) {
    case Difficulty::Easy:
      SetRelativeSpeed(snake.get()->speed / 4.0f);
      break;
    case Difficulty::Medium:
      SetRelativeSpeed(snake.get()->speed / 3.0f);
      break;
    case Difficulty::Hard:
      SetRelativeSpeed(snake.get()->speed / 1.5f);
      break;
  }
}
