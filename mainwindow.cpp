#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "backend.cpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), on_result(false),
      editing_input(false) {
	ui->setupUi(this);
	input = "";
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_op_button_clicked() {
	if (on_result && !editing_input) {
        input.clear();
        ui->Input->clear();
		on_result = false;
	}
}

void MainWindow::on_zero_clicked() {
	on_op_button_clicked();
	int cp = ui->Input->cursorPosition();
	input.insert(cp, "0");
	ui->Input->setText(input);
}

void MainWindow::on_one_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "1");
	ui->Input->setText(input);
}

void MainWindow::on_two_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "2");
	ui->Input->setText(input);
}

void MainWindow::on_three_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "3");

	ui->Input->setText(input);
}

void MainWindow::on_four_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "4");
	ui->Input->setText(input);
}

void MainWindow::on_five_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "5");
	ui->Input->setText(input);
}

void MainWindow::on_six_clicked() {
	int cp = ui->Input->cursorPosition();
	input.insert(cp, "6");
	ui->Input->setText(input);
}

void MainWindow::on_seven_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "7");
	ui->Input->setText(input);
}

void MainWindow::on_eight_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "8");
	ui->Input->setText(input);
}

void MainWindow::on_nine_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "9");
	ui->Input->setText(input);
}

void MainWindow::on_mul_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "*");
	ui->Input->setText(input);
}

void MainWindow::on_div_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "/");
	ui->Input->setText(input);
}

void MainWindow::on_dot_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, ".");
	ui->Input->setText(input);
}

void MainWindow::on_plus_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "+");
	ui->Input->setText(input);
}

void MainWindow::on_minus_clicked() {
	on_op_button_clicked();

	int cp = ui->Input->cursorPosition();
	input.insert(cp, "-");
	ui->Input->setText(input);
}

void MainWindow::on_del_clicked() {
	input.truncate(input.size() - 1);
	ui->Input->setText(input);
}

void MainWindow::on_clear_clicked() {
	input.clear();
	ui->Input->setText("");
}

void MainWindow::on_equal_clicked() {
    QString qtext = input;
	std::string str = qtext.toStdString();
    try {
        double result = calculate(str);
        ui->Result->display(result);

    }  catch (std::string error) {
        ui->Result->display("math error");
        input.clear();

    }
	on_result = true;
}
