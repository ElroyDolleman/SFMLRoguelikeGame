#include "stdafx.h"
#include "managers/gamemanager.h"

#include "collision\collisionmanager.h"
#include "managers\contentloader.h"
#include "interfaces\damageable.h"
#include "entities\Entity.h"
#include "entities\Player.h"
#include "map\roomloader.h"

GameManager::GameManager(RenderWindow& window)
	: window(window)
{
	contentLoader = new ContentLoader();
	roomLoader = new RoomLoader();

	mapSheet = contentLoader->LoadTexture("spritesheet.png");
	testRoom = roomLoader->CreateRoom(
		mapSheet,
		contentLoader->LoadJSON("rooms\\test1"),
		contentLoader->LoadJSON("sheetdata1")
	);

	collisionManager = new CollisionManager(testRoom);

	// Initialize damageable objects map
	damageableObjects = {
		{ CollisionLayers::Players,{} },
		{ CollisionLayers::Enemies,{} },
		{ CollisionLayers::Objects,{} }
	};

	// Initialize entities map
	entities = {
		{ CollisionLayers::Players,{} },
		{ CollisionLayers::Enemies,{} },
		{ CollisionLayers::Objects,{} }
	};
	
	// Adding the player to the world
	player = new Player(SpriteAnimation(contentLoader->LoadTexture("playersheet.png"), 32, 64, 16, 16));
	AddEntity(CollisionLayers::Players, player);

	player->SetPosition(128, 64);

	collisionManager->AddCollidableEntity(player);
}

GameManager::~GameManager()
{
	delete contentLoader;
	delete roomLoader;
}

void GameManager::Update(float deltaTime)
{
	UpdateEntities(deltaTime, CollisionLayers::Players);
	UpdateEntities(deltaTime, CollisionLayers::Enemies);
	UpdateEntities(deltaTime, CollisionLayers::Objects);
}

void GameManager::UpdateEntities(float deltaTime, CollisionLayers layer)
{
	for (int i = 0; i < entities[layer].size(); i++)
	{
		Vector2f prevPos = entities[layer][i]->GetPosition();
		entities[layer][i]->Update(deltaTime);
	}
}

void GameManager::Draw()
{
	// TODO: Think of a proper room handling system
	if (testRoom != nullptr)
		testRoom->Draw(window);

	DrawEntities(CollisionLayers::Objects);
	DrawEntities(CollisionLayers::Enemies);
	DrawEntities(CollisionLayers::Players);
}

void GameManager::DrawEntities(CollisionLayers layer)
{
	for (int i = 0; i < entities[layer].size(); i++)
		entities[layer][i]->Draw(window);
}

void GameManager::AddEntity(CollisionLayers layer, Entity* newEntity)
{
	entities[layer].push_back(newEntity);
}

void GameManager::AddDamageableObject(CollisionLayers layer, IDamageable* newObject)
{
	damageableObjects[layer].push_back(newObject);
}
