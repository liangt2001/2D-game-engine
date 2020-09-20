#pragma once
#include "Component.h"
#include "TextureManager.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	PositionComponent *position;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* ren;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path, SDL_Renderer* renderer)
	{
		ren = renderer;
		texture = TextureManager::LoadTexture(path, ren);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path, ren);
	}

	void init() override
	{
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;

	}

	void update() override
	{
		destRect.x = position->x();
		destRect.y = position->y();
	}

	void draw() override
	{
		TextureManager::Draw(ren, texture, srcRect, destRect);
	}
};