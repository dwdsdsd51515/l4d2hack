

#define NUM_OF_TABS 3

enum
{
	FL_DISABLEDRAG = (1 << 1)
};

enum
{
	AIMTAB,
	ESPTAB,
	MISCTAB
};

enum
{
	ONOFF,
	DROPDOWN,
	SLIDER,
	ADDER
};

typedef struct DropDown_s
{
	int x, y;
	int iCount;

	float *fValues;
	float *cvar;

	char **ppszNames;
} DropDown_t;

class cMenuSection
{
public:
	void Draw(int x, int y, int w, int h);

	void AddElement(int iType, int add_to_x, const wchar_t *pszElementName, float *cvar, float min = 0, float max = 1, float step = 1);

	void DrawAllDropDowns();

	void PostSection()
	{
		DrawAllDropDowns();
	}

	void ClearSection()
	{
		vecDropDowns.clear();

		RestartSection();
	}

	void RestartSection()
	{
		iSection = 0;
	}

	void PostElement(int increment = 1)
	{
		iSection += increment;
	}
	
	void SetSlider(int &iCurrentSlider, bool bColor = false, float fLen = 360.0f)
	{
		bColored = bColor;

		fLength = fLen;
		
		iCurrentSlider++;
	}

	void SetSectionPos(int x, int y)
	{
		s_x = x;
		s_y = y;
	}

	void SetValueNames(char **szArrayArray, float *fArray, int iCount)
	{
		ppszValueNames = szArrayArray;
		fValueList = fArray;
		iValueCount = iCount;
	}

	void ClearAllElementSpecifics()
	{
		SetValueNames(NULL,NULL,0);
	}

private:
	void AddDropDownToDrawList(DropDown_t ddNew)
	{
		vecDropDowns.push_back(ddNew);
	}

	int iSection;
	int s_x, s_y;

	//dropdown specifics
	//----------------------
	float *fValueList;
	char **ppszValueNames;
	int iValueCount;
	bool bActiveDropDown[50];
	std::vector<DropDown_t> vecDropDowns;
	//----------------------

	//slider specifics
	//----------------------
	bool bColored;
	float fLength;
};

class cMenu
{
public:
	cMenu(int x, int y, int w, int h);

	void InitMenuElements();

	void DrawMenu();

	void SetMenuPos(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	void GetMenuPos(int &out_x, int &out_y)
	{
		out_x = m_x;
		out_y = m_y;
	}

	void GetMenuSize(int &out_w, int &out_h)
	{
		out_w = m_w;
		out_h = m_h;
	}

	bool IsHandlingItem()
	{
		return (iMenuFlags & FL_DISABLEDRAG);
	}

	void AddMenuFlag(int iFlag)
	{
		iMenuFlags |= iFlag;
	}

	void RemoveMenuFlag(int iFlag)
	{
		iMenuFlags &= ~iFlag;
	}

	int GetTabIndex()
	{
		return iTabIndex;
	}
private:
	void DrawTab(int index, int &setindex, int x, int y, const char *pszTitle);

	int m_x, m_y, m_w, m_h;
	int iMenuFlags;
	int iTabIndex;
};

extern cMenu g_Menu;