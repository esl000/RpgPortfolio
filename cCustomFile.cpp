#include "stdafx.h"
#include "cCustomFile.h"



cCustomFile::cCustomFile()
{
}


cCustomFile::~cCustomFile()
{
}


bool cCustomFile::LoadCustomFile(IN const char* szFullPath, IN std::set<std::string>& setCategory, OUT std::map<std::string, std::string>& mapLoadData)
{
	FILE* fp;
	fopen_s(&fp, szFullPath, "r");

	if (!fp) return false;

	char* szToken = NULL;
	char* szContext = NULL;
	char szBuf[1024];

	while (true)
	{
		if (feof(fp)) break;
		fgets(szBuf, 1024, fp);
		szToken = strtok_s(szBuf, ":\n", &szContext);
		if (!szToken)
			return true;
		string sKey(szToken);
		szToken = strtok_s(szContext, ":\n", &szContext);
		if (!szToken)
			return true;
		string sValue(szToken);
		if (setCategory.find(sKey) != setCategory.end())
		{
			mapLoadData[sKey] = sValue;
		}
		szToken = NULL;
		szContext = NULL;
	}

	fclose(fp);

	return true;
}
