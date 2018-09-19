#include "graphics.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::graphDrawD()
{
    QString prognoz=ui->comboBoxMetods->currentText();
    int Index=1;
    QString stockGraph="";
    double Vol1dAgo, Vol2dAgo, Vol3dAgo, Vol4dAgo;
    QSqlQuery query;
    QString cur1=ui->comboBoxPair1->currentText();
    QString cur2=ui->comboBoxPair2->currentText();
    str=cur1+"/"+cur2;
    double koef;
    QString k=ui->comboBoxKRyad->currentText();
    koef=k.toDouble();
    double tr;
    QString t=ui->comboBoxKTr->currentText();
    tr=t.toDouble();
    double GrProd4,GrProd3,GrProd2,GrProd1,GrNewProg;
    while(Index!=4){
    GrProd4=0; GrProd3=0; GrProd2=0; GrProd1=0; GrNewProg=0;

        if(Index==1) stockGraph="volume";
        if(Index==2) stockGraph="volumeHit";
        if(Index==3) stockGraph="volumeHuobi";

        query.exec("SELECT Vol1dAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString x = query.value(0).toString();
        Vol1dAgo=x.toDouble();
        }
        query.exec("SELECT Vol2dAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol2dAgo=y.toDouble();
        }
        query.exec("SELECT Vol3dAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol3dAgo=y.toDouble();
        }
        query.exec("SELECT Vol4dAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol4dAgo=y.toDouble();
        }

        if(prognoz=="Экспоненциальное сглаживание"){
        GrProd4=Vol4dAgo;
        GrProd3=koef*Vol4dAgo+(1-koef)*GrProd4;
        GrProd2=koef*Vol3dAgo+(1-koef)*GrProd3;
        GrProd1=koef*Vol2dAgo+(1-koef)*GrProd2;
        GrNewProg=koef*Vol1dAgo+(1-koef)*GrProd1;
        }
        if(prognoz=="Метод Хольта"){
            double Ryad4,Ryad3,Ryad2,Ryad1,Prog4,Prog3,Prog2,Prog1,Trend4,Trend3,Trend2,Trend1;
            GrProd4=Vol4dAgo; Ryad4=GrProd4; Trend4=0; Prog4=Vol4dAgo;
            GrProd3=Vol3dAgo;
            Ryad3=koef*Vol3dAgo+(1-koef)*(Ryad4-Trend4);
            Trend3=tr*(Ryad3-Ryad4)+(1-tr)*Trend4;
            Prog3=Ryad4+Trend4;
            GrProd2=Vol2dAgo;
            Ryad2=koef*Vol2dAgo+(1-koef)*(Ryad3-Trend3);
            Trend2=tr*(Ryad2-Ryad3)+(1-tr)*Trend3;
            Prog2=Ryad3+Trend3;
            GrProd1=Vol1dAgo;
            Prog1=Ryad2+Trend2;
            Ryad1=koef*Vol1dAgo+(1-koef)*(Ryad2-Trend2);
            Trend1=tr*(Ryad1-Ryad2)+(1-tr)*Trend2;
            GrNewProg=Ryad1+Trend1;
        }
        if(prognoz=="Линейный тренд"){
            double sred,sred2,q,w,b,e,r,a;
            GrProd4=Vol4dAgo; GrProd3=Vol3dAgo; GrProd2=Vol2dAgo; GrProd1=Vol1dAgo;
            sred=Vol1dAgo+Vol2dAgo+Vol3dAgo+Vol4dAgo;
            sred2=Vol1dAgo+Vol2dAgo*2+Vol3dAgo*3+Vol4dAgo*4;
            q=sred*2.5;
            w=sred2-q;
            b=w/5;
            e=sred*3;
            r=sred2-e;
            a=r/-2;
            GrNewProg=b*1+a;
        }

        int N=6;

        if(Index==1){
            QVector<double> x(N), y1(N);
           // QVector<double> ticks;
           // ticks<<1<<2<<3<<4<<5;
            //QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
           // ui->graph1->xAxis->setTicker(ticks);
            x[0] = 0; y1[0] = 0;
            x[1] = 1; y1[1] = GrProd4;
            x[2] = 2; y1[2] = GrProd3;
            x[3] = 3; y1[3] = GrProd2;
            x[4] = 4; y1[4] = GrProd1;
            x[5] = 5; y1[5] = GrNewProg;

            ui->graph1->addGraph();
              ui->graph1->graph()->setName(QString("Bitfinex"));
                ui->graph1->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph1->graph()->setPen(graphPen);
              ui->graph1->graph(0)->setData(x, y1);
              double minY = y1[0], maxY = y1[0];
                  for (int i=1; i<N; i++)
                  {
                      if (y1[i]<minY) minY = y1[i];
                      if (y1[i]>maxY) maxY = y1[i];
                  }

                  ui->graph1->yAxis->setRange(minY, maxY*2);
                  ui->graph1->xAxis->setRange(0, 7);
                  ui->graph1->yAxis->setNumberFormat("eb");

                   ui->graph1->yAxis->setNumberPrecision(2);
                   QCPItemText *textLabel = new QCPItemText(ui->graph1);
                   textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
                   textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
                   textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
                   textLabel->setText("Прогноз");
                   textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
                   ui->graph1->addItem(textLabel);

                   // add the arrow:
                   QCPItemLine *arrow = new QCPItemLine(ui->graph1);
                   arrow->start->setParentAnchor(textLabel->bottom);
                   arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
                   arrow->setHead(QCPLineEnding::esNone);
                   ui->graph1->addItem(arrow);
              ui->graph1->replot();
        }

        if(Index==2){
            QVector<double> x(N), y2(N);
            x[0] = 0; y2[0] = 0;
            x[1] = 1; y2[1] = GrProd4;
            x[2] = 2; y2[2] = GrProd3;
            x[3] = 3; y2[3] = GrProd2;
            x[4] = 4; y2[4] = GrProd1;
            x[5] = 5; y2[5] = GrNewProg;

            ui->graph4->clearGraphs();
            ui->graph4->addGraph();
              ui->graph4->graph()->setName(QString("HitBTC"));
                ui->graph4->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph4->graph()->setPen(graphPen);
              ui->graph4->graph(0)->setData(x, y2);

              ui->graph4->legend->setVisible(true);
                QFont legendFont = font();
                legendFont.setPointSize(10);
                ui->graph4->legend->setFont(legendFont);
                ui->graph4->legend->setSelectedFont(legendFont);
                ui->graph4->legend->setSelectableParts(QCPLegend::spItems);

                ui->graph4->xAxis->setLabel("Периоды");
                ui->graph4->yAxis->setLabel("Продажи");

              double minY = y2[0], maxY = y2[0];
                  for (int i=1; i<N; i++)
                  {
                      if (y2[i]<minY) minY = y2[i];
                      if (y2[i]>maxY) maxY = y2[i];
                  }
                  ui->graph4->yAxis->setRange(minY, maxY*2);
                  ui->graph4->xAxis->setRange(0, 7);

                  ui->graph4->yAxis->setNumberFormat("eb");
                   ui->graph4->yAxis->setNumberPrecision(2);

                   QCPItemText *textLabel = new QCPItemText(ui->graph4);
                   textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
                   textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
                   textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
                   textLabel->setText("Прогноз");
                   textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
                   ui->graph4->addItem(textLabel);
                   // add the arrow:
                   QCPItemLine *arrow = new QCPItemLine(ui->graph4);
                   arrow->start->setParentAnchor(textLabel->bottom);
                   arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
                   arrow->setHead(QCPLineEnding::esNone);
                   ui->graph4->addItem(arrow);

              ui->graph4->replot();
        }

        if(Index==3){
            QVector<double> x(N), y3(N);
            x[0] = 0; y3[0] = 0;
            x[1] = 1; y3[1] = GrProd4;
            x[2] = 2; y3[2] = GrProd3;
            x[3] = 3; y3[3] = GrProd2;
            x[4] = 4; y3[4] = GrProd1;
            x[5] = 5; y3[5] = GrNewProg;

            ui->graph1->addGraph();
              ui->graph1->graph()->setName(QString("Huobi"));
                ui->graph1->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph1->graph()->setPen(graphPen);
              ui->graph1->graph(1)->setData(x, y3);
              QCPItemText *textLabel = new QCPItemText(ui->graph1);
              textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
              textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
              textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
              textLabel->setText(" ");
              textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
              ui->graph1->addItem(textLabel);
              // add the arrow:
              QCPItemLine *arrow = new QCPItemLine(ui->graph1);
              arrow->start->setParentAnchor(textLabel->bottom);
              arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
              arrow->setHead(QCPLineEnding::esNone);
              ui->graph1->addItem(arrow);
              ui->graph1->replot();
        }

              ui->graph1->legend->setVisible(true);
                QFont legendFont = font();
                legendFont.setPointSize(10);
                ui->graph1->legend->setFont(legendFont);
                ui->graph1->legend->setSelectedFont(legendFont);
                ui->graph1->legend->setSelectableParts(QCPLegend::spItems);

            ui->graph1->xAxis->setLabel("Периоды");
            ui->graph1->yAxis->setLabel("Продажи");

                Index++;
        }
    ui->graph1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
ui->graph4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        }

