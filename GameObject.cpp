#include "stdafx.h"
#include "GameObject.h"
#include "resource.h"


GameObject::GameObject()
{
	c_UDstate = DOWN;
	c_LRstate = STOP;
	c_visible = FALSE;
	jumpcount = 6;
	LRcount = 1;
	Water_drop.SetSize(11);
	wdcount[0] = wdcount[1] = wdcount[2] = wdcount[3] = wdcount[4] = wdcount[5] = wdcount[6] = wdcount[7] = wdcount[8] = wdcount[9] = wdcount[10] = 0;
	c_lastLRstate = RIGHT;
	crash[0] = crash[1] = crash[2] = crash[3]=crash[4]=crash[5]=crash[6]=crash[7]=crash[8]=crash[9]=crash[10]=FALSE;
	life = 3;
	life_time = 0;
//	sound_damege = _T("res\ddiyoung.wav");
}
GameObject::~GameObject()
{

}
void GameObject::check(CList<CPoint, CPoint&>* Tile_list, CList<tilestyle, tilestyle>* LRTile_list)
{
	POSITION p;
	CPoint pos;
	int count = 0;
	for (p = Tile_list->GetHeadPosition(); p != NULL;) // 모든 벽돌에 대해 돎.
	{
		pos = Tile_list->GetNext(p);
		if (c_UDstate == DOWN)
		{
			if (c_pos.x > pos.x - C_SIZE && c_pos.x < pos.x + B_SIZE && c_pos.y > pos.y - C_SIZE && c_pos.y < pos.y - C_SIZE + B_SIZE / 2)
			{
				c_UDstate = STOP;
				c_pos.y = pos.y - C_SIZE;
			}
		}
		else if (c_UDstate == STOP) // 밑에 벽돌이 있는지 없는지 검사.
			if (!(c_pos.x > pos.x - C_SIZE && c_pos.x < pos.x + B_SIZE && c_pos.y > pos.y - C_SIZE && c_pos.y < pos.y - C_SIZE + B_SIZE / 2))
				count++;//밑에 모든 벽돌이 없는지 검사.
	}
	for (p = LRTile_list->GetHeadPosition(); p != NULL;) {
		tilestyle s = LRTile_list->GetNext(p);
		pos = s.pos;
		if (c_UDstate == DOWN)
		{
			if (c_pos.x > pos.x - C_SIZE && c_pos.x < pos.x + B_SIZE && c_pos.y > pos.y - C_SIZE && c_pos.y < pos.y - C_SIZE + B_SIZE / 2)
			{
				c_UDstate = STOP;
				c_pos.y = pos.y - C_SIZE;
			}
		}
		else if (c_UDstate == STOP) // 밑에 벽돌이 있는지 없는지 검사.
			if (!(c_pos.x > pos.x - C_SIZE && c_pos.x < pos.x + B_SIZE && c_pos.y > pos.y - C_SIZE && c_pos.y < pos.y - C_SIZE + B_SIZE / 2))
				count++;//밑에 모든 벽돌이 없는지 검사.
		if (c_LRstate == LEFT && s.right && c_pos.x > s.pos.x + B_SIZE - 15 && c_pos.x < s.pos.x + B_SIZE && c_pos.y > s.pos.y - C_SIZE && c_pos.y < s.pos.y + B_SIZE) //오른쪽 충돌
		{
			c_LRstate = STOP;
			LRcount = -1;
			c_pos.x = s.pos.x + B_SIZE + 1;
		}
		if (c_LRstate == RIGHT && s.left && c_pos.x + C_SIZE < s.pos.x + 15 && c_pos.x + C_SIZE > s.pos.x && c_pos.y > s.pos.y - C_SIZE && c_pos.y < s.pos.y  + B_SIZE) //왼쪽 충돌
		{
			c_LRstate = STOP;
			LRcount = 1;
			c_pos.x = s.pos.x - C_SIZE - 1;
		}
	}
	if (count == Tile_list->GetCount() + LRTile_list->GetCount())
		c_UDstate = DOWN; // 타일숫자 = 검사한 숫자 -> 떨어짐.
	if (jumpcount == 6)
		c_UDstate = DOWN;

}
void GameObject::WD_Cehck(CList<CPoint, CPoint&>* Tile_list, CArray<CPoint, CPoint&>* Monster_point)
{
	for (int i = 1; i <= 10; i++) {
		CPoint wd_pos;
		wd_pos = Water_drop[i];

		POSITION p;
		CPoint tile_pos;
		int count = 0;


		// 타일 충돌을 검사하는 코드입니다.
		for (p = Tile_list->GetHeadPosition(); p != NULL;)
		{
			tile_pos = Tile_list->GetNext(p);
			if (wd_LRstate[i] == LEFT) {
				if ((wd_pos.x - 36 <= tile_pos.x) && (wd_pos.x >= tile_pos.x) && (wd_pos.y + 24 > tile_pos.y) && (wd_pos.y - 24 < tile_pos.y))
				{
					wdcount[i] = 0;
					break;
				}
			}
			else if (wd_LRstate[i] == RIGHT) {
				if ((wd_pos.x + 36 >= tile_pos.x) && (wd_pos.x <= tile_pos.x) && (wd_pos.y + 24 > tile_pos.y) && (wd_pos.y - 24 < tile_pos.y))
				{
					wdcount[i] = 0;
					break;
				}
			}
		}

		// 몬스터 충돌을 검사하는 코드입니다.
		for (int p = 1; p < Monster_point->GetSize() + 1; p++) {
			if (wd_LRstate[i] == LEFT) {
				if ((wd_pos.x - 36 <= Monster_point->GetAt(p - 1).x) && (wd_pos.x >= Monster_point->GetAt(p - 1).x) && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y))
				{
					crash[i] = TRUE;
					monster_index[i] = p - 1;
					wdcount[i] = 0;
					break;
				}
				else if (wdcount[i] == 16 && Monster_point->GetAt(p - 1).x > c_pos.x - 40 && Monster_point->GetAt(p - 1).x < c_pos.x + 40 && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y)) {
					wdcount[i] = 0;
					crash[i] = TRUE;
					break;
				}
				else if (wdcount[i] == 16 && Monster_point->GetAt(p - 1).x < c_pos.x + 40 && Monster_point->GetAt(p - 1).x >c_pos.x - 40 && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y)) {
					wdcount[i] = 0;
					crash[i] = TRUE;
					break;
				}
			}
			else if (wd_LRstate[i] == RIGHT) {
				if ((wd_pos.x + 36 >= Monster_point->GetAt(p - 1).x) && (wd_pos.x <= Monster_point->GetAt(p - 1).x) && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y))
				{
					wdcount[i] = 0;
					crash[i] = TRUE;
					monster_index[i] = p - 1;
					break;
				}
				else if (wdcount[i] == 16 && Monster_point->GetAt(p - 1).x < c_pos.x + 40 && Monster_point->GetAt(p - 1).x >c_pos.x - 40 && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y)) {
					wdcount[i] = 0;
					crash[i] = TRUE;
					break;
				}
				else if (wdcount[i] == 16 && Monster_point->GetAt(p - 1).x > c_pos.x - 40 && Monster_point->GetAt(p - 1).x < c_pos.x + 40 && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y)) {
					wdcount[i] = 0;
					crash[i] = TRUE;
					break;
				}
			}
		}
	}
}

	

