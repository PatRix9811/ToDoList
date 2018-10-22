#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

class ListItem : public QLabel
{
public:
    ListItem(QString value,QPushButton* pb);

private:
    QPushButton* delButton;
};

#endif // MAINWINDOW_H
