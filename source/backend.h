#include <stdbool.h>

enum Direction { UP, DOWN, LEFT, RIGHT };
enum Status { OK, FAIL };
struct PosList {
	int x;
	int y;
	struct PosList* next;
};
typedef struct PosList PosList;

typedef struct {
	PosList* playerPos;
	PosList* targetPos;
	int x_max;
	int y_max;
} Map;

void addNewTarget(Map* map);
bool removeFromList(PosList* elt, PosList** list);
Map* createMap(PosList* targetPos, PosList* playerPosPos, int x_max, int y_max);
PosList* createPlayer();
bool listContains(PosList* cell, PosList* list);
PosList* createRandomCell(int x_max, int y_max);
PosList* createCell(int x, int y);
PosList* nextMove(Map* map, enum Direction dir);
enum Status movePlayer(Map* map, enum Direction dir);
bool samePos(PosList* c1, PosList* c2);