void MainWindow::graphDrawW()
{
    QString prognoz=ui->comboBoxMetods->currentText();
    int Index=1;
    QString stockGraph="";
    double Vol1dAgo, Vol2dAgo, Vol3dAgo, Vol4dAgo;
    QSqlQuery query;
    QString cur1=ui->comboBoxPair1->currentText();
    QString cur2=ui->comboBoxPair2->currentText();
    str=cur1+"/"+cur2;
    double koef;
    QString k=ui->comboBoxKRyad->currentText();
    koef=k.toDouble();
    double tr;
    QString t=ui->comboBoxKTr->currentText();
    tr=t.toDouble();
    double GrProd4,GrProd3,GrProd2,GrProd1,GrNewProg;
    while(Index!=4){
    GrProd4=0; GrProd3=0; GrProd2=0; GrProd1=0; GrNewProg=0;

        if(Index==1) stockGraph="volume";
        if(Index==2) stockGraph="volumeHit";
        if(Index==3) stockGraph="volumeHuobi";

        query.exec("SELECT Vol1wAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString x = query.value(0).toString();
        Vol1dAgo=x.toDouble();
        }
        query.exec("SELECT Vol2wAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol2dAgo=y.toDouble();
        }
        query.exec("SELECT Vol3wAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol3dAgo=y.toDouble();
        }
        query.exec("SELECT Vol4wAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol4dAgo=y.toDouble();
        }

        if(prognoz=="Экспоненциальное сглаживание"){
        GrProd4=Vol4dAgo;
        GrProd3=koef*Vol4dAgo+(1-koef)*GrProd4;
        GrProd2=koef*Vol3dAgo+(1-koef)*GrProd3;
        GrProd1=koef*Vol2dAgo+(1-koef)*GrProd2;
        GrNewProg=koef*Vol1dAgo+(1-koef)*GrProd1;
        }
        if(prognoz=="Метод Хольта"){
            double Ryad4,Ryad3,Ryad2,Ryad1,Prog4,Prog3,Prog2,Prog1,Trend4,Trend3,Trend2,Trend1;
            GrProd4=Vol4dAgo; Ryad4=GrProd4; Trend4=0; Prog4=Vol4dAgo;
            GrProd3=Vol3dAgo;
            Ryad3=koef*Vol3dAgo+(1-koef)*(Ryad4-Trend4);
            Trend3=tr*(Ryad3-Ryad4)+(1-tr)*Trend4;
            Prog3=Ryad4+Trend4;
            GrProd2=Vol2dAgo;
            Ryad2=koef*Vol2dAgo+(1-koef)*(Ryad3-Trend3);
            Trend2=tr*(Ryad2-Ryad3)+(1-tr)*Trend3;
            Prog2=Ryad3+Trend3;
            GrProd1=Vol1dAgo;
            Prog1=Ryad2+Trend2;
            Ryad1=koef*Vol1dAgo+(1-koef)*(Ryad2-Trend2);
            Trend1=tr*(Ryad1-Ryad2)+(1-tr)*Trend2;
            GrNewProg=Ryad1+Trend1;
        }
        if(prognoz=="Линейный тренд"){
            double sred,sred2,q,w,b,e,r,a;
            GrProd4=Vol4dAgo; GrProd3=Vol3dAgo; GrProd2=Vol2dAgo; GrProd1=Vol1dAgo;
            sred=Vol1dAgo+Vol2dAgo+Vol3dAgo+Vol4dAgo;
            sred2=Vol1dAgo+Vol2dAgo*2+Vol3dAgo*3+Vol4dAgo*4;
            q=sred*2.5;
            w=sred2-q;
            b=w/5;
            e=sred*3;
            r=sred2-e;
            a=r/-2;
            GrNewProg=b*1+a;
        }

        int N=6;

        if(Index==1){
            QVector<double> x(N), y1(N);
            x[0] = 0; y1[0] = 0;
            x[1] = 1; y1[1] = GrProd4;
            x[2] = 2; y1[2] = GrProd3;
            x[3] = 3; y1[3] = GrProd2;
            x[4] = 4; y1[4] = GrProd1;
            x[5] = 5; y1[5] = GrNewProg;

            ui->graph2->addGraph();
              ui->graph2->graph()->setName(QString("Bitfinex"));
                ui->graph2->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
              QPen graphPen;
              int i=rand();
              //graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph2->graph()->setPen(graphPen);
              ui->graph2->graph(0)->setData(x, y1);
              double minY = y1[0], maxY = y1[0];
                  for (int i=1; i<N; i++)
                  {
                      if (y1[i]<minY) minY = y1[i];
                      if (y1[i]>maxY) maxY = y1[i];
                  }

                  ui->graph2->yAxis->setRange(minY, maxY*2);
                  ui->graph2->xAxis->setRange(0, 7);
                  ui->graph2->yAxis->setNumberFormat("eb");
                   ui->graph2->yAxis->setNumberPrecision(2);
                   QCPItemText *textLabel = new QCPItemText(ui->graph2);
                   textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
                   textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
                   textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
                   textLabel->setText("Прогноз");
                   textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
                   ui->graph2->addItem(textLabel);
                   // add the arrow:
                   QCPItemLine *arrow = new QCPItemLine(ui->graph2);
                   arrow->start->setParentAnchor(textLabel->bottom);
                   arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
                   arrow->setHead(QCPLineEnding::esNone);
                   ui->graph2->addItem(arrow);
              ui->graph2->replot();
        }
        if(Index==2){
            QVector<double> x(N), y2(N);
            x[0] = 0; y2[0] = 0;
            x[1] = 1; y2[1] = GrProd4;
            x[2] = 2; y2[2] = GrProd3;
            x[3] = 3; y2[3] = GrProd2;
            x[4] = 4; y2[4] = GrProd1;
            x[5] = 5; y2[5] = GrNewProg;

            ui->graph5->clearGraphs();
            ui->graph5->addGraph();
              ui->graph5->graph()->setName(QString("HitBTC"));
                ui->graph5->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph5->graph()->setPen(graphPen);
              ui->graph5->graph(0)->setData(x, y2);

              ui->graph5->legend->setVisible(true);
                QFont legendFont = font();
                legendFont.setPointSize(10);
                ui->graph5->legend->setFont(legendFont);
                ui->graph5->legend->setSelectedFont(legendFont);
                ui->graph5->legend->setSelectableParts(QCPLegend::spItems);

                ui->graph5->xAxis->setLabel("Периоды");
                ui->graph5->yAxis->setLabel("Продажи");

              double minY = y2[0], maxY = y2[0];
                  for (int i=1; i<N; i++)
                  {
                      if (y2[i]<minY) minY = y2[i];
                      if (y2[i]>maxY) maxY = y2[i];
                  }

                  ui->graph5->yAxis->setRange(minY, maxY*2);
                  ui->graph5->xAxis->setRange(0, 7);
                  ui->graph5->yAxis->setNumberFormat("eb");
                   ui->graph5->yAxis->setNumberPrecision(2);
                   QCPItemText *textLabel = new QCPItemText(ui->graph5);
                   textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
                   textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
                   textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
                   textLabel->setText("Прогноз");
                   textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
                    ui->graph5->addItem(textLabel);
                   // add the arrow:
                   QCPItemLine *arrow = new QCPItemLine(ui->graph5);
                   arrow->start->setParentAnchor(textLabel->bottom);
                   arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
                   arrow->setHead(QCPLineEnding::esNone);
                   ui->graph5->addItem(arrow);
              ui->graph5->replot();
        }

        if(Index==3){
            QVector<double> x(N), y3(N);
            x[0] = 0; y3[0] = 0;
            x[1] = 1; y3[1] = GrProd4;
            x[2] = 2; y3[2] = GrProd3;
            x[3] = 3; y3[3] = GrProd2;
            x[4] = 4; y3[4] = GrProd1;
            x[5] = 5; y3[5] = GrNewProg;

            ui->graph2->addGraph();
              ui->graph2->graph()->setName(QString("Huobi"));
                ui->graph2->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph2->graph()->setPen(graphPen);
              ui->graph2->graph(1)->setData(x, y3);
              QCPItemText *textLabel = new QCPItemText(ui->graph2);
              textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
              textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
              textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
              textLabel->setText(" ");
              textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
ui->graph2->addItem(textLabel);
              // add the arrow:
              QCPItemLine *arrow = new QCPItemLine(ui->graph2);
              arrow->start->setParentAnchor(textLabel->bottom);
              arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
              arrow->setHead(QCPLineEnding::esNone);
              ui->graph2->addItem(arrow);
              ui->graph2->replot();
        }

              ui->graph2->legend->setVisible(true);
                QFont legendFont = font();
                legendFont.setPointSize(10);
                ui->graph2->legend->setFont(legendFont);
                ui->graph2->legend->setSelectedFont(legendFont);
                ui->graph2->legend->setSelectableParts(QCPLegend::spItems);

            ui->graph2->xAxis->setLabel("Периоды");
            ui->graph2->yAxis->setLabel("Продажи");

                Index++;
        }
    ui->graph2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
ui->graph5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        }

