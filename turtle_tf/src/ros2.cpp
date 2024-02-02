#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2_ros/buffer.h"
#include <cmath>
rclcpp::Node::SharedPtr node=nullptr;
std::string name;

void turtle_callback(const turtlesim::msg::Pose::SharedPtr pose)
{
   
    static tf2_ros::TransformBroadcaster broad(node);
   
    geometry_msgs::msg::TransformStamped tf_pose;

    tf_pose.transform.translation.x = pose->x;
    tf_pose.transform.translation.y = pose->y;
    tf_pose.transform.translation.z = 0.0;
    RCLCPP_INFO(rclcpp::get_logger("pose"),"turtle1 pose : 距离: %.2f，偏角：%.2f",sqrt(pose->x*pose->x+pose->y*pose->y), atan2(pose->x,pose->y)*180.0/3.14);
   
}

int main(int argc, char *argv[])
{
   
    rclcpp::init(argc,argv);
    name=argv[1];
    node = std::make_shared<rclcpp::Node>("turtle_pub_Node");
    auto sub = node->create_subscription<turtlesim::msg::Pose>(name+"/pose",100,turtle_callback);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

