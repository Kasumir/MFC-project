// Monster.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Monster.h"
#include "GameObject.h"


// Monster

IMPLEMENT_DYNAMIC(Monster, CWnd)

Monster::Monster() // 몬스터 생성. 매개변수로 원하는 위치에 생성.
{
	jumpcount = 6;
	m_visible = TRUE;
	m_UDstate = DOWN;
	m_LRstate = STOP;
	Lcount = 0;
	Rcount = 0;
	random1 = 0;
	die = FALSE;
	followstate = FALSE;
}

Monster::~Monster()
{
	m_visible = FALSE;
}


BEGIN_MESSAGE_MAP(Monster, CWnd)
END_MESSAGE_MAP()



// Monster 메시지 처리기입니다.




void Monster::MoveState()//돌아다니다가 유저를 인식하면 쫓아감
{
	if (die == TRUE)
		StopState();
	else if (followstate != FALSE)
	{
		if (followstate == LEFT)
			m_LRstate = LEFT;
		else if (followstate == RIGHT)
			m_LRstate = RIGHT;
	}
	else
	{
		if (Lcount == 0 || Rcount == 0)
		{
			random1 = rand() % 3;
		}
		if (Lcount < 10 || Rcount < 10)
			if (random1 == 0) // 몬스터가 랜덤으로 돌아다님. 근데 점프 횟수를 더 적게.
			{
				m_LRstate = LEFT;
				Lcount++;
			}
			else if (random1 == 1)
			{
				m_LRstate = RIGHT;
				Rcount++;
			}
			else  if (random1 == 2)// 랜덤으로 점프
			{
				for (; jumpcount < 6; jumpcount++)
					m_UDstate = UP;
			}
		if (Lcount == 10 || Rcount == 10)
		{
			Lcount = 0;
			Rcount = 0;
		}
	}
	switch (m_UDstate) {
	case STOP:
		m_pos.y += 0;
		break;
	case UP:
		m_pos.y -= 16;
		break;
	case DOWN:
		m_pos.y += 16;
		if (m_pos.y > 611)
			m_pos.y = 0;
		break;
	}
	switch (m_LRstate) {
	case STOP:
		m_pos.x += 0;
		break;
	case LEFT:
		m_pos.x -= 8;
		break;
	case RIGHT:
		m_pos.x += 8;
		break;
	}

}


void Monster::StopState()//게임대기상태나 캐릭터에게 공격당해서 갇혀있는 상태
{
	m_LRstate = STOP;
	m_UDstate = STOP;
	m_pos.x += 0;
	m_pos.y += 0;

}



void Monster::check(CList<CPoint, CPoint&>* Tile_list)
{
	POSITION p;
	CPoint pos;
	int count = 0;
	for (p = Tile_list->GetHeadPosition(); p != NULL;) // 모든 벽돌에 대해 돎.
	{
		pos = Tile_list->GetNext(p);
		if (m_UDstate == DOWN) // 떨어지다가 땅에 붙도록.
		{
			if (m_pos.x > pos.x - M_SIZE && m_pos.x < pos.x + B_SIZE && m_pos.y > pos.y - M_SIZE && m_pos.y < pos.y - M_SIZE + B_SIZE / 2)
			{
				m_UDstate = STOP;
				m_pos.y = pos.y - M_SIZE;
			}
		}
		else if (m_UDstate == STOP) // 밑에 벽돌이 있는지 없는지 검사.
			if (!(m_pos.x > pos.x - M_SIZE && m_pos.x < pos.x + B_SIZE && m_pos.y > pos.y - M_SIZE && m_pos.y < pos.y - M_SIZE + B_SIZE / 2))
				count++;//밑에 모든 벽돌이 없는지 검사.

		if (m_LRstate == LEFT||m_LRstate == STOP) {
			if ((m_pos.x - B_SIZE <= pos.x) && (m_pos.x >= pos.x) && (m_pos.y + B_SIZE > pos.y) && (m_pos.y - B_SIZE < pos.y))
			{
				m_LRstate = STOP;
				m_pos.x = pos.x + B_SIZE;
			}
		}
		else if (m_LRstate == RIGHT||m_LRstate == STOP) {
			if ((m_pos.x + B_SIZE >= pos.x) && (m_pos.x <= pos.x) && (m_pos.y + B_SIZE > pos.y) && (m_pos.y - B_SIZE < pos.y))
			{
				m_LRstate = STOP;
				m_pos.x = pos.x - M_SIZE;
			}
		}

		if (count == Tile_list->GetCount())
			m_UDstate = DOWN; // 타일숫자 = 검사한 숫자 -> 떨어짐.
		if (jumpcount == 6) // 점프가 6번 프레임 만큼 돌고 떨어짐.
			m_UDstate = DOWN;
	}
}


void Monster::MonsterDie()
{
	m_visible = FALSE;
	m_pos.x = -1;
	m_pos.y = 0;
	m_LRstate = STOP;
	m_UDstate = STOP;
	die = TRUE;
}

void Monster::MonsterCreate(int x, int y)
{
	m_visible = TRUE;
	die = FALSE;
	m_pos.x = x;
	m_pos.y = y;
}

void Monster::followcharacter(CPoint point, int state)
{
	if (state == LEFT) {
		if ((m_pos.x + 48 * 4 + M_SIZE >= point.x) && (point.y <= m_pos.y + 48 * 4 + M_SIZE) && (point.y + C_SIZE >= m_pos.y - 48 * 4)&&(point.x>=m_pos.x))
		{
			followstate = RIGHT;
		}
		else
			followstate = 0;
	}
	else if (state == RIGHT) {
		if ((m_pos.x - 48 * 4 <= point.x + C_SIZE) && (point.y <= m_pos.y + 48 * 4 + M_SIZE) && (point.y + C_SIZE >= m_pos.y - 48 * 4)&&(point.x<=m_pos.x))
		{
			followstate = LEFT;
		}
		else
			followstate = 0;
	}
}
