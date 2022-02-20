#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMainWindow>

#include <QKeyEvent>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_clear_clicked();

    void on_del_clicked();

    void on_minus_clicked();

    void on_plus_clicked();

    void on_dot_clicked();

    void on_zero_clicked();

    void on_nine_clicked();

    void on_seven_clicked();

    void on_div_clicked();

    void on_mul_clicked();

    void on_five_clicked();

    void on_four_clicked();

    void on_three_clicked();

    void on_six_clicked();

    void on_two_clicked();

    void on_one_clicked();

    void on_eight_clicked();

    void on_equal_clicked();

    void on_inverse_clicked();

    void on_left_b_clicked();

    void on_cos_clicked();

    void on_tan_clicked();

    void on_sin_clicked();

    void on_right_b_clicked();

    void on_up_clicked();

    void on_down_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_ans_clicked();

    void on_digit_button_clicked();
    void on_pow_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    bool on_result, on_edit;
    void on_op_button_clicked();
    std::vector<std::string> display_stack;
    std::vector<std::string> calculate_stack;
    int s_count;
    Calculator c;
    int cp;
};
#endif // MAINWINDOW_H
