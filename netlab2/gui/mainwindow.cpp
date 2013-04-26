#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkProxy>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setFixedSize(size());

    ui->tasksTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->tasksTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("State"));
    ui->tasksTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Url"));
    ui->tasksTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Type"));

    ui->tasksTableWidget->setColumnWidth(0, 20);
    ui->tasksTableWidget->setColumnWidth(1, 55);
    ui->tasksTableWidget->setColumnWidth(2, 483);
    ui->tasksTableWidget->setColumnWidth(3, 40);

    on_taskIDSpinBox_valueChanged();

    QObject::connect(&taskRunner, SIGNAL(taskFinished(int)), this, SLOT(onTaskFinished(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_applyProxyButton_clicked() {
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(ui->proxyHostLineEdit->text());
    proxy.setPort(ui->proxyPortSpinBox->value());
    proxy.setUser(ui->proxyUserNameLineEdit->text());
    proxy.setPassword(ui->proxyUserPasswordLineEdit->text());

    QNetworkProxy::setApplicationProxy(proxy);
}

void MainWindow::on_newTaskAddButton_clicked() {
    ui->tasksTableWidget->setRowCount(ui->tasksTableWidget->rowCount() + 1);

    QString url = ui->newTaskUrlLineEdit->text();
    int type = ui->newTaskTypeSpinBox->value();
    int id = taskRunner.addTask(url, type);

    QTableWidgetItem* idItem = new QTableWidgetItem();
    idItem->setText(QString::number(id));
    idItem->setTextAlignment(Qt::AlignCenter);
    ui->tasksTableWidget->setItem(ui->tasksTableWidget->rowCount() - 1, 0, idItem);

    QTableWidgetItem* stateItem = new QTableWidgetItem();
    stateItem->setText("Stopped");
    stateItem->setTextAlignment(Qt::AlignCenter);
    ui->tasksTableWidget->setItem(ui->tasksTableWidget->rowCount() - 1, 1, stateItem);

    QTableWidgetItem* urlItem = new QTableWidgetItem();
    urlItem->setText(url);
    urlItem->setTextAlignment(Qt::AlignCenter);
    ui->tasksTableWidget->setItem(ui->tasksTableWidget->rowCount() - 1, 2, urlItem);

    QTableWidgetItem* typeItem = new QTableWidgetItem();
    typeItem->setText(QString::number(type));
    typeItem->setTextAlignment(Qt::AlignCenter);
    ui->tasksTableWidget->setItem(ui->tasksTableWidget->rowCount() - 1, 3, typeItem);

    on_taskIDSpinBox_valueChanged();
}

void MainWindow::on_taskIDSpinBox_valueChanged() {
    int taskID = ui->taskIDSpinBox->value();

    int state = 0;
    int i = 0;
    for(; i < ui->tasksTableWidget->rowCount(); ++i) {
        if(ui->tasksTableWidget->item(i, 0)->text().toInt() == taskID) {
            if(ui->tasksTableWidget->item(i, 1)->text() == "Started") {
                state = 1;
            } else {
                state = 2;
            }
            break;
        }
    }

    if(state == 0) {
        ui->toggleTaskStateButton->setEnabled(false);
        ui->toggleTaskStateButton->setText("");
    } else if(state == 1) {
        ui->toggleTaskStateButton->setEnabled(true);
        ui->toggleTaskStateButton->setText("Stop");
    } else {
        ui->toggleTaskStateButton->setEnabled(true);
        ui->toggleTaskStateButton->setText("Start");
    }
}

void MainWindow::on_toggleTaskStateButton_clicked() {
    int taskID = ui->taskIDSpinBox->value();

    for(int i = 0; i < ui->tasksTableWidget->rowCount(); ++i) {
        if(ui->tasksTableWidget->item(i, 0)->text().toInt() == taskID) {
            if(ui->tasksTableWidget->item(i, 1)->text() == "Started") {
                taskRunner.stopTask(taskID);
                ui->tasksTableWidget->item(i, 1)->setText("Stopped");
            } else {
                taskRunner.startTask(taskID);
                ui->tasksTableWidget->item(i, 1)->setText("Started");
            }
            on_taskIDSpinBox_valueChanged();
            break;
        }
    }
}

void MainWindow::on_startAllTasksButton_clicked() {
    for(int i = 0; i < ui->tasksTableWidget->rowCount(); ++i) {
        taskRunner.startTask(ui->tasksTableWidget->item(i, 0)->text().toInt());
        ui->tasksTableWidget->item(i, 1)->setText("Started");
    }
}

void MainWindow::on_stopAllTasksButton_clicked() {
    for(int i = 0; i < ui->tasksTableWidget->rowCount(); ++i) {
        taskRunner.stopTask(ui->tasksTableWidget->item(i, 0)->text().toInt());
        ui->tasksTableWidget->item(i, 1)->setText("Stopped");
    }
}

void MainWindow::onTaskFinished(int taskID) {
    for(int i = 0; i < ui->tasksTableWidget->rowCount(); ++i) {
        if(ui->tasksTableWidget->item(i, 0)->text().toInt() == taskID) {
            ui->tasksTableWidget->removeRow(i);
            on_taskIDSpinBox_valueChanged();
            break;
        }
    }
}
