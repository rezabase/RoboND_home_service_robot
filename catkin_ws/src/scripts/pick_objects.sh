#!/bin/sh

xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch pick_objects my_turtlebot_world.launch world_file:=/home/robond/workspace/catkin_ws/src/gazeboConfig/worlds/MyWorld.world" & 
sleep 5

xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/robond/workspace/catkin_ws/src/map/map.yaml" & 

sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" & 

sleep 5
xterm -e "source ~/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects" & 



