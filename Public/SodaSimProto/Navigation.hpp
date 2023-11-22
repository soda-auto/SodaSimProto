#pragma once
#include "Common.hpp"
#include <cstdint>

namespace soda
{
#pragma pack(push, 8)

	struct NavigationState 
	{
		Vector position;  // [m]
		Rotator rotation; // [rad]
		Vector loc_velocity;  // in the vehicle frame (x=forward, y=lateral, z=up) [m/s]
		Vector world_velocity;  // in global coordinate system [m/s]
		Vector angular_velocity;  // in the vehicle frame (x=roll, y=pitch, z=yaw) [m/s^2]
		Vector acceleration;  // in the vehicle frame (x=forward, y=lateral, z=up) [m/s^2]
		Vector gyro_biases;  // Estimated biases in gyros, rad/s
		Vector acc_biases;  // Estimated biases in accelerometers, m/s^2
		
		double longitude; // [Deg]
		double latitude;  // [Deg]
		double altitude;  // [m]
		
		int64 timestamp; // [ns]
	};
#pragma pack (pop)
} // namespace soda