BOOL GameObject::CreateCharacter(int x, int y)
{
	if (c_visible)
		return FALSE;
	c_pos.x = x;
	c_pos.y = y;
	c_visible = TRUE;
	life = 3;
	return TRUE;
}
BOOL GameObject::DeleteCharacter()
{
	if (!c_visible)
		return FALSE;
	c_pos.x = -100;
	c_pos.y = -100;
	c_visible = FALSE;
	return TRUE;
}
void GameObject::WaterDrop()
{
	int index = 1;
	if (wdcount[0] == 0) {
		for (int i = 1; i <= 10; i++) {
			if (wdcount[i] == 0)	//물방울을 사용 중이지 않은 인덱스를 찾습니다.
				break;
			index++;
		}

		//찾은 인덱스에 새로운 물방울을 생성하는 코드입니다.

		if (index < 10) {
			CPoint pos = c_pos;
			if (c_lastLRstate == LEFT) {
				pos.x -= 65;
				pos.y += 25;
				wd_LRstate[index] = LEFT;
			}
			else {
				pos.x += 65;
				pos.y += 25;
				wd_LRstate[index] = RIGHT;
			}

			Water_drop.SetAt(index, pos);

			wdcount[index] = 16;
			wd_visible = TRUE;
		}
	}
}
void GameObject::WaterDropMove()
{
	//물방울을 이동시키는 코드입니다.
	for (int i = 1; i <= 10; i++) {
		if (wdcount[i] > 0) {
			wdcount[i] -= 1;
			CPoint d_pos = Water_drop.GetAt(i);
			if (wd_LRstate[i] == RIGHT) {
				d_pos.x += 13;
			}
			else if (wd_LRstate[i] == LEFT)
			{
				d_pos.x -= 13;
			}
			Water_drop.SetAt(i, d_pos);
		}
	}
	int count = 0;
	//생성된 물방울이 존재 하는지 확인하는 코드입니다.
	for (int i = 1; i <= 10; i++) {
		if (wdcount[i] == 0) {
			Water_drop[i].SetPoint(0, 0);
			count++;
		}
	}
	if (count == 10) {	//생성된 물방울이 존재하지 않으면 보이지 않도록 설정합니다.
		wd_visible = FALSE;
	}
}
BOOL GameObject::monstercrash(int i)
{
	return crash[i];
}
int GameObject::monsterindex(int i)
{
	return monster_index[i];
}

