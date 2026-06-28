

	public:
		[...]
		
		float		GetHeight();
		#ifdef ENABLE_MODEL_RENDER_TARGET
		void		RenderAllAttachingEffect();
		#endif
		void		ShowAllAttachingEffect();
		void		HideAllAttachingEffect();
		void		ClearAttachingEffect();

		[...]