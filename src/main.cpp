
#include <iostream>
#include "Game.h"

using namespace std;

/*!  main function that takes comand line parameter of path to map file */
int main ( int argc, char **argv )
{
  //! path to mapfile
  char * path;
  if ( argc != 2 )
  {
    cout << "Invalid number of arguments" << endl;
    return 0;
  }
  else
  {
    path = argv[1];
  }
  
  //! standard fps of game
  const size_t FPS = 60;
  /*! frame exposure time in milliseconds so 1000 / FPS is a period of frame wiht 60fps in milliseconds */
  const size_t * frame_delay = new size_t ( 1000 / FPS );

  uint32_t frame_start;

  size_t last_frame = 0; 

  /** event structure that is used*/
  SDL_Event custom_event;
  custom_event . type = SDL_USEREVENT; //MY_EVENT_TYPE;
  custom_event . user . code = TIME_EVENT_CODE;
  custom_event . user . data1 = (void*)frame_delay;

  /*! instance of an Game class */
  Game game ( "semestralka", false, path );

  /** game loop where game class is runinng */
  while ( game . running() ) {

    game . handle_events ();
    game . collisions ();

    //! millisiseconds since initialization
    frame_start = SDL_GetTicks ();
    //! if computation of events update and render has been too fast
    if ( *frame_delay < ( frame_start - last_frame ) )
    {
      game . render ();
      last_frame = SDL_GetTicks();
      SDL_PushEvent ( & custom_event );
    }
    // else unfortunately we can not speed up our computational time
  }

  delete frame_delay;

}

