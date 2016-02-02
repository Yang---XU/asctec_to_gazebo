/*************************************************************************
    > File Name: asctec_to_gazebo.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: ven. 29 janv. 2016 17:05:26 CET
 ************************************************************************/



#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <sensor_msgs/Joy.h> 
#include <asctec_hl_comm/mav_ctrl.h>
#include "gazebo_msgs/ModelStates.h"
#include "gazebo_msgs/ModelState.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>


using namespace std;

class AsctecToGazebo{
public:
 ros::NodeHandle nh;
 ros::Subscriber asctec_sub;
 ros::Publisher gazebo_pub;
 //asctec_hl_comm::mav_ctrl ctrl_msg_in;
 geometry_msgs::Twist ctrl_msg_out;

 AsctecToGazebo(){
	 asctec_sub =  nh.subscribe("/fcu/control", 10, &AsctecToGazebo::cmdCallback,this);
	 gazebo_pub = nh.advertise<geometry_msgs::Twist> ("cmd_vel", 1);
 }

 void cmdCallback(const asctec_hl_comm::mav_ctrl ctrl_msg_in){
	 //asctec_hl_comm::mav_ctrl ctrl_msg_in = *ctrl_msg;
	 double v_x, v_y, v_z, v_yaw;
	 v_x = ctrl_msg_in.x;
	 v_y = ctrl_msg_in.y;
	 v_z = ctrl_msg_in.z;
	 v_yaw = ctrl_msg_in.yaw;

	 ctrl_msg_out.linear.x = v_x;
	 ctrl_msg_out.linear.y = v_y;
	 ctrl_msg_out.linear.z = v_z;
	 ctrl_msg_out.angular.z = v_yaw;
	 gazebo_pub.publish(ctrl_msg_out);
 }
};

int main(int argc, char** argv){

		ros::init(argc, argv, "transformation");
		AsctecToGazebo toGaz = AsctecToGazebo();
		ros::spin();
		return 0;
}


