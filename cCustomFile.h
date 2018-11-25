#pragma once
class cCustomFile
{
public:
	static bool LoadCustomFile(IN const char* szFullPath, IN std::set<std::string>& setCategory,
		OUT std::map<std::string, std::string>& mapLoadData);
	cCustomFile();
	~cCustomFile();
};

