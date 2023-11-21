#ifndef COMPUT_OBJECT_H
#define COMPUT_OBJECT_H

#include "bbox.h"
#include "globals.h"
#include "object_properties.h"
#include "util/force.h"
#include "util/mass.h"
#include "util/position.h"
#include "util/velocity.h"

#include <string>

#ifdef COMPUT_DEBUG
#include <iostream>
#endif

namespace comput
{
    // objects are unique for now, there is no instantiation
    // their names are also unique (there is no check for validity currently)
    class Object
    {
    public:
        Object(std::string name, bool isStatic = true, 
               int x = 0, int y = 0, int w = 0, int h = 0,
               const SDL_Color &col = {0, 0, 0, 255},
               const Velocity &vel = Velocity::zero(), const Mass &mass = 0,
               ObjectPropertiesInteraction propertiesInteraction = ObjectPropertiesInteraction());

        Object(const Object &other);

        virtual ~Object() {}

        void update(float dt = COMPUT_SIMULATION_TIMESTEP);

        // applies the force 'f' to itself
        virtual void applyForce(Force &f, float dt = COMPUT_SIMULATION_TIMESTEP);

        // applies the forces etc. caused by collision with object 'other' to itself
        void applyCollisionResponseTo(const Object &other, double dt);

        void scale(float multiplier);

        // can't really return a reference rn since point (position) is not an explicit member
        Pointd getPosition() const;
        Velocity &getVelocity();
        Velocity getVelocity() const;
        Mass &getMass();
        Mass getMass() const;
        SDL_Rect &getRect();
        SDL_Rect getRect() const;
        SDL_Color &getColor();
        SDL_Color getColor() const;
        BBox &getBBox();
        BBox getBBox() const;
        std::string &getName();
        std::string getName() const;
        ObjectPropertiesInteraction& getPropertiesInteraction();
        Force getCollisionResponseTo(const Object &other) const;
        template <typename T> std::vector<Position<T>> getPolygon() const;
        template <typename T> std::vector<Position<T>> &getPolygon();

        void setVelocity(const Velocity &vel);
        void setMass(const Mass &mass);
        void setRect(const SDL_Rect &rect);
        void setColor(const SDL_Color &col);
        void setBBox(const BBox &bbox);
        void setName(std::string &n);
        void setPropertiesInteraction(ObjectPropertiesInteraction &propInt);
        template <typename T> void setPolygon(const std::vector<T> &points);

        virtual Force getInteractionForces(const Object &to) const;

#ifdef COMPUT_DEBUG
        void print()
        {
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
        bool _isStatic;
        double _x;
        double _y;
        Velocity _vel;
        Mass _mass;
        SDL_Color _color;
        std::vector<Pointf> _poly;

        void _carryBbox(SDL_Rect &rect);
        // bbox can scale itself, but we need to scale rect as well
        void _scaleRect(float multiplier);

        ObjectPropertiesInteraction _propertiesInteraction;
    };

} // namespace comput
#endif
