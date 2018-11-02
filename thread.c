/******************************************
thread.c
SDL thread experiment
Zack Mitchell Klaric
2018 nov 2
*******************************************/
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

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

  puts("ToolThread says: Hi");
  return 0;
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
  
