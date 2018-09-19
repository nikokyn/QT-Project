#include "info.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_Spravka1_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Справка для ориентации в таблице");
    msgBox.setInformativeText("<b>Таблица объема продаж</b><br>Вчера - объем продаж за вчерашний день <br>2 дня назад - объем продаж за позавчера <br>"
                              "3 дня назад - объем продаж 3 дня назад <br>4 дня назад - объем продаж 4 дня назад <br>Прошлая неделя - Продажи за всю прошлую неделю<br>"
                              "2 недели назад - продажи за позапрошлую неделю <br>3 недели назад - продажи за третью неделю назад <br>4 недели назад  - продажи за четвертую неделю назад<br>"
                              "За 30 дней - Объем продаж за прошедшие 30 дней <br>2 месяца назад - объем продаж за второй месяц назад <br>"
                              "3 месяца назад  - объем продаж за третий месяц назад <br>4 месяца назад  - объем продаж за четвертый месяц назад");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}


void MainWindow::on_Spravka2_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Справка для названий криптовалют");
    msgBox.setText("Раcшифровка названий криптовалют");
    msgBox.setInformativeText("<b>BTC</b> - Bitcoin <br> <b>ETH</b> - Ethereum <br> <b>LTC</b> - Litecoin <br> <b>BCH</b> - Bitcoin Cash <br>"
                              "<b>NEO</b> - AntShares(old) <br> <b>ETC</b> - Ethereum Classic <br> <b>ZEC</b> - Zcash <br>"
                              "<b>XMR</b> - Monero <br> <b>DASH</b> - Darkcoin и XCoin(old) <br> <b>BTG</b> - Bitcoin Gold <br>"
                              "<b>QTUM</b> - Quantum <br> <b>EOS</b> - EOS <br> <b>OMG</b> - OmiseGO <br>");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}


void MainWindow::on_pushMetodsHelp_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Справка методам прогноза");
    msgBox.setText("Методы прогноза");
    msgBox.setInformativeText("<b>Экспоненциальное сглаживание(англ. Exponential average)</b> - оптимальный вариант прогноза, когда продажи"
                              " имеются только за несколько периодов (месяцев, дней, недель, кварталов) и еще не понятно - существуют"
                              " тенденции роста или падения. Название метода происходит из того факта, что при его применении получаются"
                              " экспоненциально взвешенные скользящие средние по всему временному ряду. При экспоненциальном сглаживании"
                              " учитываются все предыдущие наблюдения с максимальным весом, то есть наблюдение влияет на результат с "
                              "минимальным статистическим весом.<br>"
                              "<b>Метод Хольта(англ. Holt Method)</b> - используется для прогнозирования временных рядов, когда уже есть"
                              " тенденция к росту или падению значений временного ряда. А также для рядов, когда данные не за полный цикл,"
                              " и сезонность еще не выделить (например, за неполный год для прогноза по месяцам)<br>"
                              "<b>Линейный тренд(англ. Linear Trend)</b> - основная тенденция изменения чего-либо. Линейный тренд следует"
                              " применять для прогнозирования временных рядов, данные которых"
                              " увеличиваются или уменьшаются с постоянной скоростью.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}


void MainWindow::on_pushHelp_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Справка по главному меню");
    msgBox.setText("Кнопки");
    msgBox.setInformativeText("<b>Курс</b> - выводит таблицу курсов всех трех бирж криптовалюты <br> <b>Bitfinex, HitBTC, Huobi</b> - выводит"
                              " продажи выбраной биржы  по 4 дням, неделям, месяцам <br> <b>Пара валют</b> - нажмите на левую стрелку, чтобы"
                              " выбрать валюту продажи и нажмите на правую, что бы выбрать валюту покупки <br> <b>Методы прогноза</b> - "
                              " выбирайте один из трех методов прогноза продаж <br> <b>Коэффициенты</b> - экспериментируйте с прогнозами или "
                              "оставьте стандартные показатели(Для знающих) <br> <b>Результат</b> - отправит обратно на страницу результата прогноза"
                              ", если он уже был <br> <b>Обработка</b> - прогнозирует продажи и переводит вас на страницу результата <br>");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_pushHelp2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Справка по меню результата");
    msgBox.setText("Прогноз");
    msgBox.setInformativeText("<b>Прогноз</b> - в окне показаны графики продаж выбраной валюты по трем биржам. Первые 4 точки - последние"
                              " продажи по четырём периодам, зависимо от того что выбрать будут показаны периоды 4 последних дней, 4 недель и"
                              " месяцев. Последняя 5 точка - прогнозируемая.<br> <b>Дни, Недели, Месяцы</b> - при нажатии выводит графики трёх"
                              " бирж по этому периоду и прогнозируемое следующее значение продажи.<br> <b>Выводы</b> -  уточняет, что показано"
                              " на странице и указывает дополнительную статистику. <br> <b>Рекомендации</b> - показывает анализ выгоды по трем "
                              "биржам и выводит советы по вложениям.<br> <b>Назад</b> - возвращает обратно на главную страницу. <br>");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

