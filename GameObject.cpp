#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	c_UDstate = DOWN;
	c_LRstate = STOP;
	c_visible = FALSE;
	jumpcount = 6;
	LRcount = 1;
	Water_drop.SetSize(4);
	wdcount[0] = 0;
	wdcount[1] = 0;
	wdcount[2] = 0;
	wdcount[3] = 0;
	c_lastLRstate = RIGHT;
}
GameObject::~GameObject()
{

}
void GameObject::check(CList<CPoint, CPoint&>* Tile_list)
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
	if (count == Tile_list->GetCount())
		c_UDstate = DOWN; // 타일숫자 = 검사한 숫자 -> 떨어짐.
	if (jumpcount == 6)
		c_UDstate = DOWN;

}
void GameObject::CreateCharacter(int x, int y)
{
	c_pos.x = x;
	c_pos.y = y;
	c_visible = TRUE;
}
void GameObject::DeleteCharacter()
{
	c_visible = FALSE;
}
void GameObject::WaterDrop()
{
	int index = 1;
	if (wdcount[0] == 0) {
		for (int i = 1; i <= 3; i++) {
			if (wdcount[i] == 0)	//물방울을 사용 중이지 않은 인덱스를 찾습니다.
				break;
			index++;
		}

		//찾은 인덱스에 새로운 물방울을 생성하는 코드입니다.

		if (index < 4) {
			CPoint pos = c_pos;
			if (c_lastLRstate == LEFT) {
				pos.x -= 40;
				wd_LRstate[index] = LEFT;
			}
			else {
				pos.x += 40;
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
	for (int i = 1; i <= 3; i++) {
		if (wdcount[i] > 0) {
			wdcount[i] -= 1;
			CPoint d_pos = Water_drop.GetAt(i);
			if (wd_LRstate[i] == RIGHT) {
				d_pos.x += 9;
			}
			else if (wd_LRstate[i] == LEFT)
			{
				d_pos.x -= 9;
			}
			Water_drop.SetAt(i, d_pos);
		}
	}

	//생성된 물방울이 존재 하는지 확인하는 코드입니다.
	if (wdcount[1] == 0)
		Water_drop[1].SetPoint(0, 0);
	else if (wdcount[2] == 0)
		Water_drop[2].SetPoint(0, 0);
	else if (wdcount[3] == 0)
		Water_drop[3].SetPoint(0, 0);
	if (wdcount[1] == 0 && wdcount[2] == 0 && wdcount[3] == 0) {	//생성된 물방울이 존재하지 않으면 보이지 않도록 설정합니다.
		wd_visible = FALSE;
	}
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