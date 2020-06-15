#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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

                    Bricks[placeTemp].setPosition(i*20+i+offsetX,temp*20+temp+offsetY);

                } else {
                    Bricks[placeTemp].setPosition(i*20+i+offsetX,-1000);
                }
                placeTemp++;
            }
        }

    } else if(rotation == "Down") {

        for(int j = 1; j>-1; j--) {
            for(int i = 0; i < 4; i++) {

                if(Shape[i][j] != 0) {


                    Bricks[placeTemp].setPosition(i*20+i+offsetX,j*20+j+offsetY);

                } else {
                    Bricks[placeTemp].setPosition(i*20+i+offsetX,-1000);
                }
                placeTemp++;
            }

        }

    } else if(rotation == "Side") {

        for(int i = 0; i < 4; i++) {

            for(int j = 0; j<2; j++) {


                if(Shape[i][j] != 0) {
                    Bricks[placeTemp].setPosition(j*20+j+offsetX,i*20+i+offsetY);
                } else {
                    Bricks[placeTemp].setPosition(i*20+i+offsetX,-1000);
                }
                placeTemp++;
            }
        }

    } else if(rotation == "BackSide") {

        for(int i = 0; i < 4; i++) {

            for(int j = 0; j<2; j++) {

                if(Shape[i][j] != 0) {

                    if(j == 1)
                        temp = 0;

                    if(j == 0)
                        temp = 1;

                    Bricks[placeTemp].setPosition(temp*20+temp+offsetX,i*20+i+offsetY);
                } else {
                    Bricks[placeTemp].setPosition(i*20+i+offsetX,-1000);
                }
                placeTemp++;
            }
        }

    }

}


bool CanLeft(std::vector<sf::RectangleShape> &Bricks, vector<vector<int>> GameMatrix, std::vector<sf::RectangleShape> places) {

    vector<int> row;
    vector<int> col;
    vector<int> tempcol;
    int rowCal;

    for(int i = 0; i<Bricks.size(); i++) {

        if(Bricks[i].getPosition().y>0) {

            row.push_back(i);

            tempcol.push_back(Bricks[i].getPosition().y);

        }
    }

    for(int i = 0; i < places.size(); i++) {
        for(int k = 0; k< tempcol.size(); k++) {

            if(places[i].getPosition().y == tempcol[k]) {

                col.push_back(i/10);
            }
        }
    }

    for(int j = 0; j<row.size(); j++) {

        for(int i = 0; i<places.size(); i++) {
            for(int k = 0; k<col.size(); k++) {

                if(places[i].getPosition().x == Bricks[row[j]].getPosition().x && places[i].getPosition().y == Bricks[row[j]].getPosition().y ) {

                    rowCal = (int)Bricks[row[j]].getPosition().x%10;

                    if(rowCal>0) {
                        if(GameMatrix[rowCal-1][col[k]] > 0) {

                            return false;

                        }
                    }
                }
            }
        }
    }



    int temp = Bricks[0].getPosition().x;

    for(int i=0; i<Bricks.size(); i++) {

        if(Bricks[i].getPosition().x<temp && Bricks[i].getPosition().y >0) {
            temp = Bricks[i].getPosition().x;
        }
    }

    for(int i = 0; i < places.size(); i++) {

        if(places[i].getPosition().x == temp) {

            temp = i;
            break;
        }
    }

    if(temp >0) {
        return true;
    } else {
        return false;
    }

}


bool CanRight(std::vector<sf::RectangleShape> &Bricks, vector<vector<int>> GameMatrix, std::vector<sf::RectangleShape> places) {

    int temp = Bricks[0].getPosition().x;

    vector<int> row;
    vector<int> col;
    vector<int> tempcol;
    int rowCal;

    for(int i = 0; i<Bricks.size(); i++) {

        if(Bricks[i].getPosition().y>0) {

            row.push_back(i);

            tempcol.push_back(Bricks[i].getPosition().y);

        }
    }

    for(int i = 0; i < places.size(); i++) {
        for(int k = 0; k< tempcol.size(); k++) {

            if(places[i].getPosition().y == tempcol[k]) {

                col.push_back(i/10);
            }
        }
    }

    for(int j = 0; j<row.size(); j++) {

        for(int i = 0; i<places.size(); i++) {
            for(int k = 0; k<col.size(); k++) {

                if(places[i].getPosition().x == Bricks[row[j]].getPosition().x && places[i].getPosition().y == Bricks[row[j]].getPosition().y ) {

                    rowCal = (int)Bricks[row[j]].getPosition().x%10;


                    if(rowCal<9) {
                        if(GameMatrix[rowCal+1][col[k]] > 0) {
                            return false;

                        }
                    }
                }
            }
        }
    }




    for(int i=0; i<Bricks.size(); i++) {

        if(Bricks[i].getPosition().x>temp && Bricks[i].getPosition().y >0) {
            temp = Bricks[i].getPosition().x;
        }
    }

    for(int i = 0; i < places.size(); i++) {

        if(places[i].getPosition().x == temp) {

            temp = i;
            break;
        }
    }


    if(temp < 9) {
        return true;
    } else {
        return false;
    }
}



