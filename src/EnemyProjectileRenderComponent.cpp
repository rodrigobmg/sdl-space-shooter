/*******************************************************************//*
 * Implementation of the EnemyProjectileRenderComponent class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2014-09-17
 * @modified    2015-02-16
 *********************************************************************/
#include "EnemyProjectileRenderComponent.h"

#include <cstddef>
#include "GameEntity.h"
#include "RenderComponent.h"
#include "SDL_util.h"
#include "WindowElements.h"

EnemyProjectileRenderComponent::EnemyProjectileRenderComponent(GameEntity* gameEntity,
                                               WindowElements* windowElements,
                                               GameEntity* enemyEntity)
{
    this->gameEntity = gameEntity;
    this->windowElements = windowElements;

    texture = new Texture(windowElements);
    texture->setTexture("../data/graphics/sprites/laserRed03.png");

    renderRect.w = texture->getSpriteWidth();
    renderRect.h = texture->getSpriteHeight();
    gameEntity->position.x = enemyEntity->position.x;
    gameEntity->position.y = enemyEntity->position.y
        + (enemyEntity->getRenderComponent()->getTexture()->getSpriteHeight())/2
        - (texture->getSpriteHeight())/2;
}

void EnemyProjectileRenderComponent::update()
{
    renderRect.x = gameEntity->position.x - renderRect.w/2;
    renderRect.y = gameEntity->position.y - renderRect.h/2;
    SDL_RenderCopy(windowElements->renderer, texture->getTexture(), NULL, &renderRect);
}

EnemyProjectileRenderComponent::~EnemyProjectileRenderComponent()
{
    delete texture;
}
