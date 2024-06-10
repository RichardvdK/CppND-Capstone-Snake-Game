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
  // std::cout << "Speed: " << GetRelativeSpeed() << "\n";

  if (distanceX > 0) {
    SetBodyX(body_x + GetRelativeSpeed());
  } else if (distanceX < 0) {
    SetBodyX(body_x - GetRelativeSpeed());
  }

  if (distanceY > 0) {
    SetBodyY(body_y + GetRelativeSpeed());
  } else if (distanceY < 0) {
    SetBodyY(body_y - GetRelativeSpeed());
  }

  // Wrap the Eagle around to the beginning if going off of the screen.
  body_x = fmod(body_x + grid_width, grid_width);
  body_y = fmod(body_y + grid_height, grid_height);
}

void Eagle::SetDifficulty(Difficulty difficulty){
  this->difficulty = difficulty;
  switch (difficulty) {
    case Difficulty::Easy:
      SetRelativeSpeed(snake.get()->speed / 4.0f);
      break;
    case Difficulty::Medium:
      SetRelativeSpeed(snake.get()->speed / 2.0f);
      break;
    case Difficulty::Hard:
      SetRelativeSpeed(snake.get()->speed);
      break;
  }
}
