

#ifndef __D3dCommon_h__
#define __D3dCommon_h__

#define USE_D3DX  0

#if USE_D3DX

#include <d3dx9.h>

struct 	KCUSTOMVERTEX
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    DWORD color;    // The color
    FLOAT tu, tv;   // The texture coordinates
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd , LPDIRECT3D9 &pD3D, LPDIRECT3DDEVICE9 &pd3dDevice);


HRESULT ResetDevice(LPDIRECT3DDEVICE9 &pd3dDevice);
HRESULT ResetCreateDevice(HWND hWnd , LPDIRECT3D9 &pD3D, LPDIRECT3DDEVICE9 &pd3dDevice);

void FillD3DTextureFromBuffer(UINT Width, UINT Height, LPDIRECT3DTEXTURE9 &pTexture, DWORD* data, bool bA8L8 = false);

void D3DTextureToBuffer(UINT Width, UINT Height, LPDIRECT3DTEXTURE9 &pTexture, DWORD* io_Buffer);

//�ۦP�j�p�� D3d texture �P System::Drawing::Bitmap, �� D3d texture ����copy�L�k.
void D3DTextureToSystemDrawBitmap(LPDIRECT3DTEXTURE9 &pTexture, System::Drawing::Bitmap ^io_bitmap);

//�� D3d texture �����,�ӫإߤ@�� System::Drawing::Bitmap.
System::Drawing::Bitmap ^CreateSystemDrawBitmapFromD3DTexture(LPDIRECT3DTEXTURE9 &pTexture);
#endif

#endif