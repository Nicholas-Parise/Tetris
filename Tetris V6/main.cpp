#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace std;

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}


void BlockHandler(vector<vector<int>> Shape, vector<sf::RectangleShape> &Bricks, string rotation, int offsetX, int offsetY) {

    int placeTemp = 0;
    int temp;
    int temp2;

//rotation = "Normal";
//rotation = "Down";
//rotation = "Side";
//rotation = "BackSide";
//[up][right]

    if(rotation == "Normal") {

        for(int j = 1; j>-1; j--) {
            for(int i = 0; i < 4; i++) {
                if(Shape[i][j] != 0) {

                    if(j == 1)
                        temp = 0;

                    if(j == 0)
                        temp = 1;

                    Bricks[placeTemp].setPosition((i*20)+i+offsetX,(temp*20)+temp+offsetY);

                } else {
                    Bricks[placeTemp].setPosition((i*20)+i+offsetX,-1000);
                }
                placeTemp++;
            }
        }

    } else if(rotation == "Down") {
        for(int j = 1; j>-1; j--) {
            for(int i = 0; i < 4; i++) {

                if(Shape[i][j] != 0) {

                    if(i == 0) {
                        temp = 3;
                    }
                    if(i == 1) {
                        temp = 2;
                    }
                    if(i == 2) {
                        temp = 1;
                    }
                    if(i == 3) {
                        temp = 0;
                    }

                    Bricks[placeTemp].setPosition((temp*20)+temp+offsetX-21,(j*20)+j+offsetY);

                } else {

                    Bricks[placeTemp].setPosition((temp*20)+temp+offsetX,-1000);
                }
                placeTemp++;
            }
        }
    } else if(rotation == "Side") {

        for(int i = 0; i < 4; i++) {

            for(int j = 0; j<2; j++) {


                if(Shape[i][j] != 0) {
                    Bricks[placeTemp].setPosition((j*20)+j+offsetX,i*20+i+offsetY);
                } else {
                    Bricks[placeTemp].setPosition((i*20)+i+offsetX,-1000);
                }
                placeTemp++;
            }
        }

    } else if(rotation == "BackSide") {

        for(int i = 0; i < 4; i++) {

            for(int j = 0; j<2; j++) {

                if(Shape[i][j] != 0) {


                    if(j == 0) {
                        temp2 = 1;
                    }
                    if(j == 1) {
                        temp2 = 0;
                    }

                    if(i == 0) {
                        temp = 3;
                    }
                    if(i == 1) {
                        temp = 2;
                    }
                    if(i == 2) {
                        temp = 1;
                    }
                    if(i == 3) {
                        temp = 0;
                    }

                    Bricks[placeTemp].setPosition((temp2*20)+temp2+offsetX,(temp*20)+temp+offsetY-21);
                } else {
                    Bricks[placeTemp].setPosition((i*20)+i+offsetX,-1000);
                }
                placeTemp++;
            }
        }
    }
}


bool CanLeft(std::vector<sf::RectangleShape> &Bricks, vector<vector<int>> GameMatrix, std::vector<sf::RectangleShape> places) {

    vector<int> LowestPointsTemp;
    vector<int> LowestPointsY;
    vector<int> LowestPointsX;

    int temp;
    int temp2;

    for(int i = 0; i<Bricks.size(); i++) {
        if(Bricks[i].getPosition().y >0) {

            temp = Bricks[i].getPosition().y;
            temp2 = (int)Bricks[i].getPosition().x%10;

            LowestPointsY.push_back(temp);
            LowestPointsX.push_back(temp2);
        }
    }


    for(int i = 0; i < places.size(); i++) {
        for(int k = 0; k< LowestPointsY.size(); k++) {

            if(places[i].getPosition().y == LowestPointsY[k]) {

                LowestPointsY[k]=(i/10);

            }
        }
    }


    for(int k = 0; k<LowestPointsY.size(); k++) {


        if(LowestPointsX[k]<1) {

            return false;
        }



        if(GameMatrix[LowestPointsX[k]-1][LowestPointsY[k]] > 0) {

            return false;

        }
    }


    return true;
}


bool CanRight(std::vector<sf::RectangleShape> &Bricks, vector<vector<int>> GameMatrix, std::vector<sf::RectangleShape> places) {

    vector<int> LowestPointsTemp;
    vector<int> LowestPointsY;
    vector<int> LowestPointsX;

    int temp;
    int temp2;

    for(int i = 0; i<Bricks.size(); i++) {
        if(Bricks[i].getPosition().y >0) {

            temp = Bricks[i].getPosition().y;
            temp2 = (int)Bricks[i].getPosition().x%10;

            LowestPointsY.push_back(temp);
            LowestPointsX.push_back(temp2);
        }
    }


    for(int i = 0; i < places.size(); i++) {
        for(int k = 0; k< LowestPointsY.size(); k++) {

            if(places[i].getPosition().y == LowestPointsY[k]) {

                LowestPointsY[k]=(i/10);

            }
        }
    }


    for(int k = 0; k<LowestPointsY.size(); k++) {


        if(LowestPointsX[k]>8) {

            return false;
        }



        if(GameMatrix[LowestPointsX[k]+1][LowestPointsY[k]] > 0) {

            return false;

        }
    }


    return true;
}


