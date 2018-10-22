#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->database = QSqlDatabase::addDatabase("QSQLITE");
    this->query = new QSqlQuery(this->database);
    this->database.setDatabaseName("ToDoNote.db");
    if(!this->database.open())
    {
        ui->dbInfo->setText("Database open filed");
    }else
    {
        if(!this->checkDbExist())
        {
            this->query->prepare("CREATE TABLE ToDoNote (ToDoNote  text)");
            if(this->query->exec())
            {
                ui->dbInfo->setText("Database was created");
            }
            else
            {
                ui->dbInfo->setText("Database cannot created");
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkDbExist()
{
    this->query->prepare("SELECT count(*) AS ToDo FROM ToDoNote");
    //this->query->prepare("INSERT INTO ToDoNote (ToDoNote) VALUES ('Nowa notatka')");
    if(this->query->exec())
    {
        while(this->query->next())
        {
            QString retVal = this->query->value(this->query->record().indexOf("ToDoNote")).toString();

            if(retVal!="")
                return true;


                return false;
        }
    }
    else return false;
}
