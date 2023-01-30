#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "opencv_apps/CircleArrayStamped.h"
// 320~0으로 갈 수록 서보모터 줄어듦

float center_x = 0;

void center_cb(const opencv_apps::CircleArrayStamped::ConstPtr& msg)
{
  center_x = msg->circles[0].center.x;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_to_servo_node");
  ros::NodeHandle nh;

  ros::Publisher servo_pub = nh.advertise<std_msgs::UInt16>("servo", 1000);

  ros::Rate loop_rate(10);

  ros::Subscriber centersub = nh.subscribe("hough_circles/circles", 1000, center_cb);

  while (ros::ok())
  {
    std_msgs::UInt16 msg;

    //  msg.data = (int)(90 + dir*90*center_x);
    msg.data = (int)(center_x*90/320);

    ROS_INFO("I heard: [%f]", center_x);

    servo_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
