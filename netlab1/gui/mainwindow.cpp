#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    htmlGetter = new HtmlPageGetter(this);

    QObject::connect(htmlGetter, SIGNAL(finished(QString)), this, SLOT(htmlGetterFinished(QString)));
    QObject::connect(htmlGetter, SIGNAL(error()), this, SLOT(htmlGetterError()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::htmlGetterFinished(const QString& result) {

}

void MainWindow::htmlGetterError() {

}
