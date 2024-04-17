#include "mainwindow.h"
#include "widget.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QLayout>
#include <QColorDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Widget* widget = new Widget(this);
    QLabel* label = new QLabel("Толщина");
    this->widget = widget;
    ui->WidgetLayout->insertWidget(0, widget, 1);
    //ui->config_grid->addWidget(color_dialog, 0, 0);
    QPushButton* btn = new QPushButton("Цвет графика");
    ui->config_grid->addWidget(btn, 0, 1, Qt::AlignVCenter);
    connect(btn, SIGNAL(clicked(bool)), widget, SLOT(set_line_color()));
    label = new QLabel();
    label->setPalette(QPalette(QColor(0, 0, 0)));
    label->setAutoFillBackground(true);
    ui->config_grid->addWidget(label, 0, 0, Qt::AlignVCenter);
    widget->btn_grpah_color = label;
    btn = new QPushButton("Цвет оси");
    ui->config_grid->addWidget(btn, 1, 1, Qt::AlignVCenter);
    connect(btn, SIGNAL(clicked(bool)), widget, SLOT(set_xy_color()));
    label = new QLabel();
    label->setPalette(QPalette(QColor(0, 0, 0)));
    label->setAutoFillBackground(true);
    ui->config_grid->addWidget(label, 1, 0, Qt::AlignVCenter);
    widget->btn_xy_color = label;
    btn = new QPushButton("Цвет подписей");
    ui->config_grid->addWidget(btn, 2, 1, Qt::AlignVCenter);
    connect(btn, SIGNAL(clicked(bool)), widget, SLOT(set_text_xy_color()));
    label = new QLabel();
    label->setPalette(QPalette(QColor(0, 0, 0)));
    label->setAutoFillBackground(true);
    ui->config_grid->addWidget(label, 2, 0, Qt::AlignVCenter);
    widget->btn_xy_numbers_color = label;
    // Толщина
    QSpinBox* spin_box = new QSpinBox();
    widget->size = spin_box;
    spin_box->setValue(widget->get_graph_size());
    label = new QLabel("Толщина");
    ui->config_grid->addWidget(spin_box, 3, 1, Qt::AlignVCenter);
    ui->config_grid->addWidget(label, 3, 0, Qt::AlignVCenter);
    connect(spin_box, SIGNAL(valueChanged(int)), widget, SLOT(set_xy_size(int)));
    // Шаг
    QDoubleSpinBox* double_spin_box = new QDoubleSpinBox();
    widget->step = double_spin_box;
    double_spin_box->setValue(widget->get_point_step());
    double_spin_box->setSingleStep(0.01);
    label = new QLabel("Шаг");
    ui->config_grid->addWidget(double_spin_box, 4, 1, Qt::AlignVCenter);
    ui->config_grid->addWidget(label, 4, 0, Qt::AlignVCenter);
    connect(double_spin_box, SIGNAL(valueChanged(double)), widget, SLOT(set_point_step(double)));
    btn = new QPushButton("Таблица");
    ui->config_grid->addWidget(btn, 5, 1, Qt::AlignVCenter);
    connect(btn, SIGNAL(clicked(bool)), widget, SLOT(show_points_tabel()));
    //layout().addWidget(Q)
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QFont fnt("Arial Black", 14);
    painter.setFont(fnt);
    painter.drawText(45, 45, "График функции: y = x^3 + 12x – 2");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_save_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),
        "untitled.dat",
        tr("(*.dat)")
        );
    qInfo() << file_name;
    if (!file_name.isNull())
    {
        // Создаём объект файла
        QFile file(file_name);
        // Пытаемся открыть файл в необходимом режиме
        if (file.open(QIODevice::WriteOnly))
        {
            QDataStream dataStream(&file);
            dataStream << widget->line_pen <<
                widget->xy_pen <<
                widget->xy_number_pen <<
                widget->point_pen <<
                widget->graph_size <<
                widget->point_step <<
                widget->point_count <<
                widget->btn_grpah_color->palette() <<
                widget->btn_xy_color->palette() <<
                widget->btn_xy_numbers_color->palette();
            file.close();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Ошибка в чтении файла!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}


void MainWindow::on_load_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(
        this,
        tr("Save File"),
        "untitled.dat",
        tr("(*.dat)")
        );
    qInfo() << file_name;
    if (!file_name.isNull())
    {
        // Создаём объект файла
        QFile file(file_name);
        // Пытаемся открыть файл в необходимом режиме
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream dataStream(&file);
            QPalette palet1, palet2, palet3;
            int size;
            double step;
            dataStream >> widget->line_pen >>
                widget->xy_pen >>
                widget->xy_number_pen >>
                widget->point_pen >>
                size >>
                step >>
                widget->point_count >>
                palet1 >>
                palet2 >>
                palet3;
            widget->btn_grpah_color->setPalette(palet1);
            widget->btn_xy_color->setPalette(palet2);
            widget->btn_xy_numbers_color->setPalette(palet3);
            widget->set_xy_size(size);
            widget->set_point_step(step);
            widget->size->setValue(size);
            widget->step->setValue(step);
            file.close();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Ошибка в чтении файла!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}

