
if app.ENABLE_MODEL_RENDER_TARGET:
	import renderTarget
	
	
	
	
	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	
	
	
		self.questButtonList = []
		self.whisperButtonList = []
		self.whisperDialogDict = {}
		self.privateShopAdvertisementBoardDict = {}
		self.guildScoreBoardDict = {}
		self.equipmentDialogDict = {}

		uiChat.DestroyChatInputSetWindow()
		
		if app.ENABLE_MODEL_RENDER_TARGET:
			renderTarget.Destroy()
			
			