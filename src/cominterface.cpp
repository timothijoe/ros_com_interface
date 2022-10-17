#include "../src/cominterface.h"

#include <ros/ros.h>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/Float64MultiArray.h>
#include <std_srvs/SetBool.h>
#include <std_srvs/Empty.h>
#include <unistd.h>

ComInterface::ComInterface()
{

}
ComInterface::ComInterface(int argc, char **argv):
    init_argc(argc),
    init_argv(argv)
 {}
ComInterface::~ComInterface()
{
  if(ros::isStarted()) {
    ros::shutdown(); // explicitly needed since we use ros::start();
    ros::waitForShutdown();
  }
  wait();
}

bool ComInterface::init()
{
  ros::init(init_argc,init_argv,"showcurve");
    if ( ! ros::master::check() ) {
      return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    start_record_client = n.serviceClient<std_srvs::SetBool>("/start_record");
    end_record_client = n.serviceClient<std_srvs::SetBool>("/end_record");
    actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction> ac(n, "chatter", true);
    start();
    return true;
}

void ComInterface::run()
{
  ros::Rate loop_rate(1);
  while ( ros::ok() ) {
    ros::spinOnce();
    loop_rate.sleep();
  }
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown();
}

bool ComInterface::callStartRecord(bool label)
{

   ROS_INFO("Call Start Record");
  // std_srvs::SetBool srv;
  // srv.request.data = label;
  // start_record_client.call(srv);

  // if(restart_client.call(srv))
  // {
  //   ROS_INFO("Success");
  // }
  // else
  // {
  //   ROS_ERROR("Failed to call service add_two_ints");
  // }
}

bool ComInterface::callEndRecord(bool label)
{
  ROS_INFO("Call End Record");
  // std_srvs::SetBool srv;
  // srv.request.data = label;
  // end_record_client.call(srv);

}

bool ComInterface::callTrackAction(int traj_idx)
{
  ROS_INFO("Call Track Action");
//  ac.waitForServer();
  // std_srvs::SetBool srv;
  // srv.request.data = label;
  // end_record_client.call(srv);

}
