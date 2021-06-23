#ifndef C1T_VESC_DRIVER_H
#define C1T_VESC_DRIVER_H

#include <cav_driver_utils/driver_wrapper/driver_wrapper.h>
#include "cav_srvs/SetEnableRobotic.h"

/**
 * VESC ROS package wrapper that conforms to the CARMA controller 
 * hardware interface.
 * 
 * Subscribers:
 *   system_alert: CARMA system_alert topic
 *   vehicle_cmd: vehicle control commands
 *   
 * Publishers
 *   driver_discovery: driver information
 *   robot_status: controller status
 *   ackermann_cmd: vehicle control commands from vehicle_cmd converted
 *                  into AckermannDriveStamped messages
 * 
 * Services
 *   enable_robotic: enable or disable the controller
 */
class VescDriverWrapper : public cav::DriverWrapper
{
public:
  /**
   * @brief VescDriverWrapper constructor
   * 
   * @param argc commandline argument count
   * @param argv array of commandline argument values
   * @param name ROS node name
   */
  VescDriverWrapper(int argc, char** argv, const std::string& name = "c1t_vesc_driver");

  /**
   * VescDrvierWrapper destructor
   */
  virtual ~VescDriverWrapper() = default;

private:
  ros::Publisher ackermann_pub_;
  ros::Publisher robot_states_pub_;
  ros::Subscriber vehicle_cmd_sub_;
  ros::ServiceServer enable_robotic_srv_;

  ros::Timer robot_status_timer_;  // Drives robot_status topic publishing
  ros::Time last_upate_time_;  // Used to check for VESC timeouts
  double vesc_timeout_ = 0.0;  // Timeout threshold
  bool enabled_ = false;  // If controller is enabled

  /**
   * @brief Initializes the ROS node
   * 
   * This function is called before the ROS node starts running.
   */
  void initialize() override;

  /**
   * @brief Process stuff before spinning
   * 
   * This function is called before the spinOnce() function.
   */
  void pre_spin() override;

  /**
   * @brief Process stuff after spinning
   * 
   * This function is called after the spinOnce() function.
   */
  void post_spin() override;

  /**
   * @brief Prepare ROS node for shutting down
   * 
   * This function is called before the node is shut down.
   */
  void shutdown() override;

  /**
   * @brief EnableRobotic service callback function
   * 
   * @param req incomming service request
   * @param res outgoing service response
   */
  bool enableRoboticCallback(cav_srvs::SetEnableRobotic::Request& req, cav_srvs::SetEnableRobotic::Response& res);

  /**
   * @brief Check if the VESC has timeed out
   * 
   * Check if the time between VESC messages exceeds
   * the timeout threshold.
   */
  void checkVescTimeout();
};

#endif  // C1T_VESC_DRIVER_H