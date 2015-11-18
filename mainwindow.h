#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSql>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QVBoxLayout>
#include <QLabel>
#include <QCompleter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Connect_clicked();

    void on_Query_clicked();

    void on_Image_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QLabel*> imgLabelVec;
    void setComplete(MainWindow* window);
    void setImgLabelVec();
};

#endif // MAINWINDOW_H
