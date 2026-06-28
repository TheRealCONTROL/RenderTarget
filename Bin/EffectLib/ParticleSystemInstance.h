
class CParticleSystemInstance : public CEffectElementBaseInstance
{
	public:
		static void DestroySystem();

		static CParticleSystemInstance* New();
		static void Delete(CParticleSystemInstance* pkData);

		static CDynamicPool<CParticleSystemInstance>	ms_kPool;

	public:
		template <typename T>
		inline void ForEachParticleRendering(T&& FunObj) noexcept
		{
			const size_t size = m_kVct_pkImgInst.size();

			for (size_t i = 0; i < size; ++i)
			{
				STATEMANAGER.SetTexture(0, m_kVct_pkImgInst[i]->GetTextureReference().GetD3DTexture());
				auto& particleList = m_ParticleInstanceListVector[i];

				for (auto* pInstance : particleList)
				{
		#ifdef ENABLE_MODEL_RENDER_TARGET
					if (!m_ignoreFrustum && !InFrustum(pInstance))
		#else
					if (!InFrustum(pInstance))
		#endif
						return;

					std::forward<T>(FunObj)(pInstance);
				}
			}
		}
		
	[...]
	[...]
	[...]
};