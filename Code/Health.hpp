#pragma once

#include "Entity.hpp"

class Health : public Entity{
public:
	Health(SDL_Rect srcR_param, Entity * target_param);
	void Update() override;
	void Render() override;
	Entity * target;
};