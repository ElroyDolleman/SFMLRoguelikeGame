#include "stdafx.h"
#include "managers/gamemanager.h"

GameManager::GameManager(RenderWindow& window)
	: window(window)
{
	textureManager = new TextureManager();

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
	player = new Player(Sprite(textureManager->GetSpriteSheet(TextureManager::SpriteSheetNames::Player), IntRect(0, 0, 16, 16)));
	AddEntity(CollisionLayers::Players, player);

	player->SetPosition(128, 64);
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