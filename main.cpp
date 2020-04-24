#include <SFML/Graphics.hpp>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include<conio.h>
using namespace std;
string arr[8][8] = {
    {"br", "bkn", "bb", "bq", "bk", "bb", "bkn", "br"},
    {"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
    {"n", "n", "n", "n", "n", "n", "n", "n"},
    {"n", "n", "n", "n", "n", "n", "n", "n"},
    {"n", "n", "n", "n", "n", "n", "n", "n"},
    {"n", "n", "n", "n", "n", "n", "n", "n"},
    {"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"},
    {"wr", "wkn", "wb", "wq", "wk", "wb", "wkn", "wr"}
};
bool fmovewhite[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
bool fmoveblack[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
string curselected = "";
bool validmove(int ox, int oy, int cx, int cy, string type) {
    if (ox == cx && oy == cy) {
        return false;
    }
    else {
        if (arr[cy][cx][0] == type[0]) {
            return false;
        }
        else {
            //HORSE
            if (type.size() == 3) {
                if (cx == ox - 1 && cy == oy + 2) {
                    return true;
                }
                if (cx == ox - 1 && cy == oy - 2) {
                    return true;
                }
                if (cx == ox + 1 && cy == oy + 2) {
                    return true;
                }
                if (cx == ox + 1 && cy == oy - 2) {
                    return true;
                }
                if (cx == ox - 2 && cy == oy + 1) {
                    return true;
                }
                if (cx == ox - 2 && cy == oy - 1) {
                    return true;
                }
                if (cx == ox + 2 && cy == oy + 1) {
                    return true;
                }
                if (cx == ox + 2 && cy == oy - 1) {
                    return true;
                }
            }
            //PAWN
            if (type[1] == 'p') {
                if (type[0] == 'w') {
                    if (cx == ox && cy == oy - 1 && arr[cy][cx] == "n") {
                        fmovewhite[cx] = false;
                        return true;
                    }
                    else if (cx == ox - 1 && cy == oy - 1 && arr[cy][cx][0] == 'b') {
                        fmovewhite[cx] = false;
                        return true;
                    }
                    else if (cx == ox + 1 && cy == oy - 1 && arr[cy][cx][0] == 'b') {
                        fmovewhite[cx] = false;
                        return true;
                    }
                    else if (fmovewhite[cx] && cx == ox && cy == oy - 2 && arr[cy][cx] == "n") {
                        fmovewhite[cx] = false;
                        return true;
                    }
                }
                else {
                    if (cx == ox && cy == oy + 1 && arr[cy][cx] == "n") {
                        fmoveblack[cx] = false;
                        if (cy == 7) {
                            curselected = "bq";
                        }
                        return true;
                    }
                    else if (cx == ox - 1 && cy == oy + 1 && arr[cy][cx][0] == 'w') {
                        fmoveblack[cx] = false;
                        if (cy == 7) {
                            curselected = "bq";
                        }
                        return true;
                    }
                    else if (cx == ox + 1 && cy == oy + 1 && arr[cy][cx][0] == 'w') {
                        fmoveblack[cx] = false;
                        if (cy == 7) {
                            curselected = "bq";
                        }
                        return true;
                    }
                    else if (fmoveblack[cx] && cx == ox && cy == oy + 2 && arr[cy][cx] == "n") {
                        fmoveblack[cx] = false;
                        return true;
                    }
                }
            }
            //ROOK
            if (type[1] == 'r') {
                if (cy == oy) {
                    if (cx < ox) {
                        for (int x = cx + 1; x < ox; x++) {
                            if (arr[cy][x] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int x = ox + 1; x < cx; x++) {
                            if (arr[cy][x] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if (cx == ox) {
                    if (cy < oy) {
                        for (int y = cy + 1; y < oy; y++) {
                            if (arr[y][cx] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int y = oy + 1; y < cy; y++) {
                            if (arr[y][cx] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }
            }
            //BISHOP
            if (type[1] == 'b') {
                if (cy - oy == cx - ox) {
                    // DIAGONAL \ //
                    if (cx < ox) {
                        for (int x = 1; x < ox - cx; x++) {
                            if (arr[cy + x][cx + x] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int x = 1; x < cx - ox; x++) {
                            if (arr[oy + x][ox + x] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if (cy - oy == -1 * (cx - ox)) {
                    // DIAGONAL / //
                    if (cx < ox) {
                        for (int x = 1; x < ox - cx; x++) {
                            if (arr[oy + x][ox - x] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int x = 1; x < cx - ox; x++) {
                            if (arr[oy - x][ox + x] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }
            }
            //QUEEN
            if (type[1] == 'q') {
                // | //
                if (cy == oy) {
                    if (cx < ox) {
                        for (int x = cx + 1; x < ox; x++) {
                            if (arr[cy][x] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int x = ox + 1; x < cx; x++) {
                            if (arr[cy][x] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }
                // | //
                else if (cx == ox) {
                    if (cy < oy) {
                        for (int y = cy + 1; y < oy; y++) {
                            if (arr[y][cx] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int y = oy + 1; y < cy; y++) {
                            if (arr[y][cx] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if (cy - oy == cx - ox) {
                    // DIAGONAL \ //
                    if (cx < ox) {
                        for (int x = 1; x < ox - cx; x++) {
                            if (arr[cy + x][cx + x] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int x = 1; x < cx - ox; x++) {
                            if (arr[oy + x][ox + x] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if (cy - oy == -1 * (cx - ox)) {
                    // DIAGONAL / //
                    if (cx < ox) {
                        for (int x = 1; x < ox - cx; x++) {
                            if (arr[oy + x][ox - x] != "n") {
                                return false;
                            }
                        }
                    }
                    else {
                        for (int x = 1; x < cx - ox; x++) {
                            if (arr[oy - x][ox + x] != "n") {
                                return false;
                            }
                        }
                    }
                    return true;
                }

            }
            if (type[1] == 'k') {
                if (abs(ox - cx) <= 1 && abs(oy - cy) <= 1) {
                    return true;
                }
            }
            return false;
        }
    }
}
int main()
{
    int curx = 0;
    int cury = 0;
    bool whiteturn = true;
    bool blackturn = false;
    bool selectingwhite = false;
    bool selectingblack = false;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    sf::RectangleShape blacksquare(sf::Vector2f(100, 100));
    blacksquare.setFillColor(sf::Color(139, 69, 19));
    sf::RectangleShape whitesquare(sf::Vector2f(100, 100));
    whitesquare.setFillColor(sf::Color::White);


    while (window.isOpen())
    {
        window.setKeyRepeatEnabled(false);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255));
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 8; y++) {
                window.draw(blacksquare);
                window.draw(whitesquare);
                whitesquare.setPosition(x * 200.0f + 100 * ((y + 1) % 2), y * 100.0f);
                blacksquare.setPosition(x * 200.0f + 100 * (y % 2), y * 100.0f);
            }
        }
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (arr[x][y] != "n") {
                    string ad = "images/" + arr[x][y] + ".png";
                    sf::Texture texture;
                    texture.loadFromFile(ad);
                    sf::Sprite p(texture);
                    p.setScale(sf::Vector2f(2.22, 2.22));
                    p.setPosition(y * 100, x * 100);
                    window.draw(p);

                }
            }
        }
        if (selectingblack || selectingwhite) {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            string ad = "images/" + curselected + ".png";
            sf::Texture texture;
            texture.loadFromFile(ad);
            sf::Sprite p(texture);
            p.setScale(sf::Vector2f(2.22, 2.22));
            p.setPosition(position.x - 50, position.y - 50);
            window.draw(p);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if (whiteturn) {
                if (!selectingwhite) {
                    if (arr[(int)floor(position.y / 100)][(int)floor(position.x / 100)][0] == 'w') {
                        selectingwhite = true;
                        curselected = arr[(int)floor(position.y / 100)][(int)floor(position.x / 100)];
                        cury = (int)floor(position.y / 100);
                        curx = (int)floor(position.x / 100);
                        arr[cury][curx] = "n";
                    }
                }
            }
            else if (blackturn) {
                if (!selectingblack) {
                    if (arr[(int)floor(position.y / 100)][(int)floor(position.x / 100)][0] == 'b') {
                        selectingblack = true;
                        curselected = arr[(int)floor(position.y / 100)][(int)floor(position.x / 100)];
                        cury = (int)floor(position.y / 100);
                        curx = (int)floor(position.x / 100);
                        arr[cury][curx] = "n";
                    }
                }
            }
        }
        else {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if (selectingwhite) {
                selectingwhite = false;
                int cx = (int)floor(position.x / 100);
                int cy = (int)floor(position.y / 100);
                if (validmove(curx, cury, cx, cy, curselected)) {
                    arr[cy][cx] = curselected;
                    curselected = "";
                    selectingwhite = false;
                    whiteturn = false;
                    blackturn = true;
                }
                else {
                    selectingwhite = false;
                    arr[cury][curx] = curselected;
                }
            }
            if (selectingblack) {
                selectingblack = false;
                int cx = (int)floor(position.x / 100);
                int cy = (int)floor(position.y / 100);
                if (validmove(curx, cury, cx, cy, curselected)) {
                    arr[cy][cx] = curselected;
                    curselected = "";
                    selectingblack = false;
                    whiteturn = true;
                    blackturn = false;

                }
                else {
                    selectingblack = false;
                    arr[cury][curx] = curselected;
                }
            }
        }
        //CHECK IF ANY OF THE KINGS WERE KILLED
        int gameover = 0;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (arr[x][y][1] == 'k' && arr[x][y].size() != 3) {
                    gameover++;
                }
            }
        }
        if (gameover < 2) {
            curx = 0;
            cury = 0;
            whiteturn = true;
            blackturn = false;
            selectingwhite = false;
            selectingblack = false;
            string temp[8][8] = {
            {"br", "bkn", "bb", "bq", "bk", "bb", "bkn", "br"},
            {"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
            {"n", "n", "n", "n", "n", "n", "n", "n"},
            {"n", "n", "n", "n", "n", "n", "n", "n"},
            {"n", "n", "n", "n", "n", "n", "n", "n"},
            {"n", "n", "n", "n", "n", "n", "n", "n"},
            {"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"},
            {"wr", "wkn", "wb", "wq", "wk", "wb", "wkn", "wr"}
            };
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    arr[x][y] = temp[x][y];
                }
                fmovewhite[x] = 1;
                fmoveblack[x] = 1;
            }
            curselected = "";
        }
        window.display();
    }
    return 0;
}