void MainWindow::graphDrawM()
{
    QString prognoz=ui->comboBoxMetods->currentText();
    int Index=1;
    QString stockGraph="";
    double Vol1dAgo, Vol2dAgo, Vol3dAgo, Vol4dAgo;
    QSqlQuery query;
    QString cur1=ui->comboBoxPair1->currentText();
    QString cur2=ui->comboBoxPair2->currentText();
    str=cur1+"/"+cur2;
    double koef;
    QString k=ui->comboBoxKRyad->currentText();
    koef=k.toDouble();
    double tr;
    QString t=ui->comboBoxKTr->currentText();
    tr=t.toDouble();
    double GrProd4,GrProd3,GrProd2,GrProd1,GrNewProg;

    while(Index!=4){
    GrProd4=0; GrProd3=0; GrProd2=0; GrProd1=0; GrNewProg=0;

        if(Index==1) stockGraph="volume";
        if(Index==2) stockGraph="volumeHit";
        if(Index==3) stockGraph="volumeHuobi";

        query.exec("SELECT Vol1mAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString x = query.value(0).toString();
        Vol1dAgo=x.toDouble();
        }
        query.exec("SELECT Vol2mAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol2dAgo=y.toDouble();
        }
        query.exec("SELECT Vol3mAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol3dAgo=y.toDouble();
        }
        query.exec("SELECT Vol4mAgo FROM "+stockGraph+" WHERE Pairs ='"+str+"';");
        while(query.next()) {
        QString y = query.value(0).toString();
        Vol4dAgo=y.toDouble();
        }

        if(prognoz=="Экспоненциальное сглаживание"){
        GrProd4=Vol4dAgo;
        GrProd3=koef*Vol4dAgo+(1-koef)*GrProd4;
        GrProd2=koef*Vol3dAgo+(1-koef)*GrProd3;
        GrProd1=koef*Vol2dAgo+(1-koef)*GrProd2;
        GrNewProg=koef*Vol1dAgo+(1-koef)*GrProd1;
        }
        if(prognoz=="Метод Хольта"){
            double Ryad4,Ryad3,Ryad2,Ryad1,Prog4,Prog3,Prog2,Prog1,Trend4,Trend3,Trend2,Trend1;
            GrProd4=Vol4dAgo; Ryad4=GrProd4; Trend4=0; Prog4=Vol4dAgo;
            GrProd3=Vol3dAgo;
            Ryad3=koef*Vol3dAgo+(1-koef)*(Ryad4-Trend4);
            Trend3=tr*(Ryad3-Ryad4)+(1-tr)*Trend4;
            Prog3=Ryad4+Trend4;
            GrProd2=Vol2dAgo;
            Ryad2=koef*Vol2dAgo+(1-koef)*(Ryad3-Trend3);
            Trend2=tr*(Ryad2-Ryad3)+(1-tr)*Trend3;
            Prog2=Ryad3+Trend3;
            GrProd1=Vol1dAgo;
            Prog1=Ryad2+Trend2;
            Ryad1=koef*Vol1dAgo+(1-koef)*(Ryad2-Trend2);
            Trend1=tr*(Ryad1-Ryad2)+(1-tr)*Trend2;
            GrNewProg=Ryad1+Trend1;
        }
        if(prognoz=="Линейный тренд"){
            double sred,sred2,q,w,b,e,r,a;
            GrProd4=Vol4dAgo; GrProd3=Vol3dAgo; GrProd2=Vol2dAgo; GrProd1=Vol1dAgo;
            sred=Vol1dAgo+Vol2dAgo+Vol3dAgo+Vol4dAgo;
            sred2=Vol1dAgo+Vol2dAgo*2+Vol3dAgo*3+Vol4dAgo*4;
            q=sred*2.5;
            w=sred2-q;
            b=w/5;
            e=sred*3;
            r=sred2-e;
            a=r/-2;
            GrNewProg=b*1+a;
        }

        int N=6;

        if(Index==1){
            QVector<double> x(N), y1(N);
            x[0] = 0; y1[0] = 0;
            x[1] = 1; y1[1] = GrProd4;
            x[2] = 2; y1[2] = GrProd3;
            x[3] = 3; y1[3] = GrProd2;
            x[4] = 4; y1[4] = GrProd1;
            x[5] = 5; y1[5] = GrNewProg;

            ui->graph3->addGraph();
              //ui->graph3->graph()->setName(QString("Bitfinex").arg(ui->graph3->graphCount()-1));
                ui->graph3->graph()->setName(QString("Bitfinex"));
                ui->graph3->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph3->graph()->setPen(graphPen);
              ui->graph3->graph(0)->setData(x, y1);
              double minY = y1[0], maxY = y1[0];
                  for (int i=1; i<N; i++)
                  {
                      if (y1[i]<minY) minY = y1[i];
                      if (y1[i]>maxY) maxY = y1[i];
                  }

                  ui->graph3->yAxis->setRange(minY, maxY*2);
                  ui->graph3->xAxis->setRange(0, 7);
                  ui->graph3->yAxis->setNumberFormat("eb");
                   ui->graph3->yAxis->setNumberPrecision(2);
                   QCPItemText *textLabel = new QCPItemText(ui->graph3);
                   textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
                   textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
                   textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
                   textLabel->setText("Прогноз");
                   textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
                   ui->graph3->addItem(textLabel);

                   // add the arrow:
                   QCPItemLine *arrow = new QCPItemLine(ui->graph3);
                   arrow->start->setParentAnchor(textLabel->bottom);
                   arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
                   arrow->setHead(QCPLineEnding::esNone);
                   ui->graph3->addItem(arrow);
              ui->graph3->replot();
        }

        if(Index==2){
            QVector<double> x(N), y2(N);
            x[0] = 0; y2[0] = 0;
            x[1] = 1; y2[1] = GrProd4;
            x[2] = 2; y2[2] = GrProd3;
            x[3] = 3; y2[3] = GrProd2;
            x[4] = 4; y2[4] = GrProd1;
            x[5] = 5; y2[5] = GrNewProg;

            ui->graph6->clearGraphs();
            ui->graph6->addGraph();
              ui->graph6->graph()->setName(QString("HitBTC"));
                ui->graph6->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph6->graph()->setPen(graphPen);
              ui->graph6->graph(0)->setData(x, y2);

              double minY = y2[0], maxY = y2[0];
                  for (int i=1; i<N; i++)
                  {
                      if (y2[i]<minY) minY = y2[i];
                      if (y2[i]>maxY) maxY = y2[i];
                  }

                  ui->graph6->yAxis->setRange(minY, maxY*2);
                  ui->graph6->xAxis->setRange(0, 7);
                  ui->graph6->yAxis->setNumberFormat("eb");
                   ui->graph6->yAxis->setNumberPrecision(2);

              ui->graph6->legend->setVisible(true);
                QFont legendFont = font();
                legendFont.setPointSize(10);
                ui->graph6->legend->setFont(legendFont);
                ui->graph6->legend->setSelectedFont(legendFont);
                ui->graph6->legend->setSelectableParts(QCPLegend::spItems);


                ui->graph6->xAxis->setLabel("Периоды");
                ui->graph6->yAxis->setLabel("Продажи");
                QCPItemText *textLabel = new QCPItemText(ui->graph6);
                textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
                textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
                textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
                textLabel->setText("Прогноз");
                textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
ui->graph6->addItem(textLabel);
                // add the arrow:
                QCPItemLine *arrow = new QCPItemLine(ui->graph6);
                arrow->start->setParentAnchor(textLabel->bottom);
                arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
                arrow->setHead(QCPLineEnding::esNone);
                ui->graph6->addItem(arrow);
              ui->graph6->replot();
        }

        if(Index==3){
            QVector<double> x(N), y3(N);
            x[0] = 0; y3[0] = 0;
            x[1] = 1; y3[1] = GrProd4;
            x[2] = 2; y3[2] = GrProd3;
            x[3] = 3; y3[3] = GrProd2;
            x[4] = 4; y3[4] = GrProd1;
            x[5] = 5; y3[5] = GrNewProg;

            ui->graph3->addGraph();
              ui->graph3->graph()->setName(QString("Huobi"));
                ui->graph3->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1+1)));
              QPen graphPen;
              int i=rand();
              graphPen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
              graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
              ui->graph3->graph()->setPen(graphPen);
              ui->graph3->graph(1)->setData(x, y3);
              QCPItemText *textLabel = new QCPItemText(ui->graph3);
              textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
              textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
              textLabel->position->setCoords(0.8, 0.05); // place position at center/top of axis rect
              textLabel->setText(" ");
              textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
