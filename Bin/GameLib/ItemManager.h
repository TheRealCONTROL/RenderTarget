
	public:
		CItemManager();
		virtual ~CItemManager();
		
		[...]
		[...]
		[...]
		
		#ifdef ENABLE_MODEL_RENDER_TARGET
		bool 			CanUseByRaceAndGender(int race, const CItemData* itemData);
		#endif
		CItemData *		MakeItemData(DWORD dwIndex);


		[...]
		[...]
};