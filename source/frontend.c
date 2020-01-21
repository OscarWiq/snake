#include "backend.h"
#include "frontend.h"
#include <ncurses.h>

void displayPoints(PosList* playerPos, const chtype symbol) {
	while (playerPos) {
		mvaddch(playerPos->y, playerPos->x, symbol);
		playerPos = playerPos->next;
	}
}

enum Direction getNextMove(enum Direction prev) {
	int ch = getch();
	switch (ch) {
		case KEY_LEFT:
			if (prev != RIGHT) return LEFT;
		case KEY_RIGHT:
			if (prev != LEFT) return RIGHT;
		case KEY_DOWN:
			if (prev != UP) return DOWN;
		case KEY_UP:
			if (prev != DOWN) return UP;
		default:
			return prev;
	}
}
