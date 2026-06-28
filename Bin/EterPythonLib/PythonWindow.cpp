#ifdef ENABLE_MODEL_RENDER_TARGET
#include "../eterLib/CRenderTargetManager.h"
#endif







	// find this
	void CDragButton::OnMouseOverOut()
	{
		if (!IsEnable())
			return;

		CButton::OnMouseOverIn();
		PyCallClassMemberFunc(m_poHandler, "OnMouseOverOut", BuildEmptyTuple());
	}
	
	
	
	// add this
	#ifdef ENABLE_MODEL_RENDER_TARGET
	CUiRenderTarget::CUiRenderTarget(PyObject* ppyObject) : CWindow(ppyObject)
	{
		m_dwIndex = -1;
	}
	CUiRenderTarget::~CUiRenderTarget() = default;

	int CUiRenderTarget::SetRenderTarget()
	{
		const int index = (m_dwIndex == -1) ? CRenderTargetManager::Instance().GetFreeIndex() : m_dwIndex;
		
		if (!CRenderTargetManager::Instance().GetRenderTarget(index))
		{
			if (!CRenderTargetManager::Instance().CreateRenderTarget(index, GetWidth(), GetHeight()))
			{
				TraceError("CRenderTargetManager could not create the texture. w %d h %d for index %d", GetWidth(), GetHeight(), m_dwIndex);
				return m_dwIndex;
			}
		}
		m_dwIndex = index;

		UpdateRect();
		return m_dwIndex;
	}

	void CUiRenderTarget::OnRender()
	{
		auto target = CRenderTargetManager::Instance().GetRenderTarget(m_dwIndex);
		if (!target)
		{
			TraceError("SetRenderingRect -> target empty!");
			return;
		}
		
		target->SetRenderingRect(&m_rect);
		target->RenderTexture();
	}
	#endif
};