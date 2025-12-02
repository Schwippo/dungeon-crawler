#ifndef TERMINALUI_H
#define TERMINALUI_H

#include "abstractView.h"
#include "abstractController.h"

class TerminalUI : public AbstractView, public AbstractController {
public:
    TerminalUI() = default;
    ~TerminalUI() override = default;

    void draw(Level* level) override;
    Input move() override;
};



#endif //TERMINALUI_H
