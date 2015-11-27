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
    setTableView(this);
    imgResultVec = QVector<QString>(10);

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

void MainWindow::setTableView(MainWindow* window){
    tableModel = new QStandardItemModel(10,2,window);
    ui->resultTable->setModel(tableModel);
}


void MainWindow::setComplete(MainWindow* window){
    QStringList wordList;
    wordList << "select" <<"pos_car_degrees_mini";
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
        ui->statusInfoText->setText("Database open error ! ");
    }else{
        std::cout<<" Success "<<std::endl;
        ui->statusInfoText->setText("Connection succeeded! ");
    }
}

void MainWindow::on_Query_clicked()
{
    QSqlQuery query(ui->inQuery->text());
    int row = 0;
    QString nodeLocation = ui->nodeLocation->toPlainText();
    while (query.next()) {
        if(row < 10){
            QModelIndex indexRow = tableModel->index(row, 0,QModelIndex());
            QModelIndex indexCol = tableModel->index(row, 1, QModelIndex());
            tableModel->setData(indexRow, query.value(1));
            tableModel->setData(indexCol, query.value(2));
            imgResultVec[row] = nodeLocation+query.value(2).toString()+query.value(1).toString();
        }
        row += 1;
        std::cout<< qPrintable(query.value(1).toString()+" : "+query.value(2).toString())<<std::endl;
    }

    displayResult();


}

void MainWindow::displayResult()
{
    QImage imgResult_1;
    QImage imgResult_2;
    QImage imgResult_3;
    QImage imgResult_4;
    QImage imgResult_5;
    QImage imgResult_6;

    imgResult_1.load(imgResultVec[0]);
    imgResult_2.load(imgResultVec[1]);
    imgResult_3.load(imgResultVec[2]);
    imgResult_4.load(imgResultVec[3]);
    imgResult_5.load(imgResultVec[4]);
    imgResult_6.load(imgResultVec[5]);


    imgLabelVec[0]->setPixmap(QPixmap::fromImage(imgResult_1));
    imgLabelVec[1]->setPixmap(QPixmap::fromImage(imgResult_2));
    imgLabelVec[2]->setPixmap(QPixmap::fromImage(imgResult_3));
    imgLabelVec[3]->setPixmap(QPixmap::fromImage(imgResult_4));
    imgLabelVec[4]->setPixmap(QPixmap::fromImage(imgResult_5));
    imgLabelVec[5]->setPixmap(QPixmap::fromImage(imgResult_6));

    for(int i = 1; i < imgLabelVec.size() ; ++i){
     //   imgLabelVec[i]->setPixmap(QPixmap::fromImage(myImage));
        imgLabelVec[i]->show();
    }

    //std::cout<<qPrintable(nodeLocation);

}



void MainWindow::on_Image_clicked()
{
    QImage myImage;
    myImage.load("/Users/jeffwang/Desktop/002.png");
    QImage imageTest;

    imgResultVec[0]="/Users/jeffwang/Developer/Cardatabase/mini_pos/degree_0/pos_degree_000_010.png";
    imageTest.load(imgResultVec[0]);
    imgLabelVec[0]->setPixmap(QPixmap::fromImage(imageTest));
    imgLabelVec[0]->show();
     //QLabel imgTest;
    for(int i = 1; i < imgLabelVec.size() ; ++i){
        imgLabelVec[i]->setPixmap(QPixmap::fromImage(myImage));
        imgLabelVec[i]->show();
    }

    //imgTest.setPixmap(QPixmap::fromImage(myImage));
}
