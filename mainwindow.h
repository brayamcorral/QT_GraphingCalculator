#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_pressed();


    void on_pushButton_decimal_released();
    void unary_operation_pressed();
    void on_pushButton_clear_released();
    void on_pushButton_equals_released();
    void binary_operation_pressed();

    // Graph
    void makePlot(std::string equationString, int size = 10);


    //page 2 buttons
    void on_pushButton_Mode_clicked();
    void on_pushButton_Mode_2_clicked();

    void on_pushButton_clear_2_released(); //functions for graphing
    void graph_digit_pressed();
    void on_pushButton_Graph_released();

    void on_pushButton_Euler_released();
    void on_pushButton_Pi_released();

};


#endif // MAINWINDOW_H
