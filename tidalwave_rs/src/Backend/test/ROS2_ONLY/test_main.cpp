#include <gtest/gtest.h>

#include "../../ros2.hpp"     // Path to your class header

using namespace std::chrono_literals;

class TidalwaveFixture : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        rclcpp::init(0, nullptr);
    }

    static void TearDownTestSuite() {
        rclcpp::shutdown();
    }

    void SetUp() override {
        node = std::make_shared<TidalwaveROS>();
        // Create a helper node to publish the mode change
        test_pub_node = std::make_shared<rclcpp::Node>("test_publisher_node");
        publisher = test_pub_node->create_publisher<std_msgs::msg::Bool>("current_mode", 10);
    }

    std::shared_ptr<TidalwaveROS> node;
    std::shared_ptr<rclcpp::Node> test_pub_node;
    std::shared_ptr<rclcpp::Publisher<std_msgs::msg::Bool>> publisher;
};

TEST_F(TidalwaveFixture, CurrentMode) {
    // 1. Start spinning the node in a background thread
    std::jthread ros_thread([this]() { 
        rclcpp::spin(node); 
    });

    // 2. Prepare the message
    auto msg = std_msgs::msg::Bool();
    msg.data = true;

    // 3. Publish and wait for the atomic load to flip
    // We use a timeout to prevent the test from hanging forever if it fails
    auto start_time = std::chrono::steady_clock::now();
    bool success = false;

    while (std::chrono::steady_clock::now() - start_time < 2s) {
        publisher->publish(msg);
        std::cout << "published msg" << std::endl;
        if (node->current_mode.load()) {
            success = true;
            break;
        }
        std::this_thread::sleep_for(100ms);
    }

    EXPECT_TRUE(success) << "Failed to detect current_mode change within timeout";
    rclcpp::shutdown();
    ros_thread.join();
}
