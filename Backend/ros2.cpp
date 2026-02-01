#include "ros2.hpp"
void TidalwaveROS::CreateRobotROSSub(){
	std::cout << "sub creation, ";
	auto currentModeLamb = [this](std_msgs::msg::Bool::SharedPtr msg) -> void {
		current_mode = msg->data;
	}; 
	Current_Control_sub = this->create_subscription<std_msgs::msg::Bool>(
        "current_mode", rclcpp::QoS(10),
        currentModeLamb,
        RobotOptions);
}
#ifdef ROS2ONLY
int main(int argc, char **argv) {
	std::cout << "ROS2 ONLY BUILD--" << std::endl;
  rclcpp::init(argc, argv);
  std::shared_ptr<TidalwaveROS> mainObject = std::make_shared<TidalwaveROS>();
std::jthread ros_thread([mainObject]() {
    rclcpp::spin(mainObject); 
});

	/*
		best example of undefined behavior when it comes to multithreading. 
		intentional, as I could care right now less about the misorder of print statements.
	*/
	std::cout << "Test Thread Creation" << std::endl;
	std::thread testThread([mainObject](){
	while(!mainObject->current_mode.load()){
		std::cout << mainObject->current_mode.load() << std::endl;
		 std::this_thread::sleep_for(200ms);
	}});
	if(testThread.joinable()){
		std::cout << "got out of test loop." << std::endl;
		testThread.join();
		rclcpp::shutdown();
	}
	  ros_thread.join();
  return 0;
}
#endif
