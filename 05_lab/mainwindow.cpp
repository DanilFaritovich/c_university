#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_le_input_clicked()
{
    QLayoutItem* item;
    QLayoutItem* item_00;
    while ( ( item = this->ui->VL_update->takeAt( 0 ) ) != NULL )
    {
        while ( ( item_00 = item->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item_00->widget();
            delete item_00;
        }
        delete item->widget();
        delete item;
    }
    int column_count = this->ui->le_input->text().toInt();
    for (int i = 1;i <= column_count;i++)
    {
        QHBoxLayout* layout = new QHBoxLayout();
        QLineEdit* line_edit = new QLineEdit(QString::number(i), this);
        QLabel* label = new QLabel(QString::number(i), this);
        label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        label->setAlignment(Qt::AlignCenter);
        QLineEdit::connect(line_edit, SIGNAL(textChanged(QString)), label, SLOT(setText(QString))
        );
        layout->addWidget(line_edit);
        layout->addWidget(label);
        this->ui->VL_update->addLayout(layout);
    }
}
