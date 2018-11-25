#pragma once
class cDataload
{
public:
	cDataload();
	~cDataload();

	static void GameLoad(ST_CHUNK_INDEX stIndex);

	static void Load(vector<cEntity*>& vecEntity);
	static void Load(vector<cEntity*>& vecEntity, ST_CHUNK_INDEX stIndex);

	static void Save(vector<cEntity*>& vecEntity);
	static void Save(vector<cEntity*>& vecEntity, ST_CHUNK_INDEX stIndex);
};

