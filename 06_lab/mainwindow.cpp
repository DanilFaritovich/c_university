#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    painter.drawPolyline(QPolygonF{QPointF{30, 30}, QPointF{600-30, 30}, QPointF{600-30, 500-30}, QPointF{30, 500-30}, QPointF{30, 30}});

    QPolygonF list = this->get_coords(-2, 2, 0.1);
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
        qInfo() << x << y;
        qInfo() << (-round(x*100)/100 + 100) * 5 << -y + 100;
        list.push_back(QPointF(((-round(x*100)/100) * 120) + 300, -y * 4 + 250));
    }
    return list;
}

MainWindow::~MainWindow()
{
    delete ui;
}
