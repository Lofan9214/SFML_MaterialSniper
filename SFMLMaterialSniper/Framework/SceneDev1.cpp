#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	rect1.setSize({ 200.f, 100.f });
	rect1.setFillColor(sf::Color::Blue);
	Utils::SetOrigin(rect1, Origins::MC);

	rect2.setSize({ 100.f,200.f });
	rect2.setFillColor(sf::Color::Green);
	Utils::SetOrigin(rect2, Origins::MC);

	Scene::Init();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetDefaultSize());
}

void SceneDev1::Enter()
{
	Scene::Enter();
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	rect1.rotate(100.f * dt);
	sf::Vector2f mousePos = ScreenToWorld(InputMgr::GetMousePosition());

	if (InputMgr::GetMouseButtonPressing(sf::Mouse::Left))
	{
		rect2.setPosition(mousePos);
	}

	if (Utils::CheckCollision(rect1, rect2))
	{
		rect2.setFillColor(sf::Color::Red);
	}
	else
	{
		rect2.setFillColor(sf::Color::Green);
	}
	
	if (InputMgr::GetMouseButtonPressing(sf::Mouse::Right))
	{
		if (Utils::PointInTransformBounds(rect1, rect1.getLocalBounds(), mousePos))
		{
			rect1.setFillColor(sf::Color::Red);
		}
		else
		{
			rect1.setFillColor(sf::Color::Blue);
		}
	}

}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(rect1);
	window.draw(rect2);
}