#include "SodaSimProto/Pose.hpp"
#include <cassert>
#include <limits>

namespace soda
{

void write(std::ostream & out, Pose3d const& pose)
{
  std::uint8_t const type = pose.is2d() ? 0 : 1;
  soda::write(out, &type, sizeof(type));
  if (! out)
    return;

  if (type == 0) {
    auto value = pose.x();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;

    value = pose.y();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;

    value = pose.yaw();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;
  }
  else if (type == 1) {
    auto value = pose.x();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;

    value = pose.y();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;

    value = pose.z();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;

    value = pose.roll();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;

    value = pose.pitch();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;

    value = pose.yaw();
    soda::write(out, &value, sizeof(value));
    if (! out)
      return;
  }
  else {
    assert(false);
  }
}

void read(std::istream & in, Pose3d & pose)
{
  std::uint8_t type;
  soda::read(in, &type, sizeof(type));
  if (! in)
    return;

  if (type == 0) {
    float value;

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setX(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setY(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setYaw(value);
  } else if (type == 1) {
    float value;

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setX(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setY(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setZ(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setRoll(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setPitch(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setYaw(value);
  } else {
    assert(false);
  }
}

void write(std::ostream & out, Pose2d const& pose)
{
  std::uint8_t type = 0;
  soda::write(out, &type, sizeof(type));
  if (! out)
    return;

  auto value = pose.x();
  soda::write(out, &value, sizeof(value));
  if (! out)
    return;

  value = pose.y();
  soda::write(out, &value, sizeof(value));
  if (! out)
    return;

  value = pose.yaw();
  soda::write(out, &value, sizeof(value));
  if (! out)
    return;
}

void read(std::istream & in, Pose2d & pose)
{
  std::uint8_t type;
  soda::read(in, &type, sizeof(type));
  if (! in)
    return;

  if (type == 0) {
    float value;

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setX(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setY(value);

    soda::read(in, &value, sizeof(value));
    if (! in)
      return;
    pose.setYaw(value);
  } else {
    assert(false);
  }
}

} // namespace soda