ui->graph3->addItem(textLabel);
              // add the arrow:
              QCPItemLine *arrow = new QCPItemLine(ui->graph3);
              arrow->start->setParentAnchor(textLabel->bottom);
              arrow->end->setCoords(5, GrNewProg); // point to (4, 1.6) in x-y-plot coordinates
              arrow->setHead(QCPLineEnding::esNone);
              ui->graph3->addItem(arrow);
              ui->graph3->replot();
}

              ui->graph3->legend->setVisible(true);
                QFont legendFont = font();
                legendFont.setPointSize(10);
                ui->graph3->legend->setFont(legendFont);
                ui->graph3->legend->setSelectedFont(legendFont);
                ui->graph3->legend->setSelectableParts(QCPLegend::spItems);

            ui->graph3->xAxis->setLabel("Периоды");
            ui->graph3->yAxis->setLabel("Продажи");

                Index++;
        }
ui->graph3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
ui->graph6->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        }

void MainWindow::showPointToolTip(QMouseEvent *event)
{

    int y = ui->graph1->yAxis->pixelToCoord(event->pos().y());
    int y1 = ui->graph2->yAxis->pixelToCoord(event->pos().y());
    int y2 = ui->graph3->yAxis->pixelToCoord(event->pos().y());
    int y3 = ui->graph4->yAxis->pixelToCoord(event->pos().y());
    int y4 = ui->graph5->yAxis->pixelToCoord(event->pos().y());
    int y5 = ui->graph6->yAxis->pixelToCoord(event->pos().y());

    ui->graph1->setToolTip(QString("%1").arg(y));
    ui->graph2->setToolTip(QString("%1").arg(y1));
    ui->graph3->setToolTip(QString("%1").arg(y2));
    ui->graph4->setToolTip(QString("%1").arg(y3));
    ui->graph5->setToolTip(QString("%1").arg(y4));
    ui->graph6->setToolTip(QString("%1").arg(y5));

}
