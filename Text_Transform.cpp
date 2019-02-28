#include "Text_Transform.h"



Text_Transform::Text_Transform() : Transform::Transform()
{
	font = TTF_OpenFont("BRLNSR.ttf", 24);
}

Text_Transform::Text_Transform(std::string name) : Transform::Transform(name)
{
	font = TTF_OpenFont("BRLNSR.ttf", 24);
}

Text_Transform::Text_Transform(Vector2 pos, Vector2 scale, std::string name) : Transform::Transform(pos, scale, name)
{
	font = TTF_OpenFont("BRLNSR.ttf", 24);
}


Text_Transform::~Text_Transform()
{
	delete font;
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void Text_Transform::SetText(std::string text)
{
	textToDisplay = text;
}

void Text_Transform::Render(SDL_Renderer* renderer)
{
	
	if(font == nullptr)
		font = TTF_OpenFont("BRLNSR.ttf", 24);
	
	SDL_Color col = { color->red, color->green, color->blue };

	surfaceMessage = TTF_RenderText_Solid(font, textToDisplay.c_str(), col);
	message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_RenderCopy(renderer, message, NULL, &GetRect());

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
	
}