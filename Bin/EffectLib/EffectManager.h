
class CEffectManager : public CScreen, public CSingleton<CEffectManager>
{
	public:
		using TEffectDataMap     = ankerl::unordered_dense::map<DWORD, CEffectData*>;
		using TEffectInstanceMap = ankerl::unordered_dense::map<DWORD, CEffectInstance*>;

	public:
		CEffectManager();
		virtual ~CEffectManager();

		void Destroy();

		void UpdateSound();
		void Update();
		void Render();
#ifdef ENABLE_MODEL_RENDER_TARGET
		void RenderOne(DWORD id) noexcept;
#endif
		void GetInfo(std::string* pstInfo);

		bool IsAliveEffect(DWORD dwInstanceIndex);
		
	[...]
	[...]
	[...]
};