#include "mainwindow.h"

Window::Window(QWidget *parent) //Конструктор, задаем начальный вид виджета
        : QWidget(parent)
{
    this->setWindowTitle("Меню");
    layout = new QGridLayout;
    button1 = new QPushButton("Выбрать");
    button2 = new QPushButton("Выбрать");
    button3 = new QPushButton("Выбрать");
    button1->setMaximumWidth(80);
    button2->setMaximumWidth(80);
    button3->setMaximumWidth(80);
    label1 = new QLabel("Решения системы линейных\nалгебраических уравнений");
    label2 = new QLabel("Интегрирование функции");
    label3 = new QLabel("Интерполяция функций");
    label_welcoming = new QLabel("Приветствуем в системе решения математических задач.\nВыберите раздел:");
    label_welcoming->setWordWrap(true);
    label_welcoming ->setStyleSheet("font: bold 16px; color:white");
    label1 ->setStyleSheet("font: bold 14px; color:rgba(255,200,0,255)");
    label2 ->setStyleSheet("font: bold 14px; color:rgba(255,200,0,255)");
    label3 ->setStyleSheet("font: bold 14px; color:rgba(255,200,0,255)");
    layout->addWidget(label_welcoming, 0, 0, 2, 1);
    layout->addWidget(label1, 2, 0);
    layout->addWidget(label2 , 4, 0);
    layout->addWidget(label3, 6, 0);
    layout->addWidget(button1, 3, 0);
    layout->addWidget(button2, 5, 0);
    layout->addWidget(button3, 7, 0);
    this->setLayout(layout);
    button1->setStyleSheet("background-color: rgba(0,185,0,255); color: white; "
                                       "border-style:outset;border-width: 2px;border-color: "
                                       "blue;font:bold 13px;min-width: 10em;padding: 6px;border-radius: 12px;");
    button2->setStyleSheet("background-color: rgba(0,185,0,255);color: white; "
                               "border-style:outset;border-width: 2px;border-color: "
                               "blue;font:bold 13px;min-width: 10em;padding: 6px;border-radius: 12px;");
    button3->setStyleSheet("background-color: rgba(0,185,0,255);color: white; "
                                "border-style:outset;border-width: 2px;border-color: "
                                "blue;font:bold 13px;min-width: 10em;padding: 6px;border-radius: 12px;");
    connect(button1, SIGNAL (clicked()), this, SLOT (loadMatrixWindow())); //отслеживание сигналов и обработчики
    connect(button2, SIGNAL (clicked()), this, SLOT (loadIntegralWindow())); //отслеживание сигналов и обработчики
    connect(button3, SIGNAL (clicked()), this, SLOT (loadInterpolateWindow()));
    QPixmap bkgnd(R"(C:\Users\Mitty Vasilmann\Desktop\UNIVERSITY\math_helper\1.jpg)");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void Window::reloadProgram() //Перезапуск программы
{
    qDebug() << "Performing application reboot...";
    qApp->exit( this->EXIT_CODE_REBOOT ); //Выход со специальным кодом-индикатором
}

void Window::loadMatrixWindow()
{
    newind = new MatrixWindow(this);
    this->hide();
    newind->show();
}

void Window::loadIntegralWindow()
{
    newind = new IntegralWindow(this);
    this->hide();
    newind->show();
}

void Window::loadInterpolateWindow()
{
    newind = new InterpolateWindow(this);
    this->hide();
    newind->show();
}

MatrixWindow::MatrixWindow(Window *parent) //Задается начальный вид нашего окна
{
    this->setWindowTitle("Решение СЛАУ");
    win = parent;
    layout = new QGridLayout;
    sizeBox = new QSpinBox();
    sizeBox->setValue(3);
    sizeBox->setRange(1,8);
    label_gauss = new QLabel("Метод Гаусса");
    label_gauss_choose = new QLabel("Метод Гаусса с выбором");
    label_iterate = new QLabel("Метод простых\nитераций");
    label_gauss_zeidel = new QLabel("Метод Гаусса-Зейделя");
    label_iterate_error = new QLabel();
    button_gauss = new QPushButton("Применить");
    button_gauss_choose = new QPushButton("Применить");
    button_iterate = new QPushButton("Применить");
    button_gauss_zeidel = new QPushButton("Применить");
    button_perezagruzka = new QPushButton("Сброс матрицы");
    button_back = new QPushButton("Назад");
    label_gauss -> setWordWrap(true);
    label_gauss_choose -> setWordWrap(true);
    label_iterate -> setWordWrap(true);
    label_gauss_zeidel -> setWordWrap(true);
    label_iterate_error -> setWordWrap(true);
    label_gauss ->setStyleSheet("font: bold 11px; color: white");
    label_gauss_choose ->setStyleSheet("font: bold 11px; color: white");
    label_iterate ->setStyleSheet("font: bold 11px; color: white");
    label_gauss_zeidel ->setStyleSheet("font: bold 11px; color: white");
    label_iterate_error ->setStyleSheet("font: bold 11px; color: red");
    label_iterate_error -> setVisible(false);
    button_gauss->setMaximumWidth(60);
    button_gauss_choose ->setMaximumWidth(60);
    button_iterate -> setMaximumWidth(60);
    button_gauss_zeidel ->setMaximumWidth(60);
    //button_perezagruzka->setMaximumWidth(130);
    button_perezagruzka->setStyleSheet("background-color: rgba(200,255,0,255);; "
                                       "border-style:outset;border-width: 1px;border-color: "
                                       "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_back->setStyleSheet("background-color: rgba(200,255,0,255);; "
                               "border-style:outset;border-width: 1px;border-color: "
                               "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_gauss->setStyleSheet("background-color: rgba(255,255,0,255); "
                                    "border-style:outset;border-width: 1px;border-color: "
                                    "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_gauss_choose ->setStyleSheet("background-color: rgba(255,200,0,255); "
                                        "border-style:outset;border-width: 1px;border-color: "
                                        "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_iterate ->setStyleSheet("background-color: rgba(255,160,0,255); "
                                   "border-style:outset;border-width: 1px;border-color: "
                                   "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_gauss_zeidel ->setStyleSheet("background-color: rgba(255,100,0,255); "
                                        "border-style:outset;border-width: 1px;border-color: "
                                        "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    metka3 = new QLabel("Введите размерность\nматрицы");
    metka1 = new QLabel("Исходная\nсистема");
    metka2 = new QLabel("Матрица\nответов");
    metka1->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    metka2->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    metka1->setStyleSheet("font: bold 13px; color: white");
    metka2->setStyleSheet("font: bold 13px; color: white");
    metka3->setStyleSheet("font: bold 13px; color: white");
    layout->addWidget(metka3, 0, 0);
    layout->addWidget(sizeBox, 1, 0);
    layout->addWidget(label_gauss, 2, 0);
    layout->addWidget(label_gauss_choose, 2, 1);
    layout->addWidget(label_iterate, 4, 0);
    layout->addWidget(label_gauss_zeidel, 4, 1);
    layout->addWidget(button_gauss, 3, 0);
    layout->addWidget(button_gauss_choose, 3, 1);
    layout->addWidget(button_iterate, 5, 0);
    layout->addWidget(button_gauss_zeidel, 5, 1);
    layout->addWidget(button_perezagruzka, 9, 0);
    layout->addWidget(button_back, 9, 1);
    layout->addWidget(label_iterate_error, 10, 0);
    sizeBox->setMaximumWidth(100);
    layout->addWidget(metka1, 7,0);
    layout->addWidget(metka2, 7, 1);
    layout->setRowMinimumHeight(4, 20);
    layout1 = new QGridLayout;
    layout2 = new QGridLayout;
    layout->addLayout(layout1, 8, 0 );
    layout->addLayout(layout2, 8, 1 );
    layout->setVerticalSpacing(5);
    //привязка обработчиков к обрабатываемым событиям
    connect(sizeBox, SIGNAL (valueChanged(int)), this, SLOT (pererisovka(int)));
    connect(button_perezagruzka, SIGNAL (clicked()), this, SLOT (perezagruzka()));
    connect(button_gauss, SIGNAL (clicked()), this, SLOT (gauss()));
    connect(button_gauss_choose, SIGNAL (clicked()), this, SLOT (gauss_choose()));
    connect(button_iterate, SIGNAL (clicked()), this, SLOT (iterate()));
    connect(button_gauss_zeidel, SIGNAL (clicked()), this, SLOT (gauss_zeidel()));
    connect(button_back, SIGNAL (clicked()), this, SLOT (closing()));
    this->setLayout(layout);
    //на задний фон помещаем картинку
    QPixmap bkgnd(R"(C:\Users\Mitty Vasilmann\Desktop\UNIVERSITY\math_helper\2.jpg)");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    emit sizeBox->valueChanged(sizeBox->value()); //инициируем сигнал для начальной отрисовки матриц
}

void MatrixWindow::pererisovka(int size)
{
    QLayoutItem* item, *item1;
    QValidator *validator = new QIntValidator(-999, 1000);//валидатор для корректного ввода значений
    while ( ( item = layout1->layout()->takeAt( 0 ) ) != nullptr && \
        (item1 = layout2->layout()->takeAt( 0 ) ) != nullptr) //если матрица уже есть
    {
        delete item->widget(); //чистим память, если когда перерисовать матрицы с новым размером
        delete item1->widget();
        delete item;
        delete item1;
    }
    int i, j, k;
    sizeM = size;
    metkaVector.resize(size*2+1);
    answerMetka.resize(size);
    answerMetka2.resize(size);
    answerVector.resize(size);
    answerVector2.resize(size);
    textVector.resize(size*size);
    metkaVector2.resize(size*2+1);
    textVector2.resize(size*size);
    equationVector.resize(size*2);
    layout1->setRowMinimumHeight(0, 20);
    layout2->setRowMinimumHeight(0, 20);
    layout1->setColumnMinimumWidth( 0, 20);
    layout2->setColumnMinimumWidth( 0, 20);
    for (i = 0; i < size; i++) { //инициализируем строки и столбцы матриц
        metkaVector[i] = new QLabel("X" + QString::number(i));
        metkaVector[size + i] = new QLabel(QString::number(i+1));
        metkaVector2[i] = new QLabel("X" + QString::number(i));
        metkaVector2[size + i] = new QLabel(QString::number(i+1));
        metkaVector[i]->setAlignment(Qt::AlignCenter);
        metkaVector2[i]->setAlignment(Qt::AlignCenter);
        metkaVector[size + i]->setAlignment(Qt::AlignCenter);
        metkaVector2[size + i]->setAlignment(Qt::AlignCenter);
        metkaVector[i]->setStyleSheet("background-color: yellow;font: bold;");
        metkaVector[size + i]->setStyleSheet("background-color: yellow;font: bold;");
        metkaVector2[i]->setStyleSheet("background-color: yellow;font: bold");
        metkaVector2[size + i]->setStyleSheet("background-color: yellow;font: bold;");
        layout1->addWidget(metkaVector[i], 0, i + 1);
        layout1->addWidget(metkaVector[size + i], i + 1, 0);
        layout2->addWidget(metkaVector2[i], 0, i + 1);
        layout2->addWidget(metkaVector2[size + i], i + 1, 0);
    }
    metkaVector[size*2] = new QLabel("V");
    metkaVector2[size*2] = new QLabel("V");
    metkaVector[size*2]->setStyleSheet("background-color: yellow;font: bold;");
    metkaVector2[size*2]->setStyleSheet("background-color: yellow;font: bold;");
    metkaVector[size*2]->setAlignment(Qt::AlignCenter);
    metkaVector2[size*2]->setAlignment(Qt::AlignCenter);
    layout1->addWidget(metkaVector[size*2], 0, size + 2);
    layout2->addWidget(metkaVector2[size*2], 0, size + 2);
    for (i = 0; i < size*size; i++) {
        textVector[i] = new QLineEdit();
        textVector2[i] = new QLineEdit();
        textVector[i]->setText(QString::number(0));
        textVector[i]->setFixedSize(30,20);
        textVector2[i]->setFixedSize(30,20);
        textVector[i]->setValidator(validator);
        textVector2[i]->setReadOnly(true);
        textVector[i]->installEventFilter(this);
    }
    for (i = 0; i < size*2; i++)
    {
        equationVector[i] = new QLabel("=");
        equationVector[i]->setStyleSheet("font: bold 13px; color: white");
        equationVector[i]->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    }
    for (i = 0; i < size; i++)
    {
        answerVector[i] = new QLineEdit();
        answerVector2[i] = new QLineEdit();
        answerVector[i]->setText(QString::number(0));
        answerVector[i]->setFixedSize(30,20);
        answerVector2[i]->setFixedSize(30,20);
        answerVector[i]->setValidator(validator);
        answerVector2[i]->setReadOnly(true);
        answerVector[i]->installEventFilter(this);
    }
    k = 0;
    for (i = 1; i < size+1; i++)
    {
        for (j = 1; j < size+1; j++) {
            layout1->addWidget(textVector[k], i, j);
            layout2->addWidget(textVector2[k], i, j);
            k++;
        }
        layout1->addWidget(equationVector[i-1], i, j);
        layout2->addWidget(equationVector[i+size-1], i, j);
        layout1->addWidget(answerVector[i-1], i, j+1);
        layout2->addWidget(answerVector2[i-1], i, j+1);
    }

    this->hide();
    this->show();
}

void MatrixWindow::gauss()
{
    label_iterate_error->setVisible(false);
    tmatr Matr;
    int i, j, k;
    double determinant = 1, div = 0, tmp = 0;
    Matr = new tstr[sizeM];
    for (i = 0; i<sizeM; i++)
        Matr[i] = new telem[sizeM+1];
    for (i = 0; i < sizeM; i++) {
        for (j = 0; j < sizeM; j++)
            Matr[i][j] = textVector[i * sizeM + j]->text().toDouble();
        Matr[i][sizeM] = answerVector[i]->text().toDouble();
    }
    for (i = 0; i < sizeM; i++) {
        determinant *= Matr[i][i];
    }
    for (i = 1; i < sizeM; i++)
    {
        for (j = i; j < sizeM; j++)
        {
            div = Matr[j][i - 1] / Matr[i - 1][i - 1];
            for (k = 0; k <= sizeM; k++)
            {
                Matr[j][k] -= div * Matr[i - 1][k];
            }
        }
    }
    for (i = sizeM - 1; i >= 0; i--)
    {
        if (i == sizeM - 1)
        {
            answerVector2[i]->setText(QString::number(Matr[i][sizeM]/Matr[i][i])) ;
            continue;
        }
        tmp = Matr[i][sizeM];
        for (j = sizeM - 1; j > i; j--)
        {
            tmp -= Matr[i][j] * answerVector2[j]->text().toDouble();
        }
        answerVector2[i] ->setText(QString::number(tmp / Matr[i][i], 'f', 2));
    }
    for (i = 0; i < sizeM*sizeM; i+=sizeM+1)
        textVector2[i] ->setText(QString::number(1));
    for (i=0; i<sizeM; i++)
        delete[] Matr[i]; //память освобождается
    delete[] Matr;
}

void MatrixWindow::gauss_choose()
{
    label_iterate_error->setVisible(false);
    tmatr Matr;
    tstr Answ;
    int i, j, k, n, im;
    telem v, s;
    Matr = new tstr[sizeM];
    Answ = new telem[sizeM];
    for (i = 0; i<sizeM; i++)
        Matr[i] = new telem[sizeM+1];
    for (i = 0; i < sizeM; i++) {
        for (j = 0; j < sizeM; j++)
            Matr[i][j] = textVector[i * sizeM + j]->text().toDouble();
        Answ[i] = answerVector[i]->text().toDouble();
    }
    for(k = 0; k < sizeM - 1; k++)
    {
        im = k;
        for(i = k + 1; i < sizeM; i++)
        {
            if(abs(Matr[im][k]) < abs(Matr[i][k]))
            {
                im = i;
            }
        }
        if(im != k)
        {
            for(j = 0; j < sizeM; j++)
            {
                v = Matr[im][j];
                Matr[im][j] = Matr[k][j];
                Matr[k][j] = v;
            }
            v = Answ[im];
            Answ[im] = Answ[k];
            Answ[k]  = v;
        }
        for(i = k + 1; i < sizeM; i++)
        {
            v = Matr[i][k]/Matr[k][k];
            Matr[i][k] = 0;
            Answ[i] = Answ[i] - v*Answ[k];
            if(v != 0)
                for(j = k + 1; j < sizeM; j++)
                {
                    Matr[i][j] = Matr[i][j] - v*Matr[k][j];
                }
        }
        s = 0;
        answerVector2[sizeM - 1] ->setText(QString::number(Answ[sizeM - 1]/Matr[sizeM - 1][sizeM - 1]));
        for(i = sizeM - 2, j; 0 <= i; i--)
        {
            s = 0;
            for (j = i + 1; j < sizeM; j++) {
                s = s + Matr[i][j] * answerVector2[j]->text().toDouble();;
            }
            answerVector2[i] ->setText(QString::number((Answ[i] - s)/Matr[i][i], 'f', 2));
        }
    }
    for (i = 0; i < sizeM*sizeM; i+=sizeM+1)
        textVector2[i] ->setText(QString::number(1));
    for (i=0; i<sizeM; i++)
        delete[] Matr[i]; //память освобождается
    delete [] Matr;
    delete [] Answ;
}

void MatrixWindow::iterate()
{
    label_iterate_error->setVisible(false);
    vector <d_vector> a;
    vector <vector <bool>> diagonal;
    d_vector prev_x, x, b;
    bool flag = 0;
    float epsilon = 0.000000000001;
    int iteration = 0, i, j;
    vector <d_vector> src_1(sizeM);
    d_vector src_2(sizeM);
    for (i=0; i<sizeM; i++)
    {
        src_1[i].resize(sizeM);
        for (j = 0; j < sizeM; j++)
            src_1[i][j] = textVector[i*sizeM+j]->text().toDouble();
        src_2[i] = answerVector[i]->text().toDouble();
    }
    vector <vector<bool>> m(sizeM, vector<bool>(sizeM, false));
    for (i = 0; i < sizeM; i++)
    {
        float sum = 0;
        for (j = 0; j < sizeM; j++)
        {
            sum += abs(src_1[i][j]);
        }
        for (j = 0; j < sizeM; j++)
        {
            if (2 * abs(src_1[i][j]) > sum)
            {
                m[i][j] = true;
            }
        }
    }
    vector <d_vector> patch_1(m.size());
    d_vector patch_2(m.size());
    for (i = 0; i < min(m.size(), m[0].size()); i++)
    {
        bool found = 0;
        for (j = 0; j < min(m.size(), m[0].size()); j++)
        {
            if (m[j][i])
            {
                found = 1;
                patch_1[i] = src_1[j];
                patch_2[i] = src_2[j];
                break;
            }
            if (!found)
                flag = 1;
        }
    }
    if (!flag)
    {
        src_1 = patch_1;
        src_2 = patch_2;
    }
    a.resize(src_1.size());
    double normal_a = 0, normal_b = 0;
    for (i = 0; i < src_1.size(); i++)
    {
        a[i].resize(src_1[i].size());
        for (j = 0; j < src_1[i].size(); j++)
        {
            if (i == j)
            {
                a[i][i] = 0;
            }
            else {
                a[i][j] = - src_1[i][j] / src_1[i][i];
                normal_a = max(normal_a, abs(a[i][j]));
            }
        }
    }
    b.resize(src_2.size());
    for (i = 0; i < src_2.size(); i++)
    {
        b[i] = src_2[i] / src_1[i][i];
        normal_b = max(normal_b, abs(b[i]));
    }
    //первоначальное приближение
    x = b;
    //основной цикл
    while (checkDiagonal(a) && checkEpsilon(iteration, x, prev_x, epsilon))
    {
        for (i; i < sizeM; i++)
            cout << x[i] << " ";
        cout << endl;
        iteration++;
        prev_x = x;
        for (i = 0; i < a.size(); i++)
        {
            double sum = 0;
            for (j = 0; j < a[i].size(); j++)
            {
                sum += a[i][j] * prev_x[j];
            }
            x[i] = sum + b[i];
        }
    }
    if (!flag) {
        for (i = 0; i < sizeM; i++)
            answerVector2[i]->setText(QString::number(x[i], 'f', 2));
        for (i = 0; i < sizeM * sizeM; i += sizeM + 1)
            textVector2[i]->setText(QString::number(1));
    }
    else
    {
        label_iterate_error->setText("Отсутствует диагональное преобладание!\nРезультат будет некорректен.");
        label_iterate_error->setVisible(true);
    }
}

bool MatrixWindow::checkEpsilon(int iteration, d_vector x, d_vector prev_x, float epsilon)
{
    if (iteration < 1) return true;
    double cmax = abs(x[0] - prev_x[0]);
    for (int i = 1; i < x.size(); i++)
    {
        cmax = max(cmax, abs(x[i] - prev_x[i]));
    }
    return cmax > epsilon;
}

bool MatrixWindow::checkDiagonal(vector <d_vector> a)
{
    float normal = 0;
    for (int j = 0; j < a[0].size(); j++)
    {
        float sum = 0;
        for (int i = 0; i < a.size(); i++)
        {
            sum += abs(a[i][j]);
        }
        normal = max(normal, sum);
    }
    return normal < 1;
}


void MatrixWindow::gauss_zeidel()
{
    label_iterate_error->setVisible(false);
    tmatr Matr;
    tstr Answ, x, p;
    int i, j,
    k = 1,
    m = 0;
    telem sum;
    double eps = 0.00000001;
    Matr = new tstr[sizeM];
    Answ = new telem[sizeM];
    x = new telem[sizeM];
    p = new telem[sizeM];
    for (i = 0; i<sizeM; i++)
        Matr[i] = new telem[sizeM+1];
    for (i = 0; i < sizeM; i++)
    {
        for (j = 0; j < sizeM; j++)
            Matr[i][j] = textVector[i * sizeM + j]->text().toDouble();
        Answ[i] = answerVector[i]->text().toDouble();
    }
    for (int i = 0; i < sizeM; i++)
        x[i] = 1;

    for (i = 0; i < sizeM; i++)
    {
        sum = 0;
        for (j = 0; j < sizeM; j++)
            sum += abs(Matr[i][j]);
            sum -= abs(Matr[i][i]);
        if (sum > Matr[i][i])
            k = 0;
    }
    if (k)
    {
        do{
            for (int i = 0; i < sizeM; i++)
                p[i] = x[i];
            for (int i = 0; i < sizeM; i++)
            {
                double var = 0;
                for (int j = 0; j < i; j++)
                    var += (Matr[i][j] * x[j]);
                for (int j = i + 1; j < sizeM; j++)
                    var += (Matr[i][j] * p[j]);
                x[i] = (Answ[i] - var) / Matr[i][i];
            }
            m++;
        }
        while (!converge(x, p, sizeM, eps));
        for (i = 0; i < sizeM; i++)
        {
           int n = 0;
            double neweps = eps;
               while (neweps < 1)
               {
                   n++;
                   neweps *= 10;
                }
            int okr = pow(double(10), n);
            answerVector2[i] -> setText(QString::number((x[i]*okr + 0.5) / double(okr)));
        }
    }
    else
    {
        label_iterate_error->setText("Отсутствует диагональное преобладание!\nРезультат будет некорректен.");
        label_iterate_error->setVisible(true);
    }
    for (i=0; i<sizeM; i++)
        delete[] Matr[i]; //память освобождается
    delete [] Matr;
    delete [] Answ;
}

bool MatrixWindow::converge(tstr x, tstr p, int n, double eps)
{
    double norm = 0;
   for (int i = 0; i < n; i++)
      norm += (x[i] - p[i]) * (x[i] - p[i]);
   return (sqrt(norm) < eps);
}

bool MatrixWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) //перехват события фокуса на текстовом поле
    {
        auto *MatrixElement = dynamic_cast<QLineEdit *>(object); //приводим перехваченный объект к нужному типу
        if (MatrixElement->text() == "0")//если в ячейке 0, стираем и предлагаем ввести число
            MatrixElement->setText("");
    }
    else if (event->type() == QEvent::FocusOut)//перехват события снятия фокуса с текстового поля
    {
        auto *MatrixElement = dynamic_cast<QLineEdit *>(object);
        MatrixElement->text().isEmpty();
        if ((MatrixElement->text().isEmpty()))//если в ячейке ничего не ввели, ставим 0
            MatrixElement->setText("0");
    }
    return false;
}


