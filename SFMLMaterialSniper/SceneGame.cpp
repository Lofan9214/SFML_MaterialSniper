#include "stdafx.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "CircleView.h"
#include "Drum.h"
#include "RoundBoard.h"
#include "Bottle.h"
#include "UiHud.h"
#include "Player.h"
#include "GlassShard.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	SpriteGo* bg = AddGo(new SpriteGo("graphics/Stage1Background.jpg", "background"));

	bg->SetSortingLayer(SortingLayers::Background);
	bg->SetOrigin(Origins::MC);
	bullet = AddGo(new Bullet("bullet"));

	uiHud = AddGo(new UiHud("uiHud"));

	scopeview = AddGo(new CircleView("scope"));
	scopeview->SetZoom(5.f);
	scopeview->SetCircleRadius(150.f);
	player = AddGo(new Player("player"));
	player->SetCircleView(scopeview);

	Scene::Init();
}

void SceneGame::Enter()
{
	Scene::Enter();
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	SOUND_MGR.PlayBgm("sounds/bgm/stage01.mp3");

	currentStatus = Status::Awake;

	sf::Vector2f screensize = FRAMEWORK.GetWindowSizef();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(screensize);

	uiView.setCenter(screensize * 0.5f);
	uiView.setSize(screensize);

	uiHud->SetWind(wind);
	uiHud->SetAmmo(player->GetAmmo());
	uiHud->SetBreath(player->GetBreath());

	stage = 1;
	difficulty = 1;
	wave = 0;
	day = true;
}

void SceneGame::Exit()
{
	ClearTookObject();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneGame::Status::InGame:
		UpdateInGame(dt);
		break;
	case SceneGame::Status::Interlude:
		UpdateInterlude(dt);
		break;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F9))
	{
		Variables::isDrawHitBox = !Variables::isDrawHitBox;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::SetStatus(Status status)
{
	Status prev = currentStatus;
	currentStatus = status;

	switch (currentStatus)
	{
	case SceneGame::Status::Awake:
		break;
	case SceneGame::Status::InGame:
		SpawnWave();
		//SpawnDrum({ 300.f,0.f,700.f });
		//SpawnRoundBoard({ -300.f,0.f,700.f });
		//SpawnBottle({ 0.f,0.f,700.f });
		break;
	case SceneGame::Status::Interlude:
		interludeTimer = 0.f;
		break;
	}
}

void SceneGame::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::InGame);
	}
}

void SceneGame::UpdateInGame(float dt)
{
	uiHud->SetWind(wind);
	uiHud->SetAmmo(player->GetAmmo());
	uiHud->SetBreath(player->GetBreath());

	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad4))
	{
		wind -= 1.f;
		bullet->SetWind({ wind,0.f,0.f });
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad6))
	{
		wind += 1.f;
		bullet->SetWind({ wind,0.f,0.f });
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		ClearTookObject();
		SetStatus(Status::Awake);
	}
}

void SceneGame::UpdateInterlude(float dt)
{
	interludeTimer += dt;
	if (interludeTimer > 3.f)
	{

	}
}

GlassShard* SceneGame::TakeGlassShard()
{
	GlassShard* glassShard = glassShardPool.Take();
	glassShards.push_back(glassShard);
	AddGo(glassShard);
	return glassShard;
}

void SceneGame::ReturnGlassShard(GlassShard* glassShard)
{
	RemoveGo(glassShard);
	glassShardPool.Return(glassShard);
	glassShards.remove(glassShard);
}

void SceneGame::ClearTookObject()
{
	for (auto glassShard : glassShards)
	{
		RemoveGo(glassShard);
		glassShardPool.Return(glassShard);
	}
	glassShards.clear();

	for (auto drum : drums)
	{
		RemoveGo(drum);
		drumPool.Return(drum);
	}
	drums.clear();

	for (auto bottle : bottles)
	{
		RemoveGo(bottle);
		bottlePool.Return(bottle);
	}
	bottles.clear();

	for (auto roundboard : roundboards)
	{
		RemoveGo(roundboard);
		roundboardPool.Return(roundboard);
	}
	roundboards.clear();
}

void SceneGame::SpawnWave()
{
	std::string stagestr;
	stagestr = std::to_string(stage) + std::to_string(difficulty) + (day ? "D" : "N");
	const auto& data = STAGE_TABLE->Get(stagestr);

	auto find = data.waves.find(wave);
	if (find == data.waves.end())
	{
		return;
	}
	for (auto& datum : find->second)
	{
		if (datum.type == "DRUM")
		{
			SpawnDrum(datum.position);
		}
		else if (datum.type == "BOTTLE")
		{
			SpawnBottle(datum.position);
		}
		else if (datum.type == "ROUNDBOARD")
		{
			SpawnRoundBoard(datum.position);
		}
	}
}

void SceneGame::SpawnDrum(const sf::Vector3f& pos)
{
	Drum* drum = drumPool.Take();
	drums.push_back(drum);
	AddGo(drum);
	drum->SetPosition(pos);
}

void SceneGame::SpawnBottle(const sf::Vector3f& pos)
{
	Bottle* bottle = bottlePool.Take();
	bottles.push_back(bottle);
	AddGo(bottle);
	bottle->SetPosition(pos);
}

void SceneGame::SpawnRoundBoard(const sf::Vector3f& pos)
{
	RoundBoard* roundboard = roundboardPool.Take();
	roundboards.push_back(roundboard);
	AddGo(roundboard);
	roundboard->SetPosition(pos);
}
