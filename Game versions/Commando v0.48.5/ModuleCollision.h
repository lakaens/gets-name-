#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 1700

#include "Module.h"


enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_WATER,
	COLLIDER_PLAYER_FEET,
	COLLIDER_ITEM,
	COLLIDER_PRISONER,
	COLLIDER_PLAYER_GRENADE,
	COLLIDER_END_OF_BULLET,
	COLLIDER_END_OF_GRENADE,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback /*= nullptr*/;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback /*= nullptr*/) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	//update_status PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* /*callback = nullptr*/);
	bool EraseCollider(Collider* collider);
	void DebugDraw();
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];

private:

	Collider* colliders[MAX_COLLIDERS];
	bool debug = false;
};

#endif // __ModuleCollision_H__
