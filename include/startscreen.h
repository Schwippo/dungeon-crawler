#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

class GraphicalUI;

namespace Ui {
class startscreen;
}

class startscreen : public QDialog
{
    Q_OBJECT

public:
    explicit startscreen(GraphicalUI* gui, QWidget *parent = nullptr);
    ~startscreen();

private slots:
    void onNewGameClicked();

private:
    Ui::startscreen *ui;
    GraphicalUI* gui;

    void setupUIElements();
};

#endif // STARTSCREEN_H
