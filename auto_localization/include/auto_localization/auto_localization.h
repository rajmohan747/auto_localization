#ifndef AUTO_LOCALIZATION_H
#define AUTO_LOCALIZATION_H

#include <iostream>
#include <ros/ros.h>
#include "ros_class.h"
#include <ros/package.h>
#include <fstream>
#include <chrono>
#include <mutex>
using namespace std;
  /**
   * @class TrajectoryController
   * @brief A controller that follows the trajectory provided by a planner.
   */

class AutoLocalization
{
public:
        /**
     * @brief  Constructor for the TrajectoryController
     */

    //AutoLocalization(RosClass* m_getVariables);
    AutoLocalization (std::unique_ptr<RosClass> rs);
        /**
        * @brief  Destructor for the TrajectoryController
        */
    ~AutoLocalization();

       

    
    void writeLastRobotPose();
    void publishRobotPose();
    uint64_t millis();

private:

    /**
    * @brief  Initializes robot's position from the last known position
    */
    void initializeRobotPose();

    /*Member variables*/

    geometry_msgs::Pose m_robotPose;
    
    std::unique_ptr<RosClass>  m_getVariables;
    std::string filePath = ros::package::getPath("auto_localization");
    std::mutex m_mutex;

    double currentPose[4]={0.0,0.0,0.0,1.1};
    double lastRobotPose[4]={0.0};


};
#endif
