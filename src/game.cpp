#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
#include <csignal>
#include <atomic>

std::atomic<bool> keep_running(true);

void signal_handler(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nSIGINT received. Stopping threads..." << std::endl;
        keep_running.store(false);
    }
}

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(std::make_shared<Snake>(grid_width, grid_height)),
      eagle(snake),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  ExtraFoodThread = std::thread(&Game::PlaceExtraFoodTimer, this);

  // Setup the signal handler for SIGINT
  std::signal(SIGINT, signal_handler);

  while (running && keep_running.load() ){
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, *snake, eagle);
    Update();
    renderer.Render(*snake, eagle, food, extra_food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  // Game over message
  if (!snake->alive || eagle.snake_cathed) {
      std::cout << (snake->alive ? "Eagle caught the snake!" : "Snake is dead!")
                << " Game Over! Score: " << score << "\n";
      return;
  }

  std::cout << "Waiting for extra food thread to finish..." << std::endl;
  // Signal the extra food thread to stop one more time
  keep_running.store(false);
  ExtraFoodThread.join();
}

void Game::PlaceFood() {
  std::lock_guard<std::mutex> lck(mtx);
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceExtraFoodTimer(){
  const int time_for_extra_food = 3; // Time in seconds
  const int time_for_no_extra_food = 7; // Time in seconds

  auto startTime = std::chrono::high_resolution_clock::now();
  std::unique_lock<std::mutex> lock(mtx);
  bool is_extra_food_time = true;
  while (keep_running.load())
  {
    cond.wait(lock, [this]{return extra_food_placed;});
    auto current_Time = std::chrono::high_resolution_clock::now();
    auto elapsed_Seconds = std::chrono::duration_cast<std::chrono::seconds>(current_Time - startTime).count();
    if (is_extra_food_time && elapsed_Seconds >= time_for_extra_food)
    {
      // Extra food is not eaten in time
      extra_food.x = -1;
      extra_food.y = -1;
      is_extra_food_time = false;
      startTime = std::chrono::high_resolution_clock::now();
    }
    else if (!is_extra_food_time && elapsed_Seconds >= time_for_no_extra_food)
    {
      // Time for no extra food is over
      is_extra_food_time = true;
      extra_food_placed = false;
      startTime = std::chrono::high_resolution_clock::now();
    }
    // Wait for a short interval before placing extra food again
    cond.wait_for(lock, std::chrono::milliseconds(1000));
  }
}

void Game::PlaceExtraFood(){
  std::lock_guard<std::mutex> lck(mtx);

  if (!extra_food_placed)
    {
      int x = random_w(engine);
      int y = random_h(engine);

    if (!snake->SnakeCell(x, y)) {
       extra_food.x = x;
       extra_food.y = y;
    	}
      extra_food_placed = true;
      cond.notify_one();
    }
}

void Game::Update() {
  if (!snake->alive || eagle.snake_cathed){return;}

  // Update snake and eagle position and check for collision
  snake->Update();
  eagle.Update();

  int new_x = static_cast<int>(snake->GetHeadX());
  int new_y = static_cast<int>(snake->GetHeadY());

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02;
  }

  // Create extra food if it is not placed yet
  PlaceExtraFood();

  // Check if there's extra food over here
  if (extra_food.x == new_x && extra_food.y == new_y) {
    score += 5;
    std::cout << "Extra food eaten! Extra points! +5" << std::endl;
    extra_food_placed = false;
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }
