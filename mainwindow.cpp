#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QMainWindow>
#include <QFontComboBox>
#include <QPlainTextEdit>

//Abre la ventana y configura los widgets

 MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//Destruye la ventana

MainWindow::~MainWindow()
{

 delete ui;

}

//Funciones que se encarga de la funcion de guardar el archivo
bool MainWindow::on_actionGuardar_Como_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Guardar Como",
        QString(),
 "Archivos de texto (*.txt);;Archivos PDF (*.pdf);;Archivos de Word (*.doc)");
 
    if(!fileName.isEmpty()){
        curlFile = fileName;
        return savefile();
    }
    return false;
}

bool MainWindow::savefile(){
    QFile file(curlFile);
    if(file.open(QFile::WriteOnly)){
        file.write(ui->plainTextEdit->toPlainText().toUtf8());
        return true;
    }
    else{
        QMessageBox::warning(
            this,
            "TextEditor", tr("Error en el archivo %1. \nError: %2")
                .arg(curlFile)
                .arg(file.errorString()));
        return false;
    }
}

//Funcion que se encarga de guardar el archivo cuando es modificado

bool MainWindow::maybeSave()
{
    if(ui->plainTextEdit->document()->isModified()){
        QMessageBox::StandardButton ret =
            QMessageBox::warning(this,
                                 "MainWindow",
                                 tr("Documento modificado\n"
                                    "¿Deseas Guardar?"),
                                     QMessageBox:: Yes | QMessageBox:: No | QMessageBox:: Cancel);

        if(ret == QMessageBox::Yes){
            return on_actionGuardar_Como_triggered();
        }
        else if(ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}


bool MainWindow::on_actionGuardar_triggered()
{
    if(curlFile.isEmpty())
        return on_actionGuardar_Como_triggered();
    else
        return savefile();
}

//Funcion que se encarga de abrir un archivo previamente creado

void MainWindow::on_actionAbrir_Archivo_triggered()
{
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(
            this,
            "MainWindow - Abrir Archivo",
            "/home/juanc/Documents",
            "All Files (*.*)*;;PDF Files (*.pdf);;Word Files (*.doc);;Text Files (*.txt)");
        if(!fileName.isEmpty()){
            QFile file(fileName);
            if(file.open(QFile::ReadOnly)){
                ui->plainTextEdit->setPlainText(file.readAll());
                curlFile = fileName;
            } else{
                QMessageBox::warning(
                    this,
                    "MainWindow",
                    tr("Error en el archivo %1. \nError: %2")
                        .arg(fileName)
                        .arg(file.errorString()));
            }
        }
    }
}


//Funcion que se encarga de crear un nuevo archivo

void MainWindow::on_actionNuevo_triggered()
{
    if(maybeSave()){
        ui->plainTextEdit->clear();
    }

}

//Funcion que permite destruir la ventana con el boton "Salir"

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event ->accept();
    }
    else{
        event ->ignore();
    }
}
