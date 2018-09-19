#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "metods.h"



void MainWindow::PrognozExpZglaj(){
     on_Result_triggered();
     double Vol1dAgo,Vol2dAgo,Vol3dAgo,Vol4dAgo,Vol1wAgo,Vol2wAgo,Vol3wAgo,Vol4wAgo,Vol1mAgo,Vol2mAgo,Vol3mAgo,Vol4mAgo;
     QSqlQuery query;
     QString cur1=ui->comboBoxPair1->currentText();
     QString cur2=ui->comboBoxPair2->currentText();
     str=cur1+"/"+cur2;
     double koef;
     QString k=ui->comboBoxKRyad->currentText();
     koef=k.toDouble();
     qDebug()<<str;
     query.exec("SELECT Vol1dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
     while(query.next()) {
     QString x = query.value(0).toString();
     Vol1dAgo=x.toDouble();
     }
     query.exec("SELECT Vol2dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
     while(query.next()) {
     QString y = query.value(0).toString();
     Vol2dAgo=y.toDouble();
     }
     query.exec("SELECT Vol3dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
     while(query.next()) {
     QString y = query.value(0).toString();
     Vol3dAgo=y.toDouble();
     }
     query.exec("SELECT Vol4dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
     while(query.next()) {
     QString y = query.value(0).toString();
     Vol4dAgo=y.toDouble();
     }
    Prod4d=Vol4dAgo;
    Prod3d=koef*Vol4dAgo+(1-koef)*Prod4d;
    Prod2d=koef*Vol3dAgo+(1-koef)*Prod3d;
    Prod1d=koef*Vol2dAgo+(1-koef)*Prod2d;
    NewProgD=koef*Vol1dAgo+(1-koef)*Prod1d;
    ui->labelProgD->setText(QString::number(NewProgD, 'f',1));
    //graphDrawD();

    //////////////////////////////////////////Прогноз первым методом на 1 неделю
    query.exec("SELECT Vol1wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1wAgo=x.toDouble();
    }
    query.exec("SELECT Vol2wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2wAgo=y.toDouble();
    }
    query.exec("SELECT Vol3wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3wAgo=y.toDouble();
    }
    query.exec("SELECT Vol4wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4wAgo=y.toDouble();
    }
    Prod4w=Vol4wAgo;
    Prod3w=koef*Vol4wAgo+(1-koef)*Prod4w;
    Prod2w=koef*Vol3wAgo+(1-koef)*Prod3w;
    Prod1w=koef*Vol2wAgo+(1-koef)*Prod2w;
    NewProgW=koef*Vol1wAgo+(1-koef)*Prod1w;
    ui->labelProgW->setText(QString::number(NewProgW, 'f',1));
   // graphDrawW();

    //////////////////////////////////////////Прогноз первым методом на 1 месяц
    query.exec("SELECT Vol1mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1mAgo=x.toDouble();
    }
    query.exec("SELECT Vol2mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2mAgo=y.toDouble();
    }
    query.exec("SELECT Vol3mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3mAgo=y.toDouble();
    }
    query.exec("SELECT Vol4mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4mAgo=y.toDouble();
    }
    Prod4m=Vol4mAgo;
    Prod3m=koef*Vol4mAgo+(1-koef)*Prod4m;
    Prod2m=koef*Vol3mAgo+(1-koef)*Prod3m;
    Prod1m=koef*Vol2mAgo+(1-koef)*Prod2m;
    NewProgM=koef*Vol1mAgo+(1-koef)*Prod1m;
    ui->labelProgM->setText(QString::number(NewProgM, 'f',1));
    //graphDrawM();
    textVivod();
    textRecommend();
}

void MainWindow::HoltMethod(){
    on_Result_triggered();
    QString cur1=ui->comboBoxPair1->currentText();
    QString cur2=ui->comboBoxPair2->currentText();
    str=cur1+"/"+cur2;
    qDebug()<<str;
    double Vol1dAgo, Vol2dAgo, Vol3dAgo, Vol4dAgo,Vol1wAgo,Vol2wAgo,Vol3wAgo,Vol4wAgo,Vol1mAgo,Vol2mAgo,Vol3mAgo,Vol4mAgo, koef,tr;
    QString k=ui->comboBoxKRyad->currentText();
    QString t=ui->comboBoxKTr->currentText();
    koef=k.toDouble();
    tr=t.toDouble();
    //////////////////////////////////////////Прогноз вторым методом на 1 день
    QSqlQuery query;
    query.exec("SELECT Vol1dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1dAgo=x.toDouble();
    }
    query.exec("SELECT Vol2dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2dAgo=y.toDouble();
    }
    query.exec("SELECT Vol3dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3dAgo=y.toDouble();
    }
    query.exec("SELECT Vol4dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4dAgo=y.toDouble();
    }
    double Ryad4d,Ryad3d,Ryad2d,Ryad1d,Prog4d,Prog3d,Prog2d,Prog1d,Trend4d,Trend3d,Trend2d,Trend1d;
    Prod4d=Vol4dAgo; Ryad4d=Prod4d; Trend4d=0; Prog4d=Vol4dAgo;
    Prod3d=Vol3dAgo;
    Ryad3d=koef*Vol3dAgo+(1-koef)*(Ryad4d-Trend4d);
    Trend3d=tr*(Ryad3d-Ryad4d)+(1-tr)*Trend4d;
    Prog3d=Ryad4d+Trend4d;
    Prod2d=Vol2dAgo;
    Ryad2d=koef*Vol2dAgo+(1-koef)*(Ryad3d-Trend3d);
    Trend2d=tr*(Ryad2d-Ryad3d)+(1-tr)*Trend3d;
    Prog2d=Ryad3d+Trend3d;
    Prod1d=Vol1dAgo;
    Prog1d=Ryad2d+Trend2d;
    Ryad1d=koef*Vol1dAgo+(1-koef)*(Ryad2d-Trend2d);
    Trend1d=tr*(Ryad1d-Ryad2d)+(1-tr)*Trend2d;
    NewProgD=Ryad1d+Trend1d;
    ui->labelProgD->setText(QString::number(NewProgD, 'f',1));
  //  graphDrawD();

    //////////////////////////////////////////Прогноз первым методом на 1 неделю
    query.exec("SELECT Vol1wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1wAgo=x.toDouble();
    }
    query.exec("SELECT Vol2wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2wAgo=y.toDouble();
    }
    query.exec("SELECT Vol3wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3wAgo=y.toDouble();
    }
    query.exec("SELECT Vol4wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4wAgo=y.toDouble();
    }
    double Ryad4w,Ryad3w,Ryad2w,Ryad1w,Prog4w,Prog3w,Prog2w,Prog1w,Trend4w,Trend3w,Trend2w,Trend1w;
    Prod4w=Vol4wAgo; Ryad4w=Prod4w; Trend4w=0; Prog4w=Vol4wAgo;
    Prod3w=Vol3wAgo;
    Ryad3w=koef*Vol3wAgo+(1-koef)*(Ryad4w-Trend4w);
    Trend3w=tr*(Ryad3w-Ryad4w)+(1-tr)*Trend4w;
    Prog3w=Ryad4w+Trend4w;
    Prod2w=Vol2wAgo;
    Ryad2w=koef*Vol2wAgo+(1-koef)*(Ryad3w-Trend3w);
    Trend2w=tr*(Ryad2w-Ryad3w)+(1-tr)*Trend3w;
    Prog2w=Ryad3w+Trend3w;
    Prod1w=Vol1wAgo;
    Prog1w=Ryad2w+Trend2w;
    Ryad1w=koef*Vol1wAgo+(1-koef)*(Ryad2w-Trend2w);
    Trend1w=tr*(Ryad1w-Ryad2w)+(1-tr)*Trend2w;
    NewProgW=Ryad1w+Trend1w;
    ui->labelProgW->setText(QString::number(NewProgW, 'f',1));
  //  graphDrawW();

    //////////////////////////////////////////Прогноз первым методом на 1 месяц
    query.exec("SELECT Vol1mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1mAgo=x.toDouble();
    }
    query.exec("SELECT Vol2mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2mAgo=y.toDouble();
    }
    query.exec("SELECT Vol3mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3mAgo=y.toDouble();
    }
    query.exec("SELECT Vol4mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4mAgo=y.toDouble();
    }
    double Ryad4m,Ryad3m,Ryad2m,Ryad1m,Prog4m,Prog3m,Prog2m,Prog1m,Trend4m,Trend3m,Trend2m,Trend1m;
    Prod4m=Vol4mAgo; Ryad4m=Prod4m; Trend4m=0; Prog4m=Vol4mAgo;
    Prod3m=Vol3mAgo;
    Ryad3m=koef*Vol3mAgo+(1-koef)*(Ryad4m-Trend4m);
    Trend3m=tr*(Ryad3m-Ryad4m)+(1-tr)*Trend4m;
    Prog3m=Ryad4m+Trend4m;
    Prod2m=Vol2mAgo;
    Ryad2m=koef*Vol2mAgo+(1-koef)*(Ryad3m-Trend3m);
    Trend2m=tr*(Ryad2m-Ryad3m)+(1-tr)*Trend3m;
    Prog2m=Ryad3m+Trend3m;
    Prod1m=Vol1mAgo;
    Prog1m=Ryad2m+Trend2m;
    Ryad1m=koef*Vol1mAgo+(1-koef)*(Ryad2m-Trend2m);
    Trend1m=tr*(Ryad1m-Ryad2m)+(1-tr)*Trend2m;
    NewProgM=Ryad1m+Trend1m;
    ui->labelProgM->setText(QString::number(NewProgM,'f',1));
  //  graphDrawM();
    textVivod();
    textRecommend();
}


void MainWindow::LinearTrendMethod()
{
    on_Result_triggered();
    QString cur1=ui->comboBoxPair1->currentText();
    QString cur2=ui->comboBoxPair2->currentText();
    str=cur1+"/"+cur2;
    qDebug()<<str;
    double Vol1dAgo, Vol2dAgo, Vol3dAgo, Vol4dAgo,Vol1wAgo,Vol2wAgo,Vol3wAgo,Vol4wAgo,Vol1mAgo,Vol2mAgo,Vol3mAgo,Vol4mAgo;

    //////////////////////////////////////////Прогноз 3 методом на 1 день

    QSqlQuery query;
    query.exec("SELECT Vol1dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1dAgo=x.toDouble();
    }
    query.exec("SELECT Vol2dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2dAgo=y.toDouble();
    }
    query.exec("SELECT Vol3dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3dAgo=y.toDouble();
    }
    query.exec("SELECT Vol4dAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4dAgo=y.toDouble();
    }
    double sredD,sred2D,qD,wD,bD,eD,rD,aD;
    sredD=Vol1dAgo+Vol2dAgo+Vol3dAgo+Vol4dAgo;
    sred2D=Vol1dAgo+Vol2dAgo*2+Vol3dAgo*3+Vol4dAgo*4;
    qD=sredD*2.5;
    wD=sred2D-qD;
    bD=wD/5;
    eD=sredD*3;
    rD=sred2D-eD;
    aD=rD/-2;
    NewProgD=bD*1+aD;
    ui->labelProgD->setText(QString::number(NewProgD, 'f',1));
   // graphDrawD();

    //////////////////////////////////////////Прогноз 3 методом на 1 неделю
    query.exec("SELECT Vol1wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1wAgo=x.toDouble();
    }
    query.exec("SELECT Vol2wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2wAgo=y.toDouble();
    }
    query.exec("SELECT Vol3wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3wAgo=y.toDouble();
    }
    query.exec("SELECT Vol4wAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4wAgo=y.toDouble();
    }
    double sredW,sred2W,qW,wW,bW,eW,rW,aW;
    sredW=Vol1wAgo+Vol2wAgo+Vol3wAgo+Vol4wAgo;
    sred2W=Vol1wAgo+Vol2wAgo*2+Vol3wAgo*3+Vol4wAgo*4;
    qW=sredW*2.5;
    wW=sred2W-qW;
    bW=wW/5;
    eW=sredW*3;
    rW=sred2W-eW;
    aW=rW/-2;
    NewProgW=bW*1+aW;
    ui->labelProgW->setText(QString::number(NewProgW, 'f',1));
  //  graphDrawW();

    //////////////////////////////////////////Прогноз 3 методом на 1 месяц

    query.exec("SELECT Vol1mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1mAgo=x.toDouble();
    }
    query.exec("SELECT Vol2mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2mAgo=y.toDouble();
    }
    query.exec("SELECT Vol3mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3mAgo=y.toDouble();
    }
    query.exec("SELECT Vol4mAgo FROM "+stockFlag+" WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4mAgo=y.toDouble();
    }
    double sredM,sred2M,qM,wM,bM,eM,rM,aM;
    sredM=Vol4mAgo+Vol3mAgo+Vol2mAgo+Vol1mAgo;
    sred2M=Vol1mAgo+Vol2mAgo*2+Vol3mAgo*3+Vol4mAgo*4;
    qM=sredM*2.5;
    wM=sred2M-qM;
    bM=wM/5;
    eM=sredM*3;
    rM=sred2M-eM;
    aM=rM/-2;
    NewProgM=bM*1+aM;
    ui->labelProgM->setText(QString::number(NewProgM,'f',1));
   // graphDrawM();
    textVivod();
    textRecommend();
}
