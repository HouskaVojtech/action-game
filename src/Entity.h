#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <cmath>
#include <iterator>
#include "Vector2.h"
#include <random>

#define PROJECTILE_HEIGHT 5
#define PROJECTILE_WIDTH 10

#define RELOAD 20

#define TIME_EVENT_CODE 0
#define PLAYER_MOVE_EVENT_CODE 2
#define DEFAULT_PROJECTILE_SPEED 1

#define DEFAULT_ENEMY_SPEED 0.3

/**
 * Class that represents all entitis in game
 */
class Entity {
  protected:
    //! position of entity in window
    Vector2 position;

    //! velocity of entity
    Vector2 velocity;

    //! width of entity
    int width;

    //! height of entity
    int height;

    //! texture of entity
    SDL_Texture * texture;

    //! are in texture that is going to be drawn
    SDL_Rect src_rect;

    //! rectangle of entity in window
    SDL_Rect dst_rect;

    //! angle of entity in window
    size_t angle;

    //! direction of entity 
    SDL_RendererFlip flip;

    //! renderer variable used to pass to SDL for rendering
    SDL_Renderer * renderer;

    //! path to texture file of entity
    std::string texture_path; 
  public:

    explicit Entity ();

    /**
     * explicit contstuctor that specifies necesarry data
     * @param[in] x X coordinates of upper left corner of entity in window
     * @param[in] y Y coordinates of upper left corner of entity in window
     * @param[in] w Width of entity
     * @param[in] h Height of entity
     * @param[in] path Path to file that holds texture of entity
     */
    explicit Entity ( int x, int y, int w, int h, const char * path );

    /**
     * Position getter
     * @return Vector of current position
     */ 
    Vector2 get_position () const;

    /**
     * Getter that returns width and height
     * @return Vector with width and height
     */ 
    Vector2 get_width_height () const;

    /**
     * Postion setter
     * @param[in] x X coordinate of position
     * @param[in] y Y coordinate of position
     */
    void set_position ( int x, int y );

    /**
     * Method that checks wether other entity intersects with this entity
     * @param[in] e Other entity
     * @return Returns false if does not intersect
     */
    virtual bool intersects ( Entity * e ) const;

    /**
     * Method that checks wether this entity intersects with area specified by parameters
     * @param[in] x X coordinate of upper left corner of rectangular region
     * @param[in] y Y coordinate of upper left corner of rectangular region
     * @return Returns false if does not intersect
     */
    virtual bool intersects ( int x, int y, int height, int width ) const;

    /**
     * Sets renderer
     * @param[in] rndr Parameter to pass renderer that is used for SDL functions to render entities
     */
    void set_renderer ( SDL_Renderer * rndr );

    /**
     * Method that loads texture from path variable
     */
    void load_texture ();
    
    /**
     * Method used to draw entity on window
     */
    virtual void draw () const ;
                    
    /**
     * Pure virtual method that is used for handeling events by subclasses
     */
    virtual void on_event ( SDL_Event & event ) = 0;

};

class Projectile : public Entity
{
  private:
    //! speed of projectile with default value 1
    double speed = DEFAULT_PROJECTILE_SPEED;

  public:
    /**
     * Projectile constructor
     * @param[in] x X upper left coordinate of projdetile
     * @param[in] y Y upper left coordinate of projdetile
     * @param[in] w Width of projectile
     * @param[in] h Height of projectile
     * @param[in] path Path to procjectile texture
     * @param[in] angle Angle of projectile
     */
    Projectile ( int x, int y, int w, int h, const char * path, size_t angle ); 

    /**
     * Method that handles tick event
     * @param[in] event Reference to variable to pass event 
     */
    virtual void on_event ( SDL_Event & event );
};

class Player : public Entity
{
  //! Map width so player knows where to stop
  size_t map_width;

  //! Map height so player knows where to stop
  size_t map_height;

  //! Flag that checks whetger two keys are pressed at onec
  char key_flag;

  //! Speed of the player
  double speed;

  //! Counter that stores ticks to next reload
  size_t cntr = 0;

  //! Flag that checks whether player can shoot
  bool can_shoot;

  //! Reload time describes fire rate 
  unsigned short reload_time;

