

[...]
[...]
[...]
void initguild();
void initMessenger();

#ifdef ENABLE_MODEL_RENDER_TARGET
void initRenderTarget();
#endif

extern const std::string& ApplicationStringTable_GetString(DWORD dwID);
extern const std::string& ApplicationStringTable_GetString(DWORD dwID, LPCSTR szKey);