bool whereFloor(vector<sf::RectangleShape> &Bricks, vector<vector<int>> GameMatrix, std::vector<sf::RectangleShape> places) {

    vector<int> LowestPointsTemp;
    vector<int> LowestPointsY;
    vector<int> LowestPointsX;

    int temp;
    int temp2;

    for(int i = 0; i<Bricks.size(); i++) {
        if(Bricks[i].getPosition().y >0) {

            temp = Bricks[i].getPosition().y;
            temp2 = (int)Bricks[i].getPosition().x%10;

            LowestPointsY.push_back(temp);
            LowestPointsX.push_back(temp2);
        }
    }


    for(int i = 0; i < places.size(); i++) {
        for(int k = 0; k< LowestPointsY.size(); k++) {

            if(places[i].getPosition().y == LowestPointsY[k]) {

                LowestPointsY[k]=(i/10);

                if(i>=190) {
                    return true;
                }
            }
        }
    }


    for(int k = 0; k<LowestPointsY.size(); k++) {


        if(GameMatrix[LowestPointsX[k]][LowestPointsY[k]+1] > 0) {

            return true;

        }
    }


    return false;
}


vector<vector<int>> pickBlock(int Num,vector<vector<int>> a, vector<vector<int>> b, vector<vector<int>> c, vector<vector<int>> d, vector<vector<int>> e, vector<vector<int>>f, vector<vector<int>> g, string &shape) {

    if(Num == 0) {

        shape = "LShape";
        return a;
    } else if(Num == 1) {

        shape = "L2Shape";
        return b;
    } else if(Num ==2) {

        shape = "SShape";
        return c;
    } else if(Num == 3) {

        shape = "ZShape";
        return d;
    } else if(Num == 4) {

        shape = "IShape";
        return e;
    } else if(Num == 5) {

        shape = "SquShape";
        return f;
    } else if(Num == 6) {

        shape = "TShape";
        return g;
    }



    shape = "LShape";
    return a;
}


vector<vector<int>> FindCurrentBlock(vector<vector<int>> a, vector<vector<int>> b, vector<vector<int>> c, vector<vector<int>> d, vector<vector<int>> e, vector<vector<int>>f, vector<vector<int>> g, string shape) {

    if(shape == "LShape") {

        return a;
    } else if(shape == "L2Shape") {

        return b;
    } else if(shape == "SShape") {

        return c;
    } else if(shape == "ZShape") {

        return d;
    } else if(shape == "IShape") {

        return e;
    } else if(shape == "SquShape") {

        return f;
    } else if(shape == "TShape") {

        return g;
    }
    return a;
}


void FindOffset(int &x, int &y, vector<sf::RectangleShape> &Bricks) {

    int tempx = Bricks[0].getPosition().x;
    int tempy;


    for(int i = 0; i<Bricks.size(); i++) {

        if(Bricks[i].getPosition().y >0) {

            tempy = Bricks[i].getPosition().y;
            break;
        }
    }


    for(int i=0; i<Bricks.size(); i++) {

        if(Bricks[i].getPosition().x<tempx && Bricks[i].getPosition().y >0) {
            tempx = Bricks[i].getPosition().x;
        }

        if(Bricks[i].getPosition().y<tempy && Bricks[i].getPosition().y >0) {
            tempy = Bricks[i].getPosition().y;
        }
    }

    x = tempx;
    y = tempy;

}


int FullRow(vector<vector<int>> GameMatrix, int& X) {

    bool LineFull = true;
    int line = -1;

    for(int i = 0; i<20; i++) {
        for(int j = 0; j<10; j++) {

            if(GameMatrix[j][i]>0) {

                if(j==9 && LineFull == true) {
                    line=i;

                }

            } else {
                LineFull = false;
            }
        }
        LineFull = true;
    }

    X = line;
    return line;
}


void ScorePlacer(vector<sf::RectangleShape> &Blocks, vector<vector<int>> Number, int &place, int &Xoffset) {

    for(int j = 0; j<5; j++) {
        for(int i = 0; i<3; i++) {
            if(Number[j][i]>0) {

                Blocks[place].setFillColor(sf::Color::Red);
                Blocks[place].setSize(sf::Vector2f(5, 5));
                Blocks[place].setOrigin(2.5,2.5);
                Blocks[place].setPosition(i*5+Xoffset,j*5+300);

                place++;
            }
        }
    }

    Xoffset = 4*5+Xoffset;
}

void QueueFiller(vector<int> &oldQueue) {

    vector<int> NewQueue;
    bool stop = false;
    bool first = true;
    bool repeat = false;

    int WhenStop = 1;

    int Num;


    while(stop == false) {
        repeat = false;

        Num = rand()%7;

        if(first == true) {

            if(Num != oldQueue[6]) {
                NewQueue.push_back(Num);
                first = false;
            }

        } else {


            for(int i = 0; i<NewQueue.size(); i++) {

                if(NewQueue[i] == Num) {

                    repeat = true;
                }
            }

            if(repeat == false) {
                WhenStop++;
                NewQueue.push_back(Num);
            }
        }


        if(WhenStop==7) {

            stop = true;
        }
    }



    for(int i = 0; i<NewQueue.size(); i++) {

        cout<<NewQueue[i]<<" ";
    }
    cout<<endl;




    oldQueue.clear();
    oldQueue = NewQueue;
}

/*
// very cool but not what i want
void MoveTitle(std::vector<sf::RectangleShape> &TitlePlaces,vector<vector<int>> Title){

int place = 0;
sf::Color TitleColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);
sf::Color TempTitleColour = TitlePlaces[0].getFillColor();

    for(int i = 0; i<20; i++) {
    for(int j = 0; j<5; j++) {

            if(Title[j][i]>0) {
                TitlePlaces[place].setFillColor(TitleColour);
                place++;
            }
        }

        TitleColour = TempTitleColour;
        TempTitleColour = TitlePlaces[place-1].getFillColor();

    }


}
*/
/*
void MoveTitle(std::vector<sf::RectangleShape> &TitlePlaces,vector<vector<int>> Title){

int place = 0;
sf::Color TitleColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);
sf::Color TempTitleColour = TitlePlaces[0].getFillColor();
for(int j = 0; j<5; j++) {
    for(int i = 0; i<20; i++) {


            if(Title[j][i]>0) {
                TitlePlaces[place].setFillColor(TitleColour);
                place++;
            }
        }

        TitleColour = TempTitleColour;
        TempTitleColour = TitlePlaces[place].getFillColor();

    }


}
*/
/*
void MoveTitle(std::vector<sf::RectangleShape> &TitlePlaces,vector<vector<int>> Title){

int place = 0;
sf::Color TitleColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);
sf::Color TempTitleColour = TitlePlaces[0].getFillColor();
for(int j = 0; j<5; j++) {
    for(int i = 0; i<20; i++) {


            if(Title[j][i]>0) {
                TitlePlaces[place].setFillColor(TitleColour);
                place++;
            }
        }

        TitleColour = TempTitleColour;
        TempTitleColour = TitlePlaces[place-1].getFillColor();

    }


}
*/

