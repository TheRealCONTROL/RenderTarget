


	protected:
		const D3DXMATRIX *						mc_pmatLocal;

		bool									m_isActive;

		float									m_fLocalTime;
		DWORD									m_dwStartTime;
		float									m_fElapsedTime;
		float									m_fRemainingTime;
		bool									m_bStart;

	private:
		CEffectElementBase *					m_pBase;

#ifdef ENABLE_MODEL_RENDER_TARGET
	protected:
		bool m_ignoreFrustum;
	public:
		void SetIgnoreFrustum(bool frustum) { m_ignoreFrustum = frustum; } 
#endif
};
