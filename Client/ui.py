
import sys
from constInfo import ENABLE_RECURSIVE_UI_DESTROY
from _weakref import proxy
if app.ENABLE_MODEL_RENDER_TARGET:
	import renderTarget
	
	
	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	
	
			elif Type == "editline_centered":
				parent.Children[Index] = EditLineCentered()
				parent.Children[Index].SetParent(parent)
				self.LoadElementEditLine(parent.Children[Index], ElementValue, parent)
			
			elif app.ENABLE_MODEL_RENDER_TARGET and Type == "render_target":	
				parent.Children[Index] = RenderTarget()
				parent.Children[Index].SetParent(parent)
				self.LoadElementRenderTarget(parent.Children[Index], ElementValue, parent)
			else:
				Index += 1
				continue
				
	
	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	
	def LoadElementListBoxEx(self, window, value, parentWindow):

		if False == self.CheckKeyList(value["name"], value, self.LIST_BOX_KEY_LIST):
			return False

		window.SetSize(value["width"], value["height"])
		self.LoadDefaultData(window, value, parentWindow)

		if value.has_key("itemsize_x") and value.has_key("itemsize_y"):
			window.SetItemSize(int(value["itemsize_x"]), int(value["itemsize_y"]))

		if value.has_key("itemstep"):
			window.SetItemStep(int(value["itemstep"]))

		if value.has_key("viewcount"):
			window.SetViewItemCount(int(value["viewcount"]))

		return True
	
	if app.ENABLE_MODEL_RENDER_TARGET:
		def LoadElementRenderTarget(self, window, value, parentWindow):

			if False == self.CheckKeyList(value["name"], value, self.RENDER_TARGET_KEY_LIST):
				return False

			window.SetSize(value["width"], value["height"])
			
			if True == value.has_key("style"):
				for style in value["style"]:
					window.AddFlag(style)
					
			self.LoadDefaultData(window, value, parentWindow)

			return True


	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	''''''''''''''''''''''''''''''
	

if app.ENABLE_MODEL_RENDER_TARGET:
	class RenderTarget(Window):

		def __init__(self, layer = "UI"):
			Window.__init__(self, layer)
			self.index = -1
			if app.ENABLE_MODEL_RENDER_ROTATE:
				self.isHolding = False
				self.mouseLastXPos = 0

		def RegisterWindow(self, layer):
			self.hWnd = wndMgr.RegisterRenderTarget(self, layer)
		
		def SetSize(self, width, height):
			Window.SetSize(self, width, height)
			
			if self.index == -1: # auto create
				self.index = wndMgr.SetRenderTarget(self.hWnd)
			
		def GetRenderTargetIndex(self):
			return self.index
			
		if app.ENABLE_MODEL_RENDER_ROTATE:
			def OnUpdate(self):
				if self.isHolding == True:
					mouseCurrentPos = self.GetMouseLocalPosition()
					
					difference = mouseCurrentPos[0] - self.mouseLastXPos
					self.mouseLastXPos = mouseCurrentPos[0]
					renderTarget.SetModelRotation(self.index, difference)
			
			def OnMouseLeftButtonUp(self):
				self.isHolding = False

			def OnMouseLeftButtonDown(self):
				self.isHolding = True
				self.mouseLastXPos = self.GetMouseLocalPosition()[0]
				
		if app.ENABLE_MODEL_RENDER_ZOOM:
			def OnMouseWheel(self, len):
				if (len == 0):
					return False
				
				if len > 0:
					renderTarget.SetZoom(self.index, True)
				else:
					renderTarget.SetZoom(self.index, False)
				return True