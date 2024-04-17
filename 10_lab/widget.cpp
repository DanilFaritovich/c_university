#include "widget.h"
#include <QPainter>
#include <QColorDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include "coordworker.h"
#include "pointstable.h"

Widget::Widget(QWidget * parent) : QWidget(parent)
{
    //this->setGeometry(120, 120, 570, 470);
    //qInfo() << this->pos();
    //qInfo() << this->size();
}

void Widget::set_coord_lines(QPainter* painter)
{
    painter->setPen(xy_pen);
    painter->drawLine(0, (qreal)this->height() / 2, (qreal)this->width(), (qreal)this->height() / 2); // горизонтальная
    painter->drawLine((qreal)this->width() / 2, 0, (qreal)this->width() / 2, (qreal)this->height()); // Вертикальная
    painter->setPen(xy_number_pen);
    painter->drawText(QPointF((qreal)this->width() * (static_cast<double>(1)/2 + 0.01), (qreal)this->height() * (static_cast<double>(1)/2 + 0.025)), "0");
    if (point_count % 2 != 0){
        point_count++;
    }
    painter->setPen(xy_pen);
    // Горизонтальная
    for (int i = 1; i <= point_count - 1; i++){
        if (i - point_count / 2 == 0){ continue; }
        painter->setPen(xy_pen);
        painter->drawEllipse(QPointF(((qreal)this->width() / point_count) * i, (qreal)this->height() / 2), 0, 6);
        painter->setPen(xy_number_pen);
        painter->drawText(QPointF(((qreal)this->width() / point_count) * i * 1.01, (qreal)this->height() / 2 * 1.05), QString::number(i - point_count / 2));
    }
    // Вертикальная
    for (int i = 1; i <= point_count - 1; i++){
        if (-(i - point_count / 2) == 0){ continue; }
        //qInfo() << QPointF((qreal)this->width() / 2, ((qreal)this->height() / point_count) * i);
        painter->setPen(xy_pen);
        painter->drawEllipse(QPointF((qreal)this->width() / 2, ((qreal)this->height() / point_count) * i), 6, 0);
        painter->setPen(xy_number_pen);
        painter->drawText(QPointF((qreal)this->width() * (static_cast<double>(1) / 2 + 0.02), (qreal)this->height() * (static_cast<double>(1) / point_count * i + 0.01)), QString::number(-(i - point_count / 2)));
    }
}

void Widget::set_graph(QPainter* painter, float point_step)
{
    QPolygonF list = CoordWorker::get_coords(-2, 2, point_step);
    QPen pen = line_pen;
    pen.setWidth(graph_size);
    painter->setPen(pen);
    for (auto& point : list){
        point = QPointF(((qreal)this->width() / point_count) * point.x() / 120 + (qreal)this->width() / 2, (qreal)this->height() - (((qreal)this->height() / point_count) * point.y() / 10 + (qreal)this->height() / 2));
        qInfo() << point;
    }
    painter->drawPolyline(list.data(), static_cast<int>(list.size()));
    pen = point_pen;
    pen.setWidthF(graph_size / 1.1);
    painter->setPen(pen);
    for (auto point : list){
        painter->drawEllipse(point, graph_size / 2.2, graph_size / 2.2);
    }
    //painter.drawPoints(list);
}

void Widget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(QFont("Arial Black", 8));
    painter.drawPolyline(QPolygonF{QPointF{00, 00}, QPointF{(qreal)this->width(), 0}, QPointF{(qreal)this->width(), (qreal)this->height()}, QPointF{0, (qreal)this->height()}, QPointF{0, 0}});
    // Нарисуем координатную
    this->set_coord_lines(&painter);
    this->set_graph(&painter, point_step);



    /*
    QPolygonF list = CoordWorker::get_coords(-2, 2, point_step);
    painter.setPen(line_pen);
    painter.drawPolyline(list.data(), static_cast<int>(list.size()));
    painter.setPen(point_pen);
    for (auto point : list){
        painter.drawEllipse(point, 2.3, 2.3);
    }
    //painter.drawPoints(list);
    */
}

void Widget::set_line_color()
{
    QColorDialog* color_dialog = new QColorDialog();
    color_dialog->show();
    color_dialog->setCurrentColor(this->line_pen.color());
    if (color_dialog->exec() == QColorDialog::Accepted){
        this->line_pen.setColor(color_dialog->selectedColor());
        this->btn_grpah_color->setPalette(color_dialog->selectedColor());
    }
}

void Widget::set_xy_color()
{
    QColorDialog* color_dialog = new QColorDialog();
    color_dialog->show();
    color_dialog->setCurrentColor(this->xy_pen.color());
    if (color_dialog->exec() == QColorDialog::Accepted){
        this->xy_pen.setColor(color_dialog->selectedColor());
        this->btn_xy_color->setPalette(color_dialog->selectedColor());
    }
}

void Widget::set_text_xy_color()
{
    QColorDialog* color_dialog = new QColorDialog();
    color_dialog->show();
    color_dialog->setCurrentColor(this->xy_number_pen.color());
    if (color_dialog->exec() == QColorDialog::Accepted){
        this->xy_number_pen.setColor(color_dialog->selectedColor());
        this->btn_xy_numbers_color->setPalette(color_dialog->selectedColor());
    }
}

int Widget::get_graph_size()
{
    return this->graph_size;
}

void Widget::set_xy_size(int number)
{
    graph_size = number;
    update();
}

double Widget::get_point_step()
{
    return this->point_step;
}

void Widget::set_point_step(double number)
{
    if (number == 0){
        return;
    }
    point_step = number;
    update();
}

void Widget::show_points_tabel()
{
    PointsTable* form = new PointsTable();
    QPolygonF pol = CoordWorker::get_coords(-2, 2, point_step);
    QStandardItemModel* model = new QStandardItemModel(static_cast<int>(pol.size()), 2);
    model->setHeaderData(0, Qt::Horizontal, "X");
    model->setHeaderData(1, Qt::Horizontal, "Y");
    int column{0};
    qInfo() << pol.size();
    for (auto& point : pol){
        qInfo() << new QStandardItem(point.x());
        model->setItem(column, 0, new QStandardItem(QString::number(point.x() / 120)));
        model->setItem(column, 1, new QStandardItem(QString::number(point.y() / 10)));
        column++;
    }
    form->show();
    form->table->setModel(model);
}

Widget::~Widget()
{
    delete ui;
}
