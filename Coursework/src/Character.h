#pragma once
#include "Moveable.h"
#include "Projectile.h"
#include "ThrowingRock.h"
#include "irrKlang.h"
#include <memory>
class Character : public Moveable
{
private:
	float movementSpeed;
	float animationTimer;
	Texture* idle;
	Texture sword;
	Texture rock;
	std::unique_ptr<Projectile> swordSwing;
	std::unique_ptr<ThrowingRock> rockThrow;
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
	bool isAlive;
	bool swordSwinging;

	void Animate(float timeStep,  irrklang::ISoundEngine* soundEngine);
public:
	Character(float width, float height, float positionX, float positionY, float positionZ, float size, float movementSpeed);
	~Character();
	virtual void Move(float timeStep);
	virtual void Update(float timeStep, InputManager& inputManager, std::vector<std::vector<int>>& collisionMap, irrklang::ISoundEngine* soundEngine);
	void Init(float colour[3], Texture* texture, std::vector<std::vector<Texture*>> animations);
	inline Projectile& GetSword() { return *swordSwing; }
	inline ThrowingRock& GetRock() { return *rockThrow; }
	inline bool IsAlive() { return isAlive; }
	inline void SetAlive(bool a) { isAlive = a; }
};

