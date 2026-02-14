#include "ros2.hpp"
void TidalwaveROS::CreateRobotROSSub() {
  std::cout << "sub creation, ";
  auto currentModeLamb = [this](std_msgs::msg::Bool::SharedPtr msg) -> void {
    current_mode = msg->data;
  };
  Current_Control_sub = this->create_subscription<std_msgs::msg::Bool>(
      "current_mode", rclcpp::QoS(10), currentModeLamb, RobotOptions);
}

