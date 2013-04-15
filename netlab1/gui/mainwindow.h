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
    
public slots:
    void htmlGetterFinished(const QString& result);
    void htmlGetterError();

private:
    Ui::MainWindow* ui;
    HtmlPageGetter* htmlGetter;
};

#endif // MAINWINDOW_H
