#include "auto_localization.h"
#include <ros/console.h> 

#include "ros_class.h"

/**
* @brief  Constructor for the TrajectoryController
*/
AutoLocalization::AutoLocalization(std::unique_ptr<RosClass> rosPtr):m_getVariables(std::move(rosPtr))
{
    ROS_INFO("AutoLocalization Constructor called");
    initializeRobotPose();

}

/**
* @brief  Destructor for the TrajectoryController
*/

AutoLocalization::~AutoLocalization()
{

}

/**
* @brief  Initializes robot's position from the last known position
*/
void AutoLocalization::initializeRobotPose()
{
    std::unique_lock<std::mutex> r_lock(m_mutex);
    std::ifstream inFile;
    inFile.open(filePath + "/" + "initalPath.txt");
    double value;
    std::string line;
    int count = 0;
    if(inFile.is_open())
    {
    
        while (std::getline(inFile, line)) 
        {
            std::istringstream linestream(line);
            linestream  >> value;
            lastRobotPose[count] = value;
            count++;
            std::cout << value << std::endl;
        }

    }
    inFile.close();
}

/**
* @brief  Updates the robot's position to the local text file
*/
void AutoLocalization::writeLastRobotPose()
{
    std::unique_lock<std::mutex> w_lock(m_mutex);
    std::ofstream outFile;
    outFile.open(filePath + "/" + "initalPath.txt");

    geometry_msgs::Pose robotPose = m_getVariables->getRobotPose();
    currentPose[0]  = robotPose.position.x;
    currentPose[1]  = robotPose.position.y;
    currentPose[2]  = robotPose.orientation.z;
    currentPose[3]  = robotPose.orientation.w;
    if(outFile.is_open())
    {
        for(int i =0; i < 4; i++)
        {
            outFile << currentPose[i] << endl;
        }
    }
    outFile.close();
}

/**
* @brief  Publishes the robot position which will be used for localization
*/  
void AutoLocalization::publishRobotPose()
{
    geometry_msgs::PoseWithCovarianceStamped initialPose;
    //ros::Time stamp_now = ros::Time::now();
    initialPose.header.stamp = ros::Time(0);
    initialPose.header.frame_id = "/map";

    initialPose.pose.pose.position.x    = lastRobotPose[0];
    initialPose.pose.pose.position.y    = lastRobotPose[1];
    initialPose.pose.pose.orientation.z = lastRobotPose[2];
    initialPose.pose.pose.orientation.w = lastRobotPose[3];

    initialPose.pose.covariance[0]=0.1;
    initialPose.pose.covariance[7]=0.1;
    initialPose.pose.covariance[35]=0.1;

    m_getVariables->sendInitialPose(initialPose);

}


/**
* @return the clock time in milliseconds
*/
uint64_t AutoLocalization::millis() 
{
	uint64_t ms =std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	return ms;
}

/**
* @brief Main function
*/
int main(int argc, char** argv)
{

    ros::init(argc, argv, "auto_localization");
    std::unique_ptr<RosClass> rosPtr (new RosClass);    
    AutoLocalization localization(std::move(rosPtr));

    ros::Rate rate(1);
    uint64_t startTime,endTime;
    bool initialize = false;
    startTime = endTime= localization.millis();

    while(ros::ok())
    {
        /*Initializing the robot from the last known position*/
        if(endTime-startTime < 100)
    	{
    		endTime = localization.millis();
            localization.publishRobotPose();
            initialize = true;
    	}
     
        /*Updating the robot position in the local text file*/
        if(initialize)
        {
            localization.writeLastRobotPose();
        }
        rate.sleep();
        ros::spinOnce();
    }
    ros::shutdown();
    return 0;
}







