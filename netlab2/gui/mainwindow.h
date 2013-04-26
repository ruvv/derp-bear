#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "../http/htmlpagegetter.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_applyProxyButton_clicked();

    void on_taskIDSpinBox_valueChanged();

    void on_toggleTaskStateButton_clicked();

    void on_newTaskAddButton_clicked();

    void onTaskFinished(int taskID);

private:
    Ui::MainWindow* ui;

};

#endif // MAINWINDOW_H