void MoveTitle(std::vector<sf::RectangleShape> &TitlePlaces,vector<vector<int>> Title) {

    int place = 0;
    sf::Color TitleColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);
    sf::Color TempTitleColour = TitlePlaces[0].getFillColor();
    int between = 0;

    vector<int> internalVec = {3,3,4,3,3,3};

    int IntervalInterval = 0;

    for(int i = 0; i<20; i++) {
        for(int j = 0; j<5; j++) {

            if(Title[j][i]>0) {
                TitlePlaces[place].setFillColor(TitleColour);
                place++;
            }
        }

        if(between == internalVec[IntervalInterval]) {
            IntervalInterval++;

            TitleColour = TempTitleColour;
            //TempTitleColour = TitlePlaces[place-1].getFillColor();
            TempTitleColour = TitlePlaces[place+1].getFillColor();
            between = 0;
        }
        between++;
    }
}


bool isSpriteHover(sf::FloatRect Button, sf::Vector2f mp) {

    if (Button.contains(mp)) {
        return true;
    }

    return false;
}




int main() {

    srand (time(NULL));

    int LeftRightTimer = 0;
    int rotateOffsetX, rotateOffsetY;
    int RotationIndex = 0;
    int score = 0;
    int everyother = 0;
    int FullLine = 0;
    int place = 0;

    int godown = 0;
    int flashTimer = 0;
    int TitleTimer = 0;
    int PauseTimer = 0;

    int DownTime = 30;
    int scoreXoffset;
    int GameOverTimer = 0;
    int temp;
    int queuePlace = 0;
    int LastQueue;

    bool scoreUpdate = false;
    bool GameOver = false;

    string currentShape = "LShape";
    string GameState = "Menu";


    string scoreString;

    vector<int>LowestPointsY;

    vector<vector<int>> GameMatrix(201);

    vector<int> Blockqueue = {-1,-1,-1,-1,-1,-1,-1};
    QueueFiller(Blockqueue);

    LastQueue = Blockqueue[6];


    std::vector<sf::RectangleShape> places(200);
    std::vector<sf::RectangleShape> TitlePlaces(46);
    std::vector<sf::RectangleShape> StartPlaces(90);
    std::vector<sf::RectangleShape> StaticScore(85);
    std::vector<sf::RectangleShape> GameOverPlaces(92);
    std::vector<sf::RectangleShape> ScoreBlocks(100);
    std::vector<sf::RectangleShape> NextPieceBlocks(100);
    std::vector<sf::RectangleShape> PauseBlocks(18);
    std::vector<sf::RectangleShape> HelpBlocks(245);
    std::vector<sf::RectangleShape> KeyBindingsBlocks(110);
    std::vector<sf::RectangleShape> HelpTextBlocks(180);
    std::vector<sf::RectangleShape> BackTextBlocks(180);




    std::vector<sf::RectangleShape> Bricks(8);
    std::vector<sf::RectangleShape> NextBricks(8);

    const vector <string> ClockRot{"Normal","Side","Down","BackSide"};


    const vector<vector<int>> Title = {
        {1,1,1,0,1,1,0,1,1,1,0,1,1,0,0,1,0,0,1,1},
        {0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0},
        {0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1},
        {0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,0}
    };

    const vector<vector<int>> PressStart = {
        {1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,1,1,0,0,1,0,0,1,1,1,0,1,1,1},
        {1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0},
        {1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1},
        {1,0,0,0,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0},
        {1,0,0,0,1,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1}
    };

    const vector<vector<int>> ScoreText = {
        {0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,0},
        {1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1},
        {0,1,0,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,0,0},
        {0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1},
        {1,1,0,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,0}
    };

    const vector<vector<int>> GameOverText = {
        {1,1,1,1,0,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,0},
        {1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1},
        {1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0},
        {1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1},
        {1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,1,0,0,1,0,0,1,1,1,0,1,0,1}
    };

    const vector<vector<int>> NextPieceText = {
        {1,0,0,1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,0,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,},
        {1,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,},
        {1,1,0,1,0,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0,0,1,1,1,0,0,0,0,},
        {1,0,1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,},
        {1,0,0,1,0,1,1,1,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,}
    };



    const vector<vector<int>> KeyBindings = {
        {1,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,0,1,0,1,0,0,1,0,1,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,0,1,1,0,0},
        {1,0,1,0,1,0,0,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,0,0},
        {1,1,0,0,1,1,1,0,0,1,0,0,0,1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,0,1,0,0,0},
        {1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,0,1,0,0,0,1,0,0},
        {1,0,1,0,1,1,1,0,0,1,0,0,0,1,1,0,0,1,0,1,0,0,1,0,1,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,1,0,0,0}
    };



    const vector<vector<int>> PieceText = {
        {0,0,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1},
        {0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0},
        {1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,0,0,1,1,1},
        {0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0},
        {0,0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,0,1,1,1}
    };






    const vector<vector<int>> PausedVis = {
        {1,1,0,0,1,1},
        {1,1,0,0,1,1},
        {1,1,0,0,1,1},
        {1,1,0,0,1,1}
    };


    const vector<vector<int>> Arrow = {
        {1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,1},
        {1,0,0,1,1,1,0,0,1},
        {1,0,1,1,1,1,1,0,1},
        {1,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1}
    };

    const vector<vector<int>> Enter = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };


    const vector<vector<int>> HelpButton = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,2,0,2,0,2,2,2,0,2,0,0,0,2,2,2,0,1},
        {1,0,2,0,2,0,2,0,0,0,2,0,0,0,2,0,2,0,1},
        {1,0,2,2,2,0,2,2,2,0,2,0,0,0,2,2,2,0,1},
        {1,0,2,0,2,0,2,0,0,0,2,0,0,0,2,0,0,0,1},
        {1,0,2,0,2,0,2,2,2,0,2,2,2,0,2,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };


        const vector<vector<int>> BackButton = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,2,2,0,0,2,2,2,0,2,2,2,0,2,0,2,0,1},
        {1,0,2,0,2,0,2,0,2,0,2,0,0,0,2,0,2,0,1},
        {1,0,2,2,2,0,2,2,2,0,2,0,0,0,2,2,0,0,1},
        {1,0,2,0,2,0,2,0,2,0,2,0,0,0,2,0,2,0,1},
        {1,0,2,2,0,0,2,0,2,0,2,2,2,0,2,0,2,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };






    /*
        for(int i = 0; i<5; i++){

        cout<<"{";
        for(int j = 0; j<40; j++){

        cout<<"0,";

        }

        cout<<"},"<<endl;

        }

    */


    const vector<vector<int>> Zero = {
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1}
    };

    const vector<vector<int>> One = {
        {0,1,0},
        {1,1,0},
        {0,1,0},
        {0,1,0},
        {1,1,1}
    };

    const vector<vector<int>> Two = {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {1,0,0},
        {1,1,1}
    };

    const vector<vector<int>> Three = {
        {1,1,1},
        {0,0,1},
        {0,1,1},
        {0,0,1},
        {1,1,1}
    };

    const vector<vector<int>> Four = {
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1}
    };

    const vector<vector<int>> Five = {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {0,0,1},
        {1,1,1}
    };

    const vector<vector<int>> Six = {
        {1,0,0},
        {1,0,0},
        {1,1,1},
        {1,0,1},
        {1,1,1}
    };

    const vector<vector<int>> Seven = {
        {1,1,1},
        {1,0,1},
        {0,0,1},
        {0,0,1},
        {0,0,1}
    };

    const vector<vector<int>> Eight = {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,1,1}
    };

    const vector<vector<int>> Nine = {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1}
    };


    const vector<vector<int>> LShape = {
        {1,0},
        {1,0},
        {1,1},
        {0,0}
    };

    const vector<vector<int>> L2Shape = {
        {0,2},
        {0,2},
        {2,2},
        {0,0}
    };

    const vector<vector<int>> SShape = {
        {3,0},
        {3,3},
        {0,3},
        {0,0}
    };

    const vector<vector<int>> ZShape = {
        {0,4},
        {4,4},
        {4,0},
        {0,0}
    };

    const vector<vector<int>> IShape = {
        {0,5},
        {0,5},
        {0,5},
        {0,5}
    };

    const vector<vector<int>> SquShape = {
        {6,6},
        {6,6},
        {0,0},
        {0,0}
    };

    const vector<vector<int>> TShape = {
        {7,0},
        {7,7},
        {7,0},
        {0,0}
    };


    //-------------------


    // sf::Color CurrentColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);
    //sf::Color NextColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);


    sf::Color CurrentColour = sf::Color(rand()%185+30,rand()%185+30,rand()%185+30);
    sf::Color NextColour = sf::Color(rand()%185+30,rand()%185+30,rand()%185+30);


    sf::Color TitleColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);
    sf::Color TitleColourTemp;


    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(720, 480));
    rectangle.setFillColor(sf::Color(10,10,10));
    rectangle.setPosition(0, 0);



    //-------------------
    for(int i = 0; i<20; i++) {

        for(int j = 0; j<10; j++) {

            GameMatrix[i,j].push_back(0);

            places[place].setFillColor(sf::Color::White);
            places[place].setSize(sf::Vector2f(20, 20));
            places[place].setOrigin(10,10);
            places[place].setPosition(j*20+j+250,i*20+i+50);
            place++;
        }
    }


    //-------------------

    place = 0;


    for(int i = 0; i<20; i++) {
        for(int j = 0; j<5; j++) {


            if(Title[j][i]>0) {
                TitlePlaces[place].setSize(sf::Vector2f(20, 20));
                TitlePlaces[place].setOrigin(10,10);
                TitlePlaces[place].setPosition(i*20+170,j*20+50);

                place++;
            }
        }
    }

    MoveTitle(TitlePlaces,Title);

    //-------------------


    place = 0;

    for(int j = 0; j<5; j++) {
        for(int i = 0; i<40; i++) {

            if(PressStart[j][i]>0) {

                StartPlaces[place].setFillColor(sf::Color::Red);
                StartPlaces[place].setSize(sf::Vector2f(10, 10));
                StartPlaces[place].setOrigin(5,5);

                StartPlaces[place].setPosition(i*10+160,j*10+250);  //smooth

                place++;
            }
        }
    }

    //-------------------
    place = 0;

    for(int j = 0; j<5; j++) {
        for(int i = 0; i<21; i++) {

            if(ScoreText[j][i]>0) {

                StaticScore[place].setFillColor(sf::Color::Red);
                StaticScore[place].setSize(sf::Vector2f(5, 5));
                StaticScore[place].setOrigin(2.5,2.5);

                StaticScore[place].setPosition(i*5+460,j*5+300);  //smooth

                place++;
            }
        }
    }
    //-------------------
    place = 0;

    for(int j = 0; j<5; j++) {
        for(int i = 0; i<36; i++) {

            if(GameOverText[j][i]>0) {

                GameOverPlaces[place].setFillColor(sf::Color::Red);
                GameOverPlaces[place].setSize(sf::Vector2f(10, 10));
                GameOverPlaces[place].setOrigin(5,5);

                GameOverPlaces[place].setPosition(i*10+160,j*10+250);  //smooth

                place++;
            }
        }
    }


