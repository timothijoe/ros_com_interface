#include "mainwindow.h"
#include "ui_mainwindow.h"
//QT
#include "QMessageBox"
#include "QDebug"
#include "QProcess"

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui (new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ROS-QT GUI Template");
    timer = new QTimer(this);
    // Update lcd's values
    connect(timer, SIGNAL(timeout()),this,SLOT(pose_values()));
    timer->start(500);
//    manual_window = new Manual_Window();
    //ROS
    ros_f = new _Ros();
    c_inter = new ComInterface();
}
MainWindow::~MainWindow()
{
    delete ui;
    ui = NULL;
    delete ros_f;
    ros_f =NULL;
}


void MainWindow::on_Teleop_clicked()
{
//    manual_window->show();
//    manual_window->exec();
}

void MainWindow::on_Exit_clicked()
{
    qApp->exit();
}

void MainWindow::pose_values()
{
    // Subscribe turtlesim's poses
    ros_f->pose_subscriber();

    // Display the values
//    ui->x_lcd->display(turtlesim_pose.x);
//    ui->y_lcd->display(turtlesim_pose.y);
//    ui->theta_lcd->display(turtlesim_pose.theta);
//    ui->linear_lcd->display(turtlesim_pose.linear_velocity);
//    ui->angular_lcd->display(turtlesim_pose.angular_velocity);
    
}



void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_start_track_btn_clicked()
{
  std::cout<< "start button clicked" << std::endl;
  MainWindow::on_start_record_btn_clicked();
  int num = state_traj_num;
  c_inter->callTrackAction(num);
}

void MainWindow::on_interrupt_btn_clicked()
{
  std::cout<< "interrupt button clicked" << std::endl;
  c_inter->cancelTrackAction();
  MainWindow::on_end_record_btn_clicked();
}

void MainWindow::on_normal_termiate_btn_clicked()
{
  std::cout<< "normal terminate clicked" << std::endl;
  MainWindow::on_end_record_btn_clicked();
}

void MainWindow::on_start_record_btn_clicked()
{
    bool zt;
    c_inter->callStartRecord(zt);
}

void MainWindow::on_end_record_btn_clicked()
{
    bool zt;
    c_inter->callEndRecord(zt);
}

void MainWindow::on_move_to1_btn_clicked()
{
    std::cout<< "moveto 1 clicked" << std::endl;
}

void MainWindow::on_move_to2_btn_clicked()
{
    std::cout<< "moveto 2 clicked" << std::endl;
}

void MainWindow::on_state_space_box_valueChanged(const QString &arg1)
{
    state_traj_num = ui->state_space_box->value();
    ui->state_space_lcd->display(state_traj_num);
}
