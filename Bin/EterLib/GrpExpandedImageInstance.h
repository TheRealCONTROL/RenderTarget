


	protected:
		float m_fDepth;
		D3DXVECTOR2 m_v2Origin;
#ifndef ENABLE_MODEL_RENDER_TARGET
		D3DXVECTOR2 m_v2Scale;
#endif
		float m_fRotation;
		RECT m_RenderingRect;
		int m_iRenderingMode;