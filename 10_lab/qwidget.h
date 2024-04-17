#ifndef QWIDGET_H
#define QWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent* event);
    QPolygonF get_coords(double start, double end, double step);

private:
    Ui::MainWindow *ui;
};

#endif // QWIDGET_H
