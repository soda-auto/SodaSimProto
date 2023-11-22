#include "SodaSimProto/Ultrasonic.hpp"
#include <cassert>
#include <limits>

namespace soda
{

static int write(std::ostream & out, Ultrasonic const& scan) {
  soda::write(out, &scan.hfov, sizeof(scan.hfov));
  if (! out)
    return -1;

  soda::write(out, &scan.vfov, sizeof(scan.vfov));
  if (! out)
    return -1;

  soda::write(out, &scan.properties, sizeof(scan.properties));
  if (! out)
    return -1;

  std::uint8_t num_of_echoes =  static_cast<uint8_t>(scan.echoes.size());  
  soda::write(out, &num_of_echoes, sizeof(num_of_echoes));
  if (! out)
    return -1;

  if (num_of_echoes == 0)
    return 0;

  soda::write(out, scan.echoes.data(), scan.echoes.size() * sizeof(float));
  if (! out)
    return -1;

  return num_of_echoes;
}

static void read(std::istream & in, Ultrasonic & scan) {
  soda::read(in, &scan.hfov, sizeof(scan.hfov));
  if (! in)
    return;

  soda::read(in, &scan.vfov, sizeof(scan.vfov));
  if (! in)
    return;

  soda::read(in, &scan.properties, sizeof(scan.properties));
  if (! in)
    return;

  std::uint8_t num_of_echoes;
  soda::read(in, &num_of_echoes, sizeof(num_of_echoes));
  if (! in)
    return;

  scan.echoes.resize(num_of_echoes);
  soda::read(in, scan.echoes.data(), scan.echoes.size() * sizeof(float));
  if (! in)
    return;
}

int write(std::ostream& out, UltrasonicsHub const& scan)
{    
  soda::write(out, &scan.device_timestamp, sizeof(scan.device_timestamp));
  if (! out)
    return -1;

  std::uint32_t num_of_ultrasonics = static_cast<std::uint32_t>(scan.ultrasonics.size());
  soda::write(out, &num_of_ultrasonics, sizeof(num_of_ultrasonics));
  if (! out)
    return -1;

  if (num_of_ultrasonics == 0)
    return 0;

  for(std::uint8_t i = 0; i<num_of_ultrasonics; ++i) {
	  soda::write(out, scan.ultrasonics[i]);
	  if (! out)
		return -1; 
  }

  return num_of_ultrasonics;
}

void read(std::istream& in, UltrasonicsHub& scan)
{    
  soda::read(in, &scan.device_timestamp, sizeof(scan.device_timestamp));
  if (! in)
    return;

  std::uint32_t num_of_ultrasonics;
  soda::read(in, &num_of_ultrasonics, sizeof(num_of_ultrasonics));
  if (! in)
    return;

  scan.ultrasonics.resize(num_of_ultrasonics);
  for(std::uint8_t i = 0; i<num_of_ultrasonics; ++i) {
	  soda::read(in, scan.ultrasonics[i]);
	  if (! in)
		return; 
  }
}

} // namespace soda

