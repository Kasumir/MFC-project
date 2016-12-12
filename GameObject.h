#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include "Mmsystem.h"
#include "Digitalv.h"
//캐릭터, 블록, 몬스터등 오브젝트들 대부분의 정보를 GameObject파일에서 관리할 계획
//몬스터는 여러마리를 생성하므로... 여기에 함수 쓰면서 했는데 안되서 클래스로 보냄.
#define M_SIZE 48		//몬스터의 가로 세로 길이.
#define B_SIZE 48      //블록의 가로 세로 길이
#define C_SIZE 80      //캐릭터의 가로 세로 길이
#define STOP 0
#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2

typedef struct Tilestyle {
	CPoint pos;
	BOOL left;
	BOOL right;
}tilestyle;

class GameObject  //모든 오브젝트를 관리할 클레스
{
public:
	CPoint c_pos;
//	CString sound_damege;
	int c_UDstate;
	int c_LRstate;
	int jumpcount;
	int LRcount;
	int c_lastLRstate; // 캐릭터가 마지막으로 보고있던 방향을 확인합니다.
	int wd_LRstate[11];	//각 물방울의 LR state 정보를 담고 있습니다.
	int wdcount[11]; // 물방울 카운트, 인덱스 0은 일정 주기로 물방울을 쏘기 위해 OnPain()의 호출 횟수를 점검합니다.
	int monster_index[11];
	int life;
	int life_time;
	BOOL c_bottom; //캐릭터발이 땅에 닿아있는지
	BOOL c_left;  //캐릭터 왼쪽에 벽이 있는지
	BOOL c_right; //캐릭터 오른쪽에 벽이 있는지
	BOOL c_visible;//캐릭터가 생성되어 있는지
	BOOL c_space; //space 상태 정보, space가 눌려있는지 상태를 점검합니다.
	BOOL wd_visible; // 물방울이 생성되어 있는지 확인합니다.
	BOOL crash[11];

public:
	void move();
	void check(CList<CPoint, CPoint&>*, CList<tilestyle, tilestyle>*);
	void WD_Cehck(CList<CPoint, CPoint&>*, CArray<CPoint, CPoint&>*);
	BOOL CreateCharacter(int, int);
	BOOL DeleteCharacter();
	void WaterDrop();
	void WaterDropMove();
	int monsterindex(int);
	BOOL monstercrash(int);
	GameObject();
	~GameObject();

public:
	CArray<CPoint, CPoint&> Water_drop; //물방울 좌표 저장
	int monster_check(CPoint m_pos, int);
};