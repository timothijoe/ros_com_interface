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
      action_client_track = new ActionClient_track(n, "/wp_update");
}
ComInterface::ComInterface(int argc, char **argv):
    init_argc(argc),
    init_argv(argv)

{
      action_client_track = new ActionClient_track(n, "/wp_update");
}
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
//    ros::NodeHandle n;
    start_record_client = n.serviceClient<std_srvs::SetBool>("/start_record");
    end_record_client = n.serviceClient<std_srvs::SetBool>("/end_record");
    // &action_client = ActionClient(n, "try_action");
    //ActionClient action_client2(n, "try_action");


//    action_client_track = new ActionClient_track(n, "/wp_update");


//    auto server_exists = action_client_track->waitForServer(ros::Duration(3.0));
//    action_client_stop = new ActionClient_track(n, "/is_stop");
    //  &action_client2;
    //actionlib::SimpleActionClient<styx_msgs::wp_updateAction> ac(n, "chatter", true);
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


//void ComInterface::done_callback(const actionlib::SimpleClientGoalState &state,
//                                 const styx_msgs::wp_updateResultConstPtr &result,
//                                 const actionlib::SimpleActionClient<styx_msgs::wp_updateAction> *client)
//{
//    return;
//}

void ComInterface::done_callback(const actionlib::SimpleClientGoalState &state,
                                 const styx_msgs::wp_updateResultConstPtr &result)
{
    return;
}

void ComInterface::active_callback()
{
    return;
}

void ComInterface::feedback_callback( const styx_msgs::wp_updateActionFeedbackConstPtr &feedback)
{
//    track_current_idx = feedback->status;
    return;
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
  styx_msgs::wp_updateGoal goal;
  if(traj_idx >= 14){
      traj_idx = 14;
  }
  if(traj_idx <0){
      traj_idx = 0;
  }
  goal.idx = traj_idx;
  std::cout << " wait for server" << std::endl;
  bool server_exists = action_client_track->waitForServer(ros::Duration(3.0));
// std::cout << server_exists << std::endl;
//      if (!server_exists) {
//          ROS_WARN("could not connect to server; halting");
//          return 0; // 输出一个警报消息，这部分也是非必要的
//      }
std::cout << " wait for sendgoal" << std::endl;
  while(true){
      action_client_track->sendGoal(goal);
//      bool finished_before_timeout = action_client_track->waitForResult(ros::Duration(5.0));
      break;
  }
std::cout << " end sendgoal" << std::endl;
//  action_client_track->sendGoal(goal);


//  action_client_track->sendGoal(goal, &ComInterface::done_callback);

//  action_client_track->sendGoal(goal, boost::bind(&ComInterface::done_callback, _1, _2, action_client_track),
//                                boost::bind(&ComInterface::active_callback),
//                                boost::bind(&ComInterface::feedback_callback, _1));

}
