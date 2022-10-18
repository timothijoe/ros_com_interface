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
      action_client_stop= new ActionClient_track(n, "/is_stop");
      movebase_client = new MoveBaseClient(n, "/move_base");
}
ComInterface::ComInterface(int argc, char **argv):
    init_argc(argc),
    init_argv(argv)

{
      action_client_track = new ActionClient_track(n, "/wp_update");
      action_client_stop= new ActionClient_track(n, "/is_stop");
      movebase_client = new MoveBaseClient(n, "/move_base");
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


bool ComInterface::cancelTrackAction()
{
  ROS_INFO("Cancel Track Action");
  //bool server_exists = action_client_track->waitForServer(ros::Duration(3.0));
  // action_client_track->cancelGoal();
  styx_msgs::wp_updateGoal goal;
  goal.idx = 15;
  action_client_stop->sendGoal(goal);
  return true;
}


bool ComInterface::moveToOrigion1()
{
  ROS_INFO("Move to Origin 1");
  return true;

	geometry_msgs::PoseStamped send_Pose;
	move_base_msgs::MoveBaseGoal goal;
	
	send_Pose.pose.position.x = -0.0029694437980651855;
	send_Pose.pose.position.y =  2.828028678894043;
	send_Pose.pose.position.z = 0;
	send_Pose.pose.orientation.x = 0;
	send_Pose.pose.orientation.y = 0;
	send_Pose.pose.orientation.z = -0.6914743661613499;
	send_Pose.pose.orientation.w = 0.72240099732887923;
	
	goal.target_pose = send_Pose;//此处记得要定义MoveBaseGoal类的goal
	
	movebase_client->sendGoal(goal);
	
	movebase_client->waitForResult();
	if(movebase_client->getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		ROS_INFO("already reached goal!");
		//TODO: 成功到达目的地，此处发挥想象做点啥
	}
	else{
		ROS_INFO("Failed to reach the goal!");  
	}  
  return 0;
}

bool ComInterface::moveToOrigion2()
{
  ROS_INFO("Move to Origin 1");
  return true;

	geometry_msgs::PoseStamped send_Pose;
	move_base_msgs::MoveBaseGoal goal;
	
	send_Pose.pose.position.x = 0.235748291015625;
	send_Pose.pose.position.y =  -8.122727394104004;
	send_Pose.pose.position.z = 0;
	send_Pose.pose.orientation.x = 0;
	send_Pose.pose.orientation.y = 0;
	send_Pose.pose.orientation.z = 0.708872308283172;
	send_Pose.pose.orientation.w = 0.7053368348167331;
	
	goal.target_pose = send_Pose;//此处记得要定义MoveBaseGoal类的goal
	
	movebase_client->sendGoal(goal);
	
	movebase_client->waitForResult();
	if(movebase_client->getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		ROS_INFO("already reached goal!");
		//TODO: 成功到达目的地，此处发挥想象做点啥
	}
	else{
		ROS_INFO("Failed to reach the goal!");  
	}  
  return 0;
}