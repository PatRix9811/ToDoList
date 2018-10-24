#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
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
    void loadItemsFromDatabase();
    void connecDatabase();

private slots:
    void on_pbAdd_clicked();
    void delItem();

private:
    Ui::MainWindow *ui;
    //Database parst
    QSqlDatabase database;
    QSqlQuery* query;

    //ListItem vector
    QList<QCheckBox*> itemsList;
};

#endif // MAINWINDOW_H
