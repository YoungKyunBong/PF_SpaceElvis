#pragma once
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <mutex>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <thread>
#include <sstream>
#include <chrono>

using namespace std;

#define SERVERPORT 9000
#define BUFSIZE    32
#define READ 1
#define WRITE 0

#define MAX_ITEM_SIZE 3

#define OBJECT_DELETETIME 5
#define OBJECT_COOLTIME 10
#define VR_TREE_COUNT_MAP1 20
#define RESPAWN_ACTOR_PC_COUNT 10

#define FIELD_OBJECT_TREE_DEMAGE (-5)
#define FIELD_OBJECT_ROCK_DEMAGE (-40)

#define ROCKET_DEMAGE (-20)
#define STONE_DEMAGE (-10)
#define FIELD_MISSILE_DEMAGE (-30)
#define HEAL 10;
#define FIRE (-1)
#define FALLSKY (-100)
#define FistAction (-20)

#define MAKE_ROCKS_MIN 3
#define MAKE_ROCKS_MAX 5

#define PC_StartRandomPosX_Min 0
#define PC_StartRandomPosX_MaX 200
#define PC_StartRandomPosY_Min -100
#define PC_StartRandomPosY_MaX 100
#define PC_StartRandomPosZ_Min 0
#define PC_StartRandomPosZ_MaX 250

#define VR_StartRandomPosX_Min 0
#define VR_StartRandomPosX_MaX 200
#define VR_StartRandomPosY_Min 0
#define VR_StartRandomPosY_MaX 200
#define VR_StartRandomPosZ_Min 0
#define VR_StartRandomPosZ_MaX 300

#define Hit_RockStunTime 3
#define Hit_GrabStunTime 10

#define PLAYER_RESPAWNTIME 5
#define VRHAND_RESPAWNTIME 10

#define GAME_END_TIME 3
#define GAME_END_SCORE 20

#define HIDE_ITEM_TIME 10
#define FIELD_OBJECT_TIME 10


enum ClientNodeType : UINT8
{
    Node0, Node1,
};

enum SendType : UINT8
{
    SendType_All, SendType_Wall, SendType_Floor, SendType_BG_Wall, SendType_BG_Floor,
};

struct Player_Socket
{
    UINT8 Main;
    UINT8 Sub;

    char Buffer[BUFSIZE];

    Player_Socket()
    {
        Main = 0;
        Sub = 0;
        memset(this, 0x0, sizeof(struct Player_Socket));
    }
};

struct SceneData
{
    string SceneType;
    SOCKET socket;
    ClientNodeType NodeType;

    bool SceneData::operator == (const SceneData& rhs) const
    {
        if ((SceneType == rhs.SceneType) && (socket == rhs.socket) && (NodeType == rhs.NodeType))
            return true;

        return false;
    }
};

struct SocketInfo
{
    SOCKET sock;
    SOCKADDR_IN clientAddr;
    int client_imei = -1;
};