#include "header.h"

std::vector<std::vector<int>> fillBoard(Difficulty diff, std::vector<std::vector<int>> grid) {
    for (int i = 1; i <= diff.getSize(); i++) {
        for (int j = 1; j <= diff.getSize(); j++) {
            if (rand() % 7 == 0) {
                grid = placeMine(i, j, grid);
            }
            else {
                grid[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= diff.getSize(); i++) {
        for (int j = 1; j <= diff.getSize(); j++) {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;
            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;

            grid[i][j] = n;
        }
    }
    return grid;
}

std::vector<std::vector<int>> setDisplayBoard(Difficulty diff, std::vector<std::vector<int>> grid) {
    for (int i = 1; i <= diff.getSize(); i++) {
        for (int j = 1; j <= diff.getSize(); j++) {
            grid[i][j] = 10;
        }
    }
    return grid;
}

std::vector<std::vector<int>> placeMine(int x, int y, std::vector<std::vector<int>> grid) {
    grid[x][y] = 9;
    return grid;
}

void playGame(Difficulty diff) {
    using namespace sf;
    int w = 32;
    bool cleared = false;

    Clock clock;
    Time time = clock.getElapsedTime();
    Text timerText;
    Font font;
    Color color;

    std::vector<std::vector<int>> grid(diff.getBoardSize(), std::vector<int>(diff.getBoardSize(), 0));
    std::vector<std::vector<int>> displayGrid(diff.getBoardSize(), std::vector<int>(diff.getBoardSize(), 0));

    RenderWindow app(VideoMode(diff.getWindowSize() - 32, diff.getWindowSize()), "Minesweeper");

    Texture tileTexture;
    tileTexture.loadFromFile("images/tiles.jpg");
    Sprite tileSprite(tileTexture);

    Texture difficultyTexture;
    difficultyTexture.loadFromFile("images/difficulty.jpg");
    Sprite difficultySprite(difficultyTexture);

    font.loadFromFile("arial.ttf");
    timerText.setFillColor(color.Black);
    timerText.setFont(font);
    timerText.setCharacterSize(30);

    grid = fillBoard(diff, grid);
    displayGrid = setDisplayBoard(diff, displayGrid);

    difficultySprite.setTextureRect(IntRect(0, 0, w*3, w));
    difficultySprite.setPosition(diff.getWindowSize() - 128, 0);
    
    while (app.isOpen())
    {

        Vector2i pos = Mouse::getPosition(app);
        int x = (pos.x + 32) / w;
        int y = (pos.y) / w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) {
                    if (displayGrid[x][y] == 10) {
                        displayGrid[x][y] = grid[x][y];
                    }
                    if (pos.y < 32) {
                        if (pos.x > diff.getWindowSize() - 128 && pos.x < diff.getWindowSize() - 96) {
                            diff = Easy();
                            app.close();
                            playGame(diff);
                        }
                        else if (pos.x > diff.getWindowSize() - 96 && pos.x < diff.getWindowSize() - 64) {
                            diff = Medium();
                            app.close();
                            playGame(diff);
                        }
                        else if (pos.x > diff.getWindowSize() - 64 && pos.x < diff.getWindowSize() - 32) {
                            diff = Hard();
                            app.close();
                            playGame(diff);
                        }
                    }
                }
                else if (e.key.code == Mouse::Right) {
                    if (displayGrid[x][y] == 11) {
                        displayGrid[x][y] = 10;
                    }
                    else if (displayGrid[x][y] != grid[x][y]) {
                        displayGrid[x][y] = 11;
                    }

                }

        }

        app.clear(Color::White);

        for (int i = 1; i <= diff.getSize(); i++) {
            for (int j = 1; j <= diff.getSize(); j++) {
                cleared = ((displayGrid[i][j] == grid[i][j]) || (displayGrid[i][j] == 11 && grid[i][j] == 9));
                if (!(x > diff.getSize() || x < 0 || y > diff.getSize() || y < 0)) {
                    if (x >= 0 && y >= 0 && displayGrid[x][y] == 9) {
                        displayGrid[i][j] = grid[i][j];
                    }
                    if (displayGrid[i][j] == 0) {
                        for (int k = -1; k <= 1; k++)
                        {
                            for (int m = -1; m <= 1; m++)
                            {
                                displayGrid[i + k][j + m] = grid[i + k][j + m];
                            }
                        }
                    }
                }
                tileSprite.setTextureRect(IntRect(displayGrid[i][j] * w, 0, w, w));
                tileSprite.setPosition(i * w - 32, j * w);
                app.draw(tileSprite);
                
            }
        }

        //timer
        time = clock.getElapsedTime();
        char str[] = "";
        sprintf(str, "%d:%d", (int)time.asSeconds() / 60, (int)time.asSeconds() % 60);
        if (!cleared) {
            timerText.setString(str);
        }
        app.draw(difficultySprite);
        app.draw(timerText);
        app.display();
    }
}



