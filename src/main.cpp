#include "../include/mainwindow.h"
#include "../include/dungeoncrawler.h"

#include <QApplication>
#include <iostream>

/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    DungeonCrawler game;
    while (true) {
        if (!game.turn()) break;
    }

    std::cout << "Spiel beendet\n";
    return 0;
}
*/

int main() {
    DungeonCrawler game;
    game.run();
    return 0;
}
