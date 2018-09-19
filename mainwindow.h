#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSql>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include "QSqlQuery"
#include <QSqlQueryModel>
#include <QFrame>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Tables();
    void PrognozExpZglaj();
    void HoltMethod();
    void LinearTrendMethod();
    void showPointToolTip(QMouseEvent *event);


private slots:
   void on_DtbaseConnect_triggered();
   void on_pushButtonProg_clicked();
   void on_pushButtonSort_clicked();
   void on_pushButtonKurs_clicked();
   void on_Spravka1_triggered();
   void on_Spravka2_triggered();
   void on_pushButtonBitStock_clicked();
   void on_Design_triggered();
   void on_Result_triggered();
   void graphDrawD();
   void graphDrawW();
   void graphDrawM();
   void textRecommend();
   void textVivod();
   void on_pushButtonHitStock_clicked();
   void on_pushButtonHuoStock_clicked();
   void on_pushButtonResult_clicked();
   void on_pushButtonDesign_clicked();
   void on_radioButtonD_clicked();
   void on_radioButtonW_clicked();
   void on_radioButtonM_clicked();
   void on_pushVivod_clicked();
   void on_pushRec_clicked();
   void on_pushHelp_clicked();
   void on_pushHelp2_clicked();
   void on_comboBoxPair1_currentIndexChanged();
   void on_PDFButton_clicked();
   void on_comboBoxMetods_currentIndexChanged();
   void on_pushMetodsHelp_clicked();


private:
    //Ui::MainWindow *ui;
    QSqlDatabase db;
public:
    Ui::MainWindow *ui;
int flag;
QString stockFlag,str,stockName,Recommend,Vivod;
QTime Ti;
QDate Dt;
double Prod4m,Prod3m,Prod2m,Prod1m,Prod4w,Prod3w,Prod2w,Prod1w,Prod4d,Prod3d,Prod2d,Prod1d,NewProgM,NewProgW,NewProgD;
};

#endif // MAINWINDOW_H
