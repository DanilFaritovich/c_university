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
    QFont fnt("Arial Black", 14);
    painter.setFont(fnt);
    painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignTop, "Рисовалка");
    painter.setPen(this->line_pen);
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
            polygon.push_back(event->position());
            this->polygons.push_back(polygon);
        }
        else
        {
            this->polygons.back().push_back(event->position());
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

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // Узнаём код нажатой кнопки
    switch (event->key())
    {
    // Если это был пробел
    case Qt::Key::Key_1:
        this->line_pen.setColor(QColor(255, 0, 0));
        break;
    // Если это была кнопка B
    case Qt::Key::Key_2:
        this->line_pen.setColor(QColor(0, 255, 0));
        break;
    case Qt::Key::Key_Up:
        this->update_polygons_coords(0, -1);
        break;
    case Qt::Key::Key_Down:
        this->update_polygons_coords(0, 1);
        break;
    case Qt::Key::Key_Left:
        this->update_polygons_coords(-1, 0);
        break;
    case Qt::Key::Key_Right:
        this->update_polygons_coords(1, 0);
        break;
    }
    update();

}

void MainWindow::update_polygons_coords(int x, int y)
{
    for (auto& polygon : this->polygons)
    {
        for (auto& coords : polygon)
        {
            coords.setX(coords.x() + x);
            coords.setY(coords.y() + y);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
