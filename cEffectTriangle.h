#pragma once
class cEffectTriangle
{	
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	float                   m_fCurrentCount;

	SYNTHESIZE(float, m_fColorChangeTime, ColorChangeTime);
	SYNTHESIZE(float, m_fRed, RedSize);
	SYNTHESIZE(float, m_fGreen, GreenSize);
	SYNTHESIZE(float, m_fBlue, BlueSize);
	SYNTHESIZE(float, m_fAlpha, AlphaSize);
public:
	cEffectTriangle();
	~cEffectTriangle();

	void Setup(vector<ST_PC_VERTEX>	vecVertex);
	void Update();
	void Render();
};

//»¡¸® ÇÏ¼¼¿©

