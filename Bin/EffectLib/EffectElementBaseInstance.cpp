
CEffectElementBaseInstance::CEffectElementBaseInstance()
	: mc_pmatLocal(nullptr)
	, m_isActive(false)
	, m_fLocalTime(0.0f)
	, m_dwStartTime(0)
	, m_fElapsedTime(0.0f)
	, m_fRemainingTime(0.0f)
	, m_bStart(false)
	, m_pBase(nullptr)
	#ifdef ENABLE_MODEL_RENDER_TARGET
	, m_ignoreFrustum(false)
	#endif
{
}
