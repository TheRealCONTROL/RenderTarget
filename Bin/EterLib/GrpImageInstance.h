

class CGraphicImageInstance
{
	public:
		static DWORD Type();
		BOOL IsType(DWORD dwType);

	public:
		CGraphicImageInstance();
		virtual ~CGraphicImageInstance();

		void Destroy();

		void Render();

		void SetDiffuseColor(float fr, float fg, float fb, float fa);
		void SetPosition(float fx, float fy);
		#if defined(ENABLE_MODEL_RENDER_TARGET) || defined(ENABLE_OFFICAL_FEATURES)
		void SetScale(float fx, float fy);
		#endif

	[...]
	[...]
	[...]

	protected:
		D3DXCOLOR m_DiffuseColor;
		D3DXVECTOR2 m_v2Position;
		#if defined(ENABLE_MODEL_RENDER_TARGET) || defined(ENABLE_OFFICAL_FEATURES)
		D3DXVECTOR2 m_v2Scale;
		#endif

		CGraphicImage::TRef m_roImage;
	
	[...]
	[...]
	[...]
};