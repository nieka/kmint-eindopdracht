#include "SDLFacade.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

SDLFacade * SDLFacade::mInstance;
SDLFacade::SDLFacade(int offsetX, int offsetY, int width, int height)
	: mTargetDelayMS(1000 / 60),
	mStartCycleTimeMS(0),
	mDeltaTimeMS(0),
	mTimeMS(0),
	mIsRunning(true),
	mFontSize(12),
	mFontName("")
	//mTextBackgroundColor(0xFF,0xFF,0xFF,0xFF)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		LOG("SDL init failed");
		return;
	}

	mWindow = SDL_CreateWindow("Bee Mania", offsetX, offsetY, width, height, SDL_WINDOW_SHOWN);
	if (!mWindow)
	{
		LOG(SDL_GetError());
		return;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		LOG(SDL_GetError());
		SDL_DestroyWindow(mWindow);
		return;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!IMG_Init(imgFlags) & imgFlags)
	{
		LOG(IMG_GetError());
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		return;
	}

	if (TTF_Init() < 0)
	{
		LOG(TTF_GetError());
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		return;
	}

	//mFont = TTF_OpenFont(GetRelativePath("Resources/OpenSans-Regular.ttf").c_str(), mFontSize);
	SetFontSize(12);
	SetFont("OpenSans-Regular.ttf");

	mInstance = this;
	mGameObjects.reserve(32);
}


SDLFacade::~SDLFacade()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	TTF_CloseFont(mFont);
	TTF_Quit();
	SDL_Quit();
}

SDL_Window * SDLFacade::GetWindow() const
{
	return mWindow;
}

SDLFacade * SDLFacade::GetInstance()
{
	if (!mInstance)
	{
		new SDLFacade();
	}

	return mInstance;
}

bool SDLFacade::IsRunning()
{
	return mIsRunning;
}

std::string SDLFacade::GetRelativePath(const std::string & path) const
{
	std::string basePath = SDL_GetBasePath();
	return basePath + ".." + PATH_SEP + path; //  + PATH_SEP
											  //size_t pos = basePath.rfind("Debug");
											  //return basePath.substr(0, basePath.rfind("Debug")) + path + PATH_SEP; //  + "resources" + PATH_SEP
}

SDL_Texture * SDLFacade::LoadTexture(const std::string & fileName)
{
	const std::string path = GetRelativePath("Resources" PATH_SEP + fileName);
	SDL_Surface * surface = IMG_Load(path.c_str());
	if (surface)
	{
		SDL_Texture * texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		if (!texture)
		{
			LOG("Couldn't load texture: " + path);
		}
		return texture;
	}

	LOG("SDL Error, couldn't load BMP: " + path);
	return nullptr;
}

void SDLFacade::DrawTexture(SDL_Texture * texture, int xOffset, int yOffset)
{
	SDL_Rect rect = { xOffset, yOffset };

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(mRenderer, texture, &rect, &rect);
}
void SDLFacade::DrawTexture(SDL_Texture * texture, int xOffset, int yOffset, int width, int height)
{
	SDL_Rect rect = { xOffset - (width / 2), yOffset - (height / 2), width, height };

	//SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(mRenderer, texture, NULL, &rect);
}

void SDLFacade::StartTick()
{
	SDL_RenderClear(mRenderer);
	mStartCycleTimeMS = SDL_GetTicks();

	//SDL_Event ev;
	//while (SDL_PollEvent(&ev) != 0)
	//{
	//	if (ev.type == SDL_QUIT)
	//	{
	//		mIsRunning = false;
	//	}
	//}
}

void SDLFacade::EndTick()
{
	SDL_RenderPresent(mRenderer);
	//SDL_UpdateWindowSurface(mWindow);

	mTimeMS = SDL_GetTicks();
	mDeltaTimeMS = mTimeMS - mStartCycleTimeMS;
	if (((int32_t)mTargetDelayMS - (int32_t)mDeltaTimeMS) > 0)
	{
		SDL_Delay(mTargetDelayMS - mDeltaTimeMS);
	}
}

void SDLFacade::SetTargetFPS(unsigned short target)
{
	mTargetDelayMS = 1000 / target;
}

void SDLFacade::RemoveTexture(SDL_Texture * texture)
{
	SDL_DestroyTexture(texture);
}

void SDLFacade::DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, int width)
{
	thickLineRGBA(mRenderer, startPosX, startPosY, endPosX, endPosY, width, mColor.r, mColor.g, mColor.b, mColor.a);
}

void SDLFacade::SetColor(const Color & color)
{
	mColor = color;
	SDL_SetRenderDrawColor(mRenderer, mColor.r, mColor.g, mColor.b, mColor.a);
}

void SDLFacade::DrawRect(int startPosX, int startPosY, int width, int height, bool fill)
{
	SDL_Rect rect = { startPosX, startPosY, width, height };

	if (fill)
	{
		SDL_RenderFillRect(mRenderer, &rect);
	}
	else
	{
		SDL_RenderDrawRect(mRenderer, &rect);
	}
}

void SDLFacade::DrawCircle(int startPosX, int startPosY, int size, bool fill) {
	if (fill) {
		filledCircleRGBA(mRenderer, startPosX, startPosY, size, mColor.r, mColor.g, mColor.b, mColor.a);
	}
	else {
		circleRGBA(mRenderer, startPosX, startPosY, size, mColor.r, mColor.g, mColor.b, mColor.a);
	}
}

void SDLFacade::AddRenderable(IGameObject * renderable)
{
	mGameObjects.push_back(renderable);
}

uint32_t SDLFacade::GetTimeSinceStartedMS() const
{
	return mTimeMS;
}

void SDLFacade::DrawText(const std::string & message, uint32_t offsetX, uint32_t offsetY)
{
	SDL_Color color = { mColor.r, mColor.g, mColor.b, mColor.a };
	//SDL_Color bgColor = { mTextBackgroundColor.r, mTextBackgroundColor.g, mTextBackgroundColor.b, mTextBackgroundColor.a };

	SDL_Surface * surface = TTF_RenderText_Blended(mFont, message.c_str(), color);
	if (surface)
	{
		SDL_Texture * texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (texture)
		{
			DrawTexture(texture, offsetX, offsetY, surface->w, surface->h);
		}
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
}

void SDLFacade::SetFontSize(int ptSize)
{
	mFontSize = ptSize;

	if (mFontName != "")
	{
		SetFont(mFontName);
	}
}

void SDLFacade::SetFont(const std::string & filename)
{
	if (mFont)
	{
		TTF_CloseFont(mFont);
	}

	mFontName = filename;
	mFont = TTF_OpenFont(GetRelativePath("Resources/" + filename).c_str(), mFontSize);
}

void SDLFacade::Quit()
{
	mIsRunning = false;
}
