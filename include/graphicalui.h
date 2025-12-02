#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include <QPixmap>
#include <vector>

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

    // textures
    std::vector<QPixmap> floorTextures;
    QPixmap wallTexture;
    QPixmap pitTexture;
    QPixmap rampTexture;
    QPixmap switchTexture;
    QPixmap doorClosedTexture;
    QPixmap doorOpenedTexture;

    std::vector<QPixmap> portalTextures; // 3 different portals

    // character textures
    QPixmap charFront;
    QPixmap charBack;
    QPixmap charLeft;
    QPixmap charRight;

    // ui-backgrounds & buttons
    QPixmap startBackground;
    QPixmap mainBackground;
    QPixmap newGameButtonTexture;

    std::vector<QPixmap> arrowTextures; // 9 numpad-arrows

    void loadTextures();

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

    // texture-getter
    const QPixmap& getFloorTexture(int index) const;
    const QPixmap& getWallTexture() const { return wallTexture; }
    const QPixmap& getPitTexture() const { return pitTexture; }
    const QPixmap& getRampTexture() const { return rampTexture; }
    const QPixmap& getSwitchTexture() const { return switchTexture; }
    const QPixmap& getDoorTexture(bool isOpen) const {
        return isOpen ? doorOpenedTexture : doorClosedTexture;
    }
    const QPixmap& getPortalTexture(int type) const;

    const QPixmap& getCharTexture(const Input& dir) const;

    const QPixmap& getStartBackground() const { return startBackground; }
    const QPixmap& getMainBackground() const { return mainBackground; }
    const QPixmap& getNewGameButtonTexture() const { return newGameButtonTexture; }

    const QPixmap& getArrowTexture(int idx) const { return arrowTextures.at(idx); }
};

#endif // GRAPHICALUI_H
