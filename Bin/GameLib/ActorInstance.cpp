


BOOL CActorInstance::IsMovement()
{
	if (m_pkHorse)
		if (m_pkHorse->IsMovement())
			return TRUE;

	if (0.0f != m_v3Movement.x)
		return TRUE;
	if (0.0f != m_v3Movement.y)
		return TRUE;
	if (0.0f != m_v3Movement.z)
		return TRUE;

	return FALSE;
}

#ifdef ENABLE_MODEL_RENDER_TARGET
void CActorInstance::RenderAllAttachingEffect()
{
	for (const auto& it : m_AttachingEffectList)
		CEffectManager::Instance().RenderOne(it.dwEffectIndex);
}
#endif

