#include <iostream>
#include <cmath>
#include <vector>

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
                    Bricks[placeTemp].setPosition(temp*20+temp+offsetX,-1000);
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


vector<vector<int>> pickBlock(vector<vector<int>> a, vector<vector<int>> b, vector<vector<int>> c, vector<vector<int>> d, vector<vector<int>> e, vector<vector<int>>f, vector<vector<int>> g, string &shape) {

    int Num = rand()%7;

    //Num = 6;

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


int main() {

    srand (time(NULL));

    int godown = 0;
    int LeftRightTimer = 0;
    int rotateOffsetX, rotateOffsetY;
    int RotationIndex = 0;
    int score = 0;
    int everyother = 0;
    int FullLine = 0;
    int place = 0;
    int flashTimer = 0;
    int DownTime = 30;

    string currentShape = "LShape";
    string GameState = "Menu";
    const vector <string> ClockRot{"Normal","Side","Down","BackSide"};


    const vector<vector<int>> Title = {
        {1,1,1,0,1,1,0,1,1,1,0,1,1,0,0,1,0,0,1,1},
        {0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0},
        {0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1},
        {0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,0}
    };

    const vector<vector<int>> PressStart = {
        {1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1},
        {1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0},
        {1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,0,0,0,1,0},
        {1,0,0,0,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0},
        {1,0,0,0,1,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0}
    };

 const vector<vector<int>> LShape = {
        {1,0},
        {1,0},
        {1,1},
        {0,0}};

    const vector<vector<int>> L2Shape = {
        {0,2},
        {0,2},
        {2,2},
        {0,0}};

    const vector<vector<int>> SShape = {
        {3,0},
        {3,3},
        {0,3},
        {0,0}};

    const vector<vector<int>> ZShape = {
        {0,4},
        {4,4},
        {4,0},
        {0,0}};

    const vector<vector<int>> IShape = {
        {5,0},
        {5,0},
        {5,0},
        {5,0}};

    const vector<vector<int>> SquShape = {
        {6,6},
        {6,6},
        {0,0},
        {0,0}};

    const vector<vector<int>> TShape = {
        {7,0},
        {7,7},
        {7,0},
        {0,0}};


    sf::Color CurrentColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(720, 480));
    rectangle.setFillColor(sf::Color(10,10,10));
    rectangle.setPosition(0, 0);

    vector<vector<int>> GameMatrix(201);
    std::vector<sf::RectangleShape> places(200);
    std::vector<sf::RectangleShape> TitlePlaces(45);
    std::vector<sf::RectangleShape> StartPlaces(85);
    std::vector<sf::RectangleShape> Bricks(8);


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

    place = 0;

    for(int j = 0; j<5; j++) {
        for(int i = 0; i<20; i++) {

            if(Title[j][i]>0) {
                TitlePlaces[place].setFillColor(CurrentColour);
                TitlePlaces[place].setSize(sf::Vector2f(20, 20));
                TitlePlaces[place].setOrigin(10,10);

                TitlePlaces[place].setPosition(i*20+i+145,j*20+j+50);
                place++;
            }
        }
        CurrentColour = sf::Color(rand()%205+25,rand()%205+25,rand()%205+25);
    }

    place = 0;

    for(int j = 0; j<5; j++) {
        for(int i = 0; i<40; i++) {

            if(PressStart[j][i]>0) {

                StartPlaces[place].setFillColor(sf::Color::Red);
                StartPlaces[place].setSize(sf::Vector2f(10, 10));
                StartPlaces[place].setOrigin(5,5);

                StartPlaces[place].setPosition(i*10+i+150,j*10+j+250);

                place++;
            }
        }
    }


    CurrentColour = sf::Color(rand()%185+30,rand()%185+30,rand()%185+30);

    for (int i = 0; i < 8; i++) {

        Bricks[i].setFillColor(CurrentColour);
        Bricks[i].setSize(sf::Vector2f(20, 20));
        Bricks[i].setOrigin(10,10);
        Bricks[i].setPosition(0,-1000);
    }


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


    sf::Clock clock; // starts the clock

    sf::Time elapsed1;
    sf::Time elapsed2;


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

        /*
        elapsed1 = clock.getElapsedTime();
        std::cout << elapsed1.asSeconds() << std::endl;
        clock.restart();


        elapsed2 = clock.getElapsedTime();
        std::cout << elapsed2.asSeconds() << std::endl;
        */

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {


            if(GameState == "Menu") {

                BlockHandler(pickBlock(LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,"Side",250,50);
                cout<<currentShape<<endl;


                for(int i = 0; i<TitlePlaces.size(); i++) {

                    TitlePlaces[i].setPosition(-1000,-1000);

                }

            }

            GameState = "Game";
        }




        everyother++;

        if(everyother == 4) {
            everyother = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && CanLeft(Bricks, GameMatrix, places)) {


                if(GameState == "Game") {
                    if(LeftRightTimer <60) {
                        for(int i = 0; i<8; i++) {

                            Bricks[i].setPosition(Bricks[i].getPosition().x-21,Bricks[i].getPosition().y);
                        }
                    }
                }


            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && CanRight(Bricks,GameMatrix,places)) {

                if(GameState == "Game") {

                    if(LeftRightTimer <60) {
                        for(int i = 0; i<8; i++) {
                            Bricks[i].setPosition(Bricks[i].getPosition().x+21,Bricks[i].getPosition().y);
                        }
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
                if(GameState == "Game") {
                    cout<<ClockRot[RotationIndex]<<endl;
                    BlockHandler(FindCurrentBlock(LShape, L2Shape, SShape, ZShape, IShape, SquShape, TShape, currentShape),Bricks,ClockRot[RotationIndex],rotateOffsetX,rotateOffsetY);
                }

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

                if(GameState == "Game") {
                    cout<<ClockRot[RotationIndex]<<endl;
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
                cout<<currentShape<<endl;
                RotationIndex = 0;
                LeftRightTimer = 0;

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



        } else if(flashTimer >60) {

            for(int i = 0; i<StartPlaces.size(); i++) {
                StartPlaces[i].setFillColor(sf::Color(10,10,10));
            }

            flashTimer = 0;
        }




        if(GameState == "Game") {
            godown++;
        }
        if(GameState == "Menu") {
            flashTimer++;
        }

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
        }


        if(GameState == "Game") {
            for(int i = 0; i<places.size(); i++) {
                window.draw(places[i]);
            }


            for(int i = 0; i<Bricks.size(); i++) {
                window.draw(Bricks[i]);
            }

        }


        sf::View view = window.getView();
        window.display();
    }

    return 0;
}

