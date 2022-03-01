#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), on_result(false),
    on_edit(false), s_count(-1), cp(0) {
    ui->setupUi(this);
    c.angle = "d";
    ui->angleValue->setText(QString::fromStdString(c.angle));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_op_button_clicked() {
    if (on_result && !on_edit) {
        c.input.clear();
        c.input += "Ans";
        ui->Input->setText(QString::fromStdString(c.input));
        on_result = false;
    }
    ui->Input->setFocus();
}
void MainWindow::on_digit_button_clicked() {
    if (on_result && !on_edit) {
        c.input.clear();
        ui->Input->clear();
        on_result = false;
    }
    ui->Input->setFocus();
}
void MainWindow::on_zero_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "0");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_one_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "1");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_two_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "2");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_three_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "3");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_four_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "4");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_five_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "5");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_six_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "6");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_seven_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "7");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_eight_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "8");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_nine_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "9");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_mul_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "*");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_div_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "/");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_dot_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, ".");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_plus_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "+");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_minus_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "-");

    ui->Input->setText(QString::fromStdString(c.input));
    ui->Input->setCursorPosition(cp + 1);
}

void MainWindow::on_del_clicked() {
    //std::cout << (ui->Input->text().toStdString()  == "π")<< std::endl;
    std::cout << c.input.size() << std::endl;
    std::cout << cp << std::endl;
    int cp = ui->Input->cursorPosition();
    int new_cp;
    if (cp > 0) {
        std::string substr = "";
        if (cp >= 4) {
            substr = c.input.substr(cp - 4, 4);
        }
        else if (cp >= 3) {
            substr = c.input.substr(cp - 3, 3);
        }
        else if (cp >= 2) {
            substr = c.input.substr(cp - 2, 2);
        }
        if (substr != "") {
            if (substr.size() == 4 && (substr == "sin(" || substr == "cos(" || substr == "tan(" || substr == "log(")) {
                c.input.erase(cp - 4, 4);
                new_cp = cp - 4;
            }
            else if (substr.size() >= 3 && (substr.substr(substr.size() - 3, 3) == "Ans" || substr.substr(substr.size() - 3, 3) == "ln(")) {
                c.input.erase(cp - 3, 3);
                new_cp = cp - 3;
            }
            else if (substr.size() >= 2 && (substr.substr(substr.size() - 2, 2) == "pi")){
                c.input.erase(cp - 2, 2);
                new_cp = cp - 2;
            }
            else {
                c.input.erase(cp - 1, 1);
                new_cp = cp - 1;
            }
        }
        else {
            c.input.erase(cp - 1, 1);
            new_cp = cp - 1;
        }
        ui->Input->setText(QString::fromStdString(c.input));
        ui->Input->setCursorPosition(new_cp);
        on_result = false;
    }
    ui->Input->setFocus();
}

void MainWindow::on_clear_clicked() {
    c.input="";
    s_count = stk.size();
    ui->Input->clear();
    ui->Result->setText(0);
    on_result = false;
    on_edit = false;
    ui->Input->setFocus();
}

void MainWindow::on_equal_clicked() {
    QString input = ui->Input->text();
    c.input = input.toStdString();
    try {
        if (c.input == "") {
            return;
        }
        double value = c.calculate();
        if (log10(value) + 1 > 10) {
            char answer[21];
            sprintf(answer, "%e", value);
            ui->Result->setText(QString::fromStdString(std::string(answer)));
        }
        else {
            std::stringstream s;
            s << value;
            ui->Result->setText(QString::fromStdString(s.str()));
        }
        if (stk.empty() || stk.back() != c.input) {
            stk.push_back(input.toStdString());
        }
        s_count = stk.size() - 1;
        c.previous_answer = value;
    }
    catch (std::domain_error d) {
        std::cout << d.what() << std::endl;
        ui->Result->setText(d.what());
    }
    catch (...) {
        ui->Result->setText("error");
    }
    on_result = true;
    on_edit = false;
}

void MainWindow::on_inverse_clicked() {}

void MainWindow::on_left_b_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "(");

    ui->Input->setText(QString::fromStdString(c.input));
}

void MainWindow::on_cos_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "cos(");

    ui->Input->setText(QString::fromStdString(c.input));
}