//------------------

    place = 0;

    for(int j = 0; j<5; j++) {
        for(int i = 0; i<40; i++) {

            if(NextPieceText[j][i]>0) {

                NextPieceBlocks[place].setFillColor(sf::Color::Red);
                NextPieceBlocks[place].setSize(sf::Vector2f(5, 5));
                NextPieceBlocks[place].setOrigin(2.5,2.5);

                NextPieceBlocks[place].setPosition(i*5+460,j*5+100);  //smooth

                place++;
            }
        }
    }




//------------------

    place = 0;

    for(int j = 0; j<4; j++) {
        for(int i = 0; i<6; i++) {

            if(PausedVis[j][i]>0) {

                PauseBlocks[place].setFillColor(sf::Color::Black);
                PauseBlocks[place].setSize(sf::Vector2f(20, 20));
                PauseBlocks[place].setOrigin(10,10);

                PauseBlocks[place].setPosition(i*20+292+i,j*20+197+j);  //smooth

                place++;
            }
        }
    }


//------------------

    int HelpTemp = 0;

    place = 0;

    //up
    for(int j = 0; j<9; j++) {
        for(int i = 0; i<9; i++) {

            if(Arrow[j][i]>0) {

                HelpBlocks[place].setSize(sf::Vector2f(5, 5));
                HelpBlocks[place].setOrigin(2.5,2.5);
                HelpBlocks[place].setPosition(i*5+20,j*5+60);  //smooth

                if(Arrow[j][i]==1) {
                    HelpBlocks[place].setFillColor(sf::Color::White);
                }

                place++;
            }
        }
    }


