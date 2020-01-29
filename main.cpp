#include <iostream>
#include <windows.h>
#include <SDL2/SDL.h>
#include <fstream>
#include "alfabet.h"
#include "numere.h"
#include <cstdlib>
#include <ctime>
using namespace std;
int game = 1,lives = 3,judet,nr,textx = 120,texty = 300-7;
int score = 0,high_score,aux,li;
char c1,c2,c3,state;
string scurt[256],raspuns[256],try_text;

ifstream fin("scurt.txt");
ifstream asdi("high_score.txt");
ifstream save("save_file.txt");
ifstream fout("save_file.txt");

SDL_Surface* background = SDL_LoadBMP("other/back.bmp");
SDL_Surface* title = SDL_LoadBMP("other/title.bmp");
SDL_Surface* exit_icon = SDL_LoadBMP("other/exit.bmp");
SDL_Surface* start = SDL_LoadBMP("other/start.bmp");
SDL_Surface* bye = SDL_LoadBMP("other/bye.bmp");
SDL_Surface* img1 = SDL_LoadBMP("other/img1.bmp");
SDL_Surface* img2 = SDL_LoadBMP("other/img2.bmp");
SDL_Surface* cuv_img = SDL_LoadBMP("other/cuv.bmp");
SDL_Surface* plate = SDL_LoadBMP("other/plate.bmp");
SDL_Surface* under = SDL_LoadBMP("other/under.bmp");
SDL_Surface* verify = SDL_LoadBMP("other/verify.bmp");
SDL_Surface* live = SDL_LoadBMP("other/text.bmp");
SDL_Surface* good = SDL_LoadBMP("other/corect.bmp");
SDL_Surface* bad = SDL_LoadBMP("other/gresit.bmp");
SDL_Surface* ded = SDL_LoadBMP("other/ded.bmp");
SDL_Surface* scor = SDL_LoadBMP("other/score.bmp");
SDL_Surface* high = SDL_LoadBMP("other/score_max.bmp");
SDL_Surface* nani = SDL_LoadBMP("other/intrebare.bmp");
SDL_Surface* yes = SDL_LoadBMP("other/yes.bmp");
SDL_Surface* no = SDL_LoadBMP("other/no.bmp");

void Input(SDL_Window *window, SDL_Surface *windowSurface);
void Game(SDL_Window *window, SDL_Surface *windowSurface);
void Scrie(int x, int y, string text, SDL_Window *window, SDL_Surface *windowSurface);
void ScrieNr(int x, int y, int nr, SDL_Window *window, SDL_Surface *windowSurface);
void JudetNou(SDL_Window *window, SDL_Surface *windowSurface);
void ShowLives(SDL_Window *window, SDL_Surface *windowSurface);
void Verify(SDL_Window *window, SDL_Surface *windowSurface);
void Clear(SDL_Window *window, SDL_Surface *windowSurface);
void Win(SDL_Window *window, SDL_Surface *windowSurface);
void Lose(SDL_Window *window, SDL_Surface *windowSurface);
void Bye(SDL_Window *window, SDL_Surface *windowSurface);
char to_char(int index);

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}

