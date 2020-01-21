#include "backend.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

enum Status movePlayer(Map* map, enum Direction dir) {
	//start, check bounds
	PosList* start = nextMove(map, dir);
	if (!start) return FAIL;
	
	//never movebackwards	
	if (map->playerPos->next && samePos(start, map->playerPos->next)) {
		start->next = NULL;
		free(start);
		return OK;
	}
	
	//check collision
	if (listContains(start, map->playerPos)) return FAIL;

	//check for target
	if (listContains(start, map->targetPos)) {
		//add start to rest of player
		start->next = map->playerPos;
		map->playerPos = start;
		removeFromList(start, &(map->targetPos));
		addNewTarget(map);

		return OK;
	}

	start->next = map->playerPos;
	map->playerPos = start;

	//remove end
	PosList* end = map->playerPos;
	while (end->next->next) end = end->next;
	free(end->next);
	end->next = NULL;

	return OK;
}

bool samePos(PosList* c1, PosList* c2) {
	return c1->x == c2->x && c1->y == c2->y;
}

PosList* nextMove(Map* map, enum Direction dir) {
	PosList* playerPos = map->playerPos;

	int new_x = playerPos->x;
	int new_y = playerPos->y;
	switch(dir) {
		case UP:
			new_y = playerPos->y - 1;
			break;
		case DOWN:
			new_y = playerPos->y + 1;
			break;
		case LEFT:
			new_x = playerPos->x - 1;
			break;
		case RIGHT:
			new_x = playerPos->x + 1;
			break;

	}

	//Wrap player around screen
	if (new_x < 0) new_x = map->x_max + new_x;
	else if (new_y < 0) new_y = map->y_max + new_y;
	else if (new_x >= map->x_max) new_x = new_x - map->x_max;
	else if (new_y >= map->y_max) new_y = new_y - map->y_max;
	return createCell(new_x, new_y);
	
	//Old die at edge of map	
	//if (new_x < 0 || new_y < 0 || new_x >= map->x_max || new_y >= map->y_max) return NULL;
	//else return createCell(new_x, new_y);
}

PosList* createRandomCell(int x_max, int y_max) {
	return createCell(rand() % x_max, rand() % y_max);
}

void addNewTarget(Map* map) {
	PosList* new_targetPos;
	//dont create target at coordinates where player or target already exists
	do {
		new_targetPos = createRandomCell(map->x_max, map->y_max);
	} while (listContains(new_targetPos, map->targetPos) || listContains(new_targetPos, map->playerPos));
	//prepend new targetPos to list of target
	new_targetPos->next = map->targetPos;
	map->targetPos = new_targetPos;
}

bool listContains(PosList* cell, PosList* list) {
	PosList* s = list;
	while (s) {
		if (samePos(s, cell)) return true;
		s = s->next;
	}
	return false;
}

PosList* createCell(int x, int y) {
	PosList* cell = malloc(sizeof(*cell));
	cell->x = x;
	cell->y = y;
	cell->next = NULL;
	return cell;
}

Map* createMap(PosList* playerPos, PosList* targetPos, int x_max, int y_max) {
	Map* map = malloc(sizeof(*map));
	map->targetPos = targetPos;
	map->playerPos = playerPos;
	map->x_max = x_max;
	map->y_max = y_max;
	return map;
}

PosList* createPlayer() {
	PosList* a = createCell(20, 3);
	PosList* b = createCell(2, 2);
	a->next = b;
	return a;
}

//remove from list or return false
bool removeFromList(PosList* t, PosList** list) {
	PosList *prev_p, *cur_p;
	prev_p = NULL;

	for (cur_p = *list; cur_p != NULL; prev_p = cur_p, cur_p = cur_p->next) {
		if (samePos(cur_p, t)) {
			if (prev_p == NULL) {
				*list = cur_p->next;
			}
			else prev_p->next = cur_p->next;

			free(cur_p);
			return true;
		}
	}
	return false;
}

