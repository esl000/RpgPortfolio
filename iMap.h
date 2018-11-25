#pragma once
class iMap : public cObject
{
	friend class cTileManager;
public:
	virtual void Render() = 0;
	virtual bool GetHeight(IN float x, IN float z, OUT float& y) = 0;
};

