#include "../include/graphicalui.h"
#include "../include/startscreen.h"
#include "../include/mainwindow.h"
#include "../include/dungeoncrawler.h"
#include "../include/level.h"

#include <QString>

GraphicalUI::GraphicalUI(DungeonCrawler* game)
    : game(game), startScreen(nullptr), mainWindow(nullptr) {

    loadTextures();

    // create window
    startScreen = new startscreen(this);
    mainWindow = new MainWindow(this);

    startScreen->show();
    mainWindow->hide();
}

GraphicalUI::~GraphicalUI() {
    delete startScreen;
    delete mainWindow;
}

void GraphicalUI::loadTextures() {

    // floor
    floorTextures.push_back(QPixmap("../textures/floor/floor1.png"));
    floorTextures.push_back(QPixmap("../textures/floor/floor2.png"));
    floorTextures.push_back(QPixmap("../textures/floor/floor3.png"));
    floorTextures.push_back(QPixmap("../textures/floor/floor4.png"));
    floorTextures.push_back(QPixmap("../textures/floor/floor5.png"));

    wallTexture = QPixmap("../textures/wall/wall1.png");
    pitTexture = QPixmap("../textures/pit.png");
    rampTexture = QPixmap("../textures/ramp.png");
    switchTexture = QPixmap("../textures/switch.png");

    doorClosedTexture = QPixmap("../textures/doors/door1.png");
    doorOpenedTexture = QPixmap("../textures/doors/door2.png");

    portalTextures.push_back(QPixmap("../textures/portal/portal1.png"));
    portalTextures.push_back(QPixmap("../textures/portal/portal2.png"));
    portalTextures.push_back(QPixmap("../textures/portal/portal3.png"));

    // character TO DO : VECTOR WITH ALL VARIANTS
    charFront = QPixmap("../textures/char/char_front_1.png");
    charBack = QPixmap("../textures/char/back/char_back_1.png");
    charLeft = QPixmap("../textures/char/left/char_left_1.png");
    charRight = QPixmap("../textures/char/right/char_right_1.png");

    // UI
    startBackground = QPixmap("../textures/startscreen.png");
    mainBackground = QPixmap("../textures/startscreen__.png");
    newGameButtonTexture = QPixmap("../textures/new_game_button.png");

    // 9 directions for buttons
    for(int i = 0; i <= 9; ++i)
        // TO DO PUSH BACK ALL BUTTONS
        arrowTextures.push_back(QPixmap(QString("../textures/arrows/%1.png").arg(i)));
}

const QPixmap& GraphicalUI::getFloorTexture(int index) const {
    if(floorTextures.empty())
        return wallTexture;

    return floorTextures[index % floorTextures.size()];
}

const QPixmap& GraphicalUI::getPortalTexture(int type) const {
    return portalTextures[type % portalTextures.size()];
}

const QPixmap& GraphicalUI::getCharTexture(const Input& dir) const {
    if(dir.dr < 0) return charFront;
    if(dir.dr > 0) return charBack;
    if(dir.dc < 0) return charLeft;
    if(dir.dc > 0) return charRight;

    return charBack; // standard
}

void GraphicalUI::draw(Level* level) {
    mainWindow->updateView(level);
}

Input GraphicalUI::move() { return lastInput; }

void GraphicalUI::switchWindow() {
    if(!startScreen || !mainWindow) return;

    startScreen->hide();
    mainWindow->show();
    mainWindow->raise();
    mainWindow->activateWindow();

    draw(game->getLevel());
}

void GraphicalUI::setLastInput(const Input& in) { lastInput = in; }

