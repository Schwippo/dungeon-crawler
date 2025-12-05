#include "../include/graphicalui.h"
#include "../include/startscreen.h"
#include "../include/mainwindow.h"
#include "../include/dungeoncrawler.h"
#include "../include/level.h"

#include <QString>
#include <QDebug>

GraphicalUI::GraphicalUI(DungeonCrawler* game)
    : game(game), startScreen(nullptr), mainWindow(nullptr) {

    loadTextures();

    // create window
    startScreen = new startscreen(this, nullptr);
    mainWindow = new MainWindow(this);
    mainWindow->setMinimumSize(1100, 850);
    mainWindow->resize(110, 850);

    startScreen->show();
    mainWindow->hide();
}

GraphicalUI::~GraphicalUI() {
    delete startScreen;
    delete mainWindow;
}

void GraphicalUI::loadTextures() {

    // floor textures
    floorTextures.push_back(QPixmap(":/textures/floor/floor1.png"));
    floorTextures.push_back(QPixmap(":/textures/floor/floor2.png"));
    floorTextures.push_back(QPixmap(":/textures/floor/floor3.png"));
    floorTextures.push_back(QPixmap(":/textures/floor/floor4.png"));
    floorTextures.push_back(QPixmap(":/textures/floor/floor5.png"));

    // walls / tiles
    wallTexture = QPixmap(":/textures/wall/wall1.png");
    pitTexture = QPixmap(":/textures/pit.png");
    rampTexture = QPixmap(":/textures/ramp.png");
    switchTexture = QPixmap(":/textures/switch.png");

    doorClosedTexture = QPixmap(":/textures/doors/door1.png");
    doorOpenedTexture = QPixmap(":/textures/doors/door2.png");

    // portals
    portalTextures.push_back(QPixmap(":/textures/portal/portal1.png"));
    portalTextures.push_back(QPixmap(":/textures/portal/portal2.png"));
    portalTextures.push_back(QPixmap(":/textures/portal/portal3.png"));

    // character front
    {
        std::vector<QPixmap> frames;
        frames.push_back(QPixmap(":/textures/char/front/char_front_1.png"));
        frames.push_back(QPixmap(":/textures/char/front/char_front_2.png"));
        frames.push_back(QPixmap(":/textures/char/front/char_front_3.png"));

        characterAnimations["front"] = frames;
    };

    // character back
    {
        std::vector<QPixmap> frames;
        frames.push_back(QPixmap(":/textures/char/back/char_back_1.png"));
        frames.push_back(QPixmap(":/textures/char/back/char_back_2.png"));
        frames.push_back(QPixmap(":/textures/char/back/char_back_3.png"));

        characterAnimations["back"] = frames;
    };

    // character left
    {
        std::vector<QPixmap> frames;
        frames.push_back(QPixmap(":/textures/char/left/char_left_1.png"));
        frames.push_back(QPixmap(":/textures/char/left/char_left_2.png"));
        frames.push_back(QPixmap(":/textures/char/left/char_left_3.png"));

        characterAnimations["left"] = frames;
    };

    // character right
    {
        std::vector<QPixmap> frames;
        frames.push_back(QPixmap(":/textures/char/right/char_right_1.png"));
        frames.push_back(QPixmap(":/textures/char/right/char_right_2.png"));
        frames.push_back(QPixmap(":/textures/char/right/char_right_3.png"));

        characterAnimations["right"] = frames;
    };

    // zombies
    enemyAnimations["zombie_left"] = { QPixmap(":/textures/zombie/zombie_left.png") };
    enemyAnimations["zombie_right"] = { QPixmap(":/textures/zombie/zombie_right.png") };

    // arrow icons
    arrowIcons["up"] = QPixmap(":/textures/arrows/arrow_up.png");
    arrowIcons["down"] = QPixmap(":/textures/arrows/arrow_down.png");
    arrowIcons["left"] = QPixmap(":/textures/arrows/arrow_left.png");
    arrowIcons["right"] = QPixmap(":/textures/arrows/arrow_right.png");
    arrowIcons["up_left"] = QPixmap(":/textures/arrows/arrow_up_left.png");
    arrowIcons["up_right"] = QPixmap(":/textures/arrows/arrow_up_right.png");
    arrowIcons["down_left"] = QPixmap(":/textures/arrows/arrow_down_left.png");
    arrowIcons["down_right"] = QPixmap(":/textures/arrows/arrow_down_right.png");
    arrowIcons["skip"] = QPixmap(":/textures/arrows/arrow_skip.png");

    // UI textures
    startBackground = QPixmap(":/textures/startscreen.png");
    mainBackground = QPixmap(":/textures/startscreen__.png");
    newGameButtonTexture = QPixmap(":/textures/new_game_button.png");
}

const QPixmap& GraphicalUI::getFloorTexture(int index) const {
    if(floorTextures.empty())
        return wallTexture;

    return floorTextures[index % floorTextures.size()];
}

const QPixmap& GraphicalUI::getPortalTexture(int type) const {
    return portalTextures[type % portalTextures.size()];
}

std::string GraphicalUI::directionKeyFromInput(const Input& in) const {
    if(in.dr < 0) return "back";
    if(in.dr > 0) return "front";
    if(in.dc < 0) return "left";
    if(in.dc > 0) return "right";

    return "front"; // standard
}

const QPixmap& GraphicalUI::getCharacterTexture(const Input& dir) const {
    std::string key = directionKeyFromInput(dir);

    auto it = characterAnimations.find(key);
    if(it != characterAnimations.end() && !it->second.empty()) {
        return it->second[0]; // first frame of direction
    }

    auto itFront = characterAnimations.find("front");
    if(itFront != characterAnimations.end() && !it->second.empty()){
        qDebug() << "Warnung: Character-key" << QString::fromStdString(key) << " nicht gefunden.";
        return itFront->second[0];
    }

    static QPixmap dummy;
    qDebug() << "Warnung: Character-Texturen leer oder Keys fehlen";
    return dummy;
}

const QPixmap& GraphicalUI::getArrowTexture(const std::string& name) const {
    auto it = arrowIcons.find(name);
    if(it != arrowIcons.end()) {
        return it->second;
    }

    static QPixmap dummy;
    qDebug() << "Warnung: Arrow-Icon nicht gefunden für Key:" << QString::fromStdString(name);
    return dummy;
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

