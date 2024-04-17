#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVariantAnimation>
#include "math.h"

double start_coord{-2}, end_coord{2};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVariantAnimation* animation = new QVariantAnimation(this);
    // Задаём начальное значение
    animation->setStartValue(-150);
    // Задаём конечное значение
    animation->setEndValue(200);
    // Задаём продолжительность анимации в миллисекундах
    animation->setDuration(3000);
    connect(animation, &QVariantAnimation::valueChanged, [this](QVariant value)
    {
        double v = value.toDouble() / 10000;
        start_coord -= v;
        end_coord -= v;
        update();
    });
    animation->start();
}

void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen line_pen(QColor(0, 0, 0), 4);
    QPen point_pen(QColor(200, 0, 0), 5);
    QFont fnt("Arial Black", 14);
    painter.setFont(fnt);
    painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignTop, "График функции: y = x^3 + 12x – 2");

    // Нарисуем координатную
    painter.drawLine(30, 250, 600 - 30, 250); // горизонтальная
    painter.drawLine(300, 30, 300, 500 - 30); // Вертикальная
    QPolygonF pol{QPointF{30, 30}, QPointF{600-30, 30}, QPointF{600-30, 500-30}, QPointF{30, 500-30}, QPointF{30, 30}};
    painter.drawPolyline(pol);

    QPolygonF list = this->get_coords(start_coord, end_coord, 0.1);
    painter.setPen(line_pen);
    painter.drawPolyline(list.data(), static_cast<int>(list.size()));
    painter.setPen(point_pen);
    for (auto point : list){
        painter.drawEllipse(point, 2.3, 2.3);
    }
    //painter.drawPoints(list);
}

QPolygonF MainWindow::get_coords(double start, double end, double step)
{
    float y;
    QPolygonF list {};
    for (double x = start;x <= end; x += step)
    {
        y = pow(x, 3) + 12 * x - 2;
        list.push_back(QPointF(((-round(x*100)/100) * 100) + 300, -y * 4 + 250));
    }
    return list;
}

MainWindow::~MainWindow()
{
    delete ui;
}
