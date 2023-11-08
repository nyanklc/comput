#ifndef COMPUT_OBJECT_H
#define COMPUT_OBJECT_H

#include "bbox.h"
#include "globals.h"
#include "util/force.h"
#include "util/mass.h"
#include "util/position.h"
#include "util/velocity.h"

#include <string>

#ifdef COMPUT_DEBUG
#include <iostream>
#endif

namespace comput {

// this is simply a wrapper on SDL_Rect
// objects are unique for now, there is no instantiation
// their names are also unique (there is no check for validity currently)
class Object {
 public:
  Object(std::string &name, int x = 0, int y = 0, int w = 0, int h = 0,
         const SDL_Color &col = {0, 0, 0, 255},
         const Velocity &vel = Velocity::zero(), const Mass &mass = 0);

  Object(const Object &other);

  virtual ~Object() {}

  void update(float dt = COMPUT_SIMULATION_TIMESTEP);

  virtual void applyForce(Force &f,
                          float dt = COMPUT_SIMULATION_TIMESTEP);

  void scale(float multiplier);

  Velocity &getVelocity();

  Mass &getMass();

  SDL_Rect *getRect();

  BBox &getBbox();

  void setVelocity(const Velocity &vel);

  void setMass(const Mass &mass);

  void setRect(const SDL_Rect &rect);

  void setColor(const SDL_Color &col);

  SDL_Color &getColor();

  void setName(std::string &n);

  std::string getName();

  // just calls this on bbox currently
  bool isCollidingWith(const Object &other);

#ifdef COMPUT_DEBUG
  void print() {
    COMPUT_DEBUG_SEPARATOR;
    std::cout << "Object " << this << std::endl;
    std::cout << "rect: " << _rect.x << ", " << _rect.y << ", " << _rect.w
              << ", " << _rect.h << std::endl;
    std::cout << "color: " << (int)_color.r << ", " << (int)_color.g << ", "
              << (int)_color.b << ", " << (int)_color.a << std::endl;
    COMPUT_DEBUG_SEPARATOR;
  }
#endif

 protected:
  std::string _name;
  double _x;
  double _y;
  SDL_Rect _rect;
  Velocity _vel;
  Mass _mass;
  SDL_Color _color;
  BBox _bbox;

  void _carryBbox(SDL_Rect &rect);
  //bbox can scale itself, but we need to scale rect as well
  void _scaleRect(float multiplier);
};

}  // namespace comput
#endif
