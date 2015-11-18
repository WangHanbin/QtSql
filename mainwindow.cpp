#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setImgLabelVec();
    setComplete(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImgLabelVec(){
    imgLabelVec.append(ui->imgDisplay_1);
    imgLabelVec.append(ui->imgDisplay_2);
    imgLabelVec.append(ui->imgDisplay_3);
    imgLabelVec.append(ui->imgDisplay_4);
    imgLabelVec.append(ui->imgDisplay_5);
    imgLabelVec.append(ui->imgDisplay_6);

}

void MainWindow::setComplete(MainWindow* window){
    QStringList wordList;
    wordList << "select" <<"qtdemo";
    QCompleter *completer = new QCompleter(wordList, window);
    ui->inQuery->setCompleter(completer);
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
        ui->imgInfoText->setText("Database open error ! ");
    }else{
        std::cout<<" Success "<<std::endl;
        ui->imgInfoText->setText("Success! Enjoy it");
    }
}

void MainWindow::on_Query_clicked()
{
    QSqlQuery query(ui->inQuery->text());
    //QString queryInput = ;
    //query.exec(queryInput);
   // QSqlRecord query_record = query.record();
    //int i;
    //std::cout << query_record.count() <<std::endl;
    //for(i = 0 ;i<query_record.count();i++){
      //  std::cout<< qPrintable(query_record.value(i).toString())<<std::endl;
    //}
    while (query.next()) {
        std::cout<< qPrintable(query.value(0).toString()+" : "+query.value(1).toString())<<std::endl;
    }
//      QSqlTableModel tableModel;
//      tableModel.setTable("qtdemo");
//      tableModel.select();
//      for(int i = 0; i < tableModel.rowCount() ; ++i){
//          QSqlRecord record = tableModel.record(i);
//          QString key = record.value("id").toString();
//          int value = record.value("population").toInt();
//          std::cout<< qPrintable(key) << " : "<< value <<std::endl;
//      }

}



void MainWindow::on_Image_clicked()
{
    QImage myImage;
    myImage.load("/Users/jeffwang/Desktop/002.png");


    //QLabel imgTest;
    for(int i = 0; i < imgLabelVec.size() ; ++i){
        imgLabelVec[i]->setPixmap(QPixmap::fromImage(myImage));
        imgLabelVec[i]->show();
    }

    //imgTest.setPixmap(QPixmap::fromImage(myImage));
}
