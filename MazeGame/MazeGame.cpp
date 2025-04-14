#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

typedef stack<char> Room;
vector<Room> rooms;
int currentRoom = 0;
int currentPointer = 0;
bool treasureGrabbed = false;
int treasureRoom = 3;

void initializeRooms() {
    Room room1, room2, room3, room4;
    room1.push('-'); room1.push('/'); room1.push('-'); room1.push('-'); room1.push('-'); room1.push('-'); room1.push('-');
    room2.push('-'); room2.push('-'); room2.push('/'); room2.push('-'); room2.push('-');
    room3.push('-'); room3.push('/'); room3.push('-'); room3.push('-'); room3.push('-');
    room4.push('-'); room4.push('-'); room4.push('*'); room4.push('-'); room4.push('-');
    rooms.push_back(room1);
    rooms.push_back(room2);
    rooms.push_back(room3);
    rooms.push_back(room4);
}

void displayRoom() {
    cout << "Room " << currentRoom + 1 << endl;
    Room roomCopy = rooms[currentRoom];
    vector<char> roomTiles;
    while (!roomCopy.empty()) {
        roomTiles.push_back(roomCopy.top());
        roomCopy.pop();
    }
    for (int i = roomTiles.size() - 1; i >= 0; --i) {
        cout << (i == roomTiles.size() - 1 - currentPointer ? ">" : " ") << roomTiles[i] << endl;
    }
    cout << "w to move up, s to move down, x to enter door, z to grab treasure, q to quit." << endl;
}

void moveUp() {
    if (currentPointer < rooms[currentRoom].size() - 1) currentPointer++;
    else cout << "Can't move up, already at bottom" << endl;
}

void moveDown() {
    if (currentPointer > 0) currentPointer--;
    else cout << "Can't move down, already at top" << endl;
}

void enterDoor() {
    Room roomCopy = rooms[currentRoom];
    vector<char> roomTiles;
    while (!roomCopy.empty()) {
        roomTiles.push_back(roomCopy.top());
        roomCopy.pop();
    }
    char currentTile = roomTiles[roomTiles.size() - 1 - currentPointer];
    if (currentTile == '/') {
        cout << "Entering door" << endl;
        currentRoom = (currentRoom + 1) % rooms.size();
        currentPointer = 0;
    } else {
        cout << "You're not at a door" << endl;
    }
}

void grabTreasure() {
    Room roomCopy = rooms[currentRoom];
    vector<char> roomTiles;
    while (!roomCopy.empty()) {
        roomTiles.push_back(roomCopy.top());
        roomCopy.pop();
    }
    char currentTile = roomTiles[roomTiles.size() - 1 - currentPointer];
    if (currentRoom == treasureRoom && currentTile == '*') {
        cout << "You won the game!" << endl;
        treasureGrabbed = true;
        exit(0);
    } else {
        cout << "No treasure here" << endl;
    }
}

void gameLoop() {
    char input;
    while (true) {
        displayRoom();
        cout << "Enter move: ";
        cin >> input;
        if (input == 'q') break;
        else if (input == 's') moveUp();
        else if (input == 'w') moveDown();
        else if (input == 'x') enterDoor();
        else if (input == 'z') grabTreasure();
        else cout << "Invalid input" << endl;
    }
}

int main() {
    initializeRooms();
    gameLoop();
    return 0;
}
