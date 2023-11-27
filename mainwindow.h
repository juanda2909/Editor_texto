#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool on_actionGuardar_Como_triggered();

    bool on_actionGuardar_triggered();

    void on_actionAbrir_Archivo_triggered();

    void on_actionNuevo_triggered();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    bool savefile();
    bool maybeSave();
    QString curlFile;

};
#endif // MAINWINDOW_H
