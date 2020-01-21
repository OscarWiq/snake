#include "backend.h"
#include "frontend.h"
#include <string.h>
#include <ncurses.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	timeout(100);
	char game_over[] = "Game Over!\n";
	int end;

	int x_max;
	int y_max;
	getmaxyx(stdscr, y_max, x_max);
	enum Direction dir = RIGHT;

	Map* map = createMap(createPlayer(), NULL, x_max, y_max);
	for (int i = 0; i < 3; i++) {
		addNewTarget(map);
	}

	while (true) {
		clear();
		displayPoints(map->playerPos, ACS_BLOCK);
		displayPoints(map->targetPos, ACS_DIAMOND);
		refresh();
		dir = getNextMove(dir);
		enum Status status = movePlayer(map, dir);
		if (status == FAIL) break;
	}
	
	attron(A_BOLD);
	mvprintw(y_max/2, (x_max - strlen(game_over))/2, game_over);
	echo();
	refresh();
	sleep(2);
	endwin();

	return 0;
}
