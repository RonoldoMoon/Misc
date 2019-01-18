#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include <ncurses.h> // -lncurses

//#define _GNU_SOURCE

void ConjunctionFunction(int Burp)  {

  if ( Burp == SIGHUP ) puts("Hup hup.");
  else                  puts("\nYou cant destroy ME!");

}


int main()  {

  int*   SigHandle;
  int    FileHandle;
  char   ToughBuff;
  struct winsize w;
  char*  string = "Susan";
  
  SigHandle = signal(SIGINT, ConjunctionFunction);
  
  FileHandle = open("/dev/random", O_RDONLY);
  
  initscr();
  start_color();
  
  while(1)  {
  
  read(FileHandle, &ToughBuff, 1);
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  
  init_pair(1, ((ToughBuff % 7 ) + 1 ), COLOR_BLACK);
  //init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));
  mvprintw( (((ToughBuff & 0x000000FF) % w.ws_row ) - 0 ),
            (((ToughBuff & 0x000000FF) % w.ws_col ) - (strlen(string)) ), string);
  refresh();
  attroff(COLOR_PAIR(1));
  sleep(1);
  
  }
  
  return(0);
}