//down

    for(int j = 0; j<9; j++) {
        for(int i = 0; i<9; i++) {

            if(Arrow[j][i]>0) {


                if(j == 0)
                    HelpTemp = 8;

                if(j == 1)
                    HelpTemp = 7;

                if(j == 2)
                    HelpTemp = 6;

                if(j == 3)
                    HelpTemp = 5;

                if(j == 4)
                    HelpTemp = 4;

                if(j == 5)
                    HelpTemp = 3;

                if(j == 6)
                    HelpTemp = 2;

                if(j == 7)
                    HelpTemp = 1;

                if(j == 8)
                    HelpTemp = 0;



                HelpBlocks[place].setSize(sf::Vector2f(5, 5));
                HelpBlocks[place].setOrigin(2.5,2.5);
                HelpBlocks[place].setPosition(i*5+20,HelpTemp*5+(60+60));  //smooth

                if(Arrow[j][i]==1) {
                    HelpBlocks[place].setFillColor(sf::Color::White);
                }

                place++;
            }
        }
    }

//left
    for(int j = 0; j<9; j++) {
        for(int i = 0; i<9; i++) {

            if(Arrow[j][i]>0) {

                HelpBlocks[place].setSize(sf::Vector2f(5, 5));
                HelpBlocks[place].setOrigin(2.5,2.5);
                HelpBlocks[place].setPosition(j*5+20,i*5+((120+60)));  //smooth

                if(Arrow[j][i]==1) {
                    HelpBlocks[place].setFillColor(sf::Color::White);
                }

                place++;
            }
        }
    }



//right
    for(int j = 0; j<9; j++) {
        for(int i = 0; i<9; i++) {

            if(Arrow[j][i]>0) {


                if(j == 0)
                    HelpTemp = 8;

                if(j == 1)
                    HelpTemp = 7;

                if(j == 2)
                    HelpTemp = 6;

                if(j == 3)
                    HelpTemp = 5;

                if(j == 4)
                    HelpTemp = 4;

                if(j == 5)
                    HelpTemp = 3;

                if(j == 6)
                    HelpTemp = 2;

                if(j == 7)
                    HelpTemp = 1;

                if(j == 8)
                    HelpTemp = 0;



                HelpBlocks[place].setSize(sf::Vector2f(5, 5));
                HelpBlocks[place].setOrigin(2.5,2.5);
                HelpBlocks[place].setPosition(HelpTemp*5+20,i*5+((180+60)));  //smooth

                if(Arrow[j][i]==1) {
                    HelpBlocks[place].setFillColor(sf::Color::White);
                }

                place++;
            }
        }
    }


    for(int j = 0; j<9; j++) {
        for(int i = 0; i<17; i++) {

            if(Enter[j][i]>0) {

                HelpBlocks[place].setSize(sf::Vector2f(5, 5));
                HelpBlocks[place].setOrigin(2.5,2.5);
                HelpBlocks[place].setPosition(i*5+20,j*5+((240+60)));  //smooth

                if(Enter[j][i]==1) {
                    HelpBlocks[place].setFillColor(sf::Color::White);
                }

                place++;
            }
        }
    }

//------------------

    place = 0;

    //up
    for(int j = 0; j<5; j++) {
        for(int i = 0; i<45; i++) {

            if(KeyBindings[j][i]>0) {

                KeyBindingsBlocks[place].setSize(sf::Vector2f(5, 5));
                KeyBindingsBlocks[place].setOrigin(2.5,2.5);
                KeyBindingsBlocks[place].setPosition(i*5+20,j*5+20);

                KeyBindingsBlocks[place].setFillColor(sf::Color::White);


                place++;
            }
        }
    }



