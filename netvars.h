#pragma once

typedef struct
{
	char szTableName[256];
	char szPropName[256];
	RecvVarProxyFn SavedProxy;
} Oldproxy_t;

class Netvarmanager
{
public:
	~Netvarmanager(void);
	void Init();
	int GetOffset(const char *tableName, const char *propName);
private:
	int Get_Prop(const char *tableName, const char *propName, RecvProp **prop = 0);
	int Get_Prop(RecvTable *recvTable, const char *propName, RecvProp **prop = 0);
	RecvTable *GetTable(const char *tableName);
	std::vector<RecvTable*> m_tables;
	std::vector<Oldproxy_t> m_savedproxy;
};

extern Netvarmanager g_Netvarmanager;