int main(int argc, char* argv[]){
    Stealth();
    asdi >> high_score;
    asdi.close();
    for(int i = 1; i <= 42; i++){
        fin >> scurt[i] >> raspuns[i];
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "SDL Error: " << SDL_GetError() << "\n";
    }
    SDL_Window *window = SDL_CreateWindow("|-*Judet Game*-|",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          700,
                                          600,
                                          SDL_WINDOW_RESIZABLE);
    SDL_Rect rect;
    SDL_Surface *windowSurface = SDL_GetWindowSurface(window);
    Uint32 color = SDL_MapRGB(windowSurface->format, 133, 193, 233);
    SDL_FillRect(windowSurface, NULL, color);
    SDL_UpdateWindowSurface(window);
    rect.x = 0; rect.y = 0;
    SDL_BlitSurface(background, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    save >> state;
    save >> aux;
    save >> li;
    cout << state << "\n";
    cout << aux << "\n";
    cout << li << "\n";
    score = aux;
    lives = li;
    if(lives != 0){
        cout << "AAAA\n";
        game = 0;
        rect.x = 270; rect.y = 70;
        SDL_BlitSurface(title, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
        rect.x = 170; rect.y = 140;
        SDL_BlitSurface(nani, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
        rect.x = 110; rect.y = 280;
        SDL_BlitSurface(img1, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
        rect.x = 110; rect.y = 410;
        SDL_BlitSurface(img2, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
        rect.x = 180; rect.y = 250;
        SDL_BlitSurface(yes, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
        rect.x = 180; rect.y = 380;
        SDL_BlitSurface(no, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
    }else{
        lives = 3;
        rect.x = 270; rect.y = 100;
        SDL_BlitSurface(title, NULL, windowSurface, &rect);
        rect.x = 110; rect.y = 280;
        SDL_BlitSurface(img1, NULL, windowSurface, &rect);
        rect.x = 180; rect.y = 250;
        SDL_BlitSurface(start, NULL, windowSurface, &rect);
        rect.x = 110; rect.y = 410;
        SDL_BlitSurface(img2, NULL, windowSurface, &rect);
        rect.x = 180; rect.y = 380;
        SDL_BlitSurface(bye, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
    }
    while(1){
        Input(window, windowSurface);
    }
    Sleep(2000);
    return 0;
}

void Input(SDL_Window *window, SDL_Surface *windowSurface){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            if(game == 0){
                switch(event.key.keysym.sym){
                    case SDLK_1:
                        game = 2;
                        lives = li;
                        score = aux;
                        Game(window, windowSurface);
                        break;
                    case SDLK_2:
                        lives = 3;
                        score = 0;
                        game = 2;
                        Game(window, windowSurface);
                        break;
                    default:
                        break;
                }
            }else if(game == 1){
                switch(event.key.keysym.sym){
                    case SDLK_1:
                        game = 2;
                        Game(window, windowSurface);
                        break;
                    case SDLK_2:
                        SDL_Quit();
                        exit(0);
                        break;
                    default:
                        break;
                }
            }else if(game == 2){
                SDL_Rect rect;
                SDL_Surface* dash = SDL_LoadBMP("letters/dash.bmp");
                /// SDLK_BACKQUOTE
                rect.x = textx;
                rect.y = texty;
                if(texty == 393 && textx == 520){
                    Verify(window, windowSurface);
                }
                switch(event.key.keysym.sym){
                    case SDLK_RETURN:
                        Verify(window, windowSurface);
                        break;
                    case SDLK_MINUS:
                        try_text += '-';rect.x = textx; rect.y = texty;SDL_BlitSurface(dash, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_a:
                        try_text += 'a';rect.x = textx; rect.y = texty;SDL_BlitSurface(a, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_b:
                        try_text += 'b';rect.x = textx; rect.y = texty;SDL_BlitSurface(b, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_c:
                        try_text += 'c';rect.x = textx; rect.y = texty;SDL_BlitSurface(c, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_d:
                        try_text += 'd';rect.x = textx; rect.y = texty;SDL_BlitSurface(d, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_e:
                        try_text += 'e';rect.x = textx; rect.y = texty+5;SDL_BlitSurface(e, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_f:
                        try_text += 'f';rect.x = textx; rect.y = texty;SDL_BlitSurface(f, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_g:
                        try_text += 'g';rect.x = textx; rect.y = texty;SDL_BlitSurface(g, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_h:
                        try_text += 'h';rect.x = textx; rect.y = texty;SDL_BlitSurface(h, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_i:
                        try_text += 'i';rect.x = textx; rect.y = texty;SDL_BlitSurface(i, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_j:
                        try_text += 'j';rect.x = textx; rect.y = texty;SDL_BlitSurface(j, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_k:
                        try_text += 'k';rect.x = textx; rect.y = texty;SDL_BlitSurface(k, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_l:
                        try_text += 'l';rect.x = textx; rect.y = texty;SDL_BlitSurface(l, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_m:
                        try_text += 'm';rect.x = textx; rect.y = texty;SDL_BlitSurface(m, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_n:
                        try_text += 'n';rect.x = textx; rect.y = texty;SDL_BlitSurface(n, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_o:
                        try_text += 'o';rect.x = textx; rect.y = texty;SDL_BlitSurface(o, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_p:
                        try_text += 'p';rect.x = textx; rect.y = texty;SDL_BlitSurface(p, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_q:
                        try_text += 'q';rect.x = textx; rect.y = texty;SDL_BlitSurface(q, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_r:
                        try_text += 'r';rect.x = textx; rect.y = texty;SDL_BlitSurface(r, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_s:
                        try_text += 's';rect.x = textx; rect.y = texty;SDL_BlitSurface(s, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_t:
                        try_text += 't';rect.x = textx; rect.y = texty;SDL_BlitSurface(t, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_u:
                        try_text += 'u';rect.x = textx; rect.y = texty+5;SDL_BlitSurface(u, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_v:
                        try_text += 'v';rect.x = textx; rect.y = texty;SDL_BlitSurface(v, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_w:
                        try_text += 'w';rect.x = textx; rect.y = texty;SDL_BlitSurface(w, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_x:
                        try_text += 'x';rect.x = textx; rect.y = texty;SDL_BlitSurface(xi, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_y:
                        try_text += 'y';rect.x = textx; rect.y = texty;SDL_BlitSurface(yi, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty >= 300 && textx >= 520){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    case SDLK_z:
                        try_text += 'z';rect.x = textx; rect.y = texty;SDL_BlitSurface(z, NULL, windowSurface, &rect);if(textx >= 520){textx = 120;texty += 100;}else if(texty > 400-7){Verify(window, windowSurface);}else{textx += 50;}
                        break;
                    default:
                        break;
                }
                SDL_UpdateWindowSurface(window);
            }
        }else if(event.type == SDL_QUIT){
            if(game == 1){
                SDL_Quit();
                exit(0);
            }
            system("echo 1 > save_file.txt");
            int ds = 0;
            int v[5] = {0, 0, 0, 0, 0};
            int c = score;
            while(c != 0){
                ds++;
                v[ds] = c%10;
                c /= 10;
            }
            string text = "echo ";
            for(int i = ds; i >= 1; i--){
                text += to_char(v[i]);
            }
            text += " >> save_file.txt";
            if(score != 0){
                system(text.c_str());
            }else{
                system("echo 0 >> save_file.txt");
            }
            ds = 0;
            int vi[5] = {0, 0, 0, 0, 0};
            c = lives;
            while(c != 0){
                ds++;
                vi[ds] = c%10;
                c /= 10;
            }
            text = "echo ";
            for(int i = ds; i >= 1; i--){
                text += to_char(vi[i]);
            }
            text += " >> save_file.txt";
            system(text.c_str());
            SDL_Quit();
            exit(0);
        }
    }
}

char to_char(int index){
    if(index == 0){return '0';}
    if(index == 1){return '1';}
    if(index == 2){return '2';}
    if(index == 3){return '3';}
    if(index == 4){return '4';}
    if(index == 5){return '5';}
    if(index == 6){return '6';}
    if(index == 7){return '7';}
    if(index == 8){return '8';}
    if(index == 9){return '9';}
    return '0';
}

void Verify(SDL_Window *window, SDL_Surface *windowSurface){
    textx = 120; texty = 300-7;
    if(try_text.compare(raspuns[judet]) == 0){
        score++;
        int ds = 0;
        int v[5] = {0, 0, 0, 0, 0};
        int c = score;
        while(c != 0){
            ds++;
            v[ds] = c%10;
            c /= 10;
        }
        string text = "echo ";
        for(int i = ds; i >= 1; i--){
            text += to_char(v[i]);
        }
        text += " > high_score.txt";
        if(score > high_score){
            system(text.c_str());
            high_score = score;
        }
        Win(window, windowSurface);
    }else{
        if(score >= 1){
            score--;
        }
        lives--;
        if(lives == 0){
            Bye(window, windowSurface);
        }else{
            Lose(window, windowSurface);
        }
    }
    try_text = "";
    Clear(window, windowSurface);
}

void Game(SDL_Window *window, SDL_Surface *windowSurface){
    Clear(window, windowSurface);
    while(1){
        Input(window, windowSurface);
    }
}

void Win(SDL_Window *window, SDL_Surface *windowSurface){
    SDL_Rect rect;
    rect.x = 0; rect.y = 0;
    SDL_BlitSurface(good, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    Sleep(2000);
}

void Lose(SDL_Window *window, SDL_Surface *windowSurface){
    system("echo 0 > save_file.txt");
    SDL_Rect rect;
    rect.x = 0; rect.y = 0;
    SDL_BlitSurface(bad, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    Sleep(2000);
}

void Bye(SDL_Window *window, SDL_Surface *windowSurface){
    system("echo 0 > save_file.txt");
    SDL_Rect rect;
    rect.x = 0; rect.y = 0;
    SDL_BlitSurface(ded, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    Sleep(2000);
    SDL_UpdateWindowSurface(window);
    rect.x = 0; rect.y = 0;
    SDL_BlitSurface(background, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 270; rect.y = 100;
    SDL_BlitSurface(title, NULL, windowSurface, &rect);
    rect.x = 110; rect.y = 280;
    SDL_BlitSurface(img1, NULL, windowSurface, &rect);
    rect.x = 180; rect.y = 250;
    SDL_BlitSurface(start, NULL, windowSurface, &rect);
    rect.x = 110; rect.y = 410;
    SDL_BlitSurface(img2, NULL, windowSurface, &rect);
    rect.x = 180; rect.y = 380;
    SDL_BlitSurface(bye, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    game = 1;
    lives = 3;
    score = 0;
    while(1){
        Input(window, windowSurface);
    }
}

void Clear(SDL_Window *window, SDL_Surface *windowSurface){
    SDL_Rect rect;
    rect.x = 0; rect.y = 0;
    SDL_BlitSurface(background, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 480; rect.y = -15;
    SDL_BlitSurface(high, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 480; rect.y = 35;
    SDL_BlitSurface(scor, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 260; rect.y = 20;
    SDL_BlitSurface(title, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 160; rect.y = 80;
    SDL_BlitSurface(plate, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 180; rect.y = 200;
    SDL_BlitSurface(cuv_img, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 120; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 170; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 220; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 270; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 320; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 370; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 420; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 470; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 520; rect.y = 300;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 120; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 170; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 220; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 270; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 320; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 370; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 420; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 470; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 520; rect.y = 400;
    SDL_BlitSurface(under, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 160; rect.y = 500;
    SDL_BlitSurface(verify, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    JudetNou(window, windowSurface);
    ShowLives(window, windowSurface);
    ScrieNr(620, 0, high_score, window, windowSurface);
    ScrieNr(560, 35, score, window, windowSurface);
}

void ShowLives(SDL_Window *window, SDL_Surface *windowSurface){
    SDL_Rect rect;
    rect.x = 0;
    rect.y = -30;
    SDL_BlitSurface(live, NULL, windowSurface, &rect);
    SDL_UpdateWindowSurface(window);
    rect.x = 300;
    rect.y = 10;
    int x = 110;
    for(int i = 1; i <= lives; i++){
        rect.x = x;
        SDL_BlitSurface(exit_icon, NULL, windowSurface, &rect);
        SDL_UpdateWindowSurface(window);
        x += 30;
    }
}

void JudetNou(SDL_Window *window, SDL_Surface *windowSurface){
    int prev = judet;
    do{
        judet = (rand()%43);
    }while(judet == prev);
    nr = (rand()%100);
    do{
        c1 = (char)((rand()%(90-65+1))+64);
    }while(c1 == '@');
    do{
        c2 = (char)((rand()%(90-65+1))+64);
    }while(c2 == '@');
    do{
        c3 = (char)((rand()%(90-65+1))+64);
    }while(c3 == '@');
    string test = " ";
    test += c1;
    test += c2;
    test += c3;
    Scrie(230, 100, scurt[judet], window, windowSurface);
    Scrie(350, 100, test, window, windowSurface);
    ScrieNr(310, 105, nr, window, windowSurface);
}

void ScrieNr(int x, int y, int nr, SDL_Window *window, SDL_Surface *windowSurface){
    int ds = 0;
    SDL_Rect recT;
    recT.y = y;
    recT.x = x;
    int v[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if(nr == 0){
        ds++;
        v[ds] = 0;
    }
    int c = nr;
    while(c != 0){
        ds++;
        v[ds] = c%10;
        cout << v[ds] << "\n";
        c /= 10;
    }
    SDL_Surface* num_0 = SDL_LoadBMP("numbers/0.bmp");
    SDL_Surface* num_1 = SDL_LoadBMP("numbers/1.bmp");
    SDL_Surface* num_2 = SDL_LoadBMP("numbers/2.bmp");
    SDL_Surface* num_3 = SDL_LoadBMP("numbers/3.bmp");
    SDL_Surface* num_4 = SDL_LoadBMP("numbers/4.bmp");
    SDL_Surface* num_5 = SDL_LoadBMP("numbers/5.bmp");
    SDL_Surface* num_6 = SDL_LoadBMP("numbers/6.bmp");
    SDL_Surface* num_7 = SDL_LoadBMP("numbers/7.bmp");
    SDL_Surface* num_8 = SDL_LoadBMP("numbers/8.bmp");
    SDL_Surface* num_9 = SDL_LoadBMP("numbers/9.bmp");
    SDL_Surface* nrs[256];
    nrs[0] = num_0;
    nrs[1] = num_1;
    nrs[2] = num_2;
    nrs[3] = num_3;
    nrs[4] = num_4;
    nrs[5] = num_5;
    nrs[6] = num_6;
    nrs[7] = num_7;
    nrs[8] = num_8;
    nrs[9] = num_9;
    for(int i = 1; i <= ds; i++){
        recT.x = x;
        SDL_BlitSurface(nrs[v[i]], NULL, windowSurface, &recT);
        SDL_UpdateWindowSurface(window);
        x += 30;
    }
}
void Scrie(int x, int y, string text, SDL_Window *window, SDL_Surface *windowSurface){SDL_Rect recT;recT.y = y;SDL_Surface* dash = SDL_LoadBMP("letters/dash.bmp");alf[97-32] = a;alf[98-32] = b;alf[99-32] = c;alf[100-32] = d;alf[101-32] = e;alf[102-32] = f;alf[103-32] = g;alf[104-32] = h;alf[105-32] = i;alf[106-32] = j;alf[107-32] = k;alf[108-32] = l;alf[109-32] = m;alf[110-32] = n;alf[111-32] = o;alf[112-32] = p;alf[113-32] = q;alf[114-32] = r;alf[115-32] = s;alf[116-32] = t;alf[117-32] = u;alf[118-32] = v;alf[119-32] = w;alf[120-32] = xi;alf[121-32] = yi;alf[122-32] = z;alf[45] = dash;for(string::iterator it = text.begin(); it != text.end(); it++){if((int)*it == 71 || (int)*it == 61 || (int)*it == 85){recT.y = y+5;recT.x = x;SDL_BlitSurface(alf[(int)*it], NULL, windowSurface, &recT);SDL_UpdateWindowSurface(window);recT.y = y;}else{recT.x = x;SDL_BlitSurface(alf[(int)*it], NULL, windowSurface, &recT);SDL_UpdateWindowSurface(window);}x += 35;}}
