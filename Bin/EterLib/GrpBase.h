

#ifdef ENABLE_MODEL_RENDER_TARGET
		float		GetFOV() const;
		float		GetAspect() const;
		float		GetNear() const;
		float		GetFar() const;
#else
		float		GetFOV();
#endif