# RoboND-P4-Where-Am-I
Project 4 of Udacity Robotics Software Engineer Nanodegree Program

## Overview  
In this project you'll utilize ROS AMCL package to accurately localize a mobile robot inside a map in the Gazebo simulation and RVIZ environments. Here are the steps:  
* Create a ROS package that launches a custom robot model in a custom Gazebo world  
* Utilize the ROS AMCL package / Navigation Stack to localize the robot  
* Tune and test specific amcl parameters for best possible localization results  
## Prerequisites/Dependencies  
```
sudo apt-get install ros-kinetic-navigation
```
* ROS map_server package  
```
sudo apt-get install ros-kinetic-map-server
```
* ROS move_base package  
```
sudo apt-get install ros-kinetic-move-base
```
* ROS amcl package  
```
sudo apt-get install ros-kinetic-amcl
```
## Run the project  
* Clone this repository
```
git clone https://github.com/tdwilhelm/RoboND-Where-Am-I.git
```
* Open the repository and make  
```
cd /home/workspace/RoboND-Where-Am-I/catkin_ws/
catkin_make
```
* Launch my_robot in Gazebo to load both the world and plugins  
```
roslaunch my_robot world.launch
```  
* Launch amcl node  
```
roslaunch my_robot amcl.launch
```  

## Videos  
 
![Demo](localization_demo.gif)  
