#include "ros2.hpp"

void TidalwaveROS::CreateRobotROSSub() {
	std::cout << "sub creation, ";
	auto currentModeLamb = [this](std_msgs::msg::Bool::SharedPtr msg) -> void {
		dataModel->current_mode = msg->data;
		ROS_enabled = true;
	};
	auto currentIMU = [this](custom_interfaces::msg::Imu::SharedPtr msg) -> void {
		auto& imu = dataModel->imu_data;

		imu.p_x = msg->ahrs_database.pose.pose.position.x;
		imu.p_y = msg->ahrs_database.pose.pose.position.y;
		imu.p_z = msg->ahrs_database.pose.pose.position.z;

		imu.o_x = msg->imu_fusion.orientation.x;
		imu.o_y = msg->imu_fusion.orientation.y;
		imu.o_z = msg->imu_fusion.orientation.z;
		imu.o_w = msg->imu_fusion.orientation.w;

		imu.v_x = msg->ahrs_database.twist.twist.linear.x;
		imu.v_y = msg->ahrs_database.twist.twist.linear.y;
		imu.v_z = msg->ahrs_database.twist.twist.linear.z;

		imu.w_x = msg->imu_fusion.angular_velocity.x;
		imu.w_y = msg->imu_fusion.angular_velocity.y;
		imu.w_z = msg->imu_fusion.angular_velocity.z;

		imu.a_x = msg->imu_fusion.linear_acceleration.x;
		imu.a_y = msg->imu_fusion.linear_acceleration.y;
		imu.a_z = msg->imu_fusion.linear_acceleration.z;

		imu.m_x = msg->mag_array.magnetic_field.x;
		imu.m_y = msg->mag_array.magnetic_field.y;
		imu.m_z = msg->mag_array.magnetic_field.z;

		imu.pressure = msg->pressure.fluid_pressure;
	};

	Current_Control_sub = this->create_subscription<std_msgs::msg::Bool>(
		"current_mode", rclcpp::QoS(10), currentModeLamb, RobotOptions);
	imu_sub = this->create_subscription<custom_interfaces::msg::Imu>(
		"imu_custom", 10, currentIMU);
}
