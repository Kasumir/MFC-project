#include "stdafx.h"
#include "GameObject.h"


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
}
GameObject::~GameObject()
{

}
void GameObject::check(CList<CPoint, CPoint&>* Tile_list)
{
	POSITION p;
	CPoint pos;
	int count = 0;
	for (p = Tile_list->GetHeadPosition(); p != NULL;) // ��� ������ ���� ��.
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
		else if (c_UDstate == STOP) // �ؿ� ������ �ִ��� ������ �˻�.
			if (!(c_pos.x > pos.x - C_SIZE && c_pos.x < pos.x + B_SIZE && c_pos.y > pos.y - C_SIZE && c_pos.y < pos.y - C_SIZE + B_SIZE / 2))
				count++;//�ؿ� ��� ������ ������ �˻�.
	}
	if (count == Tile_list->GetCount())
		c_UDstate = DOWN; // Ÿ�ϼ��� = �˻��� ���� -> ������.
	if (jumpcount == 6)
		c_UDstate = DOWN;

}
void GameObject::WD_Cehck(CList<CPoint, CPoint&>* Tile_list, CArray<CPoint,CPoint&>* Monster_point)
{
	for (int i = 1; i <= 10; i++) {
		CPoint wd_pos;
		wd_pos = Water_drop[i];

		POSITION p;
		CPoint tile_pos;
		int count = 0;

		// Ÿ�� �浹�� �˻��ϴ� �ڵ��Դϴ�.
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

		// ���� �浹�� �˻��ϴ� �ڵ��Դϴ�.
		for (int p = 1; p < Monster_point->GetSize() + 1; p++) {
			if (wd_LRstate[i] == LEFT) {
				if ((wd_pos.x - 36 <= Monster_point->GetAt(p-1).x) && (wd_pos.x >= Monster_point->GetAt(p - 1).x) && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y))
				{
					wdcount[i] = 0;
					break;
				}
				else if (wdcount[i] == 16 && Monster_point->GetAt(p - 1).x > c_pos.x - 40 && Monster_point->GetAt(p - 1).x <c_pos.x + 40 && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y)) {
					wdcount[i] = 0;
					break;
				}
			}
			else if (wd_LRstate[i] == RIGHT) {
				if ((wd_pos.x + 36 >= Monster_point->GetAt(p - 1).x) && (wd_pos.x <= Monster_point->GetAt(p - 1).x) && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y))
				{
					wdcount[i] = 0;
					break;
				}
				else if (wdcount[i] == 16 && Monster_point->GetAt(p - 1).x < c_pos.x + 40 && Monster_point->GetAt(p - 1).x >c_pos.x - 40 && (wd_pos.y + 24 > Monster_point->GetAt(p - 1).y) && (wd_pos.y - 24 < Monster_point->GetAt(p - 1).y)) {
					wdcount[i] = 0;
					break;
				}
			}
		}
	}
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
		for (int i = 1; i <= 10; i++) {
			if (wdcount[i] == 0)	//������� ��� ������ ���� �ε����� ã���ϴ�.
				break;
			index++;
		}

		//ã�� �ε����� ���ο� ������� �����ϴ� �ڵ��Դϴ�.

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
	//������� �̵���Ű�� �ڵ��Դϴ�.
	for (int i = 1; i <= 10; i++) {
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
	int count = 0;
	//������ ������� ���� �ϴ��� Ȯ���ϴ� �ڵ��Դϴ�.
	for (int i = 1; i <= 10; i++) {
		if (wdcount[i] == 0) {
			Water_drop[i].SetPoint(0, 0);
			count++;
		}
	}
	if (count == 10) {	//������ ������� �������� ������ ������ �ʵ��� �����մϴ�.
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