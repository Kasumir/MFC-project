#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include "Mmsystem.h"
#include "Digitalv.h"
//ĳ����, ���, ���͵� ������Ʈ�� ��κ��� ������ GameObject���Ͽ��� ������ ��ȹ
//���ʹ� ���������� �����ϹǷ�... ���⿡ �Լ� ���鼭 �ߴµ� �ȵǼ� Ŭ������ ����.
#define M_SIZE 48		//������ ���� ���� ����.
#define B_SIZE 48      //����� ���� ���� ����
#define C_SIZE 80      //ĳ������ ���� ���� ����
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

class GameObject  //��� ������Ʈ�� ������ Ŭ����
{
public:
	CPoint c_pos;
//	CString sound_damege;
	int c_UDstate;
	int c_LRstate;
	int jumpcount;
	int LRcount;
	int c_lastLRstate; // ĳ���Ͱ� ���������� �����ִ� ������ Ȯ���մϴ�.
	int wd_LRstate[11];	//�� ������� LR state ������ ��� �ֽ��ϴ�.
	int wdcount[11]; // ����� ī��Ʈ, �ε��� 0�� ���� �ֱ�� ������� ��� ���� OnPain()�� ȣ�� Ƚ���� �����մϴ�.
	int monster_index[11];
	int life;
	int life_time;
	BOOL c_bottom; //ĳ���͹��� ���� ����ִ���
	BOOL c_left;  //ĳ���� ���ʿ� ���� �ִ���
	BOOL c_right; //ĳ���� �����ʿ� ���� �ִ���
	BOOL c_visible;//ĳ���Ͱ� �����Ǿ� �ִ���
	BOOL c_space; //space ���� ����, space�� �����ִ��� ���¸� �����մϴ�.
	BOOL wd_visible; // ������� �����Ǿ� �ִ��� Ȯ���մϴ�.
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
	CArray<CPoint, CPoint&> Water_drop; //����� ��ǥ ����
	int monster_check(CPoint m_pos, int);
};