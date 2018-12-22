#include <SFML/Graphics.hpp>

#include <cstdlib>

//unit is pixel
const int CELL_LEN       = 15;

//unit is cells
const int SCREEN_ROWS    = 50;
const int SCREEN_COLS    = 50;

//unit is pixel
const int GAP            = 2;

sf::RectangleShape grid[SCREEN_ROWS][SCREEN_COLS];

sf::Color getRandColor(){
		
	//random value from 0 to 1000
	int randVal = rand()%1000;

	if(randVal < 300)
		return sf::Color::Black;
	return sf::Color::White;
}

void init(){
	int curR = GAP, curC = GAP;
	for(int i = 0; i < SCREEN_ROWS; ++i){
		for(int j = 0; j < SCREEN_COLS; ++j){
			grid[i][j].setSize(sf::Vector2f(CELL_LEN, CELL_LEN));
			grid[i][j].setPosition(sf::Vector2f(curR, curC));
			grid[i][j].setFillColor(getRandColor());
			curC += CELL_LEN + GAP;
		}
		curC = GAP;
		curR += CELL_LEN + GAP;
	}
}

void draw(sf::RenderWindow &window){
	
	for(int i = 0; i < SCREEN_ROWS; ++i){
		for(int j = 0; j < SCREEN_COLS; ++j){
			window.draw(grid[i][j]);
		}
	}

}

bool islive(int i, int j){
	return grid[i][j].getFillColor() == sf::Color::Black;
}

int di[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
int dj[] = { 0, 0, 1, -1, 1, -1, -1, 1 };
int live_neighbours_count(int i, int j){

	int cnt = 0;
	for(int dir = 0; dir < 8; ++dir){
		int ni = i + di[dir];
		int nj = j + dj[dir];

		if(ni < 0 or ni >= SCREEN_ROWS or nj < 0 or nj >= SCREEN_COLS) continue;
		if(islive(ni, nj)) ++cnt;
	}

	return cnt;
}

void next_generation(){
		
	bool nxtgen[SCREEN_ROWS][SCREEN_COLS] = { 0 };
	for(int i = 0; i < SCREEN_ROWS; ++i){
		for(int j = 0; j < SCREEN_COLS; ++j){
			int ncnt = live_neighbours_count(i, j);
				if(islive(i, j)){
					if(ncnt < 2 or ncnt > 3)
						nxtgen[i][j] = false; //die;
					else if (ncnt == 2 or ncnt == 3)
						nxtgen[i][j] = true; //live
				} else {
					if(ncnt == 3)
						nxtgen[i][j] = true; //live
				}
		}
	}

	for(int i = 0; i < SCREEN_ROWS; ++i){
		for(int j = 0; j < SCREEN_COLS; ++j){					
			if(nxtgen[i][j])
				grid[i][j].setFillColor(sf::Color::Black); //live
			else 
				grid[i][j].setFillColor(sf::Color::White); //dead
		}
	}
}

const int WIDTH = CELL_LEN * SCREEN_ROWS + (GAP * (SCREEN_ROWS+1));
const int HEIGHT = CELL_LEN * SCREEN_COLS + (GAP * (SCREEN_COLS+1));

int main(){

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "GameOfLife");
    window.setFramerateLimit(10);
		
	init();
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		next_generation();

        window.clear();
		draw(window);
        window.display();
    }

    return 0;
}
