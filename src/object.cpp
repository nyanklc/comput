#include "object.h"
#include "util/util.h"

#include <iostream>

namespace comput
{

  Object::Object(std::string name, bool isStatic, int x, int y, std::vector<Pointf> &poly, const SDL_Color& col, const Velocity& vel, const Mass& mass, ObjectPropertiesInteraction propertiesInteraction)
    {
        _name = name;
        _isStatic = isStatic;
        _x = x;
        _y = y;
        _poly = poly;
        _vel = vel;
        _mass = mass;
        _color.r = col.r;
        _color.g = col.g;
        _color.b = col.b;
        _color.a = col.a;
        _propertiesInteraction = propertiesInteraction;
    }

    Object::Object(const Object &other)
    {
        _name = other._name;
        _isStatic = other._isStatic;
        _x = other._x;
        _y = other._y;
        _bbox = other._bbox;
        _vel = other._vel;
        _mass = other._mass;
        _color.r = other._color.r;
        _color.g = other._color.g;
        _color.b = other._color.b;
        _color.a = other._color.a;
        _propertiesInteraction = other._propertiesInteraction;
    }

    // updates position with velocity (gravity is applied separately)
    // (via applyForce)
    void Object::update(float dt)
    {
        _x += _vel.x() * dt; // mario
        _y += _vel.y() * dt;
        _rect.x = (int)_x;
        _rect.y = (int)_y;
        _carryBbox(_rect);
    }

    void Object::applyForce(Force &f, float dt)
    {
        if (_isStatic) return;
        auto a = f / _mass;
        _vel = _vel + a * dt;
    }

    void Object::applyCollisionResponseTo(const Object &other, double dt)
    {
        Force f = getCollisionResponseTo(other);
        applyForce(f, dt);
    }

    Force Object::getCollisionResponseTo(const Object &other) const
    {
        Force f;
        f += other.getInteractionForces(*this);
        return f;
    }

    void Object::scale(float multiplier)
    {
        if (multiplier <= 0)
            return;
        _bbox.scale(multiplier);
        _scaleRect(multiplier);
    }

    Pointd Object::getPosition() const
    {
        return Pointd(_x, _y);
    }

    Velocity &Object::getVelocity() { return _vel; }
    Velocity Object::getVelocity() const { return _vel; }

    Mass &Object::getMass() { return _mass; }
    Mass Object::getMass() const { return _mass; }

    SDL_Rect &Object::getRect() { return _rect; }
    SDL_Rect Object::getRect() const { return _rect; }

    SDL_Color &Object::getColor() { return _color; }
    SDL_Color Object::getColor() const { return _color; }

    BBox &Object::getBBox() { return _bbox; }
    BBox Object::getBBox() const { return _bbox; }

    std::string &Object::getName() { return _name; }
    std::string Object::getName() const { return _name; }

  template <typename T> std::vector<Position<T>> Object::getPolygon() const
  {
    
  }

  template <typename T> std::vector<Position<T>> &Object::getPolygon()
  {
    return _polygon;
  }


    void Object::setVelocity(const Velocity &vel) { _vel = vel; }
    void Object::setMass(const Mass &mass) { _mass = mass; }
    void Object::setRect(const SDL_Rect &rect) { _rect = rect; }
    void Object::setColor(const SDL_Color &col) { _color = col; }
    void Object::setBBox(const BBox &bbox) { _bbox = bbox; }
    void Object::setName(std::string &n) { _name = n; }

    Force Object::getInteractionForces(const Object& to) const
    {
        Force f;
        f += _propertiesInteraction.calculateRepulsionForce(_x, _y, to._x, to._y);
        return f;
    }

    ObjectPropertiesInteraction& Object::getPropertiesInteraction()
    {
        return _propertiesInteraction;
    }

    void Object::setPropertiesInteraction(ObjectPropertiesInteraction& propInt)
    {
        _propertiesInteraction = propInt;
    }

    void Object::_carryBbox(SDL_Rect &rect)
    {
        float lLx = (float)rect.x;
        float lLy = (float)rect.y + (float)rect.h;
        float uRx = (float)rect.x + (float)rect.w;
        float uRy = (float)rect.y;
        _bbox = BBox(Pointf(lLx, lLy), Pointf(uRx, uRy));
    }

    void Object::_scaleRect(float multiplier)
    {
        auto w = _rect.w;
        auto h = _rect.h;
        _rect.x -= w / multiplier;
        _rect.y -= h / multiplier;
        _rect.w = multiplier * w;
        _rect.h = multiplier * h;
        // we won't allow the rect to disappear (int 0)
        if (_rect.w == 0)
            _rect.w = 1;
        if (_rect.h == 0)
            _rect.h = 1;
    }

} // namespace comput