bool whereFloor(vector<sf::RectangleShape> &Bricks, vector<vector<int>> GameMatrix, std::vector<sf::RectangleShape> places) {

    vector<int> LowestPointsTemp;
    vector<int> LowestPoints;
    vector<int> LowestPointsX;

    int temp;
    int temp2;

    for(int i = 0; i<Bricks.size(); i++) {
        if(Bricks[i].getPosition().y >0) {

            temp = Bricks[i].getPosition().y;
            temp2 = (int)Bricks[i].getPosition().x%10;

            LowestPoints.push_back(temp);
            LowestPointsX.push_back(temp2);
        }
    }


    for(int i = 0; i < places.size(); i++) {
        for(int k = 0; k< LowestPoints.size(); k++) {

            if(places[i].getPosition().y == LowestPoints[k]) {

                LowestPoints[k]=(i/10);

                if(i>=190) {
                    return true;
                }
            }
        }
    }


    for(int k = 0; k<LowestPoints.size(); k++) {


        if(GameMatrix[LowestPointsX[k]][LowestPoints[k]+1] > 0) {

            return true;

        }
    }


    return false;
}


vector<vector<int>> pickBlock(vector<vector<int>> a, vector<vector<int>> b, vector<vector<int>> c, vector<vector<int>> d, vector<vector<int>> e, vector<vector<int>>f, vector<vector<int>> g, string &shape) {

    int Num = rand()%7;

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

}


int FindOffset(int &x, int &y, vector<sf::RectangleShape> &Bricks) {

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


int FullRow(vector<vector<int>> GameMatrix) {

    bool LineFull = true;
    int line;

    for(int i = 0; i<20; i++) {
        for(int j = 0; j<10; j++) {

            if(GameMatrix[j][i]>0) {

                if(j==9 && LineFull == true) {
                    line=i;
                    cout<<i<<" Line done"<<endl;
                }

            } else {
                LineFull = false;
            }
        }
        LineFull = true;
    }


    return line;
}


int main() {

    int godown = 0;
    int LeftRightTimer = 0;
    string currentShape = "LShape";
    sf::Color CurrentColour;

    int rotateOffsetX, rotateOffsetY;
    int RotationIndex = 0;

    int score;

    int everyother = 0;

    vector <string> ClockRot{"Normal","Side","Down","BackSide"};


    srand (time(NULL));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::RenderWindow window(sf::VideoMode(720, 480), "Totris", sf::Style::Default,settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));


    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(720, 480));

    rectangle.setFillColor(sf::Color(10,10,10));
    rectangle.setPosition(0, 0);


    vector<vector<int>> GameMatrix(201);
    std::vector<sf::RectangleShape> places(200);

    int place = 0;
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



    vector<vector<int>> LShape{
        {1,0},
        {1,0},
        {1,1},
        {0,0}};

    vector<vector<int>> L2Shape{
        {0,2},
        {0,2},
        {2,2},
        {0,0}};


    vector<vector<int>> SShape{
        {3,0},
        {3,3},
        {0,3},
        {0,0}};

    vector<vector<int>> ZShape{
        {0,4},
        {4,4},
        {4,0},
        {0,0}};

    vector<vector<int>> IShape{
        {5,0},
        {5,0},
        {5,0},
        {5,0}};

    vector<vector<int>> SquShape{
        {6,6},
        {6,6},
        {0,0},
        {0,0}};

    vector<vector<int>> TShape{
        {7,0},
        {7,7},
        {7,0},
        {0,0}};


    /*
    LShape
    L2Shape
    SShape
    ZShape
    IShape
    SquShape
    TShape
    */

    std::vector<sf::RectangleShape> Bricks(8);



    CurrentColour = sf::Color(rand()%185+30,rand()%185+30,rand()%185+30);

    for (int i = 0; i < 8; i++) {

        //    Bricks[i].setFillColor(sf::Color::Blue);

        Bricks[i].setFillColor(CurrentColour);
        Bricks[i].setSize(sf::Vector2f(20, 20));
        Bricks[i].setOrigin(10,10);
        Bricks[i].setPosition(0,-1000);
    }


    BlockHandler(pickBlock(LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,"Side",250,50);




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
                return 69;
            }

            if (event.type == sf::Event::Resized) {

                view = getLetterboxView( view, event.size.width, event.size.height );

            }
        }

        everyother++;

        if(everyother == 4) {
            everyother = 0;

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


                /*
                    LShape
                    L2Shape
                    SShape
                    ZShape
                    IShape
                    SquShape

                    */


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


        if(FullRow(GameMatrix)>-1){




        }


        if(whereFloor(Bricks,GameMatrix,places) == true) {

            LeftRightTimer++;

            if(LeftRightTimer > 60) {


                for(int j = 0; j<Bricks.size(); j++) {
                    for(int i = 0; i<places.size(); i++) {

                        if (places[i].getGlobalBounds().intersects(Bricks[j].getGlobalBounds())) {

                            places[i].setFillColor(CurrentColour);
                            Bricks[j].setPosition(1000,1000);

                            int col = 0, row = 0;

                            col = i%10;
                            row = i / 10;

                            GameMatrix[col][row] = 5;
                        }
                    }
                }


                CurrentColour = sf::Color(rand()%185+30,rand()%185+30,rand()%185+30);


                for(int i = 0; i<Bricks.size(); i++) {
                    Bricks[i].setFillColor(CurrentColour);
                }


                BlockHandler(pickBlock(LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,"Normal",250,50);
                RotationIndex = 0;
                LeftRightTimer = 0;
                //cout<<currentShape<<endl;


            }
        }



        if(godown > 20) {
            godown = 0;
            if(whereFloor(Bricks,GameMatrix,places) == false) {
                for(int i = 0; i<8; i++) {
                    Bricks[i].setPosition(Bricks[i].getPosition().x,Bricks[i].getPosition().y+21);
                }
            }

        }

        godown++;



        window.clear();
        window.setView(view);


        window.draw(rectangle);

        for(int i = 0; i<place; i++) {
            window.draw(places[i]);

        }

        for(int i = 0; i<Bricks.size(); i++) {
            window.draw(Bricks[i]);

        }


        sf::View view = window.getView();
        window.display();
    }

    return 0;
}

