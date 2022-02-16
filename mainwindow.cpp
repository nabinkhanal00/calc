#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) ,on_result(false),
      on_edit(false), s_count(-1), cp(0) {
	ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_op_button_clicked() {
    if (on_result && !on_edit) {
        c.display_input.clear();
        c.calculate_input.clear();
        c.display_input+="Ans";
        c.calculate_input+="  ~";
        ui->Input->setText(QString::fromStdString(c.display_input));
		on_result = false;
	}
}
void MainWindow::on_digit_button_clicked(){
    if (on_result && !on_edit) {
        c.display_input.clear();
        c.calculate_input.clear();
        ui->Input->clear();
        on_result = false;
    }
}
void MainWindow::on_zero_clicked() {
    on_digit_button_clicked();
	int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "0");
    c.display_input.insert(cp, "0");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_one_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "1");
    c.display_input.insert(cp, "1");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_two_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "2");
    c.display_input.insert(cp, "2");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_three_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "3");
    c.display_input.insert(cp, "3");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_four_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "4");
    c.display_input.insert(cp, "4");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_five_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "5");
    c.display_input.insert(cp, "5");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_six_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "6");
    c.display_input.insert(cp, "6");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_seven_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "7");
    c.display_input.insert(cp, "7");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_eight_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "8");
    c.display_input.insert(cp, "8");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_nine_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "9");
    c.display_input.insert(cp, "9");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_mul_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "*");
    c.display_input.insert(cp, "*");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_div_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "/");
    c.display_input.insert(cp, "/");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_dot_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, ".");
    c.display_input.insert(cp, ".");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_plus_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "+");
    c.display_input.insert(cp, "+");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_minus_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "-");
    c.display_input.insert(cp, "-");

    ui->Input->setText(QString::fromStdString(c.display_input));
}

void MainWindow::on_del_clicked() {
    if(c.display_input.size() > 0){
    int cp = ui->Input->cursorPosition();

    c.display_input.erase(cp-1, 1);
    c.calculate_input.erase(cp-1, 1);
    ui->Input->setText(QString::fromStdString(c.display_input));
}
}

void MainWindow::on_clear_clicked() {
    c.display_input.clear();
    c.calculate_input.clear();
    ui->Input->clear();
    on_result = false;
    on_edit = false;
}

void MainWindow::on_equal_clicked() {
    try {
        if(c.calculate_input == ""){
            return;
        }
        double value = c.calculate(nullptr);
        ui->Result->display(value);
        calculate_stack.push_back(c.calculate_input);
        display_stack.push_back(c.display_input);
        s_count = display_stack.size() - 1;
        c.previous_answer = value;
    }  catch (std::domain_error d) {
        std::cout << d.what() << std::endl;
        ui->Result->display(d.what());
        c.display_input.clear();
        c.calculate_input.clear();
        ui->Input->clear();
    } catch(...){
        ui->Result-> display("error");
    }
	on_result = true;
    on_edit = false;
}

void MainWindow::on_inverse_clicked()
{

}


void MainWindow::on_left_b_clicked()
{
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "(");
    c.display_input.insert(cp, "(");

    ui->Input->setText(QString::fromStdString(c.display_input));
}


void MainWindow::on_cos_clicked()
{
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "  @(");
    c.display_input.insert(cp, "cos(");

    ui->Input->setText(QString::fromStdString(c.display_input));
}


void MainWindow::on_tan_clicked()
{
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "  #(");
    c.display_input.insert(cp, "tan(");

    ui->Input->setText(QString::fromStdString(c.display_input));
}


void MainWindow::on_sin_clicked()
{
     on_op_button_clicked();
     int cp = ui->Input->cursorPosition();
     c.calculate_input.insert(cp, "  !(");
     c.display_input.insert(cp, "sin(");

     ui->Input->setText(QString::fromStdString(c.display_input));
}


void MainWindow::on_right_b_clicked()
{
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, ")");
    c.display_input.insert(cp, ")");

    ui->Input->setText(QString::fromStdString(c.display_input));
}


void MainWindow::on_up_clicked()
{
     if (on_result&&!calculate_stack.empty() && s_count>0){
         s_count--;
        c.calculate_input = calculate_stack[s_count];
        c.display_input = display_stack[s_count];
        ui->Input->setText(QString::fromStdString(c.display_input));
    }
}


void MainWindow::on_down_clicked()
{
    if(on_result && s_count < calculate_stack.size()-1){
        s_count++;
        c.calculate_input = calculate_stack[s_count];
        c.display_input = display_stack[s_count];
        ui->Input->setText(QString::fromStdString(c.display_input));
    }
}


void MainWindow::on_left_clicked()
{
    std::cout << ui->Input->cursorPosition() << std::endl;
    ui->Input->setFocus();
    ui->Input->cursorBackward(false);
    on_edit = true;
}


void MainWindow::on_right_clicked()
{
    std::cout << ui->Input->cursorPosition() << std::endl;
    ui->Input->setFocus();
    ui->Input->cursorForward(false);
    on_edit = true;

}

void MainWindow::on_ans_clicked()
{
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.calculate_input.insert(cp, "  ~");
    c.display_input.insert(cp, "Ans");
    ui->Input->setText(QString::fromStdString(c.display_input));
    ui->Input->setCursorPosition(cp);
    std::cout << cp << std::endl;
    on_edit = false;
}

