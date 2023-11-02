#ifndef COMPUT_UTIL_MASS_H
#define COMPUT_UTIL_MASS_H

namespace comput {

// used to contain a unit as well, but it complicates things
class Mass {
 public:
  Mass() { value = 0; }

  Mass(float val) { value = val; }

  Mass(const Mass &other) { value = other.value; }

  float value;
};

}  // namespace comput

#endif