//------------------

    place = 0;

    for(int j = 0; j<9; j++) {
        for(int i = 0; i<19; i++) {

            if(HelpButton[j][i]>=0) {
                HelpTextBlocks[place].setSize(sf::Vector2f(10,10));
                HelpTextBlocks[place].setOrigin(5,5);
                HelpTextBlocks[place].setPosition(i*10+262,j*10+350);

                if(HelpButton[j][i]==0) {

                    HelpTextBlocks[place].setFillColor(sf::Color::Black);
                }

                if(HelpButton[j][i]==1) {

                    HelpTextBlocks[place].setFillColor(sf::Color::Blue);
                }

                if(HelpButton[j][i]==2) {

                    HelpTextBlocks[place].setFillColor(sf::Color::White);
                }

                place++;
            }
        }
    }



//------------------

    place = 0;

    for(int j = 0; j<9; j++) {
        for(int i = 0; i<19; i++) {

            if(BackButton[j][i]>=0) {
                BackTextBlocks[place].setSize(sf::Vector2f(10,10));
                BackTextBlocks[place].setOrigin(5,5);
                BackTextBlocks[place].setPosition(i*10+262,j*10+350);

                if(BackButton[j][i]==0) {

                    BackTextBlocks[place].setFillColor(sf::Color::Black);
                }

                if(BackButton[j][i]==1) {

                    BackTextBlocks[place].setFillColor(sf::Color::Blue);
                }

                if(BackButton[j][i]==2) {

                    BackTextBlocks[place].setFillColor(sf::Color::White);
                }

                place++;
            }
        }
    }



//------------------


    for (int i = 0; i < 8; i++) {

        Bricks[i].setFillColor(CurrentColour);
        Bricks[i].setSize(sf::Vector2f(20, 20));
        Bricks[i].setOrigin(10,10);
        Bricks[i].setPosition(0,-1000);
    }

    for (int i = 0; i < NextBricks.size(); i++) {

        NextBricks[i].setFillColor(NextColour);
        NextBricks[i].setSize(sf::Vector2f(20, 20));
        NextBricks[i].setOrigin(10,10);
        NextBricks[i].setPosition(0,-1000);
    }



    //-------------------
    /*
    const unsigned SAMPLES = 44100;
    const unsigned SAMPLE_RATE = 44100;
    const unsigned AMPLITUDE = 3000;

    sf::Int16 raw[SAMPLES];

    const double TWO_PI = 6.28318;

    //increment = frequancy HZ / 44100

    const double increment = 440./44100;

    double x = 0;
    for (unsigned i = 0; i < SAMPLES; i++) {
        raw[i] = AMPLITUDE * sin(x*TWO_PI);
        x += increment;
    }

    sf::SoundBuffer Buffer;
    Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);


    const double increment2 = 350./44100;

    x = 0;
    for (unsigned i = 0; i < SAMPLES; i++) {
        raw[i] = AMPLITUDE * sin(x*TWO_PI);
        x += increment2;
    }



    sf::SoundBuffer Buffer2;
    Buffer2.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);


    sf::Sound Sound;
    Sound.setBuffer(Buffer);

    sf::Sound Sound2;
    Sound2.setBuffer(Buffer2);


         Sound.play();
         Sound2.play();
    */


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(720, 480), "Tetris", sf::Style::Default,settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));


    bool HelpHover = false;
    bool BackHover = false;
    bool pressed_Button = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
                return 69;
                if(GameOverTimer >60) {

                    GameState = "Menu";
                }
            }


            if (event.type == sf::Event::Resized) {

                view = getLetterboxView( view, event.size.width, event.size.height );

            }




// get the current mouse position in the window
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
// convert it to world coordinates
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            /*
            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {
                cout<<worldPos.x<<" "<<worldPos.y<<endl;
            }
            */

            for(int i = 0; i<HelpTextBlocks.size(); i++) {
                if(isSpriteHover(HelpTextBlocks[i].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {


                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left && pressed_Button == false && GameState == "Menu") {

                        GameState = "Help";
                        pressed_Button = true;
                    }


                    HelpHover = false;

                    place = 0;
                    for(int j = 0; j<9; j++) {
                        for(int i = 0; i<19; i++) {


                            if(HelpButton[j][i]==0) {
                                HelpTextBlocks[place].setFillColor(sf::Color::Blue);
                            }

                            place++;
                        }
                    }

                } else {

                    if(i == HelpTextBlocks.size()-1 && HelpHover == true) {

                        place = 0;
                        for(int j = 0; j<9; j++) {
                            for(int i = 0; i<19; i++) {


                                if(HelpButton[j][i]==0) {
                                    HelpTextBlocks[place].setFillColor(sf::Color::Black);
                                }

                                place++;

                            }
                        }
                    }
                }
            }


            //-------------------


        for(int i = 0; i<BackTextBlocks.size(); i++) {
                if(isSpriteHover(BackTextBlocks[i].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) == true) {


                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left && pressed_Button == false && GameState == "Help") {

                        GameState = "Menu";
                        pressed_Button = true;
                    }


                    BackHover = false;

                    place = 0;
                    for(int j = 0; j<9; j++) {
                        for(int i = 0; i<19; i++) {


                            if(BackButton[j][i]==0) {
                                BackTextBlocks[place].setFillColor(sf::Color::Blue);
                            }

                            place++;
                        }
                    }

                } else {

                    if(i == BackTextBlocks.size()-1 && BackHover == true) {

                        place = 0;
                        for(int j = 0; j<9; j++) {
                            for(int i = 0; i<19; i++) {


                                if(BackButton[j][i]==0) {
                                    BackTextBlocks[place].setFillColor(sf::Color::Black);
                                }

                                place++;

                            }
                        }
                    }
                }
            }

            BackHover = true;
            HelpHover = true;
            pressed_Button = false;
        }

        //-------------




