#!/bin/sh


xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch pick_objects my_turtlebot_world.launch world_file:=/home/robond/workspace/catkin_ws/src/gazeboConfig/worlds/MyWorld.world" & 
sleep 5

xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/robond/workspace/catkin_ws/src/map/map.yaml" & 
sleep 5

xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; rviz rviz -d ~/workspace/catkin_ws/src/rvizConfig/rviz_slam_add_marker.rviz" & 
sleep 5

xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; rosrun add_markers add_markers" & 



