#include "../include/mainwindow.h"
#include "../include/dungeoncrawler.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DungeonCrawler game;

    return app.exec();
}

