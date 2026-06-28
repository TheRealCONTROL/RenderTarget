

void CEffectInstance::__Initialize()
{
	m_isAlive = FALSE;
	m_dwFrame = 0;
	m_pSoundInstanceVector = NULL;
	m_fBoundingSphereRadius = 0.0f;
	m_v3BoundingSpherePosition.x = m_v3BoundingSpherePosition.y = m_v3BoundingSpherePosition.z = 0.0f;

	m_pkEftData=NULL;

#ifdef ENABLE_MODEL_RENDER_TARGET
	m_ignoreFrustum = false;
#endif
	D3DXMatrixIdentity(&m_matGlobal);
}