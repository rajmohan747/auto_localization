#ifndef ROS_CLASS_H
#define ROS_CLASS_H

#include <ros/ros.h>
#include <ros/time.h>
#include <iostream>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>





class RosClass 
{
public:

    /**
    * @brief  Constructor for the Ros class
    */

    RosClass();

    /**
    * @brief  Destructor for the Ros class
    */
    ~RosClass();
    
    /**
    * @brief  Getter for the current robot position
    */   
    geometry_msgs::Pose getRobotPose();
    
    
    /**
     * @brief  Publisher for initializing robot position
     */
    void sendInitialPose(geometry_msgs::PoseWithCovarianceStamped &initialPose);
    
    
private:
     /**
    * @brief NodeHandle ROS
    */
    ros::NodeHandle nh;


    /**
     * @brief  A callback to obtain the robot's current position
     * @param robot_msg The message returned from a message notifier
     */

    void robotPoseCallback(const geometry_msgs::Pose& robot_msg);

    /**
     * @brief ROS Subscriber
    */    
    ros::Subscriber robotPose;
    

    /**
     * @brief ROS Publishers
    */
    ros::Publisher initialPosePub;


    /*Member variables*/
    geometry_msgs::Pose m_robotPose;

    

};

#endif