#include <ros/console.h> 
#include "ros_class.h"

/**
* @brief  Constructor for the Computations
*/
RosClass::RosClass()
{

    ROS_INFO("RosClass Constructor called");
    
    /*Subscribers*/
    robotPose        = nh.subscribe("/robot_pose", 1, &RosClass::robotPoseCallback,this);
    
    /*Publishers*/
    initialPosePub   = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose",1);

}

    /**
    * @brief  Destructor for the Computations
    */

RosClass::~RosClass()
{

}

/**
* @brief  Call back for robot position in the map frame
*/
void RosClass::robotPoseCallback(const geometry_msgs::Pose &robot_msg)  
{
    m_robotPose  = robot_msg;
} 

/**
* @brief  Getter for the robot position.Will be used in the interface class
* @return Robot's position in geometry_msgs::Pose format
*/
geometry_msgs::Pose RosClass::getRobotPose()
{
    return m_robotPose;
    
}

/**
* @brief  Publisher for setting the robo's position
*/
void RosClass::sendInitialPose(geometry_msgs::PoseWithCovarianceStamped &initialPose)
{
    
    initialPosePub.publish(initialPose);
    ROS_INFO("Initial Pose Published");

}

