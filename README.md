# SodaSimProto

The SodaSimProto includes the generic messages serialization / deserialization for the SodaSim (mostly for sensors).
This repository is used as a submodule for SodaSim and can also be compiled as a separate static library via cmake.

## Sensors message serialization / deserialization 
* _Camera.hpp_ - generic cameras message (sends via ZMQ)
* _Lidar.hpp_ - generic LiDAR message (sends via UDP)
* _Radar.hpp_ - generic radar message (sends via UDP)
* _Ultrasonic.hpp_ - generic ultrasonic message (sends via UDP)
* _OXTS.hpp_ - GNSS/IMU message (sends via UDP). This is original NCOM protocol from [OXTS](https://support.oxts.com/hc/en-us/articles/115002163985-Decoding-OxTS-navigation-outputs)
* _VehicleState.hpp_ - generic vehicle state message (sends via UDP)

## Usage example (for Lidar.hpp, Radar.hpp, Ultrasonic.hpp)

Serialization example:  
```cpp
std::stringstream stream_out(std::ios_base::out | std::ios_base::binary); 
int points_count = soda::write(sout, Scan);
if (!stream_out)
{
    std::cout << "Serialization error";
    return;
}
const uint8* data = (const uint8*)stream_out.str().data();
size_t size = stream_out.str().length();
```


Deserialization example:  
```cpp
std::istringstream stream_in(std::string(data, size));
soda::read(stream_in, Scan);
if (!stream_in ) 
{
    std::cout << "Deserialization error" << std::endl;
    return;
}
```

## Contact
Please feel free to provide feedback or ask questions by creating a Github issue. For inquiries about collaboration, please email us at sim@soda.com.

## Copyright and License
Copyright © 2023 SODA.AUTO UK LTD. ALL RIGHTS RESERVED.  
This software contains code licensed as described in [LICENSE](https://github.com/soda-auto/SodaSim/blob/master/LICENSE.md).  
