#pragma once
#include <functional>
#include <cstdint>
#include <vector>

class IGameObject;
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;
//struct SDL_Event;

struct Color
{
	uint32_t r, g, b, a;

	Color() {}
	Color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) : r(red), g(green), b(blue), a(alpha) { }
};
class SDLFacade
{
public:
	SDLFacade(int offsetX = 50, int offsetY = 50, int width = 600, int height = 600);
	~SDLFacade();
	void SetTargetFPS(unsigned short target);
	SDL_Window * GetWindow() const;
	static SDLFacade * GetInstance();
	bool IsRunning();
	std::string GetRelativePath(const std::string & path = "") const;
	SDL_Texture * LoadTexture(const std::string & fileName);
	void DrawTexture(SDL_Texture * texture, int xOffset, int yOffset);
	void DrawTexture(SDL_Texture * texture, int xOffset, int yOffset, int width, int height);
	void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, int width = 2);
	void DrawRect(int startPosX, int startPosY, int width, int height, bool fill);
	void DrawCircle(int startPosX, int startPosY, int size, bool fill);
	void DrawText(const std::string & message, uint32_t offsetX, uint32_t offsetY);
	void StartTick();
	void EndTick();
	void RemoveTexture(SDL_Texture * texture);
	void SetColor(const Color & color);
	void SetFont(const std::string & fileName);
	void SetFontSize(int ptSize);
	void AddRenderable(IGameObject * renderable);
	uint32_t GetTimeSinceStartedMS() const;
	void Quit();

	private:
		std::vector<IGameObject *> mGameObjects;
		static SDLFacade * mInstance;

		SDL_Window * mWindow;
		SDL_Renderer * mRenderer;

		uint32_t mTimeMS;
		uint32_t mTargetDelayMS;
		uint32_t mStartCycleTimeMS;
		uint32_t mDeltaTimeMS; // The actual loop cycle time

		bool mIsRunning;

		Color mColor;
		//Color mTextBackgroundColor;
		TTF_Font * mFont;
		std::string mFontName;
		uint32_t mFontSize;
		//uint32_t mColor;
};

