
class CCameraManager : public CSingleton<CCameraManager>
{
	public:
		enum ECameraNum
		{
			NO_CURRENT_CAMERA,
			DEFAULT_PERSPECTIVE_CAMERA,
			DEFAULT_ORTHO_CAMERA,
			#ifdef ENABLE_MODEL_RENDER_TARGET
			SHOPDECO_CAMERA,
			#endif
			CAMERA_MAX = 255
		};