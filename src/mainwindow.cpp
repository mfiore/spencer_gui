#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(ros::NodeHandle node_handle, QWidget *parent):node_handle_(node_handle):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    supervision_sub_=node_handle_.subscribe("/supervision/status",1, 
        &MainWindow::supervisionStatusCallback,this);
    pause_supervision_client_=ros::serviceClient<supervision_msgs::EmptyRequest>("/supervision/pause");
    restart_supervision_client_=ros::serviceClient<supervision_msgs::EmptyRequest>("/supervision/restart");
    stop_supervision_client_=ros::serviceClient<supervision_msgs::EmptyRequest>("/supervision/stop");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_guide_me_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button_gate_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_button_input_gate_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_button_back_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button_go_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_button_back_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button_stop_4_clicked()
{
    supervision_msgs::EmptyRequest srv;
    if (!pause_supervision_client_.call(srv)){
        ROS_ERROR("Failed to pause supervor");
    }
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_button_resume_clicked()
{
    supervision_msgs::EmptyRequest srv;
    if (!pause_supervision_client_.call(srv)){
        ROS_ERROR("Failed to resume supervisor");
    }
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_button_abandon_clicked()
{
    supervision_msgs::EmptyRequest srv;
    if (!stop_supervision_client_.call(srv)){
        ROS_ERROR("Failed to stop supervisor");
    }
    ui->stackedWidget->setCurrentIndex(7);
    ros::Duration(5).sleep;
    if (!restart_superivision_client_.call(srv)) {
        ROS_ERROR("Failed to resume supervisor")
    }
}
