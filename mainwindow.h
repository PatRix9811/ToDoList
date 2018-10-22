#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool checkDbExist();

private slots:

private:
    Ui::MainWindow *ui;
    //Database
    QSqlDatabase database;
    QSqlQuery* query;
};
#endif // MAINWINDOW_H
