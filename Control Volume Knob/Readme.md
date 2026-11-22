# Control Volume Knob

### Turn any keyboard volume knob into a modifier-layered mouse scroll wheel, cursor controller, and shortcut dial.

### **Status:** In Development *(Coming soon)*

## How it Works
- **Zero Keyboard Hooks:** Uses Windows `RegisterHotKey` for volume keys only (`VK_VOLUME_UP/DOWN/MUTE`) instead of `WH_KEYBOARD_LL`. Normal typing and standard shortcuts are never hooked, polled, or delayed.
- **Swap Mode:** Enable the first setting in **Settings** to make the bare knob scroll vertically while `Ctrl + Knob` controls system volume.
- **Physical Mouse Priority (On by default):** Uses read-only Raw Input (no `WH_MOUSE_LL`) so the knob yields automatically whenever your physical mouse is moving, scrolling, or clicking.
- **Anti-Slip Rotation Clicks (Off by default):** Quick Left flick = 1 Left-click; sustained Left roll (`>= 320 ms`) = native Double-click; Right flick = 1 Right-click; `120 ms` rebound guard ignores hardware kickback.
- **0% Idle CPU & Clean Restore:** Sleeps completely at rest and evaluates keys only on knob ticks. Disabling the mod immediately restores native volume and mute.

## Shortcuts
| Icon | Shortcut | Action | Default |
| :---: | :--- | :--- | :---: |
| 🖱️ | `Ctrl + Knob` | Scroll up or down under cursor | On |
| ↔️ | `Shift + Knob` | Scroll left or right under cursor | On |
| 📄 | `Ctrl + Alt + Knob` | Jump a full page up or down | On |
| 🖍️ | `Ctrl + Shift + Knob` | Highlight and select lines/items while scrolling | On |
| 🔍 | `Alt + Knob` | Zoom in or out at cursor | On |
| 🔄 | `Ctrl + Alt + Press` | Reset zoom to 100% | On |
| 🎞️ | `Alt + Shift + Knob` | Scrub forward or backward on video/audio timeline | On |
| 🔊 | `Knob` | Native system volume *(untouched unless Swap Mode is On)* | On |
| 🔇 | `Press` | Native system mute *(untouched default)* | On |
| 🖱️ | `Shift + Press` | Left-click at cursor | On |
| 🖱️ | `Ctrl + Press` | Right-click at cursor | On |
| 🖱️ | `Alt + Press` | Middle-click at cursor | On |
| ↕️ | `Win + Ctrl + Knob` | Move mouse cursor up or down | Off |
| ↔️ | `Win + Shift + Knob` | Move mouse cursor left or right | Off |
| 🔤 | `Win + Knob` | Shrink or enlarge text and browser size | Off |
| ↩️ | `Z + Knob` | Undo one step per click (`Ctrl + Z`) | Off |
| ↪️ | `Y + Knob` | Redo one step per click (`Ctrl + Y`) | Off |
| 🎚️ | `Ctrl + Shift + Alt + Knob` | Adjust volume of active app only | Off |
| 🔕 | `Ctrl + Shift + Alt + Press` | Mute or unmute active app only | Off |
| 👆 | `Win + Alt + Knob` | Left = Left-click (sustained `>= 320 ms` = Double-click); Right = Right-click | Off |
