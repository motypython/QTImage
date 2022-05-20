#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection); //you can select any number of items
    model = new QStringListModel(this);
    ui->setupUi(this);
    model->setStringList(list);
    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectImpushButton_clicked()
{
    QString filter;
    QString filename = QFileDialog::getOpenFileName(this, "Select an image", "","Images (*.jpg; *.jpeg; *.png; *.bmp)", &filter);
    if(!filename.isEmpty())
    {
        qDebug() << filename;
        qDebug() << filter;
        QPixmap pixmap(filename);
        ui->picturelabel->setPixmap(pixmap.scaled(ui->picturelabel->size(), Qt::KeepAspectRatio));
        ui->picturelabel->setAlignment(Qt::AlignCenter);
        model->insertRow(model->rowCount());
        list.append(filename);
        QModelIndex index = model->index(model->rowCount()-1);
        model->setData(index,filename);
    }
}

void MainWindow::saveToFile(QString file)
{
   const QString path("imagePaths.txt");
   QFile pathFile(path);
   if(pathFile.open(QIODevice::WriteOnly | QIODevice::Append)){
       QTextStream out(&pathFile); out << file+"\n";
   }else
       qDebug() << "Failed to open file";


}

void MainWindow::readFromFile()
{
    QFileInfo inf (pathFile);
    qDebug() << "File path: " << inf.QFileInfo::path() << endl;
    qDebug() << "Current path:" << QDir::currentPath() << endl;

}


void MainWindow::on_pushButton_clicked()
{
    /*foreach(const QModelIndex &index,
            ui->listView->selectionModel()->selectedIndexes())
        saveToFile(model->itemFromIndex(index)->text());
        */ //selected elements can be more than one
    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    saveToFile(itemText);

}