void MainWindow::on_tan_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "tan(");

    ui->Input->setText(QString::fromStdString(c.input));
}

void MainWindow::on_sin_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "sin(");

    ui->Input->setText(QString::fromStdString(c.input));
}

void MainWindow::on_right_b_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, ")");

    ui->Input->setText(QString::fromStdString(c.input));
}

void MainWindow::on_up_clicked() {
    std::cout << "Calculate stack  size: " << stk.size() << std::endl
        << "S count: " << s_count << std::endl;
    if (!stk.empty() && s_count > 0) {
        s_count--;
        c.input = stk[s_count];
        ui->Input->setText(QString::fromStdString(c.input));
    }
}

void MainWindow::on_down_clicked() {
    if (s_count < stk.size() - 1) {
        s_count++;
        c.input = stk[s_count];
        ui->Input->setText(QString::fromStdString(c.input));
    }
}

void MainWindow::on_left_clicked() {
    std::cout << ui->Input->cursorPosition() << std::endl;
    ui->Input->setFocus();
    ui->Input->cursorBackward(false);
    on_edit = true;
}

void MainWindow::on_right_clicked() {
    std::cout << ui->Input->cursorPosition() << std::endl;
    ui->Input->setFocus();
    ui->Input->cursorForward(false);
    on_edit = true;
}

void MainWindow::on_ans_clicked() {
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "Ans");
    ui->Input->setText(QString::fromStdString(c.input));
    on_edit = false;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    int code = event->key();
    std::cout << code << std::endl;
    if (code == 16777219) {
        on_del_clicked();
        return;
    }
    else if (code == 16777220) {
        on_equal_clicked();
        return;
    }
    else if (code == Qt::Key_Up) {
        std::cout << "Up button" << std::endl;
        on_up_clicked();
    }
    else if (code == Qt::Key_Down) {
        on_down_clicked();
    }

    else {
        char c = char(code);
        switch (c) {
        case '\n':
            on_equal_clicked();
        case '\b':
            on_del_clicked();
        case '0':
            on_zero_clicked();
            break;
        case '1':
            on_one_clicked();
            break;
        case '2':
            on_two_clicked();
            break;
        case '3':
            on_three_clicked();
            break;
        case '4':
            on_four_clicked();
            break;
        case '5':
            on_five_clicked();
            break;
        case '6':
            on_six_clicked();
            break;
        case '7':
            on_seven_clicked();
            break;
        case '8':
            on_eight_clicked();
            break;
        case '9':
            on_nine_clicked();
            break;
        case 'S':
            on_sin_clicked();
            break;
        case 'C':
            on_cos_clicked();
            break;
        case 'T':
            on_tan_clicked();
            break;
        case '+':
            on_plus_clicked();
            break;
        case '-':
            on_minus_clicked();
            break;
        case '(':
            on_left_b_clicked();
            break;
        case ')':
            on_right_b_clicked();
            break;
        case '*':
            on_mul_clicked();
            break;
        case '/':
            on_div_clicked();
            break;
        case '^':
            // todo
            break;
        case '.':
            on_dot_clicked();
            break;
        default:
            break;
        }
    }
}

void MainWindow::on_pow_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "^");

    ui->Input->setText(QString::fromStdString(c.input));
}

void MainWindow::on_ln_clicked() {
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "ln(");
    ui->Input->setText(QString::fromStdString(c.input));
}


void MainWindow::on_angle_clicked()
{
    if (c.angle == "d") {
        c.angle = "g";
    }
    else if (c.angle == "g") {
        c.angle = "r";
    }
    else {
        c.angle = "d";
    }

    ui->angleValue->setText(QString::fromStdString(c.angle));
}




void MainWindow::on_log_clicked()
{
    on_op_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "log(");
    ui->Input->setText(QString::fromStdString(c.input));
}


void MainWindow::on_pie_clicked()
{
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "pi");
    ui->Input->setText(QString::fromStdString(c.input));
    std::cout << "Prev: " << cp << " After: " << ui->Input->cursorPosition() << std::endl;

}


void MainWindow::on_exp_clicked()
{
    on_digit_button_clicked();
    int cp = ui->Input->cursorPosition();
    c.input.insert(cp, "e");
    ui->Input->setText(QString::fromStdString(c.input));

}

