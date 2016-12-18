#pragma once
class Vector2D
{
public:
	Vector2D();
	~Vector2D();
	void setX(float x);
	void sety(float y);
	float getX() const;
	float getY() const;
	Vector2D multiply(Vector2D vector, int waarde);
	Vector2D Add(Vector2D vector, Vector2D vector2);
	Vector2D sub(Vector2D vector, Vector2D vector2);
	void div(float value);
	void normalise();
	float dist(Vector2D pos1, Vector2D pos2);
	float mag();
	void limit(float amount);
private:
	float _x;
	float _y;
};

