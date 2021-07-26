
#include "hooks.h"

Netvarmanager g_Netvarmanager;

void Netvarmanager::Init(void)
{
	m_tables.clear();
	m_savedproxy.clear();

	ClientClass *clientClass = pClient->GetAllClasses();

	if (!clientClass)
	{
		return;
	}

	while (clientClass)
	{
		RecvTable *recvTable = clientClass->GetTable;

		m_tables.push_back(recvTable);

		clientClass = clientClass->NextClass;
	}
}

Netvarmanager::~Netvarmanager(void)
{
	for (int i = 0; i < m_savedproxy.size(); i++)
	{
		RecvProp *recvProp = 0;
		Get_Prop(m_savedproxy[i].szTableName, m_savedproxy[i].szPropName, &recvProp);

		if (!recvProp)
			return;

		recvProp->m_ProxyFn = m_savedproxy[i].SavedProxy;
	}
}

int Netvarmanager::GetOffset(const char *tableName, const char *propName)
{
	int offset = Get_Prop(tableName, propName);

	if (!offset)
	{
		return 0;
	}

	return offset;
}


int Netvarmanager::Get_Prop(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = GetTable(tableName);

	if (!recvTable)
	{
		return 0;
	}


	int offset = Get_Prop(recvTable, propName, prop);

	if (!offset)
	{
		return 0;
	}


	return offset;
}


int Netvarmanager::Get_Prop(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;

	for (int i = 0; i < recvTable->m_nProps; ++i)
	{
		RecvProp *recvProp = &recvTable->m_pProps[i];


		RecvTable *child = recvProp->m_pDataTable;

		if (child
			&& (child->m_nProps > 0))
		{
			int tmp = Get_Prop(child, propName, prop);

			if (tmp)
			{
				extraOffset += (recvProp->m_Offset + tmp);
			}
		}


		if (_stricmp(recvProp->m_pVarName, propName))
		{
			continue;
		}


		if (prop)
		{
			*prop = recvProp;
		}

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}


RecvTable *Netvarmanager::GetTable(const char *tableName)
{
	if (m_tables.empty())
	{
		return 0;
	}


	for each (RecvTable *table in m_tables)
	{
		if (!table)
		{
			continue;
		}


		if (_stricmp(table->m_pNetTableName, tableName) == 0)
		{
			return table;
		}
	}

	return 0;
}
