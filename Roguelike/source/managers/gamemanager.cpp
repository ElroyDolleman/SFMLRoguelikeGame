#include "stdafx.h"
#include "managers/gamemanager.h"

GameManager::GameManager(RenderWindow& window)
	: window(window)
{
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
	

	AddEntity(CollisionLayers::Players, new Player(Sprite()));
}

GameManager::~GameManager()
{
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
		entities[layer][i]->Update(deltaTime);
}

void GameManager::Draw()
{

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
