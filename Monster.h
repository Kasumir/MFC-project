#pragma once

#define M_SIZE 48		//������ ���� ���� ����.
#define B_SIZE 48      //������ ���� ���� ����
#define C_SIZE 80      //ĳ������ ���� ���� ����
#define STOP 0
#define LEFT 1
#define RIGHT 2
#define UP 1
#define DOWN 2

// Monster

class Monster : public CWnd
{
	DECLARE_DYNAMIC(Monster)

public:
	CPoint m_pos;
	Monster();
	virtual ~Monster();
	BOOL m_bottom; //���͹��� ���� ����ִ���
	BOOL m_left;  //���� ���ʿ� ���� �ִ���
	BOOL m_right; //���� �����ʿ� ���� �ִ���
	BOOL m_visible;//���Ͱ� �����Ǿ� �ִ���
	int m_UDstate;
	int m_LRstate;
	int jumpcount;
	int Lcount;
	int Rcount;
	int random1;


protected:
	DECLARE_MESSAGE_MAP()
public:
	void MoveState();
	void StopState();
	void check(CList<CPoint, CPoint&>*);
	void MonsterDie();
	void MonsterCreate(int x, int y);
};