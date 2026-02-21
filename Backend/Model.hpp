#include <atomic>

struct IMU;

struct DataModel {
	std::atomic<bool> current_mode;
	IMU imu_data;
};

struct IMU{
	std::atomic<double> p_x, p_y, p_z; // point
	std::atomic<double> o_x, o_y, o_z, o_w; // orientation

	std::atomic<double> vx, vy, vz; // linear velocity
	std::atomic<double> w_x, w_y, w_z; // angular velocity

	std::atomic<double> a_x, a_y, a_z; // linear acceleration

	std::atomic<double> m_x, m_y, m_z; // magnetic field
	
	std::atomic<double> pressure; // pressure
};