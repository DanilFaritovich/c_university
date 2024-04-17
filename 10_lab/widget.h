#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QFont>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
    void set_coord_lines(QPainter* painter);
    void set_graph(QPainter* painter, float point_step);
    int get_graph_size();
    double get_point_step();

    QPen line_pen{QColor(0, 0, 0), 2};
    QPen xy_pen{QColor(0, 0, 0), 2};
    QPen xy_number_pen{QColor(0, 0, 0), 2};
    QPen point_pen{QColor(200, 0, 0), 2.5};
    int graph_size{3};
    double point_step{0.1};
    int point_count{30};
    QLabel* btn_grpah_color{};
    QLabel* btn_xy_color{};
    QLabel* btn_xy_numbers_color{};
    QSpinBox* size{};
    QDoubleSpinBox* step{};

    ~Widget();

public slots:
    void set_line_color();
    void set_xy_color();
    void set_text_xy_color();
    void set_xy_size(int);
    void set_point_step(double);
    void show_points_tabel();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
