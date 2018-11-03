/******************************************
thread2.c
SDL thread experiment - And Xlib
Zack Mitchell Klaric
2018 nov 2
*******************************************/
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

/////////GLOBALS////////////////////////
////////////////////////////////////////
//SDL_Mutex MyMutex;
////////////////////////////////////////
////////////////////////////////////////

int ViewMain(void *point) {

  SDL_Surface *Window;
  SDL_Event    Event;
  
  Window = SDL_SetVideoMode(640, 480, 0, SDL_DOUBLEBUF);
  
  while(SDL_WaitEvent(&Event) != 0)  {
  
    switch(Event.type)  {
    
      case SDL_QUIT:    { puts("ViewThread says: Bye"); return 0; }
      }
    }

  return 0;
}

int ToolMain(void *point)  {

  Display *D;
  Window   W;
  XEvent   E;
  int      S;
  
  const char *msg = "Hello, World!";
  
  XInitThreads();
  
  if ( ( D = XOpenDisplay(NULL) ) == NULL )  {
  
    fprintf(stderr, "Cannot open display\n");
    return 1;
    }
    
  S = DefaultScreen(D);
  
  XLockDisplay(D);
  
  W = XCreateSimpleWindow(D, RootWindow(D, S), 10, 10, 100, 100, 1, BlackPixel(D, S), WhitePixel(D, S));
  XSelectInput(D, W, ExposureMask | KeyPressMask);
  XMapWindow(D, W);
  
  XUnlockDisplay(D);
  
  while ( XNextEvent(D, &E) );
  
   while (1) {
      XNextEvent(D, &E);
      if (E.type == Expose) {
         XLockDisplay(D);//??????????????????????????????
         XFillRectangle(D, W, DefaultGC(D, S), 20, 20, 10, 10);
         XDrawString(D, W, DefaultGC(D, S), 10, 50, msg, strlen(msg));
	 XUnlockDisplay(D);//????????????????????????????
      }
      if (E.type == KeyPress)
         break;
   }
  
  return 5;
}

int TaskMain(void *point)  {

  puts("TaskThread says: Hi");
  return 0;
}


int main()  {

  SDL_Thread *ViewThread,
             *ToolThread,
	     *TaskThread;
	     
  int *Return = malloc(sizeof(int)); // I never get to use malloc so SHUSH!
  
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 )  {
  
    printf("Woops: %s\n", SDL_GetError());
    exit(1);
  }

  atexit(SDL_Quit);
  
  ViewThread = SDL_CreateThread(ViewMain, "bop");
  ToolThread = SDL_CreateThread(ToolMain, "pop");
  TaskThread = SDL_CreateThread(TaskMain, "hop");
  
  //wait here for ViewThread to rejoin.
  SDL_WaitThread(ViewThread, Return);
  printf("return value of ViewThread: %d\n", *Return);
  puts  ("main thread exiting");
  
  return 0;
}
  