  //! Difference between two levels of speed bonuses
  double next_level_speed_difference;

  //! Difference between two levels of reload time bonuses
  unsigned short next_level_reload_difference;

  //! Pointer to list of walls so player knows he can not move forward
  std::list<std::unique_ptr<Entity>> * walls;

  //! Pointer to list of projectiles so class Player can send put procjectile to list of projectiles
  std::list<std::unique_ptr<Entity>> * projectiles;

public:
  /** Player constructor
   * @param[in] x X upper left coordinate of Player
   * @param[in] y Y upper left coordinate of Player
   * @param[in] w Width of Player
   * @param[in] h Height of Player
   * @param[in] path Path to Player texture
   * @param[in] map_w Width of whole map
   * @param[in] map_h Height of whole map
   */
  explicit Player ( int x, int y, int w, int h, const char * path, size_t map_w, size_t map_h );

  /**
   * Setter that is used to set pointers to containers that player can colide with
   * @param[in] walls Walls that player cant go through
   * @param[in] projectiles Projectiles that player shoots
   */
  void set_colliders ( std::list<std::unique_ptr<Entity>> * walls, std::list<std::unique_ptr<Entity>> * projectiles );

  /**
   * Setter that set width and height of map
   * @param[in] w Map width
   * @param[in] h Map height
   */
  void set_map_size (size_t w , size_t h );

  /**
   * Upgrades the fire rate of player by reload time bonus differenc
   */
  void up_reload_time ();

  /**
   * Upgrades the speed of player by speed bonus differenc
   */
  void up_speed ();

  /**
   * Method used to handle tick events and sends player move event
   * @param[in] event Reference to variable to pass event 
   */
  virtual void on_event ( SDL_Event & event ) override;
};

/**
 * Class Enemy which defines enemy of player that he have to shoot
 */
class Enemy : public Entity 
{
  private:
    //! Variable that stores x upper left coordinate of player
    int player_x; 

    //! Variable that stores y upper left coordinate of player
    int player_y;

    //! Default enemy speed
    double speed = DEFAULT_ENEMY_SPEED;

    //! Flag that checks whether player's position is known with default false value
    bool known_player_position = false;

    //! Enemy constructor that uses supper class constructor
    using Entity::Entity;

    //! Pointer to list of walls so enemy knows where it can not go
    std::list<std::unique_ptr<Entity>> * walls;

    //! Number of frames that are used to animate enemy
    unsigned short frames = 8;
    //! Frame rate of enemy animation
    unsigned short frame_rate = 50;

  public:
    /**
     * Method which sets walls that enemy can not go through
     */
    void set_colliders ( std::list<std::unique_ptr<Entity>> * walls );

    /**
     * Method that handles tick events and player move events
     * @param[in] event Reference to variable to pass event 
     */
    virtual void on_event ( SDL_Event & event );
};

class Wall : public Entity
{
  public:
    //! Wall constructor that uses superclass constructor
    using Entity::Entity;

    //! nulber of frames in Wall animation
    unsigned short frames = 8;

    //! Frame rate of Wall animation
    unsigned short frame_rate = 200;

    /**
     * Method that handles tick events and player move events
     * @param[in] event Reference to variable to pass event 
     */
    virtual void on_event ( SDL_Event & event );
};

class Bonus : public Entity
{
  public:
    //! Bonus constructor that uses superclass constructor
    using Entity::Entity;

    //! nulber of frames in Bonus animation
    unsigned short frames = 4;

    //! Frame rate of Bonus animation
    unsigned short frame_rate = 100;

    /**
     * Method that handles tick events and player move events
     * @param[in] event Reference to variable to pass event 
     */
    virtual void on_event ( SDL_Event & event );
};

class Banner : public Entity
{
  public:
    /**
     * Method that handles tick events and player move events
     * @param[in] event Reference to variable to pass event 
     */
    void init ( int x, int y, int w, int h, const char * path );

    /**
     * Method that handles tick events and player move events
     * @param[in] event Reference to variable to pass event 
     */
    virtual void on_event ( SDL_Event & event );

    /**
     * Method that sets delay of Banner
     * @param[in] ms Time in milliceconds that frame has to stop
     */
    void delay ( uint32_t ms ) const;
};