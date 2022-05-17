#include "RoomManager.h"
#include <algorithm>
#include <stdlib.h>     
#include <time.h> 
#include <math.h>

#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4
#define SPAWN_POINT_X 150
#define SPAWN_POINT_Y 120

RoomManager* RoomManager::pInstance = NULL;

using namespace std;

RoomManager::RoomManager()
{
	Level.resize(0);
	aRoom = 0;
	aLevel = 0;
	srand((unsigned int)time(NULL));
}

RoomManager::~RoomManager()
{
}

Room* RoomManager::getActualRoom()
{
	for (int i = 0; i < Level.size(); i++)
	{
		if (Level[i].getRoomID() == aRoom)
		{
			return &Level[i];
		}
	}
	return nullptr;
}

void RoomManager::changeRoom(int aR, int nMove, Player* p)
{
	aRoom = aR + nMove;
	if (nMove == 10)
	{
		p->getCol()->x = SCREEN_WIDTH / 2 - p->getCol()->w;
		p->getCol()->y = SPAWN_POINT_Y;
	}
	else if (nMove == -10)
	{
		p->getCol()->x = SCREEN_WIDTH / 2 - p->getCol()->w;
		p->getCol()->y = SCREEN_HEIGHT - SPAWN_POINT_Y - p->getCol()->h * 2;
	}
	else if (nMove == -1)
	{
		p->getCol()->y = SCREEN_HEIGHT / 2 - p->getCol()->h;
		p->getCol()->x = SCREEN_WIDTH - SPAWN_POINT_X - p->getCol()->w * 2;
	}
	else if (nMove == 1)
	{
		p->getCol()->y = SCREEN_HEIGHT / 2 - p->getCol()->h;
		p->getCol()->x = SPAWN_POINT_X;
	}
	getActualRoom()->init(p);
}

void RoomManager::createNewLevel(int lDiff)
{
	Level.resize(0);
	aRoom = 0;
	aLevel = lDiff;
	int maxRooms = min(20, (int)(rand()%2 + 5 + floor(lDiff * 10 / 3)));
	

#define HEIGHT 10
#define WIDTH 10
	int mapaLogic[HEIGHT][WIDTH];
	int casellaCount = 1;

	for (int X = 0; X < WIDTH; X++) {
		for (int Y = 0; Y < HEIGHT; Y++) {
			mapaLogic[X][Y] = 0; //Primer s’omple de 0 una array de 2 dimensions (en el meu cas de 10 X 10).
		}
	}
	int X = 4;
	int Y = 4;
	//S’agafa una X i Y inicials de forma random i es guarden en variables de la classe.
	vector<pos> recorrido;
	recorrido.resize(0);
	vector<int> moved; //Amb un vector de ints, comprovaré les posicions que no pot anar.
	while (casellaCount < maxRooms) { //Mentres no omplim totes les caselles.

		moved.resize(0);
		pos newPos;
		bool repeat = true;
		if (X == 0) { //A cada volta miro si estic en algun limit del mapa i faig pushback al vector de les posicions que no puc fer.
			moved.push_back(WEST);
		}
		else if (X == WIDTH - 1) {
			moved.push_back(EAST);
		}
		if (Y == 0) {
			moved.push_back(NORTH);
		}
		else if (Y == HEIGHT - 1) {
			moved.push_back(SOUTH);
		}
		do
		{
			int Move = 0;
			bool numRepeat = true;
			if (moved.size() == 4) { //mirem si el vector de moviments que hem triat està a 4 (hem intentat tots els moviments), si ho està hem de tirar enrere.
				repeat = false;
			}
			if (repeat) {
				while (numRepeat == true) { //Fem un bucle traient numeros random mentre no siguin els que tenim al vector.
					numRepeat = false;
					Move = (rand() % 4) + 1;
					for (int i = 0; i < moved.size(); i++)
					{
						if (Move == moved.at(i))
						{
							numRepeat = true;
						}
					}
				}
				switch (Move) {
				case NORTH:
					if (mapaLogic[X][Y - 1] == 0 && Y - 1 >= 0) {
						mapaLogic[X][Y] += 1;//obrim porta cap aquella direcció
						newPos.pX = X;//omplim un struct de posició
						newPos.pY = Y;
						recorrido.push_back(newPos);//fem pushback al recorregut
						Y--; //Movem la posició
						mapaLogic[X][Y] += 2; //creem la porta en el sentit contrari a la nova posició
						casellaCount++; //Sumem un al total de caselles.
						repeat = false;
					}
					else {
						moved.push_back(Move);//si no podem anar, fem pushback de la posicio
					}
					break;
				case SOUTH:
					if (mapaLogic[X][Y + 1] == 0 && Y + 1 < HEIGHT) {
						mapaLogic[X][Y] += 2;
						newPos.pX = X;
						newPos.pY = Y;
						recorrido.push_back(newPos);
						Y++;
						mapaLogic[X][Y] += 1;
						casellaCount++;
						repeat = false;
					}
					else {
						moved.push_back(Move);
					}
					break;
				case EAST:
					if (mapaLogic[X + 1][Y] == 0 && X + 1 < WIDTH) {
						mapaLogic[X][Y] += 4;
						newPos.pX = X;
						newPos.pY = Y;
						recorrido.push_back(newPos);
						X++;
						mapaLogic[X][Y] += 8;
						casellaCount++;
						repeat = false;
					}
					else {
						moved.push_back(Move);
					}
					break;
				case WEST:
					if (mapaLogic[X - 1][Y] == 0 && X - 1 >= 0) {
						mapaLogic[X][Y] += 8;
						newPos.pX = X;
						newPos.pY = Y;
						recorrido.push_back(newPos);
						X--;
						mapaLogic[X][Y] += 4;
						casellaCount++;
						repeat = false;
					}
					else {
						moved.push_back(Move);
					}
					break;
				default:
					break;
				}
			}
			else { //Si hem de tirar enrere
				X = recorrido.at(recorrido.size() - 1).pX; //assignem les X i Y a les x i y de la ulitma posició del vector
				Y = recorrido.at(recorrido.size() - 1).pY;
				recorrido.resize(recorrido.size() - 1);//li traiem la ultima posicio
			}
		} while (repeat);
	}

	for (int X = 0; X < WIDTH; X++) {
		for (int Y = 0; Y < HEIGHT; Y++) {
			if (mapaLogic[X][Y] != 0)
			{
				int roomID = X - 4 + ((Y - 4) * 10);
				Room nRoom(mapaLogic[X][Y], roomID);
				Level.push_back(nRoom);
			}
		}
	}
	for (int i = 0; i < Level.size(); i++)
	{
		if (Level[i].getRoomID() == 0)
		{
			int doors = 0;
			if (Level[i].getDoorVect()[0].angle == 0.0) doors = 180.0;
			else if (Level[i].getDoorVect()[0].angle == 180.0) doors = 0.0;
			else if (Level[i].getDoorVect()[0].angle == 270.0) doors = 90.0;
			else if (Level[i].getDoorVect()[0].angle == 90.0) doors = 270.0;
			Room nRoom(doors,-Level[i].getDoorVect()[0].idChange);
			Level.push_back(nRoom);
		}
	}
}
