#include "recommend.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::textVivod(){
    QString ProverkaPMD,ProverkaPMW,ProverkaPMM;
    double PersD,PersW,PersM;
    PersD=(NewProgD-Prod1d)/Prod1d*100;
    if(PersD>0) ProverkaPMD="% больше последних продаж";
    if(PersD==0) ProverkaPMD="% ни больше ни меньше последней продажи";
    if(PersD<0) ProverkaPMD="% меньше последних продаж";
    PersW=(NewProgW-Prod1w)/Prod1w*100;
    if(PersW>0) ProverkaPMW="% больше последних продаж";
    if(PersW==0) ProverkaPMW="% ни больше ни меньше последней продажи";
    if(PersW<0) ProverkaPMW="% меньше последних продаж";
    PersM=(NewProgM-Prod1m)/Prod1m*100;
    if(PersM>0) ProverkaPMM="% больше последних продаж";
    if(PersM==0) ProverkaPMM="% ни больше ни меньше последней продажи";
    if(PersM<0) ProverkaPMM="% меньше последних продаж";
    QString StringD= QString::number(NewProgD,'f',1);
    QString PersentD= QString::number(PersD);
    QString StringW= QString::number(NewProgW,'f',1);
    QString PersentW= QString::number(PersW);
    QString StringM= QString::number(NewProgM,'f',1);
    QString PersentM= QString::number(PersM);
    Vivod="Спрогнозированные продажи по паре "+str+" будут следующие: на завтра "+StringD+" что на "+PersentD+" "+ProverkaPMD+", а за следующую "
            "неделю "+StringW+" что на "+PersentW+" "+ProverkaPMW+", а за следующий месяц "+StringM+" что на "+PersentM+" "+ProverkaPMM+". На графиках"
            " изображен рост и падение продаж по этой паре в бирже "+stockName+" по периодам 4 дней, 4 недель и 4 месяцев.";

}

