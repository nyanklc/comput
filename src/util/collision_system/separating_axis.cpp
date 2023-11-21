#include "separating_axis.h"

namespace comput
{
  CollisionSystemSeparatingAxis::CollisionSystemSeparatingAxis()
    : CollisionSystemBase()
  {}

  void CollisionSystemSeparatingAxis::checkCollisionsOf(Object &obj,
                                                        std::vector<Object> &objects,
                                                        double dt)
  {
    for (auto &obj2 : objects)
    {
      if (obj.getName() == obj2.getName()) continue;

      if (_separatingAxisTheorem(obj, obj2))
        {
          obj.applyCollisionResponseTo(obj2, dt);
        }
    }
  }

  void CollisionSystemSeparatingAxis::_dotScalar(Vector2f &vec1, Vector2f &vec2) const
  {
    
  }

  Vector2f CollisionSystemSeparatingAxis::_edgeDirection(Pointf &p1, Pointf &p2) const
  {
    
  }

  Vector2f CollisionSystemSeparatingAxis::_orthogonal(Vector2f &vec) const
  {
    
  }

  std::vector<Vector2f> CollisionSystemSeparatingAxis::_verticesToEdges(std::vector<Pointf> &vertices) const
  {
    
  }

  CollisionSystemSeparatingAxis::projection_t CollisionSystemSeparatingAxis::_project() const
  {
    
  }

  bool CollisionSystemSeparatingAxis::_overlap(CollisionSystemSeparatingAxis::projection_t &p1, CollisionSystemSeparatingAxis::projection_t &p2) const
  {
    
  }

  bool CollisionSystemSeparatingAxis::_separatingAxisTheorem(const Object &obj1, const Object &obj2) const
  {
    std::vector<Vector2f> edges = _verticesToEdges(obj1.polygon<float>());
  }

}    
