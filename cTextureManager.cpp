#include "StdAfx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager(void)
{
}


cTextureManager::~cTextureManager(void)
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( std::string sFullPath )
{
	if(m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, sFullPath.c_str(), &m_mapTexture[sFullPath]);
	}
	return m_mapTexture[sFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( char* szFullPath )
{
	return GetTexture(std::string(szFullPath));
}

void cTextureManager::GetTexture(OUT LPDIRECT3DTEXTURE9* pOutTexture, OUT D3DXIMAGE_INFO* pImageInfo, char* szFullPath)
{
	GetTexture(pOutTexture, pImageInfo, std::string(szFullPath));
}

void cTextureManager::GetTexture(OUT LPDIRECT3DTEXTURE9* pOutTexture, OUT D3DXIMAGE_INFO* pImageInfo, std::string sFullPath)
{
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end() ||
		m_mapImageInfo.find(sFullPath) == m_mapImageInfo.end())
	{
		SAFE_RELEASE(m_mapTexture[sFullPath]);

		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			sFullPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[sFullPath],
			NULL,
			&m_mapTexture[sFullPath]);
	}

	if (pImageInfo)
	{
		*pImageInfo = m_mapImageInfo[sFullPath];
	}

	*pOutTexture = m_mapTexture[sFullPath];
}


LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string sFullPath, OUT D3DXIMAGE_INFO* pImageInfo)
{
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end() ||
		m_mapImageInfo.find(sFullPath) == m_mapImageInfo.end())
	{
		SAFE_RELEASE(m_mapTexture[sFullPath]);

		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			sFullPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[sFullPath],
			NULL,
			&m_mapTexture[sFullPath]);
	}

	if (pImageInfo)
	{
		*pImageInfo = m_mapImageInfo[sFullPath];
	}

	return m_mapTexture[sFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char* szFullPath, OUT D3DXIMAGE_INFO* pImageInfo)
{
	return GetTexture(std::string(szFullPath), pImageInfo);
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}
