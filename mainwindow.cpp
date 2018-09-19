#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVariant>
#include <QFrame>
#include <QtGui>
#include <style.h>
#include <qcustomplot.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->DtbaseConnect,SIGNAL(clicked(bool)),this, SLOT(on_DtbaseConnect_triggered()));
    connect(ui->Spravka1,SIGNAL(clicked(bool)),this, SLOT(on_Spravka1_triggered()));
    connect(ui->Spravka2,SIGNAL(clicked(bool)),this, SLOT(on_Spravka2_triggered()));
    connect(ui->Design,SIGNAL(clicked(bool)),this, SLOT(on_Design_triggered()));
    connect(ui->Result,SIGNAL(clicked(bool)),this, SLOT(on_Result_triggered()));
    connect(ui->Handler,SIGNAL(clicked(bool)),this, SLOT(on_pushButtonProg_clicked()));
    connect(ui->Exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->graph1, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(ui->graph2, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(ui->graph3, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(ui->graph4, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(ui->graph5, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(ui->graph6, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));

    on_DtbaseConnect_triggered();
    ui->menuBar->setStyleSheet("selection-color: black;selection-background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(253, 200, 48, 255), stop:1 rgba(243, 115, 53, 255)); background-color:rgb(243, 216, 129)");
    ui->graph1->setBackground(QBrush(QColor("#f3d881")));
    ui->graph2->setBackground(QBrush(QColor("#f3d881")));
    ui->graph3->setBackground(QBrush(QColor("#f3d881")));
    ui->graph4->setBackground(QBrush(QColor("#f3d881")));
    ui->graph5->setBackground(QBrush(QColor("#f3d881")));
    ui->graph6->setBackground(QBrush(QColor("#f3d881")));
    ui->tableViewStock->verticalHeader()->setVisible(false);
    stockFlag="volume";
    stockName="Bitfinex";
    flag=5;

    ui->tableViewStock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->label->setText("Курсы обмена валюты по всем биржам(Для больших подробностей, воспользуйтесь справкой)");

    QWidget::setMaximumSize(1234,756);
    QWidget::setMinimumSize(1234,756);

    ui->frame->setVisible(true);
    ui->frame_2->setVisible(false);
    ui->labelD->setVisible(false);
    ui->labelW->setVisible(false);
    ui->labelM->setVisible(false);
    ui->labelProgD->setVisible(false);
    ui->labelProgW->setVisible(false);
    ui->labelProgM->setVisible(false);
    ui->PDFButton->setEnabled(false);
    ui->pushButtonResult->setEnabled(false);
    ui->comboBoxKTr->setEnabled(false);

    if(ui->comboBoxPair1->currentText()=="BTC")
    {
        ui->comboBoxPair2->clear();
        ui->comboBoxPair2->addItem("USD");
    }

    ui->pushButtonBitStock->setToolTip("Bitfinex — криптовалютная биржа для<br> торговли и хранения крипто-фиатных валют, принадлежит компании iFinex Inc."
                                       "C 2014 года была наибольшей биржей для торговли с больше чем 10% от биржевого трейдинга криптовалют.");
    ui->pushButtonHitStock->setToolTip("HitBTC является ведущей европейской<br> биржей биткойнов, которая предоставляет услуги по криптовалютной"
                                       " торговле институтам, торговцам и индивидуальным трейдерам по всему миру. Торговая платформа была "
                                       "основана в конце 2013 года и находится в ведении Ullus Corporation.");
    ui->pushButtonHuoStock->setToolTip("Huobi - это китайская торговая<br> платформа для торговли цифровыми валютами, расположенная в Пекине."
                                       "Huobi была основана в сентябре 2013 года. Это один из крупнейших цифровых валютных бирж в Китае.");

}

void MainWindow::Tables()
{
    flag=1;
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery qry;
    QString queryClean="SELECT Pairs,Currency,Stock FROM currency";
    qry.exec(queryClean);
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
    model->setHeaderData(1, Qt::Horizontal, tr("Курс валюты"));
    model->setHeaderData(2, Qt::Horizontal, tr("Биржа"));
    ui->tableViewStock->setModel(model);
    flag=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DtbaseConnect_triggered()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("C:\\Users/Пользователь/diplom.db");
    db.setDatabaseName("diplom.db");
    if(db.open()){
qDebug()<<"База данных успешно подключена";
    }
    ui->tableViewStock->setEditTriggers(QAbstractItemView::AllEditTriggers);
    Tables();
}

void MainWindow::on_pushButtonProg_clicked()
{
    QString cur1=ui->comboBoxPair1->currentText();
    QString cur2=ui->comboBoxPair2->currentText();
    QString Pair=cur1+"/"+cur2;
    ui->labelProg->setText("Прогноз пары "+Pair+" биржи "+stockName);

    ui->radioButtonD->setAutoExclusive(false);
    ui->radioButtonD->setChecked(false);
    ui->radioButtonD->setAutoExclusive(true);

    ui->radioButtonW->setAutoExclusive(false);
    ui->radioButtonW->setChecked(false);
    ui->radioButtonW->setAutoExclusive(true);

    ui->radioButtonM->setAutoExclusive(false);
    ui->radioButtonM->setChecked(false);
    ui->radioButtonM->setAutoExclusive(true);

    ui->pushButtonResult->setEnabled(true);

    QString prognoz=ui->comboBoxMetods->currentText();
    if(prognoz=="Экспоненциальное сглаживание") PrognozExpZglaj();
    if(prognoz=="Метод Хольта") HoltMethod();
    if(prognoz=="Линейный тренд") LinearTrendMethod();

    ui->graph1->clearGraphs();
    ui->graph1->clearItems();
    ui->graph1->replot();

    ui->graph2->clearGraphs();
    ui->graph2->clearItems();
    ui->graph2->replot();

    ui->graph3->clearGraphs();
    ui->graph3->clearItems();
    ui->graph3->replot();

    ui->graph4->clearGraphs();
    ui->graph4->clearItems();
    ui->graph4->replot();

    ui->graph5->clearGraphs();
    ui->graph5->clearItems();
    ui->graph5->replot();

    ui->graph6->clearGraphs();
    ui->graph6->clearItems();
    ui->graph6->replot();

    ui->labelD->setVisible(false);
    ui->labelProgD->setVisible(false);
    ui->labelW->setVisible(false);
    ui->labelProgW->setVisible(false);
    ui->labelM->setVisible(false);
    ui->labelProgM->setVisible(false);
}

void MainWindow::on_pushButtonSort_clicked()
{
    //ui->tableViewStock->move(-11,40);
    QString dataCh=ui->comboBoxPair1->currentText();
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery qry;
    QString queryCheck="SELECT Vol1dAgo FROM volume where Vol2dAgo=62000;";
    QString queryCleanC="SELECT Pairs,Currency,Stock FROM currency WHERE Pairs LIKE'"+dataCh+"%';";
    QString queryCleanV="SELECT * FROM volume WHERE Pairs LIKE'"+dataCh+"%';";
    QString queryCleanV2="SELECT * FROM volumeHit WHERE Pairs LIKE'"+dataCh+"%';";
    QString queryCleanV3="SELECT * FROM volumeHuobi WHERE Pairs LIKE'"+dataCh+"%';";
    qry.exec(queryCheck);
    if(flag==1){
        qry.exec(queryCleanC);
        model->setQuery(qry);
        model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
        model->setHeaderData(1, Qt::Horizontal, tr("Курс валюты"));
        model->setHeaderData(2, Qt::Horizontal, tr("Биржа"));
        ui->tableViewStock->setModel(model);
    }
    if(flag==0){
        qry.exec(queryCleanV);
        model->setQuery(qry);
        model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
        model->setHeaderData(1, Qt::Horizontal, tr("Вчера"));
        model->setHeaderData(2, Qt::Horizontal, tr("2 дня назад"));
        model->setHeaderData(3, Qt::Horizontal, tr("3 дня назад"));
        model->setHeaderData(4, Qt::Horizontal, tr("4 дня назад"));
        model->setHeaderData(5, Qt::Horizontal, tr("Прошлая неделя"));
        model->setHeaderData(6, Qt::Horizontal, tr("2 недели назад"));
        model->setHeaderData(7, Qt::Horizontal, tr("3 недели назад"));
        model->setHeaderData(8, Qt::Horizontal, tr("4 недели назад"));
        model->setHeaderData(9, Qt::Horizontal, tr("За 30 дней"));
        model->setHeaderData(10, Qt::Horizontal, tr("2 месяца назад"));
        model->setHeaderData(11, Qt::Horizontal, tr("3 месяца назад"));
        model->setHeaderData(12, Qt::Horizontal, tr("4 месяца назад"));
        model->setHeaderData(13, Qt::Horizontal, tr("Индекс биржи"));
        ui->tableViewStock->setModel(model);
    }
    if(flag==2){
        qry.exec(queryCleanV2);
        model->setQuery(qry);
        model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
        model->setHeaderData(1, Qt::Horizontal, tr("Вчера"));
        model->setHeaderData(2, Qt::Horizontal, tr("2 дня назад"));
        model->setHeaderData(3, Qt::Horizontal, tr("3 дня назад"));
        model->setHeaderData(4, Qt::Horizontal, tr("4 дня назад"));
        model->setHeaderData(5, Qt::Horizontal, tr("Прошлая неделя"));
        model->setHeaderData(6, Qt::Horizontal, tr("2 недели назад"));
        model->setHeaderData(7, Qt::Horizontal, tr("3 недели назад"));
        model->setHeaderData(8, Qt::Horizontal, tr("4 недели назад"));
        model->setHeaderData(9, Qt::Horizontal, tr("За 30 дней"));
        model->setHeaderData(10, Qt::Horizontal, tr("2 месяца назад"));
        model->setHeaderData(11, Qt::Horizontal, tr("3 месяца назад"));
        model->setHeaderData(12, Qt::Horizontal, tr("4 месяца назад"));
        model->setHeaderData(13, Qt::Horizontal, tr("Индекс биржи"));
        ui->tableViewStock->setModel(model);
    }
    if(flag==3){
        qry.exec(queryCleanV3);
        model->setQuery(qry);
        model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
        model->setHeaderData(1, Qt::Horizontal, tr("Вчера"));
        model->setHeaderData(2, Qt::Horizontal, tr("2 дня назад"));
        model->setHeaderData(3, Qt::Horizontal, tr("3 дня назад"));
        model->setHeaderData(4, Qt::Horizontal, tr("4 дня назад"));
        model->setHeaderData(5, Qt::Horizontal, tr("Прошлая неделя"));
        model->setHeaderData(6, Qt::Horizontal, tr("2 недели назад"));
        model->setHeaderData(7, Qt::Horizontal, tr("3 недели назад"));
        model->setHeaderData(8, Qt::Horizontal, tr("4 недели назад"));
        model->setHeaderData(9, Qt::Horizontal, tr("За 30 дней"));
        model->setHeaderData(10, Qt::Horizontal, tr("2 месяца назад"));
        model->setHeaderData(11, Qt::Horizontal, tr("3 месяца назад"));
        model->setHeaderData(12, Qt::Horizontal, tr("4 месяца назад"));
        model->setHeaderData(13, Qt::Horizontal, tr("Индекс биржи"));
        ui->tableViewStock->setModel(model);
    }
}

void MainWindow::on_pushButtonKurs_clicked()
{
   // ui->tableViewStock->move(-20,40);
    ui->label->setText("Курсы обмена валюты по всем биржам(Для больших подробностей, воспользуйтесь справкой)");
    flag=1;
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery qry;
    QString queryClean="SELECT Pairs,Currency,Stock FROM currency";
    qry.exec(queryClean);
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
    model->setHeaderData(1, Qt::Horizontal, tr("Курс валюты"));
    model->setHeaderData(2, Qt::Horizontal, tr("Биржа"));
    ui->tableViewStock->setModel(model);
}

void MainWindow::on_comboBoxPair1_currentIndexChanged()
{
    if(ui->comboBoxPair1->currentText()=="BTC")
    {
        ui->comboBoxPair2->clear();
        ui->comboBoxPair2->addItem("USD");
    }
    if(ui->comboBoxPair1->currentText()=="ETH")
    {
        ui->comboBoxPair2->clear();
        ui->comboBoxPair2->addItem("USD");
        ui->comboBoxPair2->addItem("BTC");
    }
    if(ui->comboBoxPair1->currentText()=="LTC" || ui->comboBoxPair1->currentText()=="ETC" || ui->comboBoxPair1->currentText()=="ZEC"
            || ui->comboBoxPair1->currentText()=="DASH" || ui->comboBoxPair1->currentText()=="BTG" || ui->comboBoxPair1->currentText()=="XMR")
    {
        ui->comboBoxPair2->clear();
        ui->comboBoxPair2->addItem("USD");
        ui->comboBoxPair2->addItem("BTC");
    }
    if(ui->comboBoxPair1->currentText()=="BCH" || ui->comboBoxPair1->currentText()=="NEO" || ui->comboBoxPair1->currentText()=="QTUM"
            || ui->comboBoxPair1->currentText()=="EOS" || ui->comboBoxPair1->currentText()=="OMG")
    {
        ui->comboBoxPair2->clear();
        ui->comboBoxPair2->addItem("USD");
        ui->comboBoxPair2->addItem("BTC");
        ui->comboBoxPair2->addItem("ETH");
    }
    if(stockFlag=="volumeHuobi")
    {
        if(ui->comboBoxPair1->currentText()=="BCH" || ui->comboBoxPair1->currentText()=="NEO"){
            ui->comboBoxPair2->clear();
            ui->comboBoxPair2->addItem("USD");
            ui->comboBoxPair2->addItem("BTC");
    }
        if(ui->comboBoxPair1->currentText()=="XMR" || ui->comboBoxPair1->currentText()=="BTG"){
           ui->comboBoxPair2->clear();
        }
    }

}

void MainWindow::on_pushButtonBitStock_clicked()
{
    //ui->tableViewStock->move(-20,40);
    ui->label->setText("Продажи валюты за последние 4 дня, 4 недели, 4 месяца(Подробности в справке)");
    flag=0;
    stockFlag="volume";
    stockName="Bitfinex";
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery qry;
    QString queryVol="SELECT * FROM volume";
    qry.exec(queryVol);
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
    model->setHeaderData(1, Qt::Horizontal, tr("Вчера"));
    model->setHeaderData(2, Qt::Horizontal, tr("2 дня назад"));
    model->setHeaderData(3, Qt::Horizontal, tr("3 дня назад"));
    model->setHeaderData(4, Qt::Horizontal, tr("4 дня назад"));
    model->setHeaderData(5, Qt::Horizontal, tr("Прошлая неделя"));
    model->setHeaderData(6, Qt::Horizontal, tr("2 недели назад"));
    model->setHeaderData(7, Qt::Horizontal, tr("3 недели назад"));
    model->setHeaderData(8, Qt::Horizontal, tr("4 недели назад"));
    model->setHeaderData(9, Qt::Horizontal, tr("За 30 дней"));
    model->setHeaderData(10, Qt::Horizontal, tr("2 месяца назад"));
    model->setHeaderData(11, Qt::Horizontal, tr("3 месяца назад"));
    model->setHeaderData(12, Qt::Horizontal, tr("4 месяца назад"));
    model->setHeaderData(13, Qt::Horizontal, tr("Индекс биржи"));
    ui->tableViewStock->setModel(model);
    qDebug()<<stockFlag;
    on_comboBoxPair1_currentIndexChanged();
}

void MainWindow::on_pushButtonHitStock_clicked()
{
    //ui->tableViewStock->move(-20,40);
    ui->label->setText("Продажи валюты за последние 4 дня, 4 недели, 4 месяца(Подробности в справке)");
    flag=2;
    stockFlag="volumeHit";
    stockName="HitBTC";
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery qry;
    QString queryVol="SELECT * FROM volumeHit";
    qry.exec(queryVol);
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
    model->setHeaderData(1, Qt::Horizontal, tr("Вчера"));
    model->setHeaderData(2, Qt::Horizontal, tr("2 дня назад"));
    model->setHeaderData(3, Qt::Horizontal, tr("3 дня назад"));
    model->setHeaderData(4, Qt::Horizontal, tr("4 дня назад"));
    model->setHeaderData(5, Qt::Horizontal, tr("Прошлая неделя"));
    model->setHeaderData(6, Qt::Horizontal, tr("2 недели назад"));
    model->setHeaderData(7, Qt::Horizontal, tr("3 недели назад"));
    model->setHeaderData(8, Qt::Horizontal, tr("4 недели назад"));
    model->setHeaderData(9, Qt::Horizontal, tr("За 30 дней"));
    model->setHeaderData(10, Qt::Horizontal, tr("2 месяца назад"));
    model->setHeaderData(11, Qt::Horizontal, tr("3 месяца назад"));
    model->setHeaderData(12, Qt::Horizontal, tr("4 месяца назад"));
    model->setHeaderData(13, Qt::Horizontal, tr("Индекс биржи"));
    ui->tableViewStock->setModel(model);
    qDebug()<<stockFlag;
    on_comboBoxPair1_currentIndexChanged();
}

void MainWindow::on_pushButtonHuoStock_clicked()
{
   // ui->tableViewStock->move(-20,40);
    ui->label->setText("Продажи валюты за последние 4 дня, 4 недели, 4 месяца(Подробности в справке)");
    flag=3;
    stockFlag="volumeHuobi";
    stockName="Huobi";
    QSqlQueryModel * model = new QSqlQueryModel(this);
    QSqlQuery qry;
    QString queryVol="SELECT * FROM volumeHuobi";
    qry.exec(queryVol);
    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, tr("Пара валют"));
    model->setHeaderData(1, Qt::Horizontal, tr("Вчера"));
    model->setHeaderData(2, Qt::Horizontal, tr("2 дня назад"));
    model->setHeaderData(3, Qt::Horizontal, tr("3 дня назад"));
    model->setHeaderData(4, Qt::Horizontal, tr("4 дня назад"));
    model->setHeaderData(5, Qt::Horizontal, tr("Прошлая неделя"));
    model->setHeaderData(6, Qt::Horizontal, tr("2 недели назад"));
    model->setHeaderData(7, Qt::Horizontal, tr("3 недели назад"));
    model->setHeaderData(8, Qt::Horizontal, tr("4 недели назад"));
    model->setHeaderData(9, Qt::Horizontal, tr("За 30 дней"));
    model->setHeaderData(10, Qt::Horizontal, tr("2 месяца назад"));
    model->setHeaderData(11, Qt::Horizontal, tr("3 месяца назад"));
    model->setHeaderData(12, Qt::Horizontal, tr("4 месяца назад"));
    model->setHeaderData(13, Qt::Horizontal, tr("Индекс биржи"));
    ui->tableViewStock->setModel(model);
    qDebug()<<stockFlag;
    on_comboBoxPair1_currentIndexChanged();
}

void MainWindow::on_Design_triggered(){
    ui->frame->setVisible(true);
    ui->frame_2->setVisible(false);
}

void MainWindow::on_Result_triggered(){
    Ti=QTime::currentTime();
    Dt=QDate::currentDate();
    ui->frame->setVisible(false);
    ui->frame_2->setVisible(true);
}

void MainWindow::on_pushButtonResult_clicked()
{
    ui->frame->setVisible(false);
    ui->frame_2->setVisible(true);
}

void MainWindow::on_pushButtonDesign_clicked()
{
    ui->frame->setVisible(true);
    ui->frame_2->setVisible(false);
}

void MainWindow::on_radioButtonD_clicked()
{
    ui->graph4->clearItems();
    ui->graph1->clearItems();
    ui->graph2->clearItems();
    ui->graph3->clearItems();
    ui->graph5->clearItems();
    ui->graph6->clearItems();
    ui->graph1->setVisible(true);
    ui->graph2->setVisible(false);
    ui->graph3->setVisible(false);
    ui->graph4->setVisible(true);
    ui->graph5->setVisible(false);
    ui->graph6->setVisible(false);
    ui->labelD->setVisible(true);
    ui->labelProgD->setVisible(true);
    ui->labelW->setVisible(false);
    ui->labelProgW->setVisible(false);
    ui->labelM->setVisible(false);
    ui->labelProgM->setVisible(false);
    ui->graph1->clearGraphs();
    graphDrawD();
    ui->PDFButton->setEnabled(true);
}

void MainWindow::on_radioButtonW_clicked()
{
    ui->graph4->clearItems();
    ui->graph1->clearItems();
    ui->graph2->clearItems();
    ui->graph3->clearItems();
    ui->graph5->clearItems();
    ui->graph6->clearItems();
    ui->graph1->setVisible(false);
    ui->graph2->setVisible(true);
    ui->graph3->setVisible(false);
    ui->graph4->setVisible(false);
    ui->graph5->setVisible(true);
    ui->graph6->setVisible(false);
    ui->labelD->setVisible(false);
    ui->labelProgD->setVisible(false);
    ui->labelW->setVisible(true);
    ui->labelProgW->setVisible(true);
    ui->labelM->setVisible(false);
    ui->labelProgM->setVisible(false);
    ui->graph2->clearGraphs();
    graphDrawW();
    ui->PDFButton->setEnabled(true);
}

void MainWindow::on_radioButtonM_clicked()
{
    ui->graph4->clearItems();
    ui->graph1->clearItems();
    ui->graph2->clearItems();
    ui->graph3->clearItems();
    ui->graph5->clearItems();
    ui->graph6->clearItems();
    ui->graph1->setVisible(false);
    ui->graph2->setVisible(false);
    ui->graph3->setVisible(true);
    ui->graph4->setVisible(false);
    ui->graph5->setVisible(false);
    ui->graph6->setVisible(true);
    ui->labelD->setVisible(false);
    ui->labelProgD->setVisible(false);
    ui->labelW->setVisible(false);
    ui->labelProgW->setVisible(false);
    ui->labelM->setVisible(true);
    ui->labelProgM->setVisible(true);
    ui->graph3->clearGraphs();
    graphDrawM();
    ui->PDFButton->setEnabled(true);
}

void MainWindow::on_pushVivod_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Выводы");
    msgBox.setInformativeText(Vivod);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_pushRec_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Рекомендации");
    msgBox.setInformativeText(Recommend);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_comboBoxMetods_currentIndexChanged()
{
    if(ui->comboBoxMetods->currentText()=="Экспоненциальное сглаживание")
    {
        ui->comboBoxKRyad->setEnabled(true);
        ui->comboBoxKTr->setEnabled(false);
    }

    if(ui->comboBoxMetods->currentText()=="Метод Хольта")
    {
        ui->comboBoxKRyad->setEnabled(true);
        ui->comboBoxKTr->setEnabled(true);
    }

    if(ui->comboBoxMetods->currentText()=="Линейный тренд")
    {
        ui->comboBoxKRyad->setEnabled(false);
        ui->comboBoxKTr->setEnabled(true);
    }
}
