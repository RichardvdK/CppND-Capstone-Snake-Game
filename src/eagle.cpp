#include "eagle.h"

void Eagle::Update(){
  // Get the x and y coordinates of the snake
  int snakeX = snake.get()->head_x;
  int snakeY = snake.get()->head_y;

  // Calculate the distance between the eagle and the snake
  int distanceX = snakeX - body_x;
  int distanceY = snakeY - body_y;

  // Update relative speed
  SetRelativeSpeed(snake.get()->speed / 4.0);

  // Move the eagle closer to the snake

  std::cout << "Speed: " << GetRelativeSpeed() << "\n";

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

  // Capture the body's cell after updating.
  current_cell = {
      static_cast<int>(body_x),
      static_cast<int>(body_y)};
}
