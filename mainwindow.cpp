#include "mainwindow.h"
#include <iostream>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    input = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_zero_clicked()
{
    input.append("0");
    ui->Input->setText(input);
}

void MainWindow::on_one_clicked()
{
    input.append("1");
    ui->Input->setText(input);
}

void MainWindow::on_two_clicked()
{
    input.append("2");
    ui->Input->setText(input);
}

void MainWindow::on_three_clicked()
{
    input.append("3");
    ui->Input->setText(input);
}

void MainWindow::on_four_clicked()
{
    input.append("4");
    ui->Input->setText(input);
}

void MainWindow::on_five_clicked()
{
    input.append("5");
    ui->Input->setText(input);
}

void MainWindow::on_six_clicked()
{
    input.append("6");
    ui->Input->setText(input);
}

void MainWindow::on_seven_clicked()
{
    input.append("7");
    ui->Input->setText(input);
}

void MainWindow::on_eight_clicked(bool checked)
{
    input.append("8");
    ui->Input->setText(input);
}

void MainWindow::on_nine_clicked()
{
    input.append("9");
    ui->Input->setText(input);
}

void MainWindow::on_mul_clicked()
{
    input.append("x");
    ui->Input->setText(input);
}

void MainWindow::on_div_2_clicked()
{
    input.append("/");
    ui->Input->setText(input);
}

void MainWindow::on_dot_clicked()
{
    input.append(".");
    ui->Input->setText(input);
}

void MainWindow::on_plus_clicked()
{
    input.append("+");
    ui->Input->setText(input);
}

void MainWindow::on_minus_clicked()
{
    input.append("-");
    ui->Input->setText(input);
}

void MainWindow::on_del_clicked()
{
    input.truncate(input.size() -1);
    ui->Input->setText(input);
}

void MainWindow::on_clear_2_clicked()
{
    ui->Input->setText("");
}
