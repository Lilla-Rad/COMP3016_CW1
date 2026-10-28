#pragma once
#include "GameState.h"

class TitleScreenState : public GameState
{
public:

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void eventHandling(SDLWindow window, Game* manager) override;
    void update(Game* manager) override;
    void Render(SDLWindow window) override;

    static TitleScreenState* Instance() {
        return &stateTitleScreen;
    }

protected:
    TitleScreenState() {}

private:
    static TitleScreenState stateTitleScreen;
    MIX_Mixer* mixer;
    MIX_Track* title;

};
