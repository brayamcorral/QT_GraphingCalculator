#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <deque>
#include <cmath>

double firstNum;
bool userIsTypingSecondNUmber= false;

//autofit display
//void QWidget::showMaximized()
//{
//    // ...
//    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
//                   | Qt::WindowMaximized);
//    show();
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Graph

    MainWindow::makePlot("2x-1", 20);


    connect(ui-> pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui-> pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui-> pushButton_00, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_01, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_02, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_03, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_04, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_05, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_06, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_07, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_08, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_09, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_Add_2, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_Subtract_2, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_equals_2, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_Square_2, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_X, SIGNAL(released()), this, SLOT(graph_digit_pressed()));
    connect(ui-> pushButton_Y, SIGNAL(released()), this, SLOT(graph_digit_pressed()));

    connect(ui-> pushButton_plusMinus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui-> pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui-> pushButton_AbsoluteValue, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui-> pushButton_sqrt, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui-> pushButton_Square, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui-> pushButton_NaturalLog, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui-> pushButton_add, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui-> pushButton_subtract, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui-> pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui-> pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    ui-> pushButton_add->setCheckable(true);
    ui-> pushButton_subtract->setCheckable(true);
    ui-> pushButton_multiply->setCheckable(true);
    ui-> pushButton_divide->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot(std::string equationString, int size)
{
    QVector<double> x((size * 100)+1), y((size * 100)+1);
    for(int  i = 0;i < (size * 100)+1; i++)
    {
        x[i] = i/50.0 - size; // x goes from -size to size
        y[i] = 0;
    }
    std::vector<char*> terms;
    std::deque<bool> signs;

    // Copy string into char array
    char equationChar[equationString.length() + 1];
    char equationCharSigns[equationString.length() + 1];
    strcpy(equationChar, equationString.c_str());
    strcpy(equationCharSigns, equationString.c_str());

    // Break up equation into a vector of terms
    char *token = strtok(equationChar, "+-");
    while (token != NULL)
    {
        terms.push_back(token);
        token = strtok(NULL, "+-"); // finds +-
    }

    // Find signs of each term
    for(char c : equationCharSigns)
    {
        qInfo() << c;
        if(c == '+')
            signs.push_back(true);
        else if(c == '-')
            signs.push_back(false);
    }
    if(signs.size() < terms.size())
        signs.push_front(true);

    qInfo() << "num signs:" << signs.size();
    for(bool b : signs)
    {
         qInfo() << b;
    }


    // Add each term to graph
    for(unsigned long i = 0; i < terms.size(); ++i)
    {
        int coefficient, exponent;
        bool carrotFound = false;
        std::string coefficientString, exponentString, term;
        term = std::string(terms[i]);

        // Get sign
        int sign  = signs[i] ? 1 : -1;
        if(!signs[i]) qInfo() << "-" << terms[i];
        else qInfo() << "+" << terms[i];

        // Get coefficient
        bool constant = true;
        for(int a = 0; a < term.size(); a++)
        {
            if(!isdigit(term[a]))\
            {
                constant = false;
                break;
            }
            else
                coefficientString += term[a];
        }
        coefficient = coefficientString.empty() ? 1 * sign : std::stoi(coefficientString) * sign;
        qInfo() << "c:" << QString::fromStdString(coefficientString) << coefficient;

        // Get exponent if term is not a constant
        if(!constant)
        {
            for(int a = 0; a < term.size(); a++)
            {
                if(carrotFound)
                    exponentString += term[a];
                else if(!carrotFound && term[a] == '^')
                    carrotFound = true;
            }
            exponent = exponentString.empty() ? (carrotFound ? 0 : 1) : std::stoi(exponentString);
        }
        else
        {
            exponent = 0;
        }

        qInfo() << "e:" << QString::fromStdString(exponentString) << exponent << "carrrot Found: " << carrotFound;

        // Add values to graph
        for (int a=0; a<(size * 100)+1; ++a)
        {
          x[a] = a/50.0 - size; // x goes from -size to size
          y[a] += coefficient * pow(x[a], exponent);
        }
    }

    // Create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);

    // Give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    // Set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-size, size);
    ui->customPlot->yAxis->setRange(-size, size);
    ui->customPlot->replot();
}

void MainWindow::digit_pressed(){
    QPushButton *button = (QPushButton*)sender();

    double labelNum;
    QString newLabel;

    if((ui->pushButton_add->isChecked()  || ui->pushButton_subtract->isChecked() || ui->pushButton_multiply->isChecked()  || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNUmber)){
        labelNum = button -> text().toDouble();
        userIsTypingSecondNUmber=  true;
        newLabel = QString::number(labelNum, 'g',  15);
    }else{
        if(ui->pushButton_label->text().contains('.') && (button->text() == "0")){
            newLabel = (ui -> pushButton_label -> text() + button-> text());
        }
        else{
           labelNum = (ui -> pushButton_label -> text() + button-> text()).toDouble();
           newLabel = QString::number(labelNum, 'g',  15);
        }

    }


    ui -> pushButton_label ->setText(newLabel);
}

void MainWindow::on_pushButton_decimal_released() //new slot for decimal
{
    ui -> pushButton_label -> setText(ui -> pushButton_label->  text() + ".");
}

void MainWindow::unary_operation_pressed(){
    QPushButton *button = (QPushButton*)sender();
    double labelNum;
    QString newLabel;
    if(button -> text() == "+/-"){
        labelNum = ui -> pushButton_label -> text().toDouble();
        labelNum *= -1;
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
    }
    else if(button -> text() == "%"){
        labelNum = ui -> pushButton_label -> text().toDouble();
        labelNum *= 0.01;
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
    }
    else if(button -> text() == "|a|"){
        labelNum = ui -> pushButton_label -> text().toDouble();
        labelNum = abs(labelNum);
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
    }
    else if(button -> text() == "^"){
        labelNum = ui -> pushButton_label -> text().toDouble();
        labelNum *= labelNum;
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
    }
    else if(button -> text() == "√"){
        labelNum = ui -> pushButton_label -> text().toDouble();
        labelNum = sqrt(labelNum);
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
    }
    else if(button -> text() == "ln  log"){
        labelNum = ui -> pushButton_label -> text().toDouble();
        labelNum = log(labelNum);
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
    }
}

void MainWindow::on_pushButton_clear_released()
{

    ui -> pushButton_add-> setChecked(false);
    ui -> pushButton_subtract-> setChecked(false);
    ui -> pushButton_multiply-> setChecked(false);
    ui -> pushButton_divide-> setChecked(false);
    ui->pushButton_AbsoluteValue -> setChecked(false);

    userIsTypingSecondNUmber = false;
    ui -> pushButton_label-> setText("0");

}

void MainWindow::on_pushButton_equals_released()
{
    double labelNum, secondNum;
    QString newLabel;

    secondNum = ui -> pushButton_label -> text().toDouble();

    if(ui-> pushButton_add -> isChecked()){
        labelNum = firstNum + secondNum;
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
        ui -> pushButton_add -> setChecked(false);
    }

    else if(ui-> pushButton_subtract -> isChecked()){
        labelNum = firstNum - secondNum;
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
        ui -> pushButton_subtract -> setChecked(false);
    }
    else if(ui-> pushButton_multiply -> isChecked()){
        labelNum = firstNum * secondNum;
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
        ui -> pushButton_multiply -> setChecked(false);
    }
    else if(ui-> pushButton_divide -> isChecked()){
        labelNum = firstNum / secondNum;
        newLabel = QString::number(labelNum, 'g', 15);
        ui -> pushButton_label -> setText(newLabel);
        ui -> pushButton_divide -> setChecked(false);
    }

    userIsTypingSecondNUmber =  false;

}
void MainWindow::binary_operation_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    firstNum =  ui -> pushButton_label-> text().toDouble();
    button -> setChecked(true);
}


