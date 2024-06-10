#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "eagle.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, Eagle &eagle) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

    void ChangeDifficulty(Eagle &eagle, Eagle::Difficulty input) const;
};

#endif
