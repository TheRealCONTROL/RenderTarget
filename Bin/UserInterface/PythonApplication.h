

#ifdef ENABLE_MODEL_RENDER_TARGET
#include "../eterLib/CRenderTarget.h"
#include "../eterLib/CRenderTargetManager.h"
#endif



class CPythonApplication : public CMSApplication, public CInputKeyboard, public IAbstractApplication
{
	
		[...]
		[...]
		[...]
		
		CGraphicDevice				m_grpDevice;
		CNetworkDevice				m_netDevice;

		CPythonSystem				m_pySystem;

#ifdef ENABLE_MODEL_RENDER_TARGET
		CRenderTargetManager		m_kRenderTargetManager;
#endif
		PyObject *					m_poMouseHandler;
		D3DXVECTOR3					m_v3CenterPosition;
		
		[...]
		[...]
		[...]
};