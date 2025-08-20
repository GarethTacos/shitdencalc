#include <notcurses/notcurses.h>
#include <unistd.h>
int main(void) {
  // initialize notcurses with default options, output to stdout
  struct notcurses_options opts = {0};
  struct notcurses* nc = notcurses_init(&opts, NULL);
  if (!nc) {
    return 1;
  }

  // get the standard plane (the default drawing canvas)
  struct ncplane* stdn = notcurses_stdplane(nc);

  // write "Hello, World!" at upper-left (y=1, x=1)
  ncplane_printf_yx(stdn, 1, 1, "Hello, World!");

  // render to the screen
  notcurses_render(nc);
  //
  sleep(2);
  // clean up and restore terminal
  notcurses_stop(nc);
  return 0;
}

