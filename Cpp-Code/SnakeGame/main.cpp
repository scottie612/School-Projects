#include <iostream>
#include <windows.h>

using namespace std;
bool gameover = false;
int width = 40;
int height = 20;
int x, y, prevX, prevY, Fruitx, Fruity;
int tailsize = 0;
int tailx[100];
int taily[100];


int score = 0;

void Setup() {
    x = width / 2;
    y = height / 2;
    Fruitx = rand() % width;
    Fruity = rand() % height;
    for (int i = 0; i < 100; i++) {
        tailx[i] = 0;
        taily[i] = 0;
    }

}


void Draw() {
    system("clear");
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == Fruity && j == Fruitx)
                cout << "$";
            else {
                bool print = false;
                for (int k = 0; k < tailsize; k++) {

                    if (tailx[k] == j && taily[k] == i) {
                        cout << "o";
                        print = true;
                    }


                }
                if (!print)
                    cout << " ";

            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << "\nScore :: " << score << endl;
}


void Logic() {
    int tempx;
    int tempy;
    prevX = tailx[0];
    prevY = taily[0];
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < tailsize; i++) {
        tempx = tailx[i];
        tempy = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = tempx;
        prevY = tempy;
    }

    if (x == Fruitx && y == Fruity) {
        tailsize++;
        score += 10;
        Fruitx = rand() % width;
        Fruity = rand() % height;
    }

    int input=0;
    if (GetAsyncKeyState(VK_LEFT)) {
        input=1;
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        input=2;
    }
    if (GetAsyncKeyState(VK_UP)) {
        input=3;
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        input=4;
    }

    switch (input)
    {
        case 1:
            x--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y--;
            break;
        case 4:
            y++;
            break;
        default:
            break;
    }




    if (x >= width || x <= 0)
        gameover = true;
    if (y >= height || y <= 0)
        gameover = true;


}

int main() {
    Setup();

    while (!gameover) {
        Logic();
        Draw();
    }
    cout << "Game Over!!";


    return 0;
}