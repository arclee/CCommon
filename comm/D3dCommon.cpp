#include "stdafx.h"



#include "D3dCommon.h"


#if USE_D3DX
//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd , LPDIRECT3D9 &pD3D, LPDIRECT3DDEVICE9 &pd3dDevice)
{
    // Create the D3D object.
    if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	
    // Create the D3DDevice
    if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn off culling
    pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


    return S_OK;
}

HRESULT ResetCreateDevice(HWND hWnd , LPDIRECT3D9 &pD3D, LPDIRECT3DDEVICE9 &pd3dDevice)
{
	if (pd3dDevice)
	{
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory( &d3dpp, sizeof( d3dpp ) );
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		//HRESULT hr = pd3dDevice->Reset(&d3dpp);
		HRESULT hr = pd3dDevice->Release();
		pd3dDevice = 0;
	}

	return InitD3D(hWnd, pD3D, pd3dDevice);
}

HRESULT ResetDevice(LPDIRECT3DDEVICE9 &pd3dDevice)
{
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Turn off culling
    pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	return pd3dDevice->Reset(&d3dpp);

}

HRESULT DestroyDevice()
{



	return 0;
}


void FillD3DTextureFromBuffer(UINT Width, UINT Height, LPDIRECT3DTEXTURE9 &pTexture, DWORD* data, bool bA8L8)
{

	D3DLOCKED_RECT lockrect;
	DWORD *ptbuffer;
	ptbuffer = (DWORD *)lockrect.pBits;
	
	if(SUCCEEDED(pTexture->LockRect(0, &lockrect, NULL, D3DLOCK_DISCARD)))
	{
		//memcpy(lockrect.pBits, data, Width*Height*4);

		BYTE* pDstRow;
		pDstRow = (BYTE*)lockrect.pBits;
		DWORD* pDst32;
		WORD* pDst16;
		DWORD x, y;

		if (bA8L8)
		{
			for( y=0; y < Height; y++ )
			{
				pDst16 = (WORD*)pDstRow;
				for( x=0; x < Width; x++ )
				{
					BYTE *srcdata = (BYTE *)&data[Width*y + x];
					//alpha.
					pDst16[0] = 0xff;
					pDst16[1] = srcdata[3];


					pDst16++;
				}
				pDstRow += lockrect.Pitch;
			}
		}
		else
		{
			for( y=0; y < Height; y++ )
			{
				pDst32 = (DWORD*)pDstRow;
				for( x=0; x < Width; x++ )
				{
					*pDst32= data[Width*y + x];
					pDst32++;
				}
				pDstRow += lockrect.Pitch;
			}
		
		}

		
		pTexture->UnlockRect(0);
	}	
	
	//D3DXSaveTextureToFile("lockedRectTest.bmp", D3DXIFF_BMP, pTexture, NULL);

}
void D3DTextureToBuffer(UINT Width, UINT Height, LPDIRECT3DTEXTURE9 &pTexture, DWORD* io_Buffer)
{

	//D3DLOCKED_RECT lockrect;
	//DWORD *ptbuffer;
	//ptbuffer = (DWORD *)lockrect.pBits;
	//
	//if(SUCCEEDED(pTexture->LockRect(0, &lockrect, NULL, D3DLOCK_READONLY)))
	//{
	//	//memcpy(lockrect.pBits, data, Width*Height*4);

	//	BYTE* pDstRow;
	//	pDstRow = (BYTE*)lockrect.pBits;
	//	DWORD* pDst32;
	//	DWORD x, y;

	//	for( y=0; y < Height; y++ )
	//	{
	//		pDst32 = (DWORD*)pDstRow;
	//		for( x=0; x < Width; x++ )
	//		{
	//			io_Buffer[Width*y + x] = *pDst32;
	//			pDst32++;
	//		}
	//		pDstRow += lockrect.Pitch;
	//	}
	//	
	//	pTexture->UnlockRect(0);
	//}
	//
	//D3DXSaveTextureToFile("LoadTextureTest.bmp", D3DXIFF_BMP, pTexture, NULL);


}

void D3DTextureToSystemDrawBitmap(LPDIRECT3DTEXTURE9 &pTexture, System::Drawing::Bitmap ^io_bitmap)
{	
	D3DLOCKED_RECT lockrect;
	if(SUCCEEDED(pTexture->LockRect(0, &lockrect, NULL, D3DLOCK_READONLY)))
	{			
		for(int y=0;y< io_bitmap->Height;++y)
		{
			for(int x=0; x < io_bitmap->Width; ++x )
			{
				unsigned long index = (y * io_bitmap->Width) + x;
				unsigned long col = ((unsigned long*)lockrect.pBits)[index];
				System::Drawing::Color color = System::Drawing::Color::FromArgb(col);
				io_bitmap->SetPixel(x, y, color);
			}
		}
		pTexture->UnlockRect(0);
	}

}

System::Drawing::Bitmap ^CreateSystemDrawBitmapFromD3DTexture(LPDIRECT3DTEXTURE9 &pTexture)
{	
	D3DSURFACE_DESC desc;
	pTexture->GetLevelDesc(0, &desc);

	//.net
	System::Drawing::Bitmap ^bitmap = gcnew System::Drawing::Bitmap(desc.Width, desc.Height, System::Drawing::Imaging::PixelFormat::Format32bppArgb);

	D3DTextureToSystemDrawBitmap(pTexture, bitmap);

	return bitmap;

}
#endif

