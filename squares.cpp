#include <iostream>
#include <SDL.h>

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Draw Squares";
const double ratio=2.2;


void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
 void drawSquares(double x, double y, double size, SDL_Renderer* renderer) {
        SDL_Rect filled_rect;
        filled_rect.x = x-size/2;
        filled_rect.y = y-size/2;
        filled_rect.w = size;
        filled_rect.h = size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
        SDL_RenderFillRect(renderer, &filled_rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderDrawRect(renderer, &filled_rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        //waitUntilKeyPressed();
    }
void draw(int n, double x, double y, double size, SDL_Renderer* renderer)
{
    if (n==0) return;

    cout<<"n = "<<n<<endl;
    drawSquares(x,y,size,renderer);

    draw(n-1, x-size/2, y-size/2, size/ratio, renderer);
    draw(n-1, x-size/2, y+size/2, size/ratio, renderer);
    draw(n-1, x+size/2, y-size/2, size/ratio, renderer);
    draw(n-1, x+size/2, y+size/2, size/ratio, renderer);
}
    int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    int n=5;
    double x=SCREEN_WIDTH/2, y=SCREEN_HEIGHT/2;
    double size=300;
    draw(n,x,y,size,renderer);
    waitUntilKeyPressed();
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