void MainWindow::on_pushButton_Mode_clicked() //first page
{
    ui -> stackedWidget-> setCurrentIndex(1);
}

void MainWindow::on_pushButton_Mode_2_clicked() //second page
{
    ui -> stackedWidget-> setCurrentIndex(0);
}

void MainWindow::on_pushButton_clear_2_released(){
    userIsTypingSecondNUmber = false;
    MainWindow::makePlot("", 10);
    ui -> pushButton_label_2-> setText("0");
}

void MainWindow::graph_digit_pressed(){
    QPushButton *button = (QPushButton*)sender();

    QString newLabel;

    if(ui->pushButton_label_2->text() == "0"){
        newLabel = button-> text();
    }
    else{
        newLabel = (ui -> pushButton_label_2 -> text() + button-> text());
    }

    ui -> pushButton_label_2 ->setText(newLabel);
}

void MainWindow::on_pushButton_Graph_released(){
    std::string equation = ui->pushButton_label_2->text().toLocal8Bit().constData();
    MainWindow::makePlot(equation, 10);
}

void MainWindow::on_pushButton_Euler_released(){

    ui -> pushButton_label ->setText(QString::number(M_E, 'g', 15));
}

void MainWindow::on_pushButton_Pi_released(){
    ui -> pushButton_label ->setText(QString::number(M_PI, 'g', 15));
}


