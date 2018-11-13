#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QCheckBox>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QFile>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class QSystemTrayIcon;

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
    void tray();
    void addToAutostart();
    bool checkAutostart(std::string);

private slots:
    void on_pbAdd_clicked();
    void delItem();

private:
    Ui::MainWindow *ui;
    //Database parst
    QSqlDatabase database;
    QSqlQuery* query;

    //Task List
    QList<QCheckBox*> itemsList;

    //Tray
    QSystemTrayIcon* trayIcon;
    QMenu* trayMenu;
};

#endif // MAINWINDOW_H
