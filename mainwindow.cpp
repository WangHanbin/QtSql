#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connect_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("vehicledb");
    db.setUserName("jeff");
    db.setPassword("ice");
    if(!db.open()){
        qDebug()<<"Database open error ! ";
    }else{
        std::cout<<" Success "<<std::endl;
    }
}

void MainWindow::on_Query_clicked()
{
    //QSqlQuery query;
    //query.exec("select * from qtdemo");
    //QSqlRecord query_record = query.record();
    //int i;
    //for(i = 0 ;i<query_record.count();i++){
      QSqlTableModel tableModel;
      tableModel.setTable("qtdemo");
      tableModel.select();
      for(int i = 0; i < tableModel.rowCount() ; ++i){
          QSqlRecord record = tableModel.record(i);
          QString key = record.value("id").toString();
          int value = record.value("population").toInt();
          std::cout<< qPrintable(key) << " : "<< value <<std::endl;
      }

}
