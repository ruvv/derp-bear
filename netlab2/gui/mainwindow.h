#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "../http/htmlpagegetter.h"
#include "../simpletaskrunner.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_enableProxyButton_clicked();

    void on_disableProxyButton_clicked();

    void on_newTaskAddButton_clicked();

    void on_tasksTableWidget_cellDoubleClicked(int row, int column);

    void on_startAllTasksButton_clicked();

    void on_stopAllTasksButton_clicked();

    void onTaskFinished(int taskID);

private:
    Ui::MainWindow* ui;
    SimpleTaskRunner taskRunner;

};

#endif // MAINWINDOW_H
