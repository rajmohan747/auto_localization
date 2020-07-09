# Auto Localization

In mobile robots with natural navigation,we need to initialize the robot's position in the first time so as the robot can localize itself.Once it's localized it will be navigating at its own.But the same process is required the next time after a restart/power off of the robot.

The package auto_localization will help to initialize the robot from it's last known position.
The robot's position will be stored into a local text file and everytime on a restart of system,
the robot will be initialized using these values.





## Prerequisites

Create and setup the workspace 

Install the packages teb_local_planner and teb_local_planner_tutorials  

```
mkdir catkin_ws
cd catkin_ws
mkdir src
cd src
catkin_init_workspace


```
## Setup

Install the teb local planner,stage-ros,robot pose publisher package and other dependies
```
cd ~/catkin_ws/src

sudo apt-get install ros-kinetic-teb-local-planner

sudo apt-get install ros-kinetic-stage-ros

sudo apt-get install ros-kinetic-robot-pose-publisher
```


Download and unzip the teb-local-planner tutorial package and auto_localization package.
And place it inside the  /src folder.

Install all the missing dependies (if any) using the following command


```
cd ~/catkin_ws/
rosdep install --from-paths src --ignore-src -r -y

```
## Build

Build the packages with the following command

```
cd ~/catkin_ws/
catkin_make -DCMAKE_BUILD_TYPE=Release -j 1

```

## Execution in simulation environment

Launch the files in the following sequence

```
roslaunch teb_local_planner_tutorials robot_diff_drive_in_stage_costmap_conversion.launch 
roslaunch auto_localization auto_localization.launch
```


##Testing



## Authors



See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.


