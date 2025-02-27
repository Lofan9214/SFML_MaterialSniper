#pragma once

class WindIcon : public GameObject
{
public:
	enum class Type
	{
		Cone,
		Arrow,
	};
protected:

	Type type;

	sf::Sprite body;
	Animator animator;

	int speed;

public:
	WindIcon(const std::string& name = "");
	~WindIcon() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetOffset(const sf::Vector2f& disp) override;
	void SetFlipX(bool flipX) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void SetType(Type type);

	void SetWindSpeed(int speed);
};
