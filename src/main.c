#include "window.h"

#define WIDTH 680
#define HEIGHT 480

int main()
{
  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  while (!lowg_window_should_close(w)) {
    lowg_window_clear(1.0f, 1.0f, 0.0f);
    lowg_window_update(w);
  }

  return 0;
}
