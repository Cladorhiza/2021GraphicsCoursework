#pragma once
#include "Moveable.h"
#include "Projectile.h"
class Character : public Moveable
{
private:
	float movementSpeed;
	float animationTimer;
	Texture* idle;
	Texture sword;
	std::unique_ptr<Projectile> swordSwing;
	std::vector<Texture*> leftAnimation;
	std::vector<Texture*> rightAnimation;
	std::vector<Texture*> upAnimation;
	std::vector<Texture*> downAnimation;
	int animationCounter;
	bool isMoving;
	bool facingLeft;
	bool facingRight;
	bool facingUp;
	bool facingDown;
	bool directionChanged;

	void Animate(float timeStep);
public:
	Character(float width, float height, float positionX, float positionY, float positionZ, float size, float movementSpeed);
	~Character();
	virtual void Move(float timeStep);
	virtual void Update(float timeStep, InputManager& inputManager);
	void SwordAttack();
	void Init(float colour[3], Texture* texture, std::vector<std::vector<Texture*>> animations);
	inline Projectile& GetSword() { return *swordSwing; }
	
};

