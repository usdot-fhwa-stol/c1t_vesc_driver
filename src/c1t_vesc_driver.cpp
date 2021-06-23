#include "c1t_vesc_driver/c1t_vesc_driver.h"

#include <ackermann_msgs/AckermannDriveStamped.h>
#include <autoware_msgs/VehicleCmd.h>
#include <cav_msgs/RobotEnabled.h>
#include <cav_srvs/SetEnableRobotic.h>

VescDriverWrapper::VescDriverWrapper(int argc, char** argv, const std::string& name)
  : cav::DriverWrapper(argc, argv, name)
{
}

void VescDriverWrapper::initialize()
{
  status_.controller = true;

  vehicle_cmd_sub_ = nh_->subscribe<autoware_msgs::VehicleCmd>(
      "vehicle_cmd", 1, [this](const autoware_msgs::VehicleCmd::ConstPtr& msg) {
        if (this->enabled_)
        {
          ackermann_msgs::AckermannDriveStamped vesc_msg;

          vesc_msg.drive.steering_angle = msg->ctrl_cmd.steering_angle;
          vesc_msg.drive.speed = msg->ctrl_cmd.linear_velocity;
          vesc_msg.drive.acceleration = msg->ctrl_cmd.linear_acceleration;

          this->ackermann_pub_.publish(vesc_msg);
        }
      });

  ackermann_pub_ = nh_->advertise<ackermann_msgs::AckermannDriveStamped>("ackermann_cmd", 1);
  robot_states_pub_ = nh_->advertise<cav_msgs::RobotEnabled>("robot_status", 1);

  enable_robotic_srv_ = nh_->advertiseService("enable_robotic", &VescDriverWrapper::enableRoboticCallback, this);

  robot_status_timer_ = nh_->createTimer(ros::Duration(0.1), [this](const ros::TimerEvent& event) {
    cav_msgs::RobotEnabled msg;

    msg.robot_enabled = this->enabled_;

    this->robot_states_pub_.publish(msg);
  });
}

void VescDriverWrapper::pre_spin()
{
  this->checkVescTimeout();
}

void VescDriverWrapper::post_spin()
{
}

void VescDriverWrapper::shutdown()
{
}

bool VescDriverWrapper::enableRoboticCallback(cav_srvs::SetEnableRobotic::Request& req,
                                              cav_srvs::SetEnableRobotic::Response& res)
{
  switch (req.set)
  {
    case req.ENABLE:
      enabled_ = true;
      break;

    case req.DISABLE:
      enabled_ = false;
      break;

    default:
      // It would be better to return this error to the called directly in the
      // response, but it seems that roscpp doesn't currently support this.
      ROS_ERROR("Unknown SetEnableRoboticRequest value: %d", req.set);
      return false;
  }

  return true;
}

void VescDriverWrapper::checkVescTimeout()
{
  if (last_upate_time_.isZero() || ros::Time::now() - last_upate_time_ > ros::Duration(vesc_timeout_))
  {
    status_.status = cav_msgs::DriverStatus::OFF;
  }
}
