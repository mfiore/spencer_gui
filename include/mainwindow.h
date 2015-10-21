#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <string>
#include <supervision_msgs/SupervisionStatus.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(ros::NodeHandle node_handle,QWidget *parent = 0);
    ~MainWindow();
    
private Q_SLOTS:
    void on_button_guide_me_clicked();

    void on_button_gate_clicked();

    void on_button_input_gate_clicked();

    void on_button_back_5_clicked();

    void on_button_go_clicked();

    void on_button_back_3_clicked();

    void on_button_stop_4_clicked();

    void on_button_resume_clicked();

    void on_button_abandon_clicked();

private:
    Ui::MainWindow *ui;
    ros::NodeHandle node_handle_;
    ros::Subscriber supervision_sub_;
    ros::ServiceClient pause_supervision_client_;
    ros::ServiceClient stop_supervision_client_;
    ros::ServiceClient restart_superivision_client_;

    void supervisionStatusCallback(const supervision_msgs::SupervisionStatus::ConstPtr& msg);

};

#endif // MAINWINDOW_H
