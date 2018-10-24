#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->trayIcon = new QSystemTrayIcon(this);
    this->trayIcon->setIcon(QIcon(":/myappico.png"));
    this->trayIcon->setVisible(true);
    this->trayIcon->showMessage(tr("ToDoNote"),tr("ToDoNote is running"));
    this->connecDatabase();
}

MainWindow::~MainWindow()
{
    delete this->query;
    delete ui;
}

bool MainWindow::checkDbExist()
{
    this->query->prepare("SELECT count(*) AS ToDo FROM ToDoNote");
    if(this->query->exec())
    {
        while(this->query->next())
        {
            QString retVal = this->query->value(this->query->record().indexOf("ToDo")).toString();

            if(retVal!="")return true;
            else return false;
        }
    }
    else return false;

    return false;
}

void MainWindow::addItemToList(QCheckBox* toList)
{
    ui->list->addWidget(toList);
}

void MainWindow::loadItemsFromDatabase()
{
    this->query->prepare("SELECT count(ToDoNote) as HowMuch FROM ToDoNote");
    if(this->query->exec())
    {
        while(this->query->next())
        {
            QString retVal = this->query->value(this->query->record().indexOf("HowMuch")).toString();
            if(retVal == "0") return;

            break;
        }

        this->query->prepare("SELECT * FROM ToDoNote");

        if(this->query->exec())
        {
            while(this->query->next())
            {
                QString retVal = this->query->value(this->query->record().indexOf("ToDoNote")).toString();

                QCheckBox* cb =new QCheckBox(retVal,this);

                connect(cb,SIGNAL(clicked(bool)),cb,SLOT(setHidden(bool)));
                connect(cb,&QCheckBox::clicked,this,&MainWindow::delItem);

                this->itemsList.push_back(cb);
                addItemToList(cb);
            }
        }else
        {
            ui->dbInfo->setText("Filed load records from database");
        }

    }else
    {
        ui->dbInfo->setText("Filed load records from database");
    }
}

void MainWindow::connecDatabase()
{
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
                if(this->query->lastError().text() != "No query Unable to fetch row")
                    ui->dbInfo->setText("Database cannot created");
            }
        }else
        {
            this->loadItemsFromDatabase();
        }
    }
}

void MainWindow::delItem()
{
    for(int item=0;item<this->itemsList.count();item++)
    {
        if(this->itemsList.at(item)->isChecked())
        {
            this->query->prepare("DELETE FROM ToDoNote WHERE ToDoNote LIKE :val");
            this->query->bindValue(":val",this->itemsList.at(item)->text());

            if(this->query->exec())
            {
                this->itemsList.removeOne(this->itemsList.at(item));
                ui->dbInfo->setText("Deleted correctly.");
            }else
            {
                ui->dbInfo->setText("Deleted incorrectly.");
            }

        }
    }
}

void MainWindow::on_pbAdd_clicked()
{
    if(ui->leAddVal->text()=="")return;

    this->query->prepare("INSERT INTO ToDoNote VALUES (:ToDo)");
    this->query->bindValue(":ToDo",ui->leAddVal->text());

    if(this->query->exec())
    {
        QCheckBox* cb =new QCheckBox(ui->leAddVal->text(),this);

        connect(cb,SIGNAL(toggled(bool)),cb,SLOT(setHidden(bool)));
        connect(cb,&QCheckBox::clicked,this,&MainWindow::delItem);

        this->itemsList.push_back(cb);
        this->addItemToList(this->itemsList.last());
        ui->dbInfo->setText(this->itemsList.last()->text()+" was added");
        ui->leAddVal->clear();
    }else
    {
         ui->dbInfo->setText("Record cannot add to database.");
    }
}
