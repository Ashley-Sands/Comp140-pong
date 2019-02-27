#pragma once
#include "Transform.h"
class Text_Transform : public Transform
{
public:
	Text_Transform();
	Text_Transform(std::string name);
	Text_Transform(Vector2 pos, Vector2 scale, std::string name);

	~Text_Transform();

	void SetText(std::string text);

	virtual void Render(SDL_Renderer* renderer) override;

private:
	std::string textToDisplay;
};

