


	public:
		static CDynamicPool<CEffectInstance>	ms_kPool;
		static int ms_iRenderingEffectCount;
		
#ifdef ENABLE_MODEL_RENDER_TARGET
    protected:
        bool m_ignoreFrustum;

        struct FEffectFrustum
        {
            const bool ignoreFrustum;
            
            explicit FEffectFrustum(bool igno) noexcept
                : ignoreFrustum(igno)
            {
            }
            
            void operator()(CEffectElementBaseInstance* pInstance) const noexcept
            {
                pInstance->SetIgnoreFrustum(ignoreFrustum);
            }
        };

    public:
        void SetIgnoreFrustum(bool frustum)
		{
			m_ignoreFrustum = frustum;

			for (auto* p : m_ParticleInstanceVector)
				if (p) p->SetIgnoreFrustum(frustum);

			for (auto* p : m_MeshInstanceVector)
				if (p) p->SetIgnoreFrustum(frustum);

			for (auto* p : m_LightInstanceVector)
				if (p) p->SetIgnoreFrustum(frustum);
		}
#endif
};