void MatrixWindow::perezagruzka() //приводим матрицу к начальному виду
{
    emit sizeBox->valueChanged(3);
    sizeBox->setValue(3);
    label_iterate_error->setVisible(false);
}

void MatrixWindow::closing() //закрытие нового окна после ввода
{
    this->hide();
    win->show();
}

IntegralWindow::IntegralWindow(Window *parent) //Задается начальный вид нашего окна
{
    this->setWindowTitle("Решение интегралов");
    win = parent;
    layout = new QGridLayout;
    text_equation = new QLineEdit();
    text_answer = new QLineEdit();
    text_upper = new QLineEdit();
    text_lower = new QLineEdit();
    text_precision = new QLineEdit();
    text_upper->setMaximumWidth(80);
    text_lower->setMaximumWidth(80);
    text_precision->setMaximumWidth(80);
    text_answer->setMaximumWidth(130);
    text_equation->setMinimumWidth(200);
    label_welcoming = new QLabel("Введите исходные данные для вычисления интергала и выберите метод");
    label_equation = new QLabel("Введите уравнение:");
    label_rectangle = new QLabel("Метод прямоугольников");
    label_trapezium = new QLabel("Метод трапеций");
    label_simpson = new QLabel("Метод Симпсона");
    label_answer = new QLabel("Ответ:");;
    label_upper = new QLabel("Верхний предел:");
    label_lower = new QLabel("Нижний предел:");
    label_precision = new QLabel("Точность:");
    //label_iterate_error = new QLabel();
    button_rectangle = new QPushButton("Применить");
    button_trapezium = new QPushButton("Применить");
    button_simpson = new QPushButton("Применить");
    button_perezagruzka = new QPushButton("Сброс матрицы");
    button_back = new QPushButton("Назад");
    label_rectangle -> setWordWrap(true);
    label_trapezium -> setWordWrap(true);
    label_simpson -> setWordWrap(true);
    label_welcoming -> setWordWrap(true);
    label_welcoming ->setStyleSheet("font: bold 14px; color:rgba(255,200,0,255)");
    label_rectangle ->setStyleSheet("font: bold 11px; color: white");
    label_trapezium ->setStyleSheet("font: bold 11px; color: white");
    label_simpson ->setStyleSheet("font: bold 11px; color: white");
    label_equation ->setStyleSheet("font: bold 12px; color: yellow");
    label_answer ->setStyleSheet("font: bold 12px; color: yellow");
    label_upper ->setStyleSheet("font: bold 12px; color: yellow");
    label_lower ->setStyleSheet("font: bold 12px; color: yellow");
    label_precision ->setStyleSheet("font: bold 12px; color: yellow");
    //label_iterate_error -> setVisible(false);
    button_rectangle->setMaximumWidth(60);
    button_trapezium ->setMaximumWidth(60);
    button_simpson -> setMaximumWidth(60);
    button_rectangle->setStyleSheet("background-color: rgba(255,0,255,140); "
                                "border-style:outset;border-width: 1px;border-color: "
                                "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_trapezium ->setStyleSheet("background-color: rgba(255,0,200,110); "
                                        "border-style:outset;border-width: 1px;border-color: "
                                        "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_simpson ->setStyleSheet("background-color: rgba(255,0,160,80); "
                                   "border-style:outset;border-width: 1px;border-color: "
                                   "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_perezagruzka->setStyleSheet("background-color: rgba(200,255,0,255);; "
                                       "border-style:outset;border-width: 1px;border-color: "
                                       "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_back->setStyleSheet("background-color: rgba(200,255,0,255);; "
                               "border-style:outset;border-width: 1px;border-color: "
                               "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    //label_iterate_error ->setStyleSheet("font: bold 11px; color: red");
    layout->addWidget(label_welcoming, 0, 0, 1, 2);
    layout->addWidget(label_equation, 1, 0);
    layout->addWidget(text_equation, 1, 1);
    layout->addWidget(label_upper, 2, 0);
    layout->addWidget(text_upper, 3, 0);
    layout->addWidget(label_lower, 2, 1);
    layout->addWidget(text_lower, 3, 1);
    layout->addWidget(label_precision, 4, 0);
    layout->addWidget(text_precision, 5, 0);
    layout->addWidget(label_rectangle, 6, 0);
    layout->addWidget(button_rectangle, 7, 0);
    layout->addWidget(label_trapezium, 6, 1);
    layout->addWidget(button_trapezium, 7, 1);
    layout->addWidget(label_simpson, 8, 0);
    layout->addWidget(button_simpson, 9, 0);
    layout->addWidget(label_answer, 10, 0, Qt::AlignRight);
    layout->addWidget(text_answer, 10, 1);
    layout->addWidget(button_back, 11, 0);
    connect(button_perezagruzka, SIGNAL (clicked()), this, SLOT (perezagruzka()));
    connect(button_back, SIGNAL (clicked()), this, SLOT (closing()));
    connect(button_rectangle, SIGNAL (clicked()), this, SLOT (rectangle()));
    connect(button_trapezium, SIGNAL (clicked()), this, SLOT (trapezium()));
    connect(button_simpson, SIGNAL (clicked()), this, SLOT (simpson()));
    this->setLayout(layout);
    //на задний фон помещаем картинку
    QPixmap bkgnd(R"(C:\Users\Mitty Vasilmann\Desktop\UNIVERSITY\math_helper\1.jpg)");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void IntegralWindow::closing() //закрытие нового окна после ввода
{
    this->hide();
    win->show();
}

void IntegralWindow::rectangle() //закрытие нового окна после ввода
{
    double x, y, upper, lower, precision, step, pr_sq, sq = 0;
    int i, err,
    n = 10;
    char *expression, *upper_exp, *lower_exp;
    precision = text_precision->text().toDouble();
    te_variable vars[] = {{"x", &x}};
    expression = new char[text_equation->text().length()+1];
    upper_exp = new char[text_upper->text().length()+1];
    lower_exp = new char[text_lower->text().length()+1];
    strcpy(expression, text_equation->text().toStdString().c_str());
    strcpy(upper_exp, text_upper->text().toStdString().c_str());
    strcpy(lower_exp, text_lower->text().toStdString().c_str());
    te_expr *expr = te_compile(expression, vars, 1, &err);
    upper = te_interp(upper_exp, 0);
    lower = te_interp(lower_exp, 0);
    if (upper < lower)
        swap(upper,lower);
    if (expr)
    {
        do{
            pr_sq = sq;
            sq = 0;
            step = (upper-lower)/n;
            for (i = 0; i < n; i++)
            {
                x = lower + step * (i + 0.5);
                sq += te_eval(expr);
            }
            sq *= step;
            n *=2;
        }
        while(fabs(sq-pr_sq)>precision);
        text_answer->setText(QString::number(sq, 'f', 8));
        te_free(expr);
        delete[] expression;
    }
    else
        cout << "Parse error at " << err << endl;
}

void IntegralWindow::trapezium()
{
    double x, y, upper, lower, precision, step, pr_sq, sq = 0;
    int i, err,
            n = 10;
    char *expression, *upper_exp, *lower_exp;
    precision = text_precision->text().toDouble();
    te_variable vars[] = {{"x", &x}};
    expression = new char[text_equation->text().length()+1];
    upper_exp = new char[text_upper->text().length()+1];
    lower_exp = new char[text_lower->text().length()+1];
    strcpy(expression, text_equation->text().toStdString().c_str());
    strcpy(upper_exp, text_upper->text().toStdString().c_str());
    strcpy(lower_exp, text_lower->text().toStdString().c_str());
    te_expr *expr = te_compile(expression, vars, 1, &err);
    upper = te_interp(upper_exp, 0);
    lower = te_interp(lower_exp, 0);
    if (upper < lower)
        swap(upper,lower);
    if (expr)
    {
        do{
            pr_sq = sq;
            sq = 0;
            step = (upper-lower)/n;
            x = lower;
            sq += te_eval(expr)/2;
            x = upper;
            sq += te_eval(expr)/2;
            for (i = 1; i < n; i++)
            {
                x = lower + step * i;
                sq += te_eval(expr);
            }
            sq *= step;
            cout << "finish sq= " << sq << endl;
            n *=2;
        }
        while(fabs(sq-pr_sq)>precision);
        text_answer->setText(QString::number(sq, 'f', 8));
        te_free(expr);
        delete[] expression;
        delete[] upper_exp;
        delete[] lower_exp;
    }
    else
        cout << "Parse error at " << err << endl;
}

void IntegralWindow::simpson()
{
    double x, y, upper, lower, precision, step, pr_sq, sq = 0;
    int i, err,
            n = 10;
    char *expression, *upper_exp, *lower_exp;
    precision = text_precision->text().toDouble();
    te_variable vars[] = {{"x", &x}};
    expression = new char[text_equation->text().length()+1];
    upper_exp = new char[text_upper->text().length()+1];
    lower_exp = new char[text_lower->text().length()+1];
    strcpy(expression, text_equation->text().toStdString().c_str());
    strcpy(upper_exp, text_upper->text().toStdString().c_str());
    strcpy(lower_exp, text_lower->text().toStdString().c_str());
    te_expr *expr = te_compile(expression, vars, 1, &err);
    upper = te_interp(upper_exp, 0);
    lower = te_interp(lower_exp, 0);
    if (upper < lower)
        swap(upper,lower);
    if (expr)
    {
        do{
            pr_sq = sq;
            sq = 0;
            step = (upper-lower)/n;
            for (i = 1; i < n-1; i++)
            {
                x = lower + step * i;
                sq+=4*te_eval(expr);
                i++;
                x = lower + step * i;
                sq+=2*te_eval(expr);
            }
            x = lower;
            sq += te_eval(expr);
            x = upper;
            sq += te_eval(expr);
            sq = sq*(step/3);
            //cout << "finish sq= " << sq << endl;
            n *=2;
        }
        while((fabs(sq-pr_sq))>precision);
        text_answer->setText(QString::number(sq, 'f', 8));
        te_free(expr);
        delete[] expression;
        delete[] upper_exp;
        delete[] lower_exp;
    }
    else
        cout << "Parse error at " << err << endl;
}

InterpolateWindow::InterpolateWindow(Window *parent) //Задается начальный вид нашего окна
{
    this->setWindowTitle("Интерполяция функций");
    win = parent;
    layout = new QGridLayout;
    chart = new QChart();
    chartView = new QChartView(chart);
    text_equation = new QLineEdit();
    text_upper = new QLineEdit();
    text_lower = new QLineEdit();
    text_coordinate = new QLineEdit();
    text_iterations = new QLineEdit();
    text_answer = new QLineEdit();
    text_upper->setMaximumWidth(80);
    text_lower->setMaximumWidth(80);
    text_equation->setMinimumWidth(200);
    text_iterations->setMaximumWidth(80);
    text_coordinate->setMaximumWidth(70);
    text_answer->setMaximumWidth(70);
    text_answer->setReadOnly(true);
    label_welcoming = new QLabel("Введите исходные данные для интерполяции функции и выберите метод");
    label_equation = new QLabel("Введите уравнение:");
    label_lagrange = new QLabel("Полином Лагранжа");
    label_newtone = new QLabel("Полином Ньютона");
    label_spline = new QLabel("Кубические сплайны");
    label_douglas = new QLabel("Дугласа-Пекера");
    label_upper = new QLabel("Верхний предел:");
    label_lower = new QLabel("Нижний предел:");
    label_iterations = new QLabel("Количество итераций:");
    label_coordinate = new QLabel("Введите координату x, по которой интерполируется f(x):");
    label_answer = new QLabel("Ответ:");
    label_error_parsing = new QLabel("Ошибка парсинга выражения!");
    button_lagrange = new QPushButton("Применить");
    button_newtone = new QPushButton("Применить");
    button_spline = new QPushButton("Применить");
    button_douglas = new QPushButton("Применить");
    button_perezagruzka = new QPushButton("Сброс матрицы");
    button_back = new QPushButton("Назад");
    button_coordinate_lagr = new QPushButton("Рассчёт");
    button_coordinate_newt = new QPushButton("Рассчёт");
    button_coordinate_spln = new QPushButton("Рассчёт");
    label_lagrange -> setWordWrap(true);
    label_newtone -> setWordWrap(true);
    label_spline -> setWordWrap(true);
    label_welcoming -> setWordWrap(true);
    label_coordinate -> setWordWrap(true);
    label_welcoming ->setStyleSheet("font: bold 14px; color:rgba(255,200,0,255)");
    label_lagrange ->setStyleSheet("font: bold 11px; color: white");
    label_newtone  ->setStyleSheet("font: bold 11px; color: white");
    label_spline ->setStyleSheet("font: bold 11px; color: white");
    label_douglas ->setStyleSheet("font: bold 11px; color: white");
    label_equation ->setStyleSheet("font: bold 12px; color: yellow");
    label_upper ->setStyleSheet("font: bold 12px; color: yellow");
    label_lower ->setStyleSheet("font: bold 12px; color: yellow");
    label_iterations ->setStyleSheet("font: bold 12px; color: yellow");
    label_coordinate ->setStyleSheet("font: bold 12px; color: yellow");
    label_answer->setStyleSheet("font: bold 12px; color: yellow");
    label_error_parsing ->setStyleSheet("font: bold 11px; color: red");
    label_error_parsing->setVisible(false);
    button_lagrange->setMaximumWidth(60);
    button_newtone ->setMaximumWidth(60);
    button_spline -> setMaximumWidth(60);
    button_douglas -> setMaximumWidth(60);
    button_coordinate_lagr->setMaximumWidth(60);
    button_coordinate_newt->setMaximumWidth(60);
    button_coordinate_spln->setMaximumWidth(60);
    button_lagrange->setStyleSheet("background-color: rgba(200,100,50,255); "
                                    "border-style:outset;border-width: 1px;border-color: "
                                    "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_newtone ->setStyleSheet("background-color: rgba(160,100,50,255); "
                                     "border-style:outset;border-width: 1px;border-color: "
                                     "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_spline ->setStyleSheet("background-color: rgba(120,100,50,255); "
                                   "border-style:outset;border-width: 1px;border-color: "
                                   "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_douglas ->setStyleSheet("background-color: rgba(120,100,50,255); "
                                  "border-style:outset;border-width: 1px;border-color: "
                                  "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_perezagruzka->setStyleSheet("background-color: rgba(200,255,0,255);; "
                                       "border-style:outset;border-width: 1px;border-color: "
                                       "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_back->setStyleSheet("background-color: rgba(200,255,0,255);; "
                               "border-style:outset;border-width: 1px;border-color: "
                               "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;");
    button_coordinate_lagr ->setStyleSheet("background-color: rgba(255,0,160,80); "
                                  "border-style:outset;border-width: 1px;border-color: "
                                  "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_coordinate_newt ->setStyleSheet("background-color: rgba(255,0,160,80); "
                                      "border-style:outset;border-width: 1px;border-color: "
                                      "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    button_coordinate_lagr ->setStyleSheet("background-color: rgba(255,0,160,80); "
                                      "border-style:outset;border-width: 1px;border-color: "
                                      "red;font: 11px;min-width: 8em;padding: 6px;border-radius: 10px;color: white");
    layout->addWidget(label_welcoming, 0, 0, 1, 2);
    layout->addWidget(label_equation, 1, 0);
    layout->addWidget(text_equation, 1, 1);
    layout->addWidget(label_lower, 2, 0);
    layout->addWidget(label_upper, 2, 1);
    layout->addWidget(text_lower, 3, 0);
    layout->addWidget(text_upper, 3, 1);
    layout->addWidget(label_iterations, 4, 0);
    layout->addWidget(text_iterations, 4, 1);
    layout->addWidget(label_lagrange, 5, 0);
    layout->addWidget(button_lagrange, 6, 0);
    layout->addWidget(label_newtone, 5, 1);
    layout->addWidget(button_newtone, 6, 1);
    layout->addWidget(label_spline, 7, 0);
    layout->addWidget(button_spline, 8, 0);
    layout->addWidget(label_douglas, 7, 1);
    layout->addWidget(button_douglas, 8, 1);
    layout->addWidget(button_back, 13, 0);
    connect(button_coordinate_lagr, SIGNAL (clicked()), this, SLOT (calc_coord_lagr()));
    connect(button_coordinate_newt, SIGNAL (clicked()), this, SLOT (calc_coord_newt()));
    connect(button_coordinate_lagr, SIGNAL (clicked()), this, SLOT (calc_coord_spln()));
    connect(button_lagrange, SIGNAL (clicked()), this, SLOT (interpolate_lagrange()));
    connect(button_newtone, SIGNAL (clicked()), this, SLOT (interpolate_newtone()));
    connect(button_spline, SIGNAL (clicked()), this, SLOT (interpolate_spline()));
    connect(button_douglas, SIGNAL (clicked()), this, SLOT (interpolate_douglas_peucker()));
    connect(button_coordinate_lagr, SIGNAL (clicked()), this, SLOT (calc_coord_lagr()));
    connect(button_coordinate_newt, SIGNAL (clicked()), this, SLOT (calc_coord_newt()));
    connect(button_coordinate_spln, SIGNAL (clicked()), this, SLOT (calc_coord_spln()));
    connect(button_back, SIGNAL (clicked()), this, SLOT (closing()));
    this->setLayout(layout);
    //на задний фон помещаем картинку
    QPixmap bkgnd(R"(C:\Users\Mitty Vasilmann\Desktop\UNIVERSITY\math_helper\1.jpg)");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void InterpolateWindow::interpolate_lagrange()
{
    label_error_parsing->setVisible(false);
    QScatterSeries *seriesPoints = new QScatterSeries();
    QSplineSeries *seriesFunc = new QSplineSeries();
    double x, y, upper, lower, step;
    int i, err,
            n;
    char *expression, *upper_exp, *lower_exp;
    vect.clear();
    te_variable vars[] = {{"x", &x}};
    expression = new char[text_equation->text().length()+1];
    upper_exp = new char[text_upper->text().length()+1];
    lower_exp = new char[text_lower->text().length()+1];
    strcpy(expression, text_equation->text().toStdString().c_str());
    strcpy(upper_exp, text_upper->text().toStdString().c_str());
    strcpy(lower_exp, text_lower->text().toStdString().c_str());
    te_expr *expr = te_compile(expression, vars, 1, &err);
    upper = te_interp(upper_exp, 0);
    lower = te_interp(lower_exp, 0);
    n = text_iterations->text().toInt();
    if (upper < lower)
        swap(upper,lower);
    if (expr)
    {
        step = (upper-lower)/n;
        for (i = 0; i<=n; i++)
        {
            x = lower+i*step;
            y = te_eval(expr);
            vect.push_back(make_pair(x,y));
            seriesFunc->append(x, y);
        }
        for (i = 0; i<=n; i++)
        {
            x = lower + i*step;
            y = lagrange(x, vect, vect.size());
            seriesPoints->append(x, y);
        }
        draw(seriesPoints, seriesFunc);
        layout->addWidget(button_coordinate_lagr, 10, 1);
    }
    else
    {
        label_error_parsing->setVisible(true);
        layout->addWidget(label_error_parsing, 9, 0, 2, 1, Qt::AlignTop);
    }
}

double InterpolateWindow::lagrange(double x, QVector<pair<double,double>> vect, int size)
{
    double lagrangePol = 0, basicsPol = 0;
    for (int i = 0; i < size; i++)
    {
        basicsPol = 1;
        for (int j = 0; j < size; j++)
        {
            if (i != j)
            {
                basicsPol *= (x - vect[j].first) / (vect[i].first - vect[j].first);
            }
        }
        lagrangePol += basicsPol * vect[i].second;
    }
    return lagrangePol;
}

void InterpolateWindow::calc_coord_lagr()
{
    text_answer->setText(
            QString::number(lagrange(text_coordinate->text().toDouble(), vect, vect.size()), 'f', 2));
}

void InterpolateWindow::calc_coord_newt()
{
    text_answer->setText(
            QString::number(newtone(text_coordinate->text().toDouble(), vect, vect.size()), 'f', 2));
}

void InterpolateWindow::calc_coord_spln()
{
    text_answer->setText(
            QString::number(spline_evaluate(text_coordinate->text().toDouble()), 'f', 2));
}

void InterpolateWindow::draw(QScatterSeries *seriesPoints, QSplineSeries *seriesFunc)
{
    seriesFunc->setName("Функция");
    seriesPoints->setName("Узлы интерполяции");
    seriesPoints->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    seriesPoints->setMarkerSize(10.0);
    seriesPoints->setColor(QColor(0, 0, 255, 127));
    chart->addSeries(seriesFunc);
    chart->addSeries(seriesPoints);
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    axisX->setTickCount(5);
    axisX->setLabelFormat("%.1f");
    axisY->setTickCount(10);
    axisY->setLabelFormat("%.1f");
    chartView->chart()->addAxis(axisX, Qt::AlignBottom);;
    chartView->chart()->addAxis(axisY, Qt::AlignLeft);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumWidth(600);
    chartView->setMinimumHeight(400);
    seriesPoints->attachAxis(axisX);
    seriesPoints->attachAxis(axisY);
    seriesFunc->attachAxis(axisX);
    seriesFunc->attachAxis(axisY);
    layout->addWidget(chartView, 0, 2, 40, 1);
    layout->addWidget(label_coordinate, 9, 0, 2, 1, Qt::AlignTop);
    layout->addWidget(text_coordinate, 9, 1);
    layout->addWidget(label_answer, 11, 1);
    layout->addWidget(text_answer, 12, 1);
}


void InterpolateWindow::interpolate_newtone()
{
    label_error_parsing->setVisible(false);
    QScatterSeries *seriesPoints = new QScatterSeries();
    QSplineSeries *seriesFunc = new QSplineSeries();
    double x, y, upper, lower, step;
    int i, err,
            n;
    char *expression, *upper_exp, *lower_exp;
    vect.clear();
    te_variable vars[] = {{"x", &x}};
    expression = new char[text_equation->text().length() + 1];
    upper_exp = new char[text_upper->text().length() + 1];
    lower_exp = new char[text_lower->text().length() + 1];
    strcpy(expression, text_equation->text().toStdString().c_str());
    strcpy(upper_exp, text_upper->text().toStdString().c_str());
    strcpy(lower_exp, text_lower->text().toStdString().c_str());
    te_expr *expr = te_compile(expression, vars, 1, &err);
    upper = te_interp(upper_exp, 0);
    lower = te_interp(lower_exp, 0);
    n = text_iterations->text().toInt();
    if (upper < lower)
        swap(upper, lower);
    if (expr)
    {
        step = (upper - lower) / n;
        for (i = 0; i <= n; i++)
        {
            x = lower + i * step;
            y = te_eval(expr);
            vect.push_back(make_pair(x, y));
            seriesFunc->append(x, y);
        }
        for (i = 0; i <= n; i++)
        {
            x = lower + i * step;
            y = newtone(x, vect, vect.size());
            seriesPoints->append(x, y);
        }
        draw(seriesPoints, seriesFunc);
        layout->addWidget(button_coordinate_newt, 10, 1);
    }
    else
    {
        label_error_parsing->setVisible(true);
        layout->addWidget(label_error_parsing, 9, 0, 2, 1, Qt::AlignTop);
    }
}

double InterpolateWindow::newtone(double x, QVector<pair<double,double>> vect, int size)
{
    double sum = vect[0].second;
    for(int i = 1; i < size; ++i)
    {

        double F = 0;
        for(int j = 0; j <= i; ++j)
        {

            double den = 1;
            for(int k = 0; k <= i; ++k)
                if (k != j)
                    den *= (vect[j].first - vect[k].first);
            F += vect[j].second/den;
        }
        for(int k = 0; k < i; ++k)
            F *= (x - vect[k].first);
        sum += F;
    }
    return sum;
}

void InterpolateWindow::interpolate_spline()
{
    label_error_parsing->setVisible(false);
    QScatterSeries *seriesPoints = new QScatterSeries();
    QSplineSeries *seriesFunc = new QSplineSeries();
    double x, y, upper, lower, step;
    int i, err,
            n;
    char *expression, *upper_exp, *lower_exp;
    vect.clear();
    te_variable vars[] = {{"x", &x}};
    expression = new char[text_equation->text().length() + 1];
    upper_exp = new char[text_upper->text().length() + 1];
    lower_exp = new char[text_lower->text().length() + 1];
    strcpy(expression, text_equation->text().toStdString().c_str());
    strcpy(upper_exp, text_upper->text().toStdString().c_str());
    strcpy(lower_exp, text_lower->text().toStdString().c_str());
    te_expr *expr = te_compile(expression, vars, 1, &err);
    upper = te_interp(upper_exp, 0);
    lower = te_interp(lower_exp, 0);
    n = text_iterations->text().toInt();
    if (upper < lower)
        swap(upper, lower);
    if (expr)
    {
        step = (upper - lower) / n;
        for (i = 0; i <= n; i++)
        {
            x = lower + i * step;
            y = te_eval(expr);
            vect.push_back(make_pair(x, y));
            seriesFunc->append(x, y);
        }
        spline_make(vect, vect.size());
        for (i = 0; i <= n; i++)
        {
            x = lower + i * step;
            y = spline_evaluate(x);
            seriesPoints->append(x, y);
        }
        draw(seriesPoints, seriesFunc);
        layout->addWidget(button_coordinate_spln, 10, 1);
    }
    else
    {
        label_error_parsing->setVisible(true);
        layout->addWidget(label_error_parsing, 9, 0, 2, 1, Qt::AlignTop);
    }
}

double InterpolateWindow::spline_make(QVector<pair<double,double>> vect, int size)
{
    splines.resize(size);
    for (int i = 0; i < size; i++) {
        splines[i].x = vect[i].first;  // x = x
        splines[i].a = vect[i].second;  // a = f(x)
    }

    splines[0].c = 0;
    splines[size - 1].c = 0;
    double *alpha = new double[size - 1];
    double *beta = new double[size - 1];
    alpha[0] = 0;
    beta[0] = 0;

    double hi, hi1, A, B, C, F;

    for (int i = 1; i < size - 1; i++)
    {
        hi = vect[i].first - vect[i - 1].first;
        hi1 = vect[i + 1].first - vect[i].first;
        A = hi;
        B = hi1;
        C = 2 * (hi + hi1);
        F = 6 * ((vect[i + 1].first - vect[i].first) / hi1 - (vect[i].first - vect[i - 1].second) / hi);
        alpha[i] = -B / (A * alpha[i - 1] + C);
        beta[i] = (F - A * beta[i - 1]) / (A * alpha[i - 1] + C);
    }

    for (int i = size - 2; i > 0; i--) {
        splines[i].c = alpha[i] * splines[i + 1].c + beta[i];
    }

    for (int i = size - 1; i > 0; i--)
    {
        hi = vect[i].first - vect[i-1].first;
        splines[i].d = (splines[i].c - splines[i - 1].c) / hi;
        splines[i].b = hi * (2.0 * splines[i].c + splines[i - 1].c) / 6.0 + (vect[i].second - vect[i - 1].second) / hi;
    }
    delete[] alpha;
    delete[] beta;
}

double InterpolateWindow::spline_evaluate(double x)
{
    SplineCoefficients s;

    if (x <= splines[0].x)
    { //х ниже
        s = splines[0];
    }
    else if (x >= splines[splines.size() - 1].x)
    {
        s = splines[splines.size() - 1];
    }
    else
        { //x внутри
            int i = 0;
            int j = (splines.size()) - 1;
            while (i + 1 < j)
            {
                int k = i + (j - i) / 2;
                if (x <= splines[k].x)
                {
                    j = k;
                }
                else
                    {
                    i = k;
                }
            }
            s = splines[j];
        }
    double dx = x - s.x;
    return s.a + s.b*dx + s.c*dx*dx/2.0 + s.d*dx*dx*dx/6.0;
}

void InterpolateWindow::closing() //закрытие нового окна после ввода
{
    this->hide();
    win->show();
}

void InterpolateWindow::interpolate_douglas_peucker()
{
    label_error_parsing->setVisible(false);
    QSplineSeries *seriesPoints = new QSplineSeries();
    QSplineSeries *seriesFunc = new QSplineSeries();
    double x, y, upper, lower, step;
    int i, err,
            n;
    char *expression, *upper_exp, *lower_exp;
    vect.clear();
    te_variable vars[] = {{"x", &x}};
    expression = new char[text_equation->text().length() + 1];
    upper_exp = new char[text_upper->text().length() + 1];
    lower_exp = new char[text_lower->text().length() + 1];
    strcpy(expression, text_equation->text().toStdString().c_str());
    strcpy(upper_exp, text_upper->text().toStdString().c_str());
    strcpy(lower_exp, text_lower->text().toStdString().c_str());
    te_expr *expr = te_compile(expression, vars, 1, &err);
    upper = te_interp(upper_exp, 0);
    lower = te_interp(lower_exp, 0);
    n = text_iterations->text().toInt();
    if (upper < lower)
        swap(upper, lower);
    if (expr)
    {
        step = (upper - lower) / n;
        for (i = 0; i <= n; i++)
        {
            x = lower + i * step;
            y = te_eval(expr);
            pointList.push_back(make_pair(x, y));
            seriesFunc->append(x, y);
        }
        douglas_peucker(pointList, 1.0, pointListOut);
        for (i = 0; i < pointListOut.size(); i++)
        {
            seriesPoints->append(pointListOut[i].first, pointListOut[i].second);
        }
        seriesFunc->setName("Оригинальная функция");
        seriesPoints->setName("Минимизация точек");
        chart->addSeries(seriesFunc);
        chart->addSeries(seriesPoints);
        QValueAxis *axisX = new QValueAxis;
        QValueAxis *axisY = new QValueAxis;
        axisX->setTickCount(5);
        axisX->setLabelFormat("%.1f");
        axisY->setTickCount(10);
        axisY->setLabelFormat("%.1f");
        chartView->chart()->addAxis(axisX, Qt::AlignBottom);;
        chartView->chart()->addAxis(axisY, Qt::AlignLeft);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumWidth(600);
        chartView->setMinimumHeight(400);
        seriesPoints->attachAxis(axisX);
        seriesPoints->attachAxis(axisY);
        seriesFunc->attachAxis(axisX);
        seriesFunc->attachAxis(axisY);
        layout->addWidget(chartView, 0, 2, 40, 1);
    }
    else
    {
        label_error_parsing->setVisible(true);
        layout->addWidget(label_error_parsing, 9, 0, 2, 1, Qt::AlignTop);
    }
}

void InterpolateWindow::douglas_peucker(const vector<pair<double,double>>& pointList, double epsilon, vector<pair<double,double>>& out)
{
    double dmax = 0.0;
    size_t index = 0;
    size_t end = pointList.size() - 1;
    for (size_t i = 1; i < end; i++) {
        double d = calculateDistance(pointList[i], pointList[0], pointList[end]);
        if (d > dmax) {
            index = i; dmax = d;
        }
    }
    if (dmax > epsilon) {
        vector<pair<double,double>> recResults1;
        vector<pair<double,double>> recResults2;
        vector<pair<double,double>> firstLine(pointList.begin(), pointList.begin() + index + 1);
        vector<pair<double,double>> lastLine(pointList.begin() + index, pointList.end());
        douglas_peucker(firstLine, epsilon, recResults1);
        douglas_peucker(lastLine, epsilon, recResults2);
        out.assign(recResults1.begin(), recResults1.end() - 1);
        out.insert(out.end(), recResults2.begin(), recResults2.end());
        if (out.size() < 2)
        {
            label_error_parsing->setText("Проблема с построением списка вывода");
            label_error_parsing->setVisible(true);
            layout->addWidget(label_error_parsing, 9, 0, 2, 1, Qt::AlignTop);
        }
    }
    else {
        out.clear();
        out.push_back(pointList[0]);
        out.push_back(pointList[end]);
    }
}

double InterpolateWindow::calculateDistance(const pair<double,double>& pt, const pair<double,double>& lineStart, const pair<double,double>& lineEnd) {
    double dx = lineEnd.first - lineStart.first;
    double dy = lineEnd.second - lineStart.second;
    double mag = pow(pow(dx, 2.0) + pow(dy, 2.0), 0.5);
    if (mag > 0.0) {
        dx /= mag; dy /= mag;
    }
    double pvx = pt.first - lineStart.first;
    double pvy = pt.second - lineStart.second;
    double pvdot = dx * pvx + dy * pvy;
    double dsx = pvdot * dx;
    double dsy = pvdot * dy;
    double ax = pvx - dsx;
    double ay = pvy - dsy;
    return pow(pow(ax, 2.0) + pow(ay, 2.0), 0.5);
}