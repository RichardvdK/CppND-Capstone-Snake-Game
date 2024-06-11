#include "eagle.h"

// Update the eagle's position based on the snake's position
void Eagle::Update(){

  // Get the x and y coordinates of the snake
  int snakeX = snake->GetHeadX();
  int snakeY = snake->GetHeadY();

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

/**
 * @brief Sets the difficulty level for the eagle.
 *
 * This function sets the difficulty level for the eagle based on the provided `difficulty` parameter.
 * The difficulty level determines the relative speed of the eagle compared to the snake's speed.
 *
 * @param difficulty The difficulty level to set for the eagle.
 */
void Eagle::SetDifficulty(const Difficulty& difficulty){
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

/**
 * @brief Sets the relative speed of the eagle.
 *
 * This function sets the relative speed of the eagle object. The relative speed
 * determines how fast the eagle moves compared to the snake.
 *
 * @param speed The relative speed of the eagle wrt the snake.
 *
 * @return void
 */
void Eagle::SetRelativeSpeed(const float& speed){
  if (speed < 0.0f) {
    std::cerr << "Error: Speed must be greater than 0" << std::endl;
    return;
  }
  relative_speed = speed;
}
