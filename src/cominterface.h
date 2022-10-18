#ifndef COMINTERFACE_H
#define COMINTERFACE_H

#include <ros/ros.h>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/Float64MultiArray.h>
#include <std_srvs/SetBool.h>
#include <std_srvs/Empty.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_tutorials/FibonacciAction.h>

#include <styx_msgs/wp_updateAction.h>
#include <styx_msgs/wp_updateGoal.h>

//typedef actionlib::SimpleActionServer<actionlib_tutorials::FibonacciAction> ActionServer;
//typedef actionlib::ActionClient <actionlib_tutorials::FibonacciAction> ActionClient;
typedef actionlib::SimpleActionClient <styx_msgs::wp_updateAction> ActionClient_track;
//typedef actionlib::ActionClient <styx_msgs::wp_updateGoal> ActionClient_ugoal;
class ComInterface: public QThread{
  Q_OBJECT
public:
  ComInterface();
  ComInterface(int argc, char** argv);
  virtual ~ComInterface();
  bool init();
  void run();
  void subCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
  bool callService();
  bool callRestartService(bool default_pos_label, int random_seed_id, std::string scene_name, std::vector<double> robot_pos);
  bool callStopService();
  bool callContinueService();
  bool setRobotStop();
  bool setRobotContinue();

//  void done_callback(const actionlib::SimpleClientGoalState &state,
//                     const styx_msgs::wp_updateResultConstPtr &result,
//                     const actionlib::SimpleActionClient<styx_msgs::wp_updateAction> *client);

  void done_callback(const actionlib::SimpleClientGoalState &state,
                                   const styx_msgs::wp_updateResultConstPtr &result);
  void active_callback();
  void feedback_callback( const styx_msgs::wp_updateActionFeedbackConstPtr &feedback);


  bool callStartRecord(bool label);
  bool callEndRecord(bool label);
  bool callTrackAction(int traj_idx);
  bool cancelTrackAction();

Q_SIGNALS:
  void figureUpdated(double data1, double data2);
  void pedCollision(int fail_times_);
  void taskCompleted(int success_times_);
  void rosShutdown();

private:
  int init_argc;
  char** init_argv;
  int total_experiments_needed = 30;
  int success_times = 0;
  int failed_times = 0;
  int total_times = 0;
  //ControlPannel *control_pannel;
  ros::NodeHandle n;
  ros::Publisher chatter_publisher;
  ros::Subscriber data_sub;
  ros::Subscriber eva_sub;
  ros::ServiceClient start_record_client;
  ros::ServiceClient end_record_client;
  ActionClient_track* action_client_track;
  ActionClient_track* action_client_stop;
  uint8_t track_current_idx;

//  actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction> ac;
  // ActionServer aserver;

};

#endif // COMINTERFACE_H
