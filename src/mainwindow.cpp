#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

#include "../include/graphicalui.h"
#include "../include/dungeoncrawler.h"

#include "../include/level.h"
#include "../include/tile.h"
#include "../include/floor.h"
#include "../include/wall.h"
#include "../include/portal.h"
#include "../include/pit.h"
#include "../include/ramp.h"
#include "../include/switch.h"
#include "../include/door.h"
#include "../include/character.h"

#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QIcon>

MainWindow::MainWindow(GraphicalUI* gui, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gui(gui), backgroundLabel(nullptr), tileLayout(nullptr), buttonLayout(nullptr), rootLayout(nullptr), characterLabel(nullptr)
{
    ui->setupUi(this);
    setupLayouts();
    createControlButtons();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupLayouts() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    backgroundLabel = new QLabel(central);
    backgroundLabel->setPixmap(gui->getMainBackground());
    backgroundLabel->setScaledContents(true);
    backgroundLabel->lower();

    tileLayout = new QGridLayout();
    buttonLayout = new QGridLayout();
    rootLayout = new QHBoxLayout();

    rootLayout->addLayout(tileLayout, 3);
    rootLayout->addLayout(buttonLayout, 1);

    central->setLayout(rootLayout);
}

void MainWindow::createControlButtons() {
    // 3x3 buttons
    int index = 0;

    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            QPushButton* button = new QPushButton(this);

            button->setIcon(QIcon(gui->getArrowTexture(index)));
            button->setIconSize(QSize(64, 64));
            button->setFlat(true);
            button->setStyleSheet("border:none;");

            int dirRow = r - 1; // mapping to -1, 0, 1
            int dirCol = c - 1;
            bool quit = false;

            // 5 = standing still -> dirRow=0, dirCol=0, quit=false
            connect(button, &QPushButton::clicked, [=]() {
                handleMoveClick(dirRow, dirCol, quit);
            });

            buttonLayout->addWidget(button, r, c);
            ++index;
        }
    }
}

void MainWindow::handleMoveClick(int dirRow, int dirCol, bool quit) {
    Input in;
    in.dr = dirRow;
    in.dc = dirCol;
    in.quit = quit;

    gui->setLastInput(in);

    DungeonCrawler* game = gui->getGame();
    if(game)
        game->turn();
}

void MainWindow::updateView(Level* level) {
    if(!level) return;

    int height = level->getHeight();
    int width = level->getWidth();

    // rebuild grid if size not right
    if(tileLabels.size() != (size_t)height || (height > 0 && tileLabels[0].size() != (size_t)width)) {
        if(tileLayout) {
            QLayoutItem* item;
            while((item = tileLayout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
        }

        tileLabels.assign(height, std::vector<QLabel*>(width, nullptr));

        for(int r = 0; r < height; ++r) {
            for(int c = 0; c < width; ++c) {
                QLabel* label = new QLabel(this);
                label->setScaledContents(true);
                tileLayout->addWidget(label, r, c);
                tileLabels[r][c] = label;
            }
        }
    }

    // draw tiles
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            QLabel* label = tileLabels[r][c];
            Tile* t = level->getTile(r, c);

            QPixmap pix;

            if (auto f = dynamic_cast<Floor*>(t)) {
                pix = gui->getFloorTexture(r * width + c);

            } else if (auto wll = dynamic_cast<Wall*>(t)) {
                pix = gui->getWallTexture();

            } else if (auto p = dynamic_cast<Portal*>(t)) {
                pix = gui->getPortalTexture(p->getPortalType());

            } else if (auto pit = dynamic_cast<Pit*>(t)) {
                pix = gui->getPitTexture();

            } else if (auto rp = dynamic_cast<Ramp*>(t)) {
                pix = gui->getRampTexture();

            } else if (auto sw = dynamic_cast<Switch*>(t)) {
                pix = gui->getSwitchTexture();

            } else if (auto d = dynamic_cast<Door*>(t)) {
                pix = gui->getDoorTexture(d->isOpenDoor());
            }

            label->setPixmap(pix);
        }
    }

    // draw character
    Character* player = level->getPlayer();
    if (player && player->getTile()) {
        int r = player->getTile()->getRow();
        int c = player->getTile()->getColumn();

        if (!characterLabel) {
            characterLabel = new QLabel(this);
            characterLabel->setScaledContents(true);
        }

        Input dir = player->getMoveDirection();
        characterLabel->setPixmap(gui->getCharTexture(dir));

        if (charRow != -1 && charCol != -1)
            tileLayout->removeWidget(characterLabel);

        tileLayout->addWidget(characterLabel, r, c);
        charRow = r;
        charCol = c;

        // sneak character if it's in a pit
        if (dynamic_cast<Pit*>(level->getTile(r, c)))
            characterLabel->lower();
        else
            characterLabel->raise();
    }

    updateTileSizes();
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    if (backgroundLabel) {
        backgroundLabel->setGeometry(rect());
        backgroundLabel->setPixmap(gui->getMainBackground().scaled(
            size(), Qt::KeepAspectRatioByExpanding));
    }

    updateTileSizes();
}

void MainWindow::updateTileSizes() {
    if (tileLabels.empty())
        return;

    int h = tileLabels.size();
    int w = tileLabels[0].size();

    int tileSize = std::min(height() / h, width() / (w + 3));

    for (auto& row : tileLabels) {
        for (QLabel* l : row) {
            l->setMinimumSize(tileSize, tileSize);
            l->setMaximumSize(tileSize, tileSize);
        }
    }

    if (characterLabel) {
        characterLabel->setMinimumSize(tileSize, tileSize);
        characterLabel->setMaximumSize(tileSize, tileSize);
    }
}
