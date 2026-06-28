# RenderTarget Improvements

This package extends the original RenderTarget system with several quality-of-life features, rendering improvements, and a cleaner API, making it significantly easier to integrate into modern systems such as Wiki, Dungeon Info, Battle Pass, Item Preview, Costume Preview, Character Viewer, and more.

---

# Features

### ✅ Automatic RenderTarget Index Allocation

RenderTarget IDs are now allocated automatically by the engine.

This completely removes manual index management and guarantees that multiple systems can safely create RenderTargets without conflicting IDs.

### Old Method

```python
def __init__(self):
    ui.Whatever.__init__(self)
    self.renderKey = 5

def OnRenderMob(self, race):
    self.modelRenderer = ui.RenderTarget()
    self.modelRenderer.SetParent(self.board)
    self.modelRenderer.SetSize(260, 170)
    self.modelRenderer.SetRenderTarget(self.renderKey)
    self.modelRenderer.Show()

    renderTarget.SetBackground(self.renderKey, "background.sub")
    renderTarget.SetVisibility(self.renderKey, True)
    renderTarget.SelectModel(self.renderKey, race)
```

### New Method

```python
def OnRenderMob(self, race):
    self.modelRenderer = ui.RenderTarget()
    self.modelRenderer.SetParent(self.board)
    self.modelRenderer.SetSize(260, 170)
    self.modelRenderer.Show()

    key = self.modelRenderer.GetRenderTargetIndex()

    renderTarget.SetBackground(key, "background.sub")
    renderTarget.SetVisibility(key, True)
    renderTarget.SelectModel(key, race)
```

No manual IDs.

No duplicated RenderTargets.

Completely plug-and-play.

---

### ✅ Smooth Mouse Rotation

Drag the model with the mouse to rotate it smoothly.

Rotation uses inertia for a much more natural feeling.

---

### ✅ Smooth Mouse Wheel Zoom

Zooming is velocity-based with damping instead of instantly jumping between positions.

---

### ✅ Automatic Camera Fitting

The camera automatically adjusts itself based on the rendered model's height.

This allows players, monsters, NPCs and objects to appear correctly centered without requiring manual camera values for every race.

---

### ✅ Hair Preview Camera

Hair preview can automatically switch to a dedicated camera focused on the character's head.

#### Example

```python
renderTarget.SetHair(key, hairCostumeVnum, True)   # Hair Preview

renderTarget.SetHair(key, hairCostumeVnum)         # Normal Preview
```

---

### ✅ Automatic Hair Model Detection

Simply pass the costume hair VNUM.

The RenderTarget automatically resolves the correct hair model internally without requiring manual `value(3)` extraction.

---

### ✅ Equipment Persistence

The RenderTarget automatically remembers compatible equipment for every race.

Supported parts:

* Armor
* Weapon
* Hair
* Acce
* Weapon Shining
* Armor Shining

Switching between races automatically restores the appropriate equipment whenever possible.

---

### ✅ Optional Auto Rotation

Auto rotation can be enabled per model.

#### Example

```python
renderTarget.SelectModel(key, race, True)   # Auto Rotate

renderTarget.SelectModel(key, race)         # Static Model
```

---

### ✅ Runtime Model Scaling

Models can be resized dynamically at runtime.

Useful for previews, bosses, decorations and custom interfaces.

---

### ✅ Automatic Weapon Selection for Weapon Shining

If no weapon is equipped, the RenderTarget automatically equips a compatible default weapon before applying the weapon shining.

This allows weapon shining previews to work correctly without requiring additional setup.

---

### ✅ Modern C++ Memory Management

The RenderTarget has been modernized using smart pointers (`std::unique_ptr` / `std::shared_ptr`) for safer and cleaner resource management.

---

### ✅ Cleaner API

Several APIs have been simplified to reduce boilerplate and make RenderTarget integration much easier for future systems.

---

# Credits

Developed by **CONTROL**

**Discord**

```
control69
```

For more free and premium Metin2 systems, tools and resources:

🌐 https://pay2win-store.vercel.app/

---

Please keep the original credits if you redistribute this project.