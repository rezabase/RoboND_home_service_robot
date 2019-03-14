
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"



double pickup_zone[2] = {2.6, 0.0};
double drop_zone[2] = {0.1, -0.2};
bool picked_up = false;


ros::Publisher marker_pub;
visualization_msgs::Marker marker;


void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) 
{
  double px = msg->pose.pose.position.x;
  double py = msg->pose.pose.position.y;
  

  if (!picked_up) {
    double pickup_distance = sqrt(pow(px - pickup_zone[0], 2.0) + pow(py - pickup_zone[1], 2.0));
    ROS_INFO("Pickup distance %f", pickup_distance);
    if (pickup_distance < 1.0) {
      ROS_INFO(">> PICKED UP <<");
      //***** Stage 2: Remove the marker:
      ROS_INFO("REMOVING at the pick up zone");
      marker.action = visualization_msgs::Marker::DELETE; // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      marker_pub.publish(marker);
      ros::Duration(5.0).sleep(); //Wait 5 seconds
      picked_up = true;
    }
  } else {
    double drop_distance = sqrt(pow(px - drop_zone[0], 2.0) + pow(py - drop_zone[1], 2.0));
    ROS_INFO("Drop-off distance %f", drop_distance);
    if (drop_distance < 0.7) {
      ROS_INFO(">> DROPPED OFF <<");
      //***** Stage 3: Publish at the drop off zone:
      ROS_INFO("Publishing at the drop off zone");
      marker.pose.position.x = drop_zone[0];
      marker.pose.position.y = drop_zone[1];
      marker.action = visualization_msgs::Marker::ADD; // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      marker_pub.publish(marker);
      //pickedUp = true;
    }
  }
}








int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_home_service");
  ros::NodeHandle n;
  ros::Rate r(1);

  //Marker for RVIZ
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  
    
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();


  //Wait for subscriber:
  // Publish the marker
  while (marker_pub.getNumSubscribers() < 1)
  {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
  }
    

  // assign constants
  ros::Subscriber odom_sub = n.subscribe("/odom", 10, &odomCallback);

  //***** Stage 1: Publish at the pickup zone:
  ROS_INFO("Publishing at the pick up zone");
  marker.pose.position.x = pickup_zone[0];
  marker.pose.position.y = pickup_zone[1];
  marker.action = visualization_msgs::Marker::ADD; // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker_pub.publish(marker);


  while (ros::ok())
  {
    ros::spinOnce();
    r.sleep();
  }


}

