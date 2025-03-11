#include "windows/formulaireconnexion.h"
#include "windows/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(R"(
        QWidget {
            background-color: #f0f0f0;
            font-family: Arial;
            font-size: 14px;
        }
        QLineEdit {
            border: 1px solid gray;
            border-radius: 5px;
            padding: 5px;
            background: white;
        }
        QPushButton {
            background-color: #0078D7;
            color: white;
            border-radius: 5px;
            padding: 5px;
        }
        QPushButton:hover {
            background-color: #005a9e;
        }
    )");
    
    qDebug() << "Test de qDebug";
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Whiteboard-B3_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