if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
GameState = "Help";

}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

            if(GameState == "Game" && PauseTimer >20) {

                GameState = "Pause";

            } else if(GameState == "Pause" && PauseTimer > 50) {

                PauseTimer = 0;
                GameState = "Game";


            }
        }





        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {


            if(GameState == "Menu") {

                BlockHandler(pickBlock(Blockqueue[queuePlace+1],LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),NextBricks,"Normal",500,150);
                BlockHandler(pickBlock(Blockqueue[queuePlace],LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,"Normal",250,50);


                queuePlace++;
                score = 0;
                place = 0;
                GameOverTimer = 0;
                scoreUpdate = true;
                GameOver = false;
                GameState = "Game";

                for(int i = 0; i<20; i++) {
                    for(int j = 0; j<10; j++) {

                        GameMatrix[j][i] = 0;

                    }
                }

                for(int i = 0; i<20; i++) {
                    for(int j = 0; j<10; j++) {

                        places[place].setFillColor(sf::Color::White);

                        place++;
                    }
                }


                for(int i = 0; i<ScoreBlocks.size(); i++) {

                    ScoreBlocks[i].setPosition(-1000,1000);
                }
            }
        }



        DownTime = 30;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

            DownTime = -1;

        }


        everyother++;

        if(everyother == 4) {
            everyother = 0;


            if(GameState == "Game") {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && CanLeft(Bricks, GameMatrix, places)) {

                    if(LeftRightTimer <60) {
                        for(int i = 0; i<8; i++) {

                            Bricks[i].setPosition(Bricks[i].getPosition().x-21,Bricks[i].getPosition().y);
                        }
                    }



                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && CanRight(Bricks,GameMatrix,places)) {



                    if(LeftRightTimer <60) {
                        for(int i = 0; i<8; i++) {
                            Bricks[i].setPosition(Bricks[i].getPosition().x+21,Bricks[i].getPosition().y);
                        }
                    }


                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {


                    FindOffset(rotateOffsetX, rotateOffsetY, Bricks);


                    if(currentShape == "TShape" || currentShape == "LShape" || currentShape == "L2Shape") {


                        if(RotationIndex>0) {
                            RotationIndex--;
                        } else {
                            RotationIndex = 3;
                        }
                    } else {

                        if(RotationIndex>0) {
                            RotationIndex--;
                        } else {
                            RotationIndex = 1;
                        }



                    }


                    BlockHandler(FindCurrentBlock(LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,ClockRot[RotationIndex],rotateOffsetX,rotateOffsetY);


                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

                    FindOffset(rotateOffsetX, rotateOffsetY, Bricks);


                    if(currentShape == "TShape" || currentShape == "LShape" || currentShape == "L2Shape") {

                        if(RotationIndex<3) {
                            RotationIndex++;
                        } else {
                            RotationIndex = 0;
                        }
                    } else {

                        if(RotationIndex<1) {
                            RotationIndex++;
                        } else {
                            RotationIndex = 0;
                        }

                    }

                    BlockHandler(FindCurrentBlock(LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,ClockRot[RotationIndex],rotateOffsetX,rotateOffsetY);

                }
            }
        }

        if(FullRow(GameMatrix,FullLine)>=0) {

            cout<<FullLine<<" Line done"<<endl;

            place = FullLine * 10;

            for(int j = 0; j<10; j++) {

                GameMatrix[j][FullLine] = 0;
                places[place].setFillColor(sf::Color::White);
                place++;

            }



            for(int i = FullLine; i>0; i--) {

                for(int j = 0; j<10; j++) {

                    GameMatrix[j][i]=GameMatrix[j][i-1];

                }
            }

//cout<<(FullLine * 10)<<" "<<(FullLine * 10)+10<<" "<<(FullLine * 10)+9<<endl;

            place = (FullLine * 10)+9;

            for(int i = place; i>-1; i--) {


                if(i-10 >0) {
                    places[i].setFillColor(places[i-10].getFillColor());

                } else {
                    places[i].setFillColor(sf::Color::White);
                }
            }

            score+=500;
            scoreUpdate = true;
        }


        if(whereFloor(Bricks,GameMatrix,places) == true && GameState == "Game") {


            LeftRightTimer++;

            if(LeftRightTimer > 60) {

                for(int i = 0; i<Bricks.size(); i++) {
                    if(Bricks[i].getPosition().y >0) {

                        temp = Bricks[i].getPosition().y;

                        LowestPointsY.push_back(temp);
                    }
                }


                for(int i = 0; i < places.size(); i++) {
                    for(int k = 0; k< LowestPointsY.size(); k++) {

                        if(places[i].getPosition().y == LowestPointsY[k]) {

                            LowestPointsY[k]=(i/10);

                            if(i<10) {
                                GameOver = true;
                            }
                        }
                    }
                }



                for(int j = 0; j<Bricks.size(); j++) {
                    for(int i = 0; i<places.size(); i++) {

                        if (places[i].getGlobalBounds().intersects(Bricks[j].getGlobalBounds())) {

                            places[i].setFillColor(CurrentColour);
                            Bricks[j].setPosition(-1000,-1000);

                            int col = 0, row = 0;

                            col = i%10;
                            row = i / 10;

                            GameMatrix[col][row] = 5;
                        }
                    }
                }



                CurrentColour = NextColour;

                do{

                NextColour = sf::Color(rand()%185+30,rand()%185+30,rand()%185+30);

                }while(NextColour.r >200 && NextColour.g >200 && NextColour.b >200);


                for(int i = 0; i<Bricks.size(); i++) {
                    Bricks[i].setFillColor(CurrentColour);
                }

                for(int i = 0; i<NextBricks.size(); i++) {
                    NextBricks[i].setFillColor(NextColour);
                }


                if(queuePlace <6) {

                    BlockHandler(pickBlock(Blockqueue[queuePlace+1],LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),NextBricks,"Normal",500,150);
                    BlockHandler(pickBlock(Blockqueue[queuePlace],LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,"Normal",250,50);

                    queuePlace++;

                } else {

                    QueueFiller(Blockqueue);

                    BlockHandler(pickBlock(Blockqueue[0],LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),NextBricks,"Normal",500,150);
                    BlockHandler(pickBlock(LastQueue,LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,"Normal",250,50);

                    queuePlace = 0;
                    LastQueue = Blockqueue[6];
                }

                RotationIndex = 0;
                LeftRightTimer = 0;
                score += 50;
                scoreUpdate = true;

            }
        }



        if(scoreUpdate == true) {

            scoreUpdate = false;

            place = 0;
            scoreXoffset = 22*5+460;

            stringstream ss;
            ss<<score;
            ss>>scoreString;

            for(int k = 0; k<scoreString.size(); k++) {

                if(scoreString.at(k)=='0') {

                    ScorePlacer(ScoreBlocks, Zero, place, scoreXoffset);
                } else if(scoreString.at(k)=='1') {

                    ScorePlacer(ScoreBlocks, One, place, scoreXoffset);
                } else if(scoreString.at(k)=='2') {

                    ScorePlacer(ScoreBlocks, Two, place, scoreXoffset);
                } else if(scoreString.at(k)=='3') {

                    ScorePlacer(ScoreBlocks, Three, place, scoreXoffset);
                } else if(scoreString.at(k)=='4') {

                    ScorePlacer(ScoreBlocks, Four, place, scoreXoffset);
                } else if(scoreString.at(k)=='5') {

                    ScorePlacer(ScoreBlocks, Five, place, scoreXoffset);
                } else if(scoreString.at(k)=='6') {

                    ScorePlacer(ScoreBlocks, Six, place, scoreXoffset);
                } else if(scoreString.at(k)=='7') {

                    ScorePlacer(ScoreBlocks, Seven, place, scoreXoffset);
                } else if(scoreString.at(k)=='8') {

                    ScorePlacer(ScoreBlocks, Eight, place, scoreXoffset);
                } else if(scoreString.at(k)=='9') {

                    ScorePlacer(ScoreBlocks, Nine, place, scoreXoffset);
                }
            }
        }




        if(godown > DownTime) {
            godown = 0;
            if(whereFloor(Bricks,GameMatrix,places) == false) {
                for(int i = 0; i<8; i++) {
                    Bricks[i].setPosition(Bricks[i].getPosition().x,Bricks[i].getPosition().y+21);
                }
            }
        }



        if(flashTimer == 30) {

            for(int i = 0; i<StartPlaces.size(); i++) {
                StartPlaces[i].setFillColor(sf::Color::Red);
            }

            MoveTitle(TitlePlaces,Title);

        } else if(flashTimer >60) {

            for(int i = 0; i<StartPlaces.size(); i++) {
                StartPlaces[i].setFillColor(sf::Color(10,10,10));
            }

            flashTimer = 0;

            MoveTitle(TitlePlaces,Title);
        }


        if(GameOverTimer == 80) {

            GameState = "Menu";
            GameOverTimer = 85;
        }


        if(GameState == "Game") {
            godown++;

            if(GameOver == true) {

                GameOverTimer++;
            }

        }
        if(GameState == "Menu") {
            flashTimer++;
        }


        PauseTimer++;





        window.clear();
        window.setView(view);


        window.draw(rectangle);


        if(GameState == "Menu") {
            for(int i = 0; i<TitlePlaces.size(); i++) {
                window.draw(TitlePlaces[i]);
            }

            for(int i = 0; i<StartPlaces.size(); i++) {
                window.draw(StartPlaces[i]);
            }

            for(int i = 0; i<HelpTextBlocks.size(); i++) {
                window.draw(HelpTextBlocks[i]);
            }

        }



        if(GameState == "Pause" || GameState == "Help") {

            for(int i = 0; i<KeyBindingsBlocks.size(); i++) {
                window.draw(KeyBindingsBlocks[i]);
            }


            for(int i = 0; i<HelpBlocks.size(); i++) {
                window.draw(HelpBlocks[i]);
            }
        }



 if(GameState == "Help") {

         for(int i = 0; i<BackTextBlocks.size(); i++) {
                window.draw(BackTextBlocks[i]);
            }

 }





        if(GameState == "Game" || GameState == "Pause") {

            for(int i = 0; i<places.size(); i++) {
                window.draw(places[i]);
            }
        }





        if(GameState == "Game") {

            for(int i = 0; i<Bricks.size(); i++) {
                window.draw(Bricks[i]);
            }

            for(int i = 0; i<NextPieceBlocks.size(); i++) {
                window.draw(NextPieceBlocks[i]);
            }

            for(int i = 0; i<NextBricks.size(); i++) {
                window.draw(NextBricks[i]);
            }


            for(int i = 0; i<StaticScore.size(); i++) {
                window.draw(StaticScore[i]);
            }

            for(int i = 0; i<ScoreBlocks.size(); i++) {
                window.draw(ScoreBlocks[i]);
            }

            if(GameOver == true) {
                for(int i = 0; i<GameOverPlaces.size(); i++) {
                    window.draw(GameOverPlaces[i]);
                }
            }
        }


        if(GameState == "Pause") {

            for(int i = 0; i<PauseBlocks.size(); i++) {
                window.draw(PauseBlocks[i]);
            }
        }








        sf::View view = window.getView();
        window.display();

    }

    return 0;
}
