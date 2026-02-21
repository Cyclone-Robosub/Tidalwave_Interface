#include <atomic>

struct IMU;

struct DataModel {
	std::atomic<bool> current_mode;
	IMU imu_data;
};

struct IMU{
	double p_x, p_y, p_z; // point
	double o_x, o_y, o_z, o_w; // orientation

	double v_x, v_y, v_z; // linear velocity
	double w_x, w_y, w_z; // angular velocity

	double a_x, a_y, a_z; // linear acceleration

	double m_x, m_y, m_z; // magnetic field
	
	double pressure; // pressure
};