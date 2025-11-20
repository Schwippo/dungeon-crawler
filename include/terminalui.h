#ifndef TERMINALUI_H
#define TERMINALUI_H

#include "../include/abstractView.h"
#include "../include/abstractcontroller.h"

class TerminalUI : public AbstractView, public AbstractController {
public:
    void draw(Level* level) override;
    Input move() override;
};



#endif //TERMINALUI_H
