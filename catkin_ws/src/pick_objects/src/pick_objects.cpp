#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//#include "geometry_msgs/Pose.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;



class MyGoal{

    public:
        //geometry_msgs::Pose target_pose;

        move_base_msgs::MoveBaseGoal goal;
 
        MyGoal(float pos_x, float pos_y, float orient_w)
        {
            // set up the frame parameters
            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();

            // Define a position and orientation for the robot to reach
            goal.target_pose.pose.position.x = pos_x;
            goal.target_pose.pose.orientation.w = orient_w;
        }
};



int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  MyGoal goal_pickup(2.5, -1, 1.0);
  MyGoal goal_dropoff(0.1, 1.2, 1.0);

  
  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(goal_pickup.goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to the pickup location");
  else
    ROS_INFO("The base failed to move to the pickup locaiton");


  ros::Duration(5.0).sleep(); // sleep for 5 seconds


  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off goal");
  ac.sendGoal(goal_dropoff.goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to the Dropp off zone");
  else
    ROS_INFO("The base failed to move to the drop off zone");


ros::Duration(50.0).sleep(); // sleep for 50 seconds, so I have time to read the messages


  return 0;
}
