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
}

bool ComInterface::init()
{
  ros::init(init_argc,init_argv,"showcurve");
    if ( ! ros::master::check() ) {
      return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    client = n.serviceClient<std_srvs::Empty>("/pedsim_simulator/unpause_simulation");
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