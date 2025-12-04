#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include <QPixmap>
#include <vector>
#include <map>
#include <string>

#include "abstractView.h"
#include "abstractcontroller.h"

class DungeonCrawler;
class startscreen;
class MainWindow;
class Level;

class GraphicalUI : public AbstractView, public AbstractController {
private:
    DungeonCrawler* game;

    // window
    startscreen* startScreen;
    MainWindow* mainWindow;

    // input memory for move()
    Input lastInput;

    // character + enemy animations
    std::map<std::string, std::vector<QPixmap>> characterAnimations;
    std::map<std::string, std::vector<QPixmap>> enemyAnimations;

    // arrow icons
    std::map<std::string, QPixmap> arrowIcons;

    // tile textures
    std::vector<QPixmap> floorTextures;
    std::vector<QPixmap> portalTextures;

    // textures
    QPixmap wallTexture;
    QPixmap pitTexture;
    QPixmap rampTexture;
    QPixmap switchTexture;
    QPixmap doorClosedTexture;
    QPixmap doorOpenedTexture;

    // ui-backgrounds & buttons
    QPixmap startBackground;
    QPixmap mainBackground;
    QPixmap newGameButtonTexture;

    void loadTextures();
    std::string directionKeyFromInput(const Input& in) const;

public:
    explicit GraphicalUI(DungeonCrawler* game);
    ~GraphicalUI();

    // abstractview
    void draw(Level* level) override;

    // abstractcontroller
    Input move() override;

    // call from startscreen
    void switchWindow();

    // call from MainWindow to set lastInput
    void setLastInput(const Input& in);
    DungeonCrawler* getGame() const { return game; }

    // texture-getters
    const QPixmap& getFloorTexture(int index) const;
    const QPixmap& getWallTexture() const { return wallTexture; }
    const QPixmap& getPitTexture() const { return pitTexture; }
    const QPixmap& getRampTexture() const { return rampTexture; }
    const QPixmap& getSwitchTexture() const { return switchTexture; }
    const QPixmap& getDoorTexture(bool isOpen) const {
        return isOpen ? doorOpenedTexture : doorClosedTexture;
    }
    const QPixmap& getPortalTexture(int type) const;

    const QPixmap& getCharacterTexture(const Input& dir) const;
    const QPixmap& getArrowTexture(const std::string& name) const;

    const QPixmap& getStartBackground() const { return startBackground; }
    const QPixmap& getMainBackground() const { return mainBackground; }
    const QPixmap& getNewGameButtonTexture() const { return newGameButtonTexture; }
};

#endif // GRAPHICALUI_H