void MainWindow::textRecommend(){
    double Prod4wRECBit,Prod3wRECBit,Prod2wRECBit,Prod1wRECBit,NewProgWRECBit;
    double Prod4wRECHit,Prod3wRECHit,Prod2wRECHit,Prod1wRECHit,NewProgWRECHit;
    double Prod4wRECHuo,Prod3wRECHuo,Prod2wRECHuo,Prod1wRECHuo,NewProgWRECHuo;
    QString cur1=ui->comboBoxPair1->currentText();
    QString cur2=ui->comboBoxPair2->currentText();
    str=cur1+"/"+cur2;
    qDebug()<<str;
    double Vol1wAgoREC,Vol2wAgoREC,Vol3wAgoREC,Vol4wAgoREC, koef,tr;
    QString k=ui->comboBoxKRyad->currentText();
    QString t=ui->comboBoxKTr->currentText();
    koef=k.toDouble();
    tr=t.toDouble();
    QSqlQuery query;
    query.exec("SELECT Vol1wAgo FROM volume WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1wAgoREC=x.toDouble();
    }
    query.exec("SELECT Vol2wAgo FROM volume WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol3wAgo FROM volume WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol4wAgo FROM volume WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4wAgoREC=y.toDouble();
    }
    Prod4wRECBit=Vol4wAgoREC;
    Prod3wRECBit=koef*Vol4wAgoREC+(1-koef)*Prod4wRECBit;
    Prod2wRECBit=koef*Vol3wAgoREC+(1-koef)*Prod3wRECBit;
    Prod1wRECBit=koef*Vol2wAgoREC+(1-koef)*Prod2wRECBit;
    NewProgWRECBit=koef*Vol1wAgoREC+(1-koef)*Prod1wRECBit;

    Vol4wAgoREC=0;Vol3wAgoREC=0;Vol2wAgoREC=0;Vol1wAgoREC=0;

    query.exec("SELECT Vol1wAgo FROM volumeHit WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1wAgoREC=x.toDouble();
    }
    query.exec("SELECT Vol2wAgo FROM volumeHit WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol3wAgo FROM volumeHit WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol4wAgo FROM volumeHit WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4wAgoREC=y.toDouble();
    }
    Prod4wRECHit=Vol4wAgoREC;
    Prod3wRECHit=koef*Vol4wAgoREC+(1-koef)*Prod4wRECHit;
    Prod2wRECHit=koef*Vol3wAgoREC+(1-koef)*Prod3wRECHit;
    Prod1wRECHit=koef*Vol2wAgoREC+(1-koef)*Prod2wRECHit;
    NewProgWRECHit=koef*Vol1wAgoREC+(1-koef)*Prod1wRECHit;

    Vol4wAgoREC=0;Vol3wAgoREC=0;Vol2wAgoREC=0;Vol1wAgoREC=0;

    query.exec("SELECT Vol1wAgo FROM volumeHuobi WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1wAgoREC=x.toDouble();
    }
    query.exec("SELECT Vol2wAgo FROM volumeHuobi WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol3wAgo FROM volumeHuobi WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol4wAgo FROM volumeHuobi WHERE Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4wAgoREC=y.toDouble();
    }
    Prod4wRECHuo=Vol4wAgoREC;
    Prod3wRECHuo=koef*Vol4wAgoREC+(1-koef)*Prod4wRECHuo;
    Prod2wRECHuo=koef*Vol3wAgoREC+(1-koef)*Prod3wRECHuo;
    Prod1wRECHuo=koef*Vol2wAgoREC+(1-koef)*Prod2wRECHuo;
    NewProgWRECHuo=koef*Vol1wAgoREC+(1-koef)*Prod1wRECHuo;

    Vol4wAgoREC=0;Vol3wAgoREC=0;Vol2wAgoREC=0;Vol1wAgoREC=0;

    double PersBitVSHit, PersBitVSHuo, PersHitVSHuo;
    if(NewProgWRECBit>NewProgWRECHit) PersBitVSHit = (NewProgWRECBit-NewProgWRECHit)/NewProgWRECHit*100;
    if(NewProgWRECBit<NewProgWRECHit) PersBitVSHit = (NewProgWRECHit-NewProgWRECBit)/NewProgWRECBit*100;
    if(NewProgWRECBit>NewProgWRECHuo) PersBitVSHuo = (NewProgWRECBit-NewProgWRECHuo)/NewProgWRECHuo*100;
    if(NewProgWRECBit<NewProgWRECHuo) PersBitVSHuo = (NewProgWRECHuo-NewProgWRECBit)/NewProgWRECBit*100;
    if(NewProgWRECHit>NewProgWRECHuo) PersHitVSHuo = (NewProgWRECHit-NewProgWRECHuo)/NewProgWRECHuo*100;
    if(NewProgWRECHit<NewProgWRECHuo) PersHitVSHuo = (NewProgWRECHuo-NewProgWRECHit)/NewProgWRECHit*100;

    double CurrencyBit,CurrencyHit,CurrencyHuo;
    query.exec("SELECT Currency FROM currency WHERE Stock like 'Bitfinex' and Pairs ='"+str+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    CurrencyBit=x.toDouble();
    }
    query.exec("SELECT Currency FROM currency WHERE Stock like 'HitBTC' and Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    CurrencyHit=y.toDouble();
    }
    query.exec("SELECT Currency FROM currency WHERE Stock like 'Huobi' and Pairs ='"+str+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    CurrencyHuo=y.toDouble();
    }

    double PersCurBitVSHit,PersCurBitVSHuo,PersCurHitVSHuo;
    if(CurrencyBit>CurrencyHit) PersCurBitVSHit = (CurrencyBit-CurrencyHit)/CurrencyHit*100;
    if(CurrencyBit<CurrencyHit) PersCurBitVSHit = (CurrencyHit-CurrencyBit)/CurrencyBit*100;
    if(CurrencyBit>CurrencyHuo) PersCurBitVSHuo = (CurrencyBit-CurrencyHuo)/CurrencyHuo*100;
    if(CurrencyBit<CurrencyHuo) PersCurBitVSHuo = (CurrencyHuo-CurrencyBit)/CurrencyBit*100;
    if(CurrencyHit>CurrencyHuo) PersCurHitVSHuo = (CurrencyHit-CurrencyHuo)/CurrencyHuo*100;
    if(CurrencyHit<CurrencyHuo) PersCurHitVSHuo = (CurrencyHuo-CurrencyHit)/CurrencyHit*100;

    QString cur3=ui->comboBoxPair1->currentText();
    QString str2,cur4;
    double Prod4wRECpairs,Prod3wRECpairs,Prod2wRECpairs,Prod1wRECpairs,NewProgWRECpairs;
    if(cur2=="USD") cur4="BTC";
    else cur4="USD";
    str2=cur3+"/"+cur4;
    query.exec("SELECT Vol1wAgo FROM "+stockFlag+" WHERE Pairs ='"+str2+"';");
    while(query.next()) {
    QString x = query.value(0).toString();
    Vol1wAgoREC=x.toDouble();
    }
    query.exec("SELECT Vol2wAgo FROM "+stockFlag+" WHERE Pairs ='"+str2+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol2wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol3wAgo FROM "+stockFlag+" WHERE Pairs ='"+str2+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol3wAgoREC=y.toDouble();
    }
    query.exec("SELECT Vol4wAgo FROM "+stockFlag+" WHERE Pairs ='"+str2+"';");
    while(query.next()) {
    QString y = query.value(0).toString();
    Vol4wAgoREC=y.toDouble();
    }
    Prod4wRECpairs=Vol4wAgoREC;
    Prod3wRECpairs=koef*Vol4wAgoREC+(1-koef)*Prod4wRECpairs;
    Prod2wRECpairs=koef*Vol3wAgoREC+(1-koef)*Prod3wRECpairs;
    Prod1wRECpairs=koef*Vol2wAgoREC+(1-koef)*Prod2wRECpairs;
    NewProgWRECpairs=koef*Vol1wAgoREC+(1-koef)*Prod1wRECpairs;

    ///////////////////////////ПОСТРОЕНИЕ РЕКОМЕНДАЦИИ///////////////////////////

    QString StockRec,GraphRec,PersStock,PersStock2,PersStock3,PersStock4,PersStock5,PersStock6, CurRec,PersCur1,PersCur2,PersCur3,PersCur4,PersCur5,PersCur6;

    if(NewProgWRECBit>NewProgWRECHit) PersStock = "% меньше продаж в Bitfinex. ";
    if(NewProgWRECBit<NewProgWRECHit) PersStock = "% больше продаж в Bitfinex. ";
    if(NewProgWRECBit>NewProgWRECHuo) PersStock2 = "% меньше продаж в Bitfinex. ";
    if(NewProgWRECBit<NewProgWRECHuo) PersStock2 = "% больше продаж в Bitfinex. ";

    if(NewProgWRECHit>NewProgWRECBit) PersStock3 = "% меньше продаж в HitBTC. ";
    if(NewProgWRECHit<NewProgWRECBit) PersStock3 = "% больше продаж в HitBTC. ";
    if(NewProgWRECHit>NewProgWRECHuo) PersStock4 = "% меньше продаж в HitBTC. ";
    if(NewProgWRECHit<NewProgWRECHuo) PersStock4 = "% больше продаж в HitBTC. ";

    if(NewProgWRECHuo>NewProgWRECBit) PersStock5 = "% меньше продаж в Huobi. ";
    if(NewProgWRECHuo<NewProgWRECBit) PersStock5 = "% больше продаж в Huobi. ";
    if(NewProgWRECHuo>NewProgWRECHit) PersStock6 = "% меньше продаж в Huobi. ";
    if(NewProgWRECHuo<NewProgWRECHit) PersStock6 = "% больше продаж в Huobi. ";

    if(CurrencyBit>CurrencyHit) PersCur1 = "% меньше чем в Bitfinex. ";
    if(CurrencyBit<CurrencyHit) PersCur1 = "% больше чем в Bitfinex. ";
    if(CurrencyBit==CurrencyHit) PersCur1 = " курс равен. ";

    if(CurrencyBit>CurrencyHuo) PersCur2 = "% меньше чем в Bitfinex. ";
    if(CurrencyBit<CurrencyHuo) PersCur2 = "% больше чем в Bitfinex. ";
    if(CurrencyBit==CurrencyHuo) PersCur2 = " курс равен. ";

    if(CurrencyHit>CurrencyBit) PersCur3 = "% меньше чем в HitBTC. ";
    if(CurrencyHit<CurrencyBit) PersCur3 = "% больше чем в HitBTC. ";
    if(CurrencyHit==CurrencyBit) PersCur3 = " курс равен. ";

    if(CurrencyHit>CurrencyHuo) PersCur4 = "% меньше чем в HitBTC. ";
    if(CurrencyHit<CurrencyHuo) PersCur4 = "% больше чем в HitBTC. ";
    if(CurrencyHit==CurrencyHuo) PersCur4 = " курс равен. ";

    if(CurrencyHuo>CurrencyBit) PersCur5 = "% меньше чем в Huobi. ";
    if(CurrencyHuo<CurrencyBit) PersCur5 = "% больше чем в Huobi. ";
    if(CurrencyHuo==CurrencyBit) PersCur5 = " курс равен. ";

    if(CurrencyHuo>CurrencyHit) PersCur6 = "% меньше чем в Huobi. ";
    if(CurrencyHuo<CurrencyHit) PersCur6 = "% больше чем в Huobi. ";
    if(CurrencyHuo==CurrencyHit) PersCur6 = " курс равен. ";

    QString StringProgPairs= QString::number(NewProgWRECpairs,'f',1);
    QString StringProgWHit= QString::number(NewProgWRECHit,'f',1);
    QString StringPersWBitHit= QString::number(PersBitVSHit,'f',1);
    QString StringProgWHuo= QString::number(NewProgWRECHuo,'f',1);
    QString StringPersWBitHuo= QString::number(PersBitVSHuo,'f',1);
    QString StringProgWBit= QString::number(NewProgWRECBit,'f',1);
    QString StringPersWHitHuo= QString::number(PersHitVSHuo,'f',1);
    QString StringCurBitHit= QString::number(PersCurBitVSHit,'f',1);
    QString StringCurBitHuo= QString::number(PersCurBitVSHuo,'f',1);
    QString StringCurHitHuo= QString::number(PersCurHitVSHuo,'f',1);
    QString StringCurBit= QString::number(CurrencyBit,'f',1);
    QString StringCurHit= QString::number(CurrencyHit,'f',1);
    QString StringCurHuo= QString::number(CurrencyHuo,'f',1);

    if(Prod2w<Prod1w && Prod1w<NewProgW && Prod2w<NewProgW) GraphRec="идет рост продаж";
    if(Prod2w>Prod1w && Prod1w>NewProgW && Prod2w>NewProgW) GraphRec="происходит упадок продаж";
    if((Prod2w<Prod1w && Prod1w>NewProgW)|| (Prod2w>Prod1w && Prod1w<NewProgW)) GraphRec="хаотичные продажи";

    if(stockFlag=="volume") StockRec="Так же можно воспользоваться биржами HitBTC или Huobi. В бирже HitBTC продажи валюты "+str+" на "
    "следующую неделю составляют "+StringProgWHit+" что на "+StringPersWBitHit+""+PersStock+" В бирже Huobi продажи валюты "+str+" на "
    "следующую неделю составляют "+StringProgWHuo+" что на "+StringPersWBitHuo+""+PersStock2;

    if(stockFlag=="volumeHit") StockRec="Так же можно воспользоваться биржами Bitfinex или Huobi. В бирже Bitfinex продажи валюты "+str+" на "
    "следующую неделю составляют "+StringProgWBit+" что на "+StringPersWBitHit+""+PersStock3+" В бирже Huobi продажи валюты "+str+" на "
    "следующую неделю составляют "+StringProgWHuo+" что на "+StringPersWHitHuo+""+PersStock4;

    if(stockFlag=="volumeHuobi") StockRec="Так же можно воспользоваться биржами Bitfinex или HitBTC. В бирже Bitfinex продажи валюты "+str+" на "
    "следующую неделю составляют "+StringProgWBit+" что на "+StringPersWBitHuo+""+PersStock5+" В бирже HitBTC продажи валюты "+str+" на "
    "следующую неделю составляют "+StringProgWHit+" что на "+StringPersWHitHuo+""+PersStock6;

    if(stockFlag=="volume") CurRec="Стоит учесть, что курс продажи по паре "+str+" составляет "+StringCurBit+" . В то время как в бирже HitBTC"
    " он "+StringCurHit+" что на "+StringCurBitHit+""+PersCur1+", а в бирже Huobi - "+StringCurHuo+" что на "+StringCurBitHuo+""+PersCur2;

    if(stockFlag=="volumeHit") CurRec="Стоит учесть, что курс продажи по паре "+str+" составляет "+StringCurHit+" . В то время как в бирже Bitfinex"
    " он "+StringCurBit+" что на "+StringCurBitHit+""+PersCur3+", а в бирже Huobi - "+StringCurHuo+" что на "+StringCurHitHuo+""+PersCur4;

    if(stockFlag=="volumeHuobi") CurRec="Стоит учесть, что курс продажи по паре "+str+" составляет "+StringCurHuo+" . В то время как в бирже Bitfinex"
    " он "+StringCurBit+" что на "+StringCurBitHuo+""+PersCur5+", а в бирже HitBTC - "+StringCurHit+" что на "+StringCurHitHuo+""+PersCur6;

    QString vigoda;
    if(cur3=="BTC") vigoda="";
    else vigoda="Можно попробывать получить выгоду продав по паре "+str2+" . Продажи по ней будут за неделю составлять "+StringProgPairs+" . ";
    Recommend="В последние недели "+GraphRec+" пары "+str+" ."+vigoda+""+StockRec+""+CurRec;
}
