#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkProxy>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tasksTableWidget->setColumnWidth(0, 20);
    ui->tasksTableWidget->setColumnWidth(1, 55);
    ui->tasksTableWidget->setColumnWidth(2, 483);
    ui->tasksTableWidget->setColumnWidth(3, 40);

    QObject::connect(&taskRunner, SIGNAL(taskFinished(int)), this, SLOT(onTaskFinished(int)), Qt::DirectConnection);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_enableProxyButton_clicked() {
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(ui->proxyHostLineEdit->text());
    proxy.setPort(ui->proxyPortSpinBox->value());
    proxy.setUser(ui->proxyUserNameLineEdit->text());
    proxy.setPassword(ui->proxyUserPasswordLineEdit->text());

    QNetworkProxy::setApplicationProxy(proxy);

    ui->proxyStatusLabel->setText("Enabled");
}

void MainWindow::on_disableProxyButton_clicked() {
    QNetworkProxy proxy;

    QNetworkProxy::setApplicationProxy(proxy);

    ui->proxyStatusLabel->setText("Disabled");
}

void MainWindow::on_newTaskAddButton_clicked() {
    ui->tasksTableWidget->setRowCount(ui->tasksTableWidget->rowCount() + 1);

    QString url = ui->newTaskUrlLineEdit->text();
    int type = ui->newTaskTypeComboBox->currentText().toInt();
    int taskID = taskRunner.addTask(url, type);

    QTableWidgetItem* idItem = new QTableWidgetItem();
    idItem->setText(QString::number(taskID));
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
}

void MainWindow::on_tasksTableWidget_cellDoubleClicked(int row, int column) {
    int taskID = ui->tasksTableWidget->item(row, 0)->text().toInt();

    if(ui->tasksTableWidget->item(row, 1)->text() == "Started") {
        taskRunner.stopTask(taskID);
        ui->tasksTableWidget->item(row, 1)->setText("Stopped");
    } else {
        taskRunner.startTask(taskID);
        ui->tasksTableWidget->item(row, 1)->setText("Started");
    }
}

void MainWindow::on_startAllTasksButton_clicked() {
    for(int i = 0; i < ui->tasksTableWidget->rowCount(); ++i) {
        int taskID = ui->tasksTableWidget->item(i, 0)->text().toInt();
        taskRunner.startTask(taskID);
        ui->tasksTableWidget->item(i, 1)->setText("Started");
    }
}

void MainWindow::on_stopAllTasksButton_clicked() {
    for(int i = 0; i < ui->tasksTableWidget->rowCount(); ++i) {
        int taskID = ui->tasksTableWidget->item(i, 0)->text().toInt();
        taskRunner.stopTask(taskID);
        ui->tasksTableWidget->item(i, 1)->setText("Stopped");
    }
}

void MainWindow::onTaskFinished(int taskID) {
    for(int i = 0; i < ui->tasksTableWidget->rowCount(); ++i) {
        if(ui->tasksTableWidget->item(i, 0)->text().toInt() == taskID) {
            ui->tasksTableWidget->removeRow(i);
            break;
        }
    }
}
