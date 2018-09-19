#include "exportpdf.h"
#include <QApplication>
#include <QtCore>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>

ExportPDF::ExportPDF()
{
    QString currDate()
    {
        QDate date = QDate::currentDate();
        return date.toString("dd.MM.yyyy");
    }
}
