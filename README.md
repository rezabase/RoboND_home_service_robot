# RoboND_home_service_robot

By: Reza Rahimi


![alt text](screenshots/rviz.png "Screenshot of Rviz.")


## ROS and Gazebo

The project was developed on Ubuntu 16.04 LTS with ROS Kinetic, Gazebo. 

## Dependencies:

- gmapping: Perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras. http://wiki.ros.org/gmapping
- turtlebot_teleop: manually control a robot using keyboard commands. I used it only when I was creating the map. http://wiki.ros.org/turtlebot_teleop
- turtlebot_rviz_launchers: With the view_navigation.launch file, you can load a preconfigured rviz workspace. http://wiki.ros.org/turtlebot_rviz_launchers
- turtlebot_gazebo: deploy a turtlebot in a gazebo environment by linking the world file to it. http://wiki.ros.org/turtlebot_gazebo

All above packages are already included in this repo. 

## Launch:

In the src/script folder, there are several shell scripts to start different solutions, listed below. Open a terminal and run the scripts. 

### test_slam.sh: 

Used to create a map that is going to be used by the localisation and navigation packages. After running the script, I waited for all ROS packages start, then used the keyboard to navigate the robot around and created a map that could be seen in rviz. Later I run the following command to save the map. 

rosrun map_server map_saver -f <map_name>

### test_navigation.sh:

It starts an amcl_demo which is the Dijkstra's, a variant of the Uniform Cost Search algorithm, to plan our robot trajectory from start to goal position. After running the script, wait for all packages to start, then use the "2D Nav Goal" button in Rviz to select a target position for the robot to move to. 

### pick_objects.sh:

Runs a custom C++ code that will give the robot multiple goals to reach. In this case, it will go to a pick up location, wait 5 seconds and continue to a drop-off location.

### add_markers.sh:

It's a custom C++ code to simulate an object in Rviz. In this case, this is used to simulate a cube at the pick up and drop off positions. This is just for testing and it will do the following:

- Publish the marker at the pickup zone
- Pause 5 seconds
- Hide the marker
- Pause 5 seconds
- Publish the marker at the drop off zone

### home_service.sh:

Similar to pick_objects which sends the robot to pick up and drop-off locations. But in here, there is also an add_markers node that is subscribing to the robot odometry topic (/odom) and when the robot reaches the pick up location, it removes the cube to simulate pick up and when the object reaches the drop off destination, it shows a cube on the drop-off location. 

## Udacity project specifications:

#### Did the student submit all required files?

- All packages including the ROS packages are included in the git repository.

#### Did the student set up the simulation environment properly?

- Robot and world loads perfectly in Gazebo.

#### Did the student's mapping function work properly?

- Works fine.

#### Did the student create a map using SLAM?

- Used the keyboard to move the robot around and map part of the environment that was needed for the home service project. -Then used rosrun map_server map_saver -f <map_name> to save the map in a map.pgm and map.yaml file. 

#### Was the student's navigation stack configured properly?

- Works fine.

#### Did the student's goal node function properly?

- Works good. Just feels a little slow some times. 

#### Did the student create virtual object with markers?

- Done

#### Does the student's robot perform home service tasks correctly?

- Functions as instructed.

#### Did the student include a write-up explaining the packages used to achieve home service functionalities?

- Done

