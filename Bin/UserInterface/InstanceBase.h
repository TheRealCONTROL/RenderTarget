


class CInstanceBase
{
	
	[...]
	[...]
	[...]
	
	protected:
		static DWORD ms_dwUpdateCounter;
		static DWORD ms_dwRenderCounter;
		static DWORD ms_dwDeformCounter;

	public:
		DWORD					GetDuelMode();
		void					SetDuelMode(DWORD type);
	protected:
		DWORD					m_dwDuelMode;
		DWORD					m_dwEmoticonTime;

	
#ifdef ENABLE_MODEL_RENDER_TARGET
	protected:
		bool m_IsAlwaysRender;
	public:
		bool IsAlwaysRender();
		void SetAlwaysRender(bool val);
		void SetStoneSmokeEffect();
#endif

	[...]
};