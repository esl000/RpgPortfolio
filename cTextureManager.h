#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, D3DXIMAGE_INFO> m_mapImageInfo;

private:
	SINGLETONE(cTextureManager);

public:
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath, OUT D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath, OUT D3DXIMAGE_INFO* pImageInfo);
	void GetTexture(OUT LPDIRECT3DTEXTURE9* pOutTexture, OUT D3DXIMAGE_INFO* pImageInfo, char* szFullPath);
	void GetTexture(OUT LPDIRECT3DTEXTURE9* pOutTexture, OUT D3DXIMAGE_INFO* pImageInfo, std::string sFullPath);

	void Destroy();
};

