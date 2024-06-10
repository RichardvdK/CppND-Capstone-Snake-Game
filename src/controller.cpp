#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::ChangeDifficulty(Eagle &eagle, Eagle::Difficulty input) const {
  std::cout << "Current difficulty: " << static_cast<int>(eagle.GetDifficulty()) << std::endl;
  if (input < eagle.GetDifficulty()) {
    auto new_difficulty = static_cast<Eagle::Difficulty>(static_cast<int>(eagle.GetDifficulty()) - 1);
    std::cout << " Difficutly descreased to " << static_cast<int>(new_difficulty) << std::endl;
    eagle.SetDifficulty(new_difficulty);
  }
  else if (input > eagle.GetDifficulty()) {
    auto new_difficulty = static_cast<Eagle::Difficulty>(static_cast<int>(eagle.GetDifficulty()) + 1);
    std::cout << " Difficutly increased to " << static_cast<int>(new_difficulty) << std::endl;
    eagle.SetDifficulty(new_difficulty);
  }
}

void Controller::HandleInput(bool &running, Snake &snake, Eagle &eagle) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;

        case SDLK_LEFTBRACKET:
          ChangeDifficulty(eagle, Eagle::Difficulty::Easy);
          break;

        case SDLK_RIGHTBRACKET:
          ChangeDifficulty(eagle, Eagle::Difficulty::Hard);
          break;
      }
    }
  }
}
