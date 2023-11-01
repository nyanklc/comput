#include "object.h"

namespace comput {

  Object::Object(int x, int y, int w, int h, const SDL_Color &col,
                 const Velocity &vel, const Mass &mass) {
    _x = x;
    _y = y;
    _rect.x = x;
    _rect.y = y;
    _rect.w = w;
    _rect.h = h;
    _vel = vel;
    _mass = mass;
    _color.r = col.r;
    _color.g = col.g;
    _color.b = col.b;
    _color.a = col.a;

  }

  Object::Object(const Object &other) {
    _x = other._x;
    _y = other._y;
    _rect = other._rect;
    _vel = other._vel;
    _mass = other._mass;
    _color.r = other._color.r;
    _color.g = other._color.g;
    _color.b = other._color.b;
    _color.a = other._color.a;
  }

  // updates position with velocity (gravity is applied separately)
  // (via applyForce)
  void Object::update(float dt) {
    std::cout << "object updating before " << _rect.x << ", " << _rect.y << std::endl;
    _x += _vel.x() * dt; // mario
    _y += _vel.y() * dt;
    _rect.x = (int)_x;
    _rect.y = (int)_y;
    std::cout << "object updating after " << _rect.x << ", " << _rect.y << std::endl;
  }

  void Object::applyForce(Force &f, float dt) {
    auto a = f / _mass;
#ifdef COMPUT_DEBUG
    std::cout << "APPLYING FORCE f: " << f.vec << std::endl;
    std::cout << "mass: " << _mass.value << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "vel before: " << _vel.vec << std::endl;
#endif
    _vel = _vel +  a * dt;
#ifdef COMPUT_DEBUG
    std::cout << "vel after: " << _vel.vec << std::endl;
#endif
  }

  Velocity &Object::getVelocity() {
    return _vel;
  }

  Mass &Object::getMass() {
    return _mass;
  }

  SDL_Rect *Object::getRect() {
    return &_rect;
  }

  void Object::setVelocity(const Velocity &vel) {
    _vel = vel;
  }

  void Object::setMass(const Mass &mass) {
    _mass = mass;
  }

  void Object::setRect(const SDL_Rect &rect) {
    _rect = rect;
  }

  void Object::setColor(const SDL_Color &col) {
    _color = col;
  }

  SDL_Color &Object::getColor() {
    return _color;
  }


}  // namespace comput
