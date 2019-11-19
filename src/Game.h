#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Entity.h"
#include <iostream>
#include <list>
#include <memory>
#include <random>

// create_renderer paramaters
#define INDEX_OF_RENDERING_DRIVER -1
#define RENDERER_FLAG 0

// background color
#define RED 255
#define GREEN 255
#define BLUE 255
#define ALPHA 255

// prepare banner size
#define PREPARE_WIDTH 512
#define PREPARE_HEIGHT 64
#define PREPARE_DELAY 3000

// game over banner size
#define GAME_OVER_WIDTH 512
#define GAME_OVER_HEIGHT 128
#define GAME_OVER_DELAY 3000

// win banner size
#define WIN_WIDTH 384
#define WIN_HEIGHT 128
#define WIN_DELAY 3000

// one unit size similar to metter
#define UNIT 32

// probability that bonus will be droped out of enemy in percent
#define BONUS_PROBABILITY 75
#define RELOAD_BONUS_PROBABILITY 75


/*!
 * Game class which holds every method needed for running the game
 */
class Game {
  
  public:
    /**
     * Game constructor
     * @param[in] name Name of the game which will be displayd on window
     * @param[in] fullscreen If set to true game runs in fullscreen
     * @param[in] map_path Path to map file
     */ 
    Game ( const char * name, bool fullscreen, const char * map_path );
    ~Game ();

    /**
     * Game runing getter
     * @return returns the bool value wethere game is runing
     */ 
    bool running () const { return is_running; }

    /**
     * Method for handling the events
     */
    void handle_events ();

    /**
     * Method for checking collisions of entities in game
     */
    void collisions ();
    
    /**
     * Method for drawing banner with initial or end game state on the screen
     * @param[in] ban instance of Banner class which is used for displaying all banners
     */
    void banner_render ( Banner & ban );

    /**
     * Method for rendering entities on screen
     */
    void render ();

    /**
     * Method for loading map file 
     * @param[in] path Path to map file 
     */
    void load_map ( const char * path );
    void quit();

    /*! event structure that is used to pass my events like tick or player position */
    SDL_Event event;
  private:
    size_t map_width;
    size_t map_height;

    //! variable where window will be rendered to
    SDL_Window * win;

    //! flag wheter game should still run
    bool is_running;

    //! rendrer variable that is passed to SDL for rendering
    SDL_Renderer * renderer;

    //! List of enemies might be a vector too but erase is more efficient in list
    std::list<std::unique_ptr<Entity>> enemies;

    //! List of walls might be a vector too but erase is more efficient in list
    std::list<std::unique_ptr<Entity>> walls;

    //! List of projcetiles might be a vector too but erase is more efficient in list
    std::list<std::unique_ptr<Entity>> projectiles;

    //! List of bonuses might be a vector too but erase is more efficient in list
    std::list<std::unique_ptr<Entity>> bonuses;

    //! Instance of Player class which is used for interaction with user
    Player player;

    //! Instance of Banner class which is used for banner displaying
    Banner banner;
};
