#include "Text_Transform.h"
#include "SDL_ttf.h"


Text_Transform::Text_Transform() : Transform::Transform()
{}

Text_Transform::Text_Transform(std::string name) : Transform::Transform(name)
{}

Text_Transform::Text_Transform(Vector2 pos, Vector2 scale, std::string name) : Transform::Transform(pos, scale, name)
{}


Text_Transform::~Text_Transform()
{
}

void Text_Transform::SetText(std::string text)
{
	textToDisplay = text;
}

void Text_Transform::Render(SDL_Renderer* renderer)
{
	
	TTF_Font* font = TTF_OpenFont("BRLNSR.ttf", 24);
	SDL_Color col = { color->red, color->green, color->blue };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, textToDisplay.c_str(), col);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_RenderCopy(renderer, message, NULL, &GetRect());

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
	
}