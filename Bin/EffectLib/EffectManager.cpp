

void CEffectManager::__DestroyEffectDataMap()
{
	for (const auto& [_, pEffectData] : m_kEftDataMap)
		CEffectData::Delete(pEffectData);
	
	m_kEftDataMap.clear();
}

#ifdef ENABLE_MODEL_RENDER_TARGET
void CEffectManager::RenderOne(DWORD id) noexcept
{
	STATEMANAGER.SetTexture(0, nullptr);
	STATEMANAGER.SetTexture(1, nullptr);

	const auto it = m_kEftInstMap.find(id);
	if (it != m_kEftInstMap.end()) {
		it->second->SetIgnoreFrustum(true);
		it->second->Show();
		it->second->Render();
	}
}
#endif

void CEffectManager::Destroy()
{
	__DestroyEffectInstanceMap();
	__DestroyEffectDataMap();

	__Initialize();
}
