#include "pdf.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_PDFButton_clicked()
{
    QPixmap pixmap1(ui->graph1->size());
    ui->graph1->render(&pixmap1);
    pixmap1.save("gr1.png");
    QPixmap pixmap2(ui->graph2->size());
    ui->graph2->render(&pixmap2);
    pixmap2.save("gr2.png");
    QPixmap pixmap3(ui->graph3->size());
    ui->graph3->render(&pixmap3);
    pixmap3.save("gr3.png");
    QPixmap pixmap4(ui->graph4->size());
    ui->graph4->render(&pixmap4);
    pixmap4.save("gr4.png");
    QPixmap pixmap5(ui->graph5->size());
    ui->graph5->render(&pixmap5);
    pixmap5.save("gr5.png");
    QPixmap pixmap6(ui->graph6->size());
    ui->graph6->render(&pixmap6);
    pixmap6.save("gr6.png");

    QString Time=Ti.toString();
    QString Date=Dt.toString();
    QString k=ui->comboBoxKRyad->currentText();
    QString tr=ui->comboBoxKTr->currentText();
    QString metod=ui->comboBoxMetods->currentText();
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
       if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setPaperSize(QPrinter::A4);
       printer.setOutputFileName(fileName);

       QTextDocument doc;
       doc.setHtml("<h1>Прогноз продаж пары криптовалюты "+str+" в бирже "+stockName+"</h1>\n<p>Прогноз на "+Time+" "+Date+".</p>\n"
                   "Прогноз выполнен с помощью метода "+metod+" c коэффициентами: сглаживания ряда - "+k+" , а сглаживания тренда - "+tr+"\n"
                   "<h2>Рекомендации по прогнозу:</h2><p>"+Recommend+"</p>\n"

                   "<p align='center'>График продаж бирж Bitfinex и Huobi на 24 часа</p>\n"
                   "<p align='center'><img src='gr1.png' height='150' width='500'></p>\n"

                   "<p align='center'>График продаж биржы HitBTC на 24 часа</p>\n"
                   "<p align='center'><img src='gr4.png' height='150' width='500'></p>\n" "<br><br><br><br><br><br><br><br><br>"
                   "<p align='center'>График продаж бирж Bitfinex и Huobi на 7 дней</p>\n"
                   "<p align='center'><img src='gr2.png' height='150' width='500'></p>\n"

                   "<p align='center'>График продаж биржы HitBTC на 7 дней</p>\n"
                   "<p align='center'><img src='gr5.png' height='150' width='500'></p>\n"

                   "<p align='center'>График продаж бирж Bitfinex и Huobi на месяц</p>\n"
                   "<p align='center'><img src='gr3.png' height='150' width='500'></p>\n"

                   "<p align='center'>График продаж биржы HitBTC на месяц</p>\n"
                   "<p align='center'><img src='gr6.png' height='150' width='500'></p>"

                   "<h2>Выводы по прогнозу:</h2><p>"+Vivod+"</p>\n");

       doc.setPageSize(printer.pageRect().size());
       doc.print(&printer);
}
