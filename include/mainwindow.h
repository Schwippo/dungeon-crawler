#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class DungeonCrawler;
class GraphicalUI;
class Level;
class QLabel;
class QGridLayout;
class QHBoxLayout;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GraphicalUI* gui, QWidget *parent = nullptr);
    ~MainWindow();

    void updateView(Level* level);

private:
    Ui::MainWindow* ui;
    GraphicalUI* gui;

    QLabel* backgroundLabel;
    QGridLayout* tileLayout;
    QGridLayout* buttonLayout;
    QHBoxLayout* rootLayout;

    std::vector<std::vector<QLabel*>> tileLabels; // 2D label grid for tiles
    QLabel* characterLabel;
    int charRow{-1}, charCol{-1}; // last position from character

    void setupLayouts();
    void createControlButtons();
    void updateTileSizes();

    void handleMoveClick(int dirRow, int dirCol, bool quit);

    std::string arrowNameFromIndex(int index) const;
};
#endif // MAINWINDOW_H
