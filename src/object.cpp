#include "object.h"

#include <iostream>

namespace comput {

Object::Object(std::string &name, int x, int y, int w, int h, const SDL_Color &col,
               const Velocity &vel, const Mass &mass) {
  _name = name;
  _x = x;
  _y = y;
  _rect.x = x;
  _rect.y = y;
  _rect.w = w;
  _rect.h = h;
  _carryBbox(_rect);
  _vel = vel;
  _mass = mass;
  _color.r = col.r;
  _color.g = col.g;
  _color.b = col.b;
  _color.a = col.a;
}

Object::Object(const Object &other) {
  _name = other._name;
  _x = other._x;
  _y = other._y;
  _rect = other._rect;
  _bbox = other._bbox;
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
  _x += _vel.x() * dt;  // mario
  _y += _vel.y() * dt;
  _rect.x = (int)_x;
  _rect.y = (int)_y;
  _carryBbox(_rect);
}

void Object::applyForce(Force &f, float dt) {
  auto a = f / _mass;
  _vel = _vel + a * dt;
}

void Object::scale(float multiplier) {
  if (multiplier <= 0)
    return;
  _bbox.scale(multiplier);
  _scaleRect(multiplier);
}

Velocity &Object::getVelocity() { return _vel; }

Mass &Object::getMass() { return _mass; }

SDL_Rect *Object::getRect() { return &_rect; }

BBox &Object::getBbox() { return _bbox; }

void Object::setVelocity(const Velocity &vel) { _vel = vel; }

void Object::setMass(const Mass &mass) { _mass = mass; }

void Object::setRect(const SDL_Rect &rect) { _rect = rect; }

void Object::setColor(const SDL_Color &col) { _color = col; }

SDL_Color &Object::getColor() { return _color; }

void Object::setName(std::string &n) {
  _name = n;
}

std::string Object::getName() {
  return _name;
}

bool Object::isCollidingWith(const Object &other) {
  return _bbox.isCollidingWith(other._bbox);
}

void Object::_carryBbox(SDL_Rect &rect) {
  float lLx = (float)rect.x;
  float lLy = (float)rect.y+(float)rect.h;
  float uRx = (float)rect.x+(float)rect.w;
  float uRy = (float)rect.y;
  _bbox = BBox(Point(lLx, lLy), Point(uRx, uRy));
}

void Object::_scaleRect(float multiplier) {
  auto w = _rect.w;
  auto h = _rect.h;
  _rect.x -= w / multiplier;
  _rect.y -= h / multiplier;
  _rect.w = multiplier * w;
  _rect.h = multiplier * h;
  //we won't allow the rect to disappear (int 0)
  if (_rect.w == 0) _rect.w = 1;
  if (_rect.h == 0) _rect.h = 1;
}

}  // namespace comput
