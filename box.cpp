#include <iostream>
#include <SDL.h>

using namespace std;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

struct Box {
    int x,y;
    int size=10;
    int stepX=0;
    int stepY=0;
    Box(int _x, int _y):x(_x), y(_y){}

    void render(SDL_Renderer* renderer) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = size;
        filled_rect.h = size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
        SDL_RenderFillRect(renderer, &filled_rect);

    }

    void move()
    {
        x+=stepX;
        y+=stepY;

    }
     void turnLeft()
    {
        stepX=-5; stepY=0;
    }
     void turnRight()
    {
        stepX=5; stepY=0;
    }
     void turnDown()
    {
        stepY=5; stepX=0;
    }
     void turnUp()
    {
        stepY=-5; stepX=0;
    }

    bool inside(int minX, int minY, int maxX, int maxY)
    {
        return (minX<=x && minY<=y && x+size<=maxX && y+size<=maxY);
    }
};
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);


    int main(int argc, char* argv[])
{
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Box box(10, 10);

    while (box.inside(0 , 0 , SCREEN_WIDTH, SCREEN_HEIGHT)) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderClear(renderer);
    box.render(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(20);
      box.move();
     if ( SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: break;
        		case SDLK_LEFT: box.turnLeft();
        			break;
            	case SDLK_RIGHT: box.turnRight();
            		break;
            	case SDLK_DOWN: box.turnDown();
					break;
            	case SDLK_UP: box.turnUp();
            		break;
        		default: break;
			}
        }
    //waitUntilKeyPressed();
    }
    //waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;

}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

