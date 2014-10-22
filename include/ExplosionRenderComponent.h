/*******************************************************************//*
 * Render component for Explosion.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-25
 * @modified    2014-10-21
 *********************************************************************/
#ifndef SPACESHOOTER_EXPLOSIONRENDERCOMPONENT_
    #define SPACESHOOTER_EXPLOSIONRENDERCOMPONENT_

#include "RenderComponent.h"
#include <SDL2/SDL.h>

class GameEntity;

struct WindowElements;

class ExplosionRenderComponent : public RenderComponent
{
    private:
        SDL_Rect srcRectArray[16];
        int animationIndex;

    public:
        //Constructor
        ExplosionRenderComponent(GameEntity* gameEntity,
                                        WindowElements* windowElements,
                                        GameEntity* destroyedEntity);

        //Destructor
        ~ExplosionRenderComponent();

        //Methods
        void update();
        bool advanceAnimation();
};

#endif