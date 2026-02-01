#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include <atomic>
#include <memory>
using namespace std::chrono_literals;
class TidalwaveROS : public rclcpp::Node {
public:
  TidalwaveROS() : Node("ros_node") {
    auto callbackRobot =  this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
	RobotOptions.callback_group = callbackRobot;
	CreateRobotROSSub();
  };


  std::atomic<bool> current_mode;

private:
  void CreateRobotROSSub();
 // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr Current_Control_sub;
  rclcpp::SubscriptionOptions RobotOptions = rclcpp::SubscriptionOptions();
};
