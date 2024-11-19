#pragma once
#include "SaveData.h"

class Gun;
class Cartridge;

class Player : public GameObject
{
public:
	enum class Status
	{
		Ready,
		Fire,
		Reloading,
	};

protected:

	Status status;

	Animator animator;
	sf::Sprite body;
	SkillData skillData;

	Gun* gun;

	int ammo;
	int magazine;

	float breath;
	float maxBreath;
	bool breathover;

	float fireTimer;
	float reloadTimer;

	const sf::Vector2f muzzlePos = sf::Vector2f(680.f, 248.5f);
	const sf::Vector2f ejectionPos = sf::Vector2f(446.f, 244.f);

	std::function<Cartridge* ()> TakeCartridge;

public:
	Player(const std::string& name = "");
	~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateReady(float dt);
	void UpdateFire(float dt);
	void UpdateReload(float dt);
	void UpdateBreathStatus(float dt);
	void Draw(sf::RenderTarget& window) override;

	void SetStatus(Status status);

	int GetAmmo() const { return ammo; }
	float GetBreath() const { return breath / maxBreath; }
	sf::Vector2f GetMuzzlePos() const { return body.getTransform().transformPoint(muzzlePos); }
};
