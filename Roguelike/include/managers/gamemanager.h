#pragma once
#include "fwd.h"

class GameManager
{
public:

	enum class CollisionLayers
	{
		Enemies,
		Players,
		Objects
	};

	GameManager(RenderWindow& window);
	~GameManager();

	void Update(float deltaTime);
	void UpdateEntities(float deltaTime, CollisionLayers layer);

	void Draw();
	void DrawEntities(CollisionLayers layer);

	void AddEntity(CollisionLayers layer, Entity* newEntity);
	void AddDamageableObject(CollisionLayers layer, IDamageable* newObject);

private:

	map<CollisionLayers, vector<Entity*>> entities;
	map<CollisionLayers, vector<IDamageable*>> damageableObjects;
	Player* player;

	RenderWindow& window;

	ContentLoader* contentLoader;
	RoomLoader* roomLoader;

	Room* testRoom;
	Texture mapSheet;
};