void GameObject::move()
{
	switch (c_UDstate) {
	case STOP:
		c_pos.y += 0;
		break;
	case UP:
		c_pos.y -= 16;
		break;
	case DOWN:
		c_pos.y += 16;
		if (c_pos.y > 611)
			c_pos.y = 0;
		break;
	}
	switch (c_LRstate) {
	case STOP:
		c_pos.x += 0;
		break;
	case LEFT:
		c_pos.x -= 15;
		break;
	case RIGHT:
		c_pos.x += 15;
		break;
	}
}

int GameObject::monster_check(CPoint m_pos, int m_state)
{
	/*if ((m_state == RIGHT)&& (m_pos.x<c_pos.x)&&(c_LRstate == LEFT)) {
		if ((m_pos.x +M_SIZE>= c_pos.x) && (c_pos.y - C_SIZE <= m_pos.y - M_SIZE) && (c_pos.y + M_SIZE >= m_pos.y))
		{
			life--;	
			c_pos.x = m_pos.x + M_SIZE + 2;
			m_pos.x = c_pos.x - M_SIZE - 2;
		}
	}
	else if ((m_state == LEFT)&& (m_pos.x>c_pos.x)&&(c_LRstate == RIGHT)) {
		if ((m_pos.x <= c_pos.x + C_SIZE) && (c_pos.y - C_SIZE <= m_pos.y - M_SIZE) && (c_pos.y + M_SIZE >= m_pos.y))
		{
			life--;
			c_pos.x = m_pos.x - C_SIZE - 2;
			m_pos.x = c_pos.x + C_SIZE + 2;
		}
	}*/
	
		if ((m_state == RIGHT) )
		{
			if (((m_pos.x + M_SIZE >= c_pos.x)) && (c_pos.y - C_SIZE <= m_pos.y - M_SIZE) && (c_pos.y + M_SIZE >= m_pos.y) && (m_pos.x < c_pos.x) )
			{
				if (life_time == 0)
				{
					life--;
					PlaySound(MAKEINTRESOURCE(IDR_DAM), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				}
				else
					life_time++;
//			else if((m_pos.x+M_SIZE>=c_pos.x)&&(c_pos.y-C_SIZE <= m_pos.y-M_SIZE)&& (c_pos.y + M_SIZE >= m_pos.y) && (m_pos.x<c_pos.x))
				
			}
			else
				life_time = 0;
		}
		else if ((m_state == LEFT))
		{
			if ((m_pos.x <= c_pos.x + C_SIZE) && (c_pos.y - C_SIZE <= m_pos.y - M_SIZE) && (c_pos.y + M_SIZE >= m_pos.y) && (m_pos.x > c_pos.x))
			{
				if (life_time == 0)
				{
					life--;
					PlaySound(MAKEINTRESOURCE(IDR_DAM), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				}
				else
					life_time++;
				
			}
			else
				life_time = 0;
		}
		

	return life;
}
