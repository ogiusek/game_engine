#include <SDL2/SDL.h>
#include <cmath>

#include <thread>
using namespace std;

class FPS
{
private:
  int limit = 0;
  int last_frame = 0;

  void PerformFrame()
  {
    deltaTime = SDL_GetTicks() - last_frame;
    last_frame = SDL_GetTicks();
  }

  void Delay()
  {
    int wanted_time_between_frames = ceil(1000.0 / (float)limit);
    int time_between_frames = SDL_GetTicks() - last_frame;
    if (time_between_frames < wanted_time_between_frames)
      SDL_Delay(wanted_time_between_frames - time_between_frames);
  }

  bool CanMakeNextFrame()
  {
    return !(ceil(1000.0 / (float)limit) > SDL_GetTicks() - last_frame);
  }

  static void removeFps(int &fps_in_last_second)
  {
    SDL_Delay(1000);
    fps_in_last_second -= 1;
  }

public:
  int deltaTime = 0;
  int &ticks = last_frame;
  int fps_in_last_second = 0;

  void CountFps()
  {
    fps_in_last_second += 1;

    thread remove_fps_thread(removeFps, ref(fps_in_last_second));
    remove_fps_thread.detach();
  }

  void MakeNewFrame()
  {
    Delay();
    PerformFrame();
    CountFps();
  }

  FPS(int _limit) : limit(_limit), last_frame(SDL_GetTicks()) {}
};