#include "Model.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_interfaces/msg/imu.hpp"

#include <atomic>
#include <memory>
using namespace std::chrono_literals;
class TidalwaveROS : public rclcpp::Node {
public:
  TidalwaveROS(std::shared_ptr<DataModel> givenModel)
      : Node("ros_node"), dataModel(givenModel) {
    auto callbackRobot =
        this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);
    RobotOptions.callback_group = callbackRobot;
    CreateRobotROSSub();
  };

  std::atomic<bool> ROS_enabled{false};

private:
  std::shared_ptr<DataModel> dataModel;
  void CreateRobotROSSub();
  // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr Current_Control_sub;
  rclcpp::SubscriptionOptions RobotOptions = rclcpp::SubscriptionOptions();

  rclcpp::Subscription<custom_interfaces::msg::Imu>::SharedPtr imu_sub;
};
