#include "../include/startscreen.h"
#include "ui_startscreen.h"
#include "../include/graphicalui.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QIcon>

startscreen::startscreen(GraphicalUI* gui, QWidget *parent)
    : QDialog(parent), ui(new Ui::startscreen), gui(gui) {
    ui->setupUi(this);
    setupUIElements();
}

startscreen::~startscreen() {
    delete ui;
}

void startscreen::setupUIElements() {
    setWindowTitle("Dungeon Crawler - Start");
    resize(900, 600);

    // main layout
    QVBoxLayout* layout = new QVBoxLayout(this);

    // background picture
    QLabel* bgLabel = new QLabel(this);
    bgLabel->setPixmap(gui->getStartBackground().scaled(size(), Qt::KeepAspectRatioByExpanding));
    bgLabel->setScaledContents(true);

    // new game button
    QPushButton* newGameButton = new QPushButton(this);
    newGameButton->setIcon(QIcon(gui->getNewGameButtonTexture()));
    newGameButton->setIconSize(QSize(250, 100));
    newGameButton->setFlat(true);
    newGameButton->setStyleSheet("border:none;");

    layout->addWidget(bgLabel);
    layout->addWidget(newGameButton, 0, Qt::AlignCenter);

    setLayout(layout);

    // connect button and slot
    connect(newGameButton, &QPushButton::clicked, this, &startscreen::onNewGameClicked);
}

void startscreen::onNewGameClicked() {
    if(gui)
        gui->switchWindow();
}


