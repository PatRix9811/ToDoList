#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVector>
#include <QCheckBox>

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
    void addItemToList(QCheckBox* toList);
    //void showItemsList();

private slots:
    void on_pbAdd_clicked();

private:
    Ui::MainWindow *ui;
    //Database parst
    QSqlDatabase database;
    QSqlQuery* query;

    //ListItem vector
    QVector<QCheckBox*> itemsList;
};

#endif // MAINWINDOW_H
