#define MAX_DRAG_OBJECTS 3

class cMouse
{
public:
	void Update();

	bool LeftClick(int x,int y,int w,int h);
	bool OneLeftClick(int x,int y,int w,int h);
	bool IsOver(int x,int y,int w,int h);

	void Drag(bool& bDrag, bool bCheck, bool bDragCheck,int& x, int& y, int& xdif, int& ydif);

	void GetMousePosition(int &posx, int &posy)
	{
		posx = mouse_x;
		posy = mouse_y;
	}

	bool HasMouseOneJustBeenReleased()
	{
		return mouse1released;
	}

	bool IsMouseTwoBeingHeld()
	{
		return mouse2pressed;
	}

	bool bDragged[MAX_DRAG_OBJECTS];
	int iDiffX[MAX_DRAG_OBJECTS];
	int iDiffY[MAX_DRAG_OBJECTS];

	int mouse_x, mouse_y;
private:
	bool mouse1pressed;
	bool mouse2pressed;
	bool mouse2released;
	bool mouse1released;
};

extern cMouse g_Mouse;
