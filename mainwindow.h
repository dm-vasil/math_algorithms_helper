#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <iostream>
#include <cmath>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <QtWidgets/QGridLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QGraphicsWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtCharts/QtCharts>
#include "tinyexpr.h"

typedef double telem; //определение типа элементов массива
typedef telem *tstr; //определение типа "указатель на telem"
typedef tstr *tmatr; //тип "указатель на указатель на telem"
using namespace std;

typedef vector<double> d_vector;

struct Answer {
    d_vector x, err;
    int iterations;
};

namespace Ui { //элементы интерфейса
    class Window;
}

class Window : public QWidget //главный виджет-контейнер
{
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0); //его конструктор
    static int const EXIT_CODE_REBOOT = -123456789; //специальный код выхода для реализации перезапуска
    QWidget *newind;
    QGridLayout *layout;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label_welcoming;
    private slots://Обработчики событий
    void reloadProgram(); //Перезапуск программы
    void loadMatrixWindow();
    void loadIntegralWindow();
    void loadInterpolateWindow();
private:
};



class MatrixWindow: public QWidget //главное окно
{
Q_OBJECT
public:
    int sizeM;
    explicit MatrixWindow(Window *parent);
    bool eventFilter(QObject *object, QEvent *event) override ; //фильтр, отлавливающий события
    Window *win;
    QLabel *metka1;
    QLabel *metka2;
    QLabel *metka3;
    QLabel *label_gauss;
    QLabel *label_iterate;
    QLabel *label_gauss_zeidel;
    QLabel *label_gauss_choose;
    QLabel *label_iterate_error;
    QSpinBox *sizeBox;
    QVector<QLabel*> metkaVector;
    QVector<QLabel*> metkaVector2;
    QVector<QLineEdit*> answerMetka;
    QVector<QLineEdit*> answerMetka2;
    QVector<QLabel*> equationVector;
    QVector<QLineEdit*> textVector;
    QVector<QLineEdit*> textVector2;
    QVector<QLineEdit*> answerVector;
    QVector<QLineEdit*> answerVector2;
    QGridLayout *layout;
    QGridLayout *layout1;
    QGridLayout *layout2;
    QPushButton *button_gauss;
    QPushButton *button_iterate;
    QPushButton *button_gauss_zeidel;
    QPushButton *button_gauss_choose;
    QPushButton *button_perezagruzka;
    QPushButton *button_back;
private slots://Обработчики событий
    void perezagruzka(); //Перезапуск программы
    void pererisovka(int);
    void gauss();
    void gauss_choose();
    void iterate();
    void gauss_zeidel();
    void closing();
private:
    bool checkEpsilon(int , d_vector, d_vector, float);
    bool checkDiagonal(vector <d_vector>);
    bool converge(tstr, tstr, int, double);
};

class IntegralWindow: public QWidget //главное окно
{
Q_OBJECT
public:
    explicit IntegralWindow(Window *parent);
    Window *win;
    QLabel *label_welcoming;
    QLabel *label_equation;
    QLabel *label_rectangle;
    QLabel *label_trapezium;
    QLabel *label_simpson;
    QLabel *label_answer;
    QLabel *label_upper;
    QLabel *label_lower;
    QLabel *label_precision;
    QSpinBox *sizeBox;
    QGridLayout *layout;
    QPushButton *button_rectangle;
    QPushButton *button_trapezium;
    QPushButton *button_simpson;
    QPushButton *button_perezagruzka;
    QPushButton *button_back;
    QLineEdit *text_equation;
    QLineEdit *text_answer;
    QLineEdit *text_upper;
    QLineEdit *text_lower;
    QLineEdit *text_precision;
private slots://Обработчики событий
    void rectangle();
    void trapezium();
    void simpson();
    void closing();
private:

};

class InterpolateWindow: public QWidget //главное окно
{
Q_OBJECT
struct SplineCoefficients
            {
                double a, b, c, d, x;
            };
public:
    explicit InterpolateWindow(Window *parent);
    Window *win;
    QVector<pair<double,double>> vect;
    QLabel *label_welcoming;
    QLabel *label_error_parsing;
    QLabel *label_equation;
    QLabel *label_lagrange;
    QLabel *label_newtone;
    QLabel *label_spline;
    QLabel *label_douglas;
    QLabel *label_upper;
    QLabel *label_lower;
    QLabel *label_iterations;
    QLabel *label_coordinate;
    QLabel *label_answer;
    QGridLayout *layout;
    QPushButton *button_lagrange;
    QPushButton *button_newtone;
    QPushButton *button_spline;
    QPushButton *button_douglas;
    QPushButton *button_perezagruzka;
    QPushButton *button_back;
    QPushButton *button_coordinate_lagr;
    QPushButton *button_coordinate_newt;
    QPushButton *button_coordinate_spln;
    QLineEdit *text_equation;
    QLineEdit *text_upper;
    QLineEdit *text_lower;
    QLineEdit *text_iterations;
    QLineEdit *text_coordinate;
    QLineEdit *text_answer;
    QChart *chart;
    QChartView *chartView;
private slots://Обработчики событий
    void interpolate_lagrange();
    void interpolate_newtone();
    void interpolate_spline();
    void calc_coord_lagr();
    void calc_coord_newt();
    void calc_coord_spln();
    void closing();
    void interpolate_douglas_peucker();
private:
    double lagrange(double , QVector<pair<double,double>>, int);
    void draw(QScatterSeries *, QSplineSeries *);
    double newtone(double , QVector<pair<double,double>>, int);
    double spline_make(QVector<pair<double,double>>, int);
    double spline_evaluate(double );
    vector<pair<double,double>> pointList;
    vector<pair<double,double>> pointListOut;
    void douglas_peucker(const vector<pair<double,double>>&, double, vector<pair<double,double>>&);
    double calculateDistance(const pair<double,double>&, const pair<double,double>&, const pair<double,double>&);
    QVector<SplineCoefficients> splines;
};