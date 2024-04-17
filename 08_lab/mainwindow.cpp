#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen line_pen(QColor(0, 0, 0), 4);
    QFont fnt("Arial Black", 14);
    painter.setFont(fnt);
    painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignTop, "Рисовалка");
    painter.setPen(line_pen);
    for (auto pol : this->polygons){
        if (pol.size() != 0){
            painter.drawPolyline(pol);
        }
    }
    //this->painter.drawPolyline(this->polygon);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (this->polygons.size() == 0)
        {
            QPolygonF polygon{};
            polygon.push_back(QPointF(event->x(), event->y()));
            this->polygons.push_back(polygon);
        }
        else
        {
            this->polygons.back().push_back(QPointF(event->x(), event->y()));
        }
    }
    else if (event->buttons() & Qt::RightButton)
    {
        if (this->polygons.size() != 0)
        {
            this->polygons.push_back(QPolygonF{});
        }
    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        this->polygons.clear();
    }
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
