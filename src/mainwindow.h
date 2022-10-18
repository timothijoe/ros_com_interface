#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
//#include "Manual_Window/manual_window.h"

//ros
#include "ros/ros.h"
#include "../src/ROS_src/_ros.h"
#include "../src/cominterface.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
Q_OBJECT
public:

    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public Q_SLOTS:
    void pose_values();
    void on_Teleop_clicked();
    void on_Exit_clicked();

/*/private slots: Note if you want to create function from mainwindow.ui delete
 * private slots and put them in public QSLOTS
 * */


private slots:
    void on_pushButton_clicked();

    void on_start_track_btn_clicked();

    void on_interrupt_btn_clicked();

    void on_normal_termiate_btn_clicked();

    void on_start_record_btn_clicked();

    void on_end_record_btn_clicked();

    void on_move_to1_btn_clicked();

    void on_move_to2_btn_clicked();

    void on_state_space_box_valueChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    ComInterface *c_inter;
    _Ros* ros_f;
    QTimer* timer;
//    Manual_Window* manual_window;
    turtlesim::Color colour_input;
    int space_channel = 0; // 0 for state space and 1 for control space
    int state_traj_num = 0;
    int control_traj_num = 0;


};

#endif // MAINWINDOW_H
