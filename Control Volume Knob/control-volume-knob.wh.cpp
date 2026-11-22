// ==WindhawkMod==
// @id              control-volume-knob
// @name            Control Volume Knob
// @description     Turn any keyboard volume knob into a modifier-layered mouse scroll wheel, cursor controller, and shortcut dial.
// @version         1.2026.2011
// @author          Ashix
// @github          https://github.com/k-ashix
// @twitter         https://x.com/k_ashix
// @donateUrl       https://ko-fi.com/kashix
// @include         windhawk-mod.exe
// @include         windhawk.exe
// @compilerOptions -luser32 -lshell32 -lole32 -loleaut32 -luuid
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Control Volume Knob

Turn any standard keyboard volume knob into a customizable scroll wheel, zoom dial,
timeline scrubber, cursor controller, and mouse-click trigger—without touching keyboard
firmware, delaying normal typing, or clashing with your physical mouse scroll wheel.

Disabling the mod immediately restores your knob to normal system volume and mute.

## Shortcuts

| Icon | Shortcut | Action | Status |
| :---: | :--- | :--- | :---: |
| 🖱️ | `Ctrl + Knob` | Scroll up or down under your cursor (smooth, natural speed). | On |
| ↕️ | `Win + Ctrl + Knob` | Move the mouse cursor up or down (no Spacebar page-scroll clash). | Off |
| ↔️ | `Shift + Knob` | Scroll left or right under your cursor (smooth, natural speed). | On |
| ↔️ | `Win + Shift + Knob` | Move the mouse cursor left or right. | Off |
| 📄 | `Ctrl + Alt + Knob` | Jump a full page up or down. | On |
| 🖍️ | `Ctrl + Shift + Knob` | Highlight and select lines or items while scrolling. | On |
| 🔍 | `Alt + Knob` | Zoom in or out at your cursor. | On |
| 🔄 | `Ctrl + Alt + Press` | Reset zoom back to 100%. | On |
| 🔤 | `Win + Knob` | Shrink or enlarge text and browser size. | Off |
| 🎞️ | `Alt + Shift + Knob` | Scrub forward or backward on a video or audio timeline. | On |
| ↩️ | `Z + Knob` | Undo one step per click (`Ctrl + Z`, never accelerated). | Off |
| ↪️ | `Y + Knob` | Redo one step per click (`Ctrl + Y`, never accelerated). | Off |
| 🔊 | `Knob` | Native system volume up or down (untouched unless Swap Mode is On). | On |
| 🔇 | `Press` | Native system mute or unmute (untouched default). | On |
| 🎚️ | `Ctrl + Shift + Alt + Knob` | Adjust volume of only the currently active app. | Off |
| 🔕 | `Ctrl + Shift + Alt + Press` | Mute or unmute only the currently active app. | Off |
| 🖱️ | `Shift + Press` | Left-click at your cursor. | On |
| 🖱️ | `Ctrl + Press` | Right-click at your cursor. | On |
| 🖱️ | `Alt + Press` | Middle-click at your cursor (open links in new tab / auto-scroll). | On |
| 👆 | `Win + Alt + Knob` | Rotate Left = Left-click (sustained roll >= 320 ms = Double-click); Right = Right-click. | Off |

## How It Works

- **Zero keyboard hooks — normal typing is never touched:** Uses Windows `RegisterHotKey`
  for the volume knob keys only (`VK_VOLUME_UP/DOWN/MUTE`) instead of a global keyboard hook
  (`WH_KEYBOARD_LL`). Normal typing (`ASDFGH`) and shortcuts (`Ctrl + C`, `Ctrl + V`, `Alt + Tab`)
  are never hooked, tracked, polled, or delayed.
- **Swap default volume and vertical scroll:** Turn on the very first setting in **Settings**
  if you want the bare knob to scroll up and down directly while `Ctrl + Knob` controls system
  volume—so you never lose either control.
- **Always prioritize your physical mouse (On by default):** Whenever your real mouse is
  scrolling, moving, or clicking, the knob yields automatically (`General → Always prioritize
  physical mouse`) using read-only Raw Input—never installing `WH_MOUSE_LL` and never
  swallowing or delaying mouse input.
- **Anti-slip Rotation Clicks (Off by default):** When enabled (`Clicks → Click by rotating
  knob`), a quick Left flick always sends **1 Left-click**, a sustained Left roll (`>= 320 ms`)
  evolves into a native **Double-click** and locks, a Right flick sends **1 Right-click**, and
  a `120 ms` rebound guard ignores hardware kickback.
- **0% idle CPU:** Sleeps completely at rest and evaluates keys only when an actual knob tick
  arrives.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- swapDefaultVolumeAndScroll: false
  $name: Swap default volume and vertical scroll
  $description: When On, turning the knob alone scrolls up/down, and holding your vertical scroll key (default Ctrl) adjusts system volume instead.

- Scroll:
  - verticalEnabled: true
    $name: Vertical scroll with knob
    $description: Hold the trigger key while turning the knob to scroll up and down under your cursor.
  - verticalTrigger: "Ctrl"
    $name: Vertical scroll key
    $description: Key or combo to hold while turning the knob (e.g., Ctrl, Alt, F13, A).
  - horizontalEnabled: true
    $name: Horizontal scroll with knob
    $description: Hold the trigger key while turning the knob to scroll left and right.
  - horizontalTrigger: "Shift"
    $name: Horizontal scroll key
  - pageScrollEnabled: true
    $name: Page Up / Page Down with knob
    $description: Hold the trigger combo while turning the knob to jump a full page up or down.
  - pageScrollTrigger: "Ctrl+Alt"
    $name: Page scroll key combo
  - selectScrollEnabled: true
    $name: Select while scrolling
    $description: Hold the trigger combo while turning the knob to highlight lines or items.
  - selectScrollTrigger: "Ctrl+Shift"
    $name: Select-while-scrolling key combo
  - baseSpeed: 1
    $name: Base scroll speed (1 = gentle natural, 3 = standard notch, 5 = fast)
    $description: Fine-tuned high-resolution scroll step per knob detent (1 to 5).
  - velocityBoost: true
    $name: Gentle fast-spin boost
    $description: Keeps single clicks slow and precise, and gently speeds up during sustained fast spins.
  - maxBoost: 2
    $name: Maximum fast-spin multiplier
    $description: Upper speed multiplier when spinning rapidly (1 to 4).
  - invertDirection: false
    $name: Reverse scroll direction
    $description: Flip clockwise and counter-clockwise scroll direction.

- Cursor:
  - verticalEnabled: false
    $name: Move cursor up / down (Off by default)
    $description: Hold the trigger combo while turning the knob to move the mouse pointer vertically.
  - verticalTrigger: "Win+Ctrl"
    $name: Cursor up / down key combo
  - horizontalEnabled: false
    $name: Move cursor left / right (Off by default)
    $description: Hold the trigger combo while turning the knob to move the mouse pointer horizontally.
  - horizontalTrigger: "Win+Shift"
    $name: Cursor left / right key combo
  - basePixels: 16
    $name: Base cursor step (pixels)
    $description: Distance in pixels per slow knob detent (4 to 80).

- Zoom:
  - zoomEnabled: true
    $name: Zoom in / out with knob
    $description: Hold the trigger key while turning the knob to zoom at your cursor.
  - zoomTrigger: "Alt"
    $name: Zoom key
  - resetZoomEnabled: true
    $name: Reset zoom to 100% on knob press
  - resetZoomTrigger: "Ctrl+Alt"
    $name: Reset zoom key combo
  - fontSizeEnabled: false
    $name: Adjust text / browser size with knob (Off by default)
    $description: Hold the trigger key while turning the knob to shrink or enlarge text.
  - fontSizeTrigger: "Win"
    $name: Text / browser size key

- Editing:
  - timelineEnabled: true
    $name: Scrub video / audio timeline
    $description: Hold the trigger combo while turning the knob to seek timelines.
  - timelineTrigger: "Alt+Shift"
    $name: Timeline scrub key combo
  - undoEnabled: false
    $name: Undo with knob (Off by default)
    $description: Hold the trigger key while turning the knob to send one Ctrl+Z per click.
  - undoTrigger: "Z"
    $name: Undo key
  - redoEnabled: false
    $name: Redo with knob (Off by default)
    $description: Hold the trigger key while turning the knob to send one Ctrl+Y per click.
  - redoTrigger: "Y"
    $name: Redo key
  - undoRedoCooldownMs: 60
    $name: Undo / Redo safety cooldown (ms)
    $description: Minimum gap between undo/redo steps so a fast flick cannot wipe out edits.

- Clicks:
  - leftClickEnabled: true
    $name: Left mouse click on knob press
  - leftClickTrigger: "Shift"
    $name: Left-click key
  - rightClickEnabled: true
    $name: Right mouse click on knob press
  - rightClickTrigger: "Ctrl"
    $name: Right-click key
  - middleClickEnabled: true
    $name: Middle mouse click on knob press
  - middleClickTrigger: "Alt"
    $name: Middle-click key
  - rotationClickEnabled: false
    $name: Click by rotating knob (Off by default)
    $description: Rotate Left for Left-click and Right for Right-click, with anti-slip burst locking so one flick never fires 2-3 accidental clicks.
  - rotationClickTrigger: "Win+Alt"
    $name: Rotation-click key combo
    $description: Hold this modifier combo while rotating the knob to click (pure modifiers never spam typed letters).
  - rotationDoubleClickEnabled: true
    $name: Evolve sustained Left roll into Double-click
    $description: A quick flick always sends 1 Left-click; keeping the Left roll going past the duration threshold sends 1 follow-up click (Double-click) and locks.
  - rotationDoubleClickMs: 320
    $name: Sustained roll duration for Double-click (ms)
    $description: Continuous Left-roll duration required to trigger the 2nd click (220 to 460 ms). Short slips below this are always absorbed.
  - rotationResetGapMs: 400
    $name: Quiet pause before next rotation click (ms)
    $description: Pause time after stopping the knob (or release the trigger key) before a new click burst can start (200 to 1000 ms).

- Audio:
  - perAppVolumeEnabled: false
    $name: Per-app volume with knob (Off by default)
    $description: Hold the trigger combo while turning the knob to adjust only the active app's volume.
  - perAppVolumeTrigger: "Ctrl+Shift+Alt"
    $name: Per-app volume key combo
  - perAppMuteEnabled: false
    $name: Mute active app on knob press (Off by default)
    $description: Hold the trigger combo while pressing the knob to mute only the active app.
  - perAppMuteTrigger: "Ctrl+Shift+Alt"
    $name: Mute active app key combo
  - perAppStepPercent: 4
    $name: Per-app volume step (%)
    $description: Volume change percentage per knob click (1 to 20).

- General:
  - prioritizeMouse: true
    $name: Always prioritize physical mouse
    $description: When On, if your physical mouse is scrolling, moving, or clicking at the same time, the knob yields immediately so it never fights your mouse. When Off, both can act together without swallowing mouse input.
  - pauseInFullscreen: true
    $name: Pause custom knob actions in fullscreen games
    $description: Keeps native volume/mute behavior while running fullscreen games or presentations.
  - checkVirtualKeyCode: false
    $name: Check virtual key code
    $description: Logs the exact virtual key code (vkCode) of your knob actions in the Windhawk log.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <shellapi.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include <endpointvolume.h>

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <cwctype>
#include <deque>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// ============================================================================
// Constants & Shared Types
// ============================================================================

constexpr ULONG_PTR KNOB_EXTRA_INFO_TAG  = 0x4B4E4F42; // 'KNOB' tag to ignore our own SendInput calls
constexpr BYTE      VK_MASK_DUMMY        = 0xFF;       // Unassigned VK_NONAME used to suppress Alt/Win menu popups
constexpr size_t    MAX_PENDING_EVENTS   = 16;         // Cap queue depth so fast spins never build a runaway backlog
constexpr ULONGLONG FULLSCREEN_CACHE_MS  = 250;        // Cache fullscreen/capture check to keep hook Hot Path <0.05ms
constexpr ULONGLONG MAX_EVENT_AGE_MS        = 120;  // Drop stale queued events so lag spikes never cause delayed ghost firing
#ifndef RI_MOUSE_HWHEEL
#define RI_MOUSE_HWHEEL 0x0800
#endif

constexpr UINT      WM_APP_RELOAD_HOTKEYS   = WM_APP + 1;
constexpr ULONGLONG MOUSE_PRIORITY_YIELD_MS = 300;  // Yield knob actions for 300ms after conflicting real mouse activity
constexpr ULONGLONG DETENT_COALESCE_MS      = 30;   // Coalesce 1-29ms encoder twin-pulses into 1 crisp detent
constexpr ULONGLONG ENCODER_GLITCH_MS       = 40;   // Ignore <40ms opposite-direction mechanical contact bounce
constexpr ULONGLONG PRESS_ROTATE_GUARD_MS   = 70;   // Ignore accidental shaft wobble for 70ms after knob press
constexpr ULONGLONG MASK_COLLISION_GUARD_MS = 65;   // Drop stray mods=0x00 pulses caused by our own modifier masking
constexpr ULONGLONG ROT_CLICK_REBOUND_MS    = 120;  // Ignore opposite-direction encoder rebound ticks within 120ms

enum ModBits : uint8_t {
    MOD_BIT_NONE  = 0,
    MOD_BIT_CTRL  = 1 << 0,
    MOD_BIT_SHIFT = 1 << 1,
    MOD_BIT_ALT   = 1 << 2,
    MOD_BIT_WIN   = 1 << 3,
};

enum class KnobInputType : uint8_t {
    RotateUp,
    RotateDown,
    Press,
};

enum class ActionKind : uint8_t {
    None = 0,
    SystemVolume, // Native master volume step via Core Audio (Swap Mode or bare-knob passthrough)
    SystemMute,   // Native master mute toggle via Core Audio (fallback passthrough)
    VerticalScroll,
    HorizontalScroll,
    PageScroll,
    SelectScroll,
    CursorVertical,
    CursorHorizontal,
    Zoom,
    ResetZoom,
    FontSize,
    TimelineScrub,
    Undo,
    Redo,
    LeftClick,
    RightClick,
    MiddleClick,
    RotationClick,
    PerAppVolume,
    PerAppMute,
};

struct TriggerChord {
    uint8_t  modMask = MOD_BIT_NONE;
    uint16_t extraVk = 0; // Optional non-modifier key (Space, P, -, Z, Y, F1-F24, 0-9, A-Z)
    bool     valid   = false;

    int Specificity() const {
        int count = 0;
        if (modMask & MOD_BIT_CTRL)  count++;
        if (modMask & MOD_BIT_SHIFT) count++;
        if (modMask & MOD_BIT_ALT)   count++;
        if (modMask & MOD_BIT_WIN)   count++;
        if (extraVk != 0)            count++;
        return count;
    }
};

struct BindingRule {
    ActionKind   action = ActionKind::None;
    TriggerChord chord;
};

struct WorkerConfig {
    // Scroll
    bool swapDefaultVolumeAndScroll = false;
    int  baseSpeed                  = 1;
    bool velocityBoost              = true;
    int  maxBoost                   = 4;
    bool invertDirection            = false;

    // Cursor
    int cursorBasePixels = 16;

    // Editing
    int undoRedoCooldownMs = 60;

    // Rotation-click anti-slip tuning
    bool rotationDoubleClickEnabled = true;
    int  rotationDoubleClickMs      = 320;
    int  rotationResetGapMs         = 400;

    // Audio
    int perAppStepPercent = 4;

    // General
    bool prioritizeMouse     = true;
    bool pauseInFullscreen   = true;
    bool checkVirtualKeyCode = false;
};

struct ModSettings {
    WorkerConfig cfg;

    // Compiled rule tables sorted from most specific chord to least specific
    std::vector<BindingRule> rotateRules;
    std::vector<BindingRule> pressRules;

    // Distinct extra keys actually bound in enabled rules (checked ONLY on knob ticks)
    std::vector<uint16_t> watchedExtraVks;

    // Precomputed standard typing/shortcut keys NOT in watchedExtraVks (zero std::find in hook)
    std::vector<uint16_t> unwatchedGuardVks;
};

struct KnobEvent {
    KnobInputType inputType;
    ActionKind    action;
    uint8_t       requiredMods;
    uint16_t      requiredExtraVk;
    ULONGLONG     timestampMs;
};

// ============================================================================
// Global State (Zero Keyboard Hook, Zero Mouse Hook, 0% Typing & Idle CPU)
// ============================================================================

// Settings state (owned by LoadSettings, read under g_settingsMutex)
static std::mutex  g_settingsMutex;
static ModSettings g_settings;

// Bumped on settings reload or mode switch so RotationClick starts a fresh burst cleanly
static std::atomic<uint32_t>  g_rotClickResetGen{0};
// Tracks active SendWithMaskedModifiers windows so twin-pulses never leak to bare Volume/Mute
static std::atomic<bool>      g_maskingModifiers{false};
static std::atomic<ULONGLONG> g_lastMaskEndMs{0};
static std::atomic<ULONGLONG> g_lastModKnobMs{0};

// Passive read-only Raw Input timestamps for real physical mouse hardware (hDevice != nullptr)
static std::atomic<bool>      g_prioritizeMouseFast{true};
static std::atomic<ULONGLONG> g_lastPhysicalMouseMoveMs{0};
static std::atomic<ULONGLONG> g_lastPhysicalMouseWheelMs{0};
static std::atomic<ULONGLONG> g_lastPhysicalMouseButtonMs{0};

// Cached Fullscreen / Capture Gate state (owned by message thread)
static std::atomic<ULONGLONG> g_lastGateCheckMs{0};
static std::atomic<bool>      g_lastGateBlocked{false};

// Message-loop thread state (owns HWND_MESSAGE for RegisterHotKey + passive Raw Input)
static std::thread        g_msgThread;
static HANDLE             g_msgReadyEvent = nullptr;
static std::atomic<HWND>  g_msgWnd{nullptr};
static std::atomic<DWORD> g_msgThreadId{0};
static std::atomic<bool>  g_msgInitOk{false};
static std::atomic<bool>  g_running{false};

// Worker queue state (produced by WM_HOTKEY, consumed by WorkerThreadProc)
static std::thread             g_workerThread;
static std::mutex              g_queueMutex;
static std::condition_variable g_queueCv;
static std::deque<KnobEvent>   g_eventQueue;

// ============================================================================
// Trigger Parser & Settings Loader (100% Wired to YAML)
// ============================================================================

static std::wstring TrimAndUpper(const std::wstring& input) {
    size_t start = 0;
    while (start < input.size() && std::iswspace(input[start])) start++;
    size_t end = input.size();
    while (end > start && std::iswspace(input[end - 1])) end--;

    std::wstring out;
    out.reserve(end - start);
    for (size_t i = start; i < end; i++) {
        out.push_back(static_cast<wchar_t>(std::towupper(input[i])));
    }
    return out;
}

static uint16_t ParseSingleKeyToken(const std::wstring& token) {
    if (token.empty()) return 0;

    if (token == L"SPACE" || token == L"SPACEBAR") return VK_SPACE;
    if (token == L"TAB") return VK_TAB;
    if (token == L"CAPS" || token == L"CAPSLOCK") return VK_CAPITAL;
    if (token == L"-" || token == L"MINUS" || token == L"OEM_MINUS") return VK_OEM_MINUS;
    if (token == L"=" || token == L"+" || token == L"PLUS" || token == L"EQUALS") return VK_OEM_PLUS;
    if (token == L"[" || token == L"LBRACKET") return VK_OEM_4;
    if (token == L"]" || token == L"RBRACKET") return VK_OEM_6;
    if (token == L"\\" || token == L"BACKSLASH") return VK_OEM_5;
    if (token == L";" || token == L"SEMICOLON") return VK_OEM_1;
    if (token == L"'" || token == L"QUOTE") return VK_OEM_7;
    if (token == L"," || token == L"COMMA") return VK_OEM_COMMA;
    if (token == L"." || token == L"PERIOD") return VK_OEM_PERIOD;
    if (token == L"/" || token == L"SLASH") return VK_OEM_2;
    if (token == L"`" || token == L"TILDE" || token == L"GRAVE") return VK_OEM_3;

    if (token.size() == 1) {
        wchar_t ch = token[0];
        if ((ch >= L'A' && ch <= L'Z') || (ch >= L'0' && ch <= L'9')) {
            return static_cast<uint16_t>(ch);
        }
    }

    if (token.size() >= 2 && token[0] == L'F') {
        try {
            int fnum = std::stoi(token.substr(1));
            if (fnum >= 1 && fnum <= 24) {
                return static_cast<uint16_t>(VK_F1 + (fnum - 1));
            }
        } catch (...) {
            return 0;
        }
    }

    if (token.rfind(L"NUMPAD", 0) == 0 && token.size() == 7) {
        wchar_t ch = token[6];
        if (ch >= L'0' && ch <= L'9') {
            return static_cast<uint16_t>(VK_NUMPAD0 + (ch - L'0'));
        }
    }

    return 0;
}

static TriggerChord ParseTriggerString(const std::wstring& raw) {
    TriggerChord chord;
    std::wstring trimmed = TrimAndUpper(raw);
    if (trimmed.empty() || trimmed == L"NONE") {
        return chord;
    }

    if (trimmed == L"-") {
        chord.extraVk = VK_OEM_MINUS;
        chord.valid   = true;
        return chord;
    }
    if (trimmed == L"+") {
        chord.extraVk = VK_OEM_PLUS;
        chord.valid   = true;
        return chord;
    }

    size_t pos = 0;
    while (pos <= trimmed.size()) {
        size_t plusPos = trimmed.find(L'+', pos);
        std::wstring part = (plusPos == std::wstring::npos)
                                ? trimmed.substr(pos)
                                : trimmed.substr(pos, plusPos - pos);
        part = TrimAndUpper(part);

        if (!part.empty()) {
            if (part == L"CTRL" || part == L"CONTROL" || part == L"LCTRL" || part == L"RCTRL") {
                chord.modMask |= MOD_BIT_CTRL;
            } else if (part == L"SHIFT" || part == L"LSHIFT" || part == L"RSHIFT") {
                chord.modMask |= MOD_BIT_SHIFT;
            } else if (part == L"ALT" || part == L"LALT" || part == L"RALT") {
                chord.modMask |= MOD_BIT_ALT;
            } else if (part == L"WIN" || part == L"LWIN" || part == L"RWIN" || part == L"META") {
                chord.modMask |= MOD_BIT_WIN;
            } else {
                uint16_t vk = ParseSingleKeyToken(part);
                // Hard guard: never allow critical system/editing keys as extra hold-triggers
                bool forbidden = (vk == 0 || vk <= 0x07 || vk == VK_ESCAPE || vk == VK_RETURN ||
                                  vk == VK_BACK || vk == VK_DELETE || vk == VK_SNAPSHOT ||
                                  vk == VK_PAUSE || vk == VK_NUMLOCK || vk == VK_SCROLL ||
                                  vk == VK_APPS || vk == VK_PACKET || vk == VK_MASK_DUMMY);
                if (!forbidden) {
                    chord.extraVk = vk;
                }
            }
        }

        if (plusPos == std::wstring::npos) break;
        pos = plusPos + 1;
    }

    chord.valid = (chord.modMask != MOD_BIT_NONE || chord.extraVk != 0);
    return chord;
}

static std::wstring ReadStringSetting(PCWSTR name, PCWSTR fallback) {
    PCWSTR val = Wh_GetStringSetting(name);
    if (!val) return fallback;
    std::wstring out(val);
    Wh_FreeStringSetting(val);
    return out;
}

static void RegisterWatchedExtraVk(std::vector<uint16_t>& watched, uint16_t vk) {
    if (vk == 0) return;
    if (std::find(watched.begin(), watched.end(), vk) == watched.end()) {
        watched.push_back(vk);
    }
}

static void AddRuleIfEnabled(
    std::vector<BindingRule>& list,
    std::vector<uint16_t>& watched,
    bool enabled,
    PCWSTR triggerSettingName,
    PCWSTR fallbackTrigger,
    ActionKind action) {
    if (!enabled) return;
    TriggerChord chord = ParseTriggerString(ReadStringSetting(triggerSettingName, fallbackTrigger));
    if (!chord.valid) return;
    RegisterWatchedExtraVk(watched, chord.extraVk);
    list.push_back(BindingRule{action, chord});
}

static void LoadSettings() {
    ModSettings next;

    // General
    next.cfg.prioritizeMouse     = Wh_GetIntSetting(L"General.prioritizeMouse") != 0;
    next.cfg.pauseInFullscreen   = Wh_GetIntSetting(L"General.pauseInFullscreen") != 0;
    next.cfg.checkVirtualKeyCode = Wh_GetIntSetting(L"General.checkVirtualKeyCode") != 0;

    // Scroll tuning
    next.cfg.swapDefaultVolumeAndScroll = Wh_GetIntSetting(L"swapDefaultVolumeAndScroll") != 0;
    next.cfg.baseSpeed                  = std::clamp(Wh_GetIntSetting(L"Scroll.baseSpeed"), 1, 5);
    next.cfg.velocityBoost              = Wh_GetIntSetting(L"Scroll.velocityBoost") != 0;
    next.cfg.maxBoost                   = std::clamp(Wh_GetIntSetting(L"Scroll.maxBoost"), 1, 4);
    next.cfg.invertDirection            = Wh_GetIntSetting(L"Scroll.invertDirection") != 0;

    // Cursor tuning
    next.cfg.cursorBasePixels = std::clamp(Wh_GetIntSetting(L"Cursor.basePixels"), 4, 80);

    // Editing tuning
    next.cfg.undoRedoCooldownMs = std::clamp(Wh_GetIntSetting(L"Editing.undoRedoCooldownMs"), 0, 500);

    // Rotation-click anti-slip tuning
    next.cfg.rotationDoubleClickEnabled = Wh_GetIntSetting(L"Clicks.rotationDoubleClickEnabled") != 0;
    next.cfg.rotationDoubleClickMs      = std::clamp(Wh_GetIntSetting(L"Clicks.rotationDoubleClickMs"), 220, 460);
    next.cfg.rotationResetGapMs         = std::clamp(Wh_GetIntSetting(L"Clicks.rotationResetGapMs"), 200, 1000);

    // Audio tuning
    next.cfg.perAppStepPercent = std::clamp(Wh_GetIntSetting(L"Audio.perAppStepPercent"), 1, 20);

    // Swap mode: bare Knob = Vertical Scroll, verticalTrigger (Ctrl) + Knob = System Volume
    bool verticalEnabled = Wh_GetIntSetting(L"Scroll.verticalEnabled") != 0;
    std::wstring verticalTriggerStr = ReadStringSetting(L"Scroll.verticalTrigger", L"Ctrl");
    if (next.cfg.swapDefaultVolumeAndScroll) {
        TriggerChord bareChord{};
        bareChord.valid = true;
        next.rotateRules.push_back(BindingRule{ActionKind::VerticalScroll, bareChord});

        TriggerChord volChord = ParseTriggerString(verticalTriggerStr);
        if (volChord.valid) {
            RegisterWatchedExtraVk(next.watchedExtraVks, volChord.extraVk);
            next.rotateRules.push_back(BindingRule{ActionKind::SystemVolume, volChord});
        }
    } else if (verticalEnabled) {
        TriggerChord scrollChord = ParseTriggerString(verticalTriggerStr);
        if (scrollChord.valid) {
            RegisterWatchedExtraVk(next.watchedExtraVks, scrollChord.extraVk);
            next.rotateRules.push_back(BindingRule{ActionKind::VerticalScroll, scrollChord});
        }
    }

    // Remaining rotation bindings
    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Scroll.horizontalEnabled") != 0,
                     L"Scroll.horizontalTrigger", L"Shift", ActionKind::HorizontalScroll);
    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Scroll.pageScrollEnabled") != 0,
                     L"Scroll.pageScrollTrigger", L"Ctrl+Alt", ActionKind::PageScroll);

    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Scroll.selectScrollEnabled") != 0,
                     L"Scroll.selectScrollTrigger", L"Ctrl+Shift", ActionKind::SelectScroll);

    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Cursor.verticalEnabled") != 0,
                     L"Cursor.verticalTrigger", L"Win+Ctrl", ActionKind::CursorVertical);
    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Cursor.horizontalEnabled") != 0,
                     L"Cursor.horizontalTrigger", L"Win+Shift", ActionKind::CursorHorizontal);

    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Zoom.zoomEnabled") != 0,
                     L"Zoom.zoomTrigger", L"Alt", ActionKind::Zoom);

    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Zoom.fontSizeEnabled") != 0,
                     L"Zoom.fontSizeTrigger", L"Win", ActionKind::FontSize);

    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Editing.timelineEnabled") != 0,
                     L"Editing.timelineTrigger", L"Alt+Shift", ActionKind::TimelineScrub);
    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Editing.undoEnabled") != 0,
                     L"Editing.undoTrigger", L"Z", ActionKind::Undo);
    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Editing.redoEnabled") != 0,
                     L"Editing.redoTrigger", L"Y", ActionKind::Redo);

    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Clicks.rotationClickEnabled") != 0,
                     L"Clicks.rotationClickTrigger", L"Win+Alt", ActionKind::RotationClick);

    AddRuleIfEnabled(next.rotateRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Audio.perAppVolumeEnabled") != 0,
                     L"Audio.perAppVolumeTrigger", L"Ctrl+Shift+Alt", ActionKind::PerAppVolume);

    // Press bindings
    AddRuleIfEnabled(next.pressRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Clicks.leftClickEnabled") != 0,
                     L"Clicks.leftClickTrigger", L"Shift", ActionKind::LeftClick);
    AddRuleIfEnabled(next.pressRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Clicks.rightClickEnabled") != 0,
                     L"Clicks.rightClickTrigger", L"Ctrl", ActionKind::RightClick);
    AddRuleIfEnabled(next.pressRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Clicks.middleClickEnabled") != 0,
                     L"Clicks.middleClickTrigger", L"Alt", ActionKind::MiddleClick);
    AddRuleIfEnabled(next.pressRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Zoom.resetZoomEnabled") != 0,
                     L"Zoom.resetZoomTrigger", L"Ctrl+Alt", ActionKind::ResetZoom);
    AddRuleIfEnabled(next.pressRules, next.watchedExtraVks,
                     Wh_GetIntSetting(L"Audio.perAppMuteEnabled") != 0,
                     L"Audio.perAppMuteTrigger", L"Ctrl+Shift+Alt", ActionKind::PerAppMute);

    // Sort rules so multi-key chords (Space+Ctrl+Shift) always evaluate before simpler ones (Ctrl / bare)
    auto bySpecificity = [](const BindingRule& a, const BindingRule& b) {
        return a.chord.Specificity() > b.chord.Specificity();
    };
    std::stable_sort(next.rotateRules.begin(), next.rotateRules.end(), bySpecificity);
    std::stable_sort(next.pressRules.begin(), next.pressRules.end(), bySpecificity);

    // Precompute standard typing/shortcut keys NOT in watchedExtraVks so knob-tick matching
    // guards against Ctrl+V / Ctrl+/ / Alt+Tab / Shift+W without std::find inside the hook.
    auto addGuardVk = [&](uint16_t vk) {
        if (std::find(next.watchedExtraVks.begin(), next.watchedExtraVks.end(), vk) ==
            next.watchedExtraVks.end()) {
            next.unwatchedGuardVks.push_back(vk);
        }
    };
    for (uint16_t vk = 'A'; vk <= 'Z'; vk++) addGuardVk(vk);
    for (uint16_t vk = '0'; vk <= '9'; vk++) addGuardVk(vk);
    static constexpr uint16_t kStandardGuardVks[] = {
        VK_SPACE, VK_TAB, VK_RETURN, VK_BACK, VK_DELETE,
        VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
        VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6,
        VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,
        VK_OEM_1, VK_OEM_PLUS, VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD,
        VK_OEM_2, VK_OEM_3, VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7,
    };
    for (uint16_t vk : kStandardGuardVks) addGuardVk(vk);

    bool prioMouse = next.cfg.prioritizeMouse;
    {
        std::lock_guard<std::mutex> lock(g_settingsMutex);
        g_settings = std::move(next);
    }

    g_prioritizeMouseFast.store(prioMouse, std::memory_order_relaxed);
    g_lastGateCheckMs.store(0, std::memory_order_relaxed);
    g_rotClickResetGen.fetch_add(1, std::memory_order_relaxed);

    HWND wnd = g_msgWnd.load(std::memory_order_acquire);
    if (wnd) {
        PostMessageW(wnd, WM_APP_RELOAD_HOTKEYS, 0, 0);
    }
    Wh_Log(L"[Control Volume Knob] Settings loaded.");
}

// ============================================================================
// Fullscreen Gate & Capture / Critical-App Guard (Cached 250ms)
// ============================================================================

static bool IsProtectedForegroundApp(HWND fg) {
    if (!fg) return false;

    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    if (pid == 0) return false;

    HANDLE proc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!proc) return false;

    wchar_t path[MAX_PATH] = {};
    DWORD size = ARRAYSIZE(path);
    bool isProtected = false;
    if (QueryFullProcessImageNameW(proc, 0, path, &size)) {
        PCWSTR file = wcsrchr(path, L'\\');
        file = file ? file + 1 : path;
        isProtected = (_wcsicmp(file, L"ScreenClippingHost.exe") == 0 ||
                       _wcsicmp(file, L"SnippingTool.exe") == 0 ||
                       _wcsicmp(file, L"GameBar.exe") == 0 ||
                       _wcsicmp(file, L"Consent.exe") == 0 ||
                       _wcsicmp(file, L"LockApp.exe") == 0 ||
                       _wcsicmp(file, L"LogonUI.exe") == 0 ||
                       _wcsicmp(file, L"CredentialUIBroker.exe") == 0 ||
                       _wcsicmp(file, L"Taskmgr.exe") == 0);
    }
    CloseHandle(proc);
    return isProtected;
}

static bool EvaluateSafetyGates(bool pauseInFullscreen) {
    HWND fg = GetForegroundWindow();

    if (IsProtectedForegroundApp(fg)) {
        return true;
    }

    if (!pauseInFullscreen) {
        return false;
    }

    QUERY_USER_NOTIFICATION_STATE state = QUNS_ACCEPTS_NOTIFICATIONS;
    if (SUCCEEDED(SHQueryUserNotificationState(&state))) {
        // Deliberately exclude QUNS_BUSY (which fires system-wide on multi-monitor setups
        // when another monitor has a fullscreen video); borderless fullscreen in the active
        // foreground window is checked precisely below.
        if (state == QUNS_RUNNING_D3D_FULL_SCREEN ||
            state == QUNS_PRESENTATION_MODE) {
            return true;
        }
    }

    if (!fg) return false;

    wchar_t cls[64] = {};
    GetClassNameW(fg, cls, ARRAYSIZE(cls));
    if (wcscmp(cls, L"Progman") == 0 || wcscmp(cls, L"WorkerW") == 0 ||
        wcscmp(cls, L"Shell_TrayWnd") == 0) {
        return false;
    }

    RECT winRect{};
    if (!GetWindowRect(fg, &winRect)) return false;

    HMONITOR mon = MonitorFromWindow(fg, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(mon, &mi)) return false;

    bool coversMonitor =
        winRect.left <= mi.rcMonitor.left &&
        winRect.top <= mi.rcMonitor.top &&
        winRect.right >= mi.rcMonitor.right &&
        winRect.bottom >= mi.rcMonitor.bottom;

    if (!coversMonitor) return false;

    LONG style = GetWindowLongW(fg, GWL_STYLE);
    return (style & (WS_CAPTION | WS_THICKFRAME)) == 0;
}

static bool IsBlockedBySafetyGatesCached(bool pauseInFullscreen, ULONGLONG nowMs) {
    ULONGLONG last = g_lastGateCheckMs.load(std::memory_order_relaxed);
    if (last != 0 && nowMs >= last && (nowMs - last) < FULLSCREEN_CACHE_MS) {
        return g_lastGateBlocked.load(std::memory_order_relaxed);
    }

    bool blocked = EvaluateSafetyGates(pauseInFullscreen);
    g_lastGateBlocked.store(blocked, std::memory_order_relaxed);
    g_lastGateCheckMs.store(nowMs, std::memory_order_relaxed);
    return blocked;
}

// ============================================================================
// Synthetic Input Engine (Modifier-Safe SendInput + Start/Menu Guard)
// ============================================================================

static bool IsKeyDownNow(int vk) {
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

// Never hijack the mouse cursor or inject clicks while the user is physically dragging or clicking
static bool IsPhysicalMouseButtonHeld() {
    return ((GetAsyncKeyState(VK_LBUTTON) |
             GetAsyncKeyState(VK_RBUTTON) |
             GetAsyncKeyState(VK_MBUTTON) |
             GetAsyncKeyState(VK_XBUTTON1) |
             GetAsyncKeyState(VK_XBUTTON2)) & 0x8000) != 0;
}

enum class MouseYieldScope : uint8_t {
    Wheel,  // Yield to physical mouse wheel or held buttons (allows aiming then scrolling)
    Cursor, // Yield to physical mouse movement or buttons (never fight pointer motion)
    Click,  // Yield to physical mouse buttons/clicks (allows aiming then clicking at 0ms)
};

static bool IsRecentTimestamp(ULONGLONG lastMs, ULONGLONG nowMs, ULONGLONG windowMs) {
    return (lastMs != 0 && nowMs >= lastMs && (nowMs - lastMs) < windowMs);
}

// When General.prioritizeMouse is On, yields knob actions whenever real mouse hardware
// (hDevice != nullptr) performed a conflicting action within 300ms.
static bool ShouldYieldToPhysicalMouse(bool prioritizeMouse, MouseYieldScope scope, ULONGLONG nowMs) {
    if (!prioritizeMouse) return false;
    if (IsPhysicalMouseButtonHeld()) return true;

    switch (scope) {
        case MouseYieldScope::Wheel:
            return IsRecentTimestamp(g_lastPhysicalMouseWheelMs.load(std::memory_order_relaxed),
                                     nowMs, MOUSE_PRIORITY_YIELD_MS);
        case MouseYieldScope::Cursor:
            return IsRecentTimestamp(g_lastPhysicalMouseMoveMs.load(std::memory_order_relaxed),
                                     nowMs, MOUSE_PRIORITY_YIELD_MS) ||
                   IsRecentTimestamp(g_lastPhysicalMouseButtonMs.load(std::memory_order_relaxed),
                                     nowMs, MOUSE_PRIORITY_YIELD_MS);
        case MouseYieldScope::Click:
            return IsRecentTimestamp(g_lastPhysicalMouseButtonMs.load(std::memory_order_relaxed),
                                     nowMs, MOUSE_PRIORITY_YIELD_MS);
    }
    return false;
}

static INPUT MakeKeyInput(WORD vk, bool keyUp, bool extended = false) {
    INPUT in{};
    in.type           = INPUT_KEYBOARD;
    in.ki.wVk         = vk;
    in.ki.wScan       = (vk != VK_MASK_DUMMY) ? static_cast<WORD>(MapVirtualKeyW(vk, MAPVK_VK_TO_VSC)) : 0;
    in.ki.dwFlags     = (keyUp ? KEYEVENTF_KEYUP : 0) | (extended ? KEYEVENTF_EXTENDEDKEY : 0);
    in.ki.dwExtraInfo = KNOB_EXTRA_INFO_TAG;
    return in;
}

static INPUT MakeMouseInput(DWORD flags, LONG dx = 0, LONG dy = 0, DWORD mouseData = 0) {
    INPUT in{};
    in.type           = INPUT_MOUSE;
    in.mi.dx          = dx;
    in.mi.dy          = dy;
    in.mi.mouseData   = mouseData;
    in.mi.dwFlags     = flags;
    in.mi.dwExtraInfo = KNOB_EXTRA_INFO_TAG;
    return in;
}

// Temporarily masks conflicting held modifiers, emits payload cleanly on the Worker Thread,
// and restores only modifiers still physically held. Uses a 2ms settle gap when modifiers
// change so browsers/apps read the exact intended modifier state for Zoom, ResetZoom, and Clicks.
static void SendWithMaskedModifiers(uint8_t desiredMods, const std::vector<INPUT>& payload) {
    if (payload.empty()) return;

    const bool lCtrlDown  = IsKeyDownNow(VK_LCONTROL);
    const bool rCtrlDown  = IsKeyDownNow(VK_RCONTROL);
    const bool lShiftDown = IsKeyDownNow(VK_LSHIFT);
    const bool rShiftDown = IsKeyDownNow(VK_RSHIFT);
    const bool lAltDown   = IsKeyDownNow(VK_LMENU);
    const bool rAltDown   = IsKeyDownNow(VK_RMENU);
    const bool lWinDown   = IsKeyDownNow(VK_LWIN);
    const bool rWinDown   = IsKeyDownNow(VK_RWIN);

    uint8_t liveMods = MOD_BIT_NONE;
    if (lCtrlDown  || rCtrlDown)  liveMods |= MOD_BIT_CTRL;
    if (lShiftDown || rShiftDown) liveMods |= MOD_BIT_SHIFT;
    if (lAltDown   || rAltDown)   liveMods |= MOD_BIT_ALT;
    if (lWinDown   || rWinDown)   liveMods |= MOD_BIT_WIN;

    const uint8_t modsToRelease = liveMods & ~desiredMods;
    const uint8_t modsToPress   = desiredMods & ~liveMods;

    // Fast path: no modifier changes needed -> emit payload directly with zero masking overhead
    if (modsToRelease == 0 && modsToPress == 0) {
        SendInput(static_cast<UINT>(payload.size()), const_cast<INPUT*>(payload.data()), sizeof(INPUT));
        return;
    }

    g_maskingModifiers.store(true, std::memory_order_release);

    std::vector<INPUT> preBatch;
    preBatch.reserve(12);

    if (modsToRelease & (MOD_BIT_ALT | MOD_BIT_WIN)) {
        preBatch.push_back(MakeKeyInput(VK_MASK_DUMMY, false));
        preBatch.push_back(MakeKeyInput(VK_MASK_DUMMY, true));
    }

    bool releasedLCtrl  = false, releasedRCtrl  = false;
    bool releasedLShift = false, releasedRShift = false;
    bool releasedLAlt   = false, releasedRAlt   = false;
    bool releasedLWin   = false, releasedRWin   = false;

    if (modsToRelease & MOD_BIT_CTRL) {
        if (lCtrlDown)  { preBatch.push_back(MakeKeyInput(VK_LCONTROL, true, false)); releasedLCtrl  = true; }
        if (rCtrlDown)  { preBatch.push_back(MakeKeyInput(VK_RCONTROL, true, true));  releasedRCtrl  = true; }
    }
    if (modsToRelease & MOD_BIT_SHIFT) {
        if (lShiftDown) { preBatch.push_back(MakeKeyInput(VK_LSHIFT, true, false));   releasedLShift = true; }
        if (rShiftDown) { preBatch.push_back(MakeKeyInput(VK_RSHIFT, true, false));   releasedRShift = true; }
    }
    if (modsToRelease & MOD_BIT_ALT) {
        if (lAltDown)   { preBatch.push_back(MakeKeyInput(VK_LMENU, true, false));    releasedLAlt   = true; }
        if (rAltDown)   { preBatch.push_back(MakeKeyInput(VK_RMENU, true, true));     releasedRAlt   = true; }
    }
    if (modsToRelease & MOD_BIT_WIN) {
        if (lWinDown)   { preBatch.push_back(MakeKeyInput(VK_LWIN, true, true));      releasedLWin   = true; }
        if (rWinDown)   { preBatch.push_back(MakeKeyInput(VK_RWIN, true, true));      releasedRWin   = true; }
    }

    if (modsToPress & MOD_BIT_CTRL)  preBatch.push_back(MakeKeyInput(VK_LCONTROL, false));
    if (modsToPress & MOD_BIT_SHIFT) preBatch.push_back(MakeKeyInput(VK_LSHIFT, false));
    if (modsToPress & MOD_BIT_ALT)   preBatch.push_back(MakeKeyInput(VK_LMENU, false));
    if (modsToPress & MOD_BIT_WIN)   preBatch.push_back(MakeKeyInput(VK_LWIN, false, true));

    if (!preBatch.empty()) {
        SendInput(static_cast<UINT>(preBatch.size()), preBatch.data(), sizeof(INPUT));
        Sleep(2);
    }

    SendInput(static_cast<UINT>(payload.size()), const_cast<INPUT*>(payload.data()), sizeof(INPUT));
    Sleep(2);

    std::vector<INPUT> postBatch;
    postBatch.reserve(12);

    if (modsToPress & MOD_BIT_WIN)   postBatch.push_back(MakeKeyInput(VK_LWIN, true, true));
    if (modsToPress & MOD_BIT_ALT)   postBatch.push_back(MakeKeyInput(VK_LMENU, true));
    if (modsToPress & MOD_BIT_SHIFT) postBatch.push_back(MakeKeyInput(VK_LSHIFT, true));
    if (modsToPress & MOD_BIT_CTRL)  postBatch.push_back(MakeKeyInput(VK_LCONTROL, true));

    bool restoredWinOrAlt = false;
    if (releasedLWin   && IsKeyDownNow(VK_LWIN))     { postBatch.push_back(MakeKeyInput(VK_LWIN, false, true));   restoredWinOrAlt = true; }
    if (releasedRWin   && IsKeyDownNow(VK_RWIN))     { postBatch.push_back(MakeKeyInput(VK_RWIN, false, true));   restoredWinOrAlt = true; }
    if (releasedLAlt   && IsKeyDownNow(VK_LMENU))    { postBatch.push_back(MakeKeyInput(VK_LMENU, false, false)); restoredWinOrAlt = true; }
    if (releasedRAlt   && IsKeyDownNow(VK_RMENU))    { postBatch.push_back(MakeKeyInput(VK_RMENU, false, true));  restoredWinOrAlt = true; }
    if (releasedLShift && IsKeyDownNow(VK_LSHIFT))   postBatch.push_back(MakeKeyInput(VK_LSHIFT, false, false));
    if (releasedRShift && IsKeyDownNow(VK_RSHIFT))   postBatch.push_back(MakeKeyInput(VK_RSHIFT, false, false));
    if (releasedLCtrl  && IsKeyDownNow(VK_LCONTROL)) postBatch.push_back(MakeKeyInput(VK_LCONTROL, false, false));
    if (releasedRCtrl  && IsKeyDownNow(VK_RCONTROL)) postBatch.push_back(MakeKeyInput(VK_RCONTROL, false, true));

    if (restoredWinOrAlt) {
        postBatch.push_back(MakeKeyInput(VK_MASK_DUMMY, false));
        postBatch.push_back(MakeKeyInput(VK_MASK_DUMMY, true));
    }

    if (!postBatch.empty()) {
        SendInput(static_cast<UINT>(postBatch.size()), postBatch.data(), sizeof(INPUT));
    }

    g_lastMaskEndMs.store(GetTickCount64(), std::memory_order_relaxed);
    g_maskingModifiers.store(false, std::memory_order_release);
}

// ============================================================================
// Core Audio Master & Per-App Volume Controller (Runs on Worker Thread Only)
// ============================================================================

static void AdjustSystemMasterAudio(KnobInputType inputType) {
    IMMDeviceEnumerator* enumerator = nullptr;
    IMMDevice* device = nullptr;
    IAudioEndpointVolume* epVol = nullptr;

    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
        __uuidof(IMMDeviceEnumerator), reinterpret_cast<void**>(&enumerator));
    if (FAILED(hr) || !enumerator) return;

    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    if (SUCCEEDED(hr) && device) {
        hr = device->Activate(
            __uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr,
            reinterpret_cast<void**>(&epVol));
    }
    if (SUCCEEDED(hr) && epVol) {
        if (inputType == KnobInputType::Press) {
            BOOL muted = FALSE;
            if (SUCCEEDED(epVol->GetMute(&muted))) {
                epVol->SetMute(!muted, nullptr);
            }
        } else {
            float before = 0.0f;
            bool gotBefore = SUCCEEDED(epVol->GetMasterVolumeLevelScalar(&before));
            HRESULT stepHr = (inputType == KnobInputType::RotateUp)
                                 ? epVol->VolumeStepUp(nullptr)
                                 : epVol->VolumeStepDown(nullptr);
            float after = before;
            bool unchanged = gotBefore && SUCCEEDED(epVol->GetMasterVolumeLevelScalar(&after)) &&
                             (after == before);
            // Fallback for USB DACs/headsets where VolumeStepUp/Down is a no-op
            if (FAILED(stepHr) || (unchanged && ((inputType == KnobInputType::RotateUp && before < 0.99f) ||
                                                 (inputType == KnobInputType::RotateDown && before > 0.01f)))) {
                float delta = (inputType == KnobInputType::RotateUp) ? 0.02f : -0.02f;
                epVol->SetMasterVolumeLevelScalar(std::clamp(before + delta, 0.0f, 1.0f), nullptr);
            }
        }
    }

    if (epVol)      epVol->Release();
    if (device)     device->Release();
    if (enumerator) enumerator->Release();
}

static void AdjustForegroundAppAudio(bool toggleMute, float deltaVolume) {
    HWND fg = GetForegroundWindow();
    if (!fg) return;

    DWORD targetPid = 0;
    GetWindowThreadProcessId(fg, &targetPid);
    if (targetPid == 0) return;

    IMMDeviceEnumerator* enumerator = nullptr;
    IMMDevice* device = nullptr;
    IAudioSessionManager2* sessionMgr = nullptr;
    IAudioSessionEnumerator* sessionEnum = nullptr;

    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
        __uuidof(IMMDeviceEnumerator), reinterpret_cast<void**>(&enumerator));
    if (FAILED(hr) || !enumerator) return;

    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &device);
    if (SUCCEEDED(hr) && device) {
        hr = device->Activate(
            __uuidof(IAudioSessionManager2), CLSCTX_ALL, nullptr,
            reinterpret_cast<void**>(&sessionMgr));
    }
    if (SUCCEEDED(hr) && sessionMgr) {
        hr = sessionMgr->GetSessionEnumerator(&sessionEnum);
    }

    if (SUCCEEDED(hr) && sessionEnum) {
        int count = 0;
        if (SUCCEEDED(sessionEnum->GetCount(&count))) {
            for (int i = 0; i < count; i++) {
                IAudioSessionControl* ctrl = nullptr;
                IAudioSessionControl2* ctrl2 = nullptr;
                if (SUCCEEDED(sessionEnum->GetSession(i, &ctrl)) && ctrl) {
                    if (SUCCEEDED(ctrl->QueryInterface(__uuidof(IAudioSessionControl2),
                                                       reinterpret_cast<void**>(&ctrl2))) && ctrl2) {
                        DWORD sessionPid = 0;
                        if (SUCCEEDED(ctrl2->GetProcessId(&sessionPid)) && sessionPid == targetPid) {
                            ISimpleAudioVolume* vol = nullptr;
                            if (SUCCEEDED(ctrl2->QueryInterface(__uuidof(ISimpleAudioVolume),
                                                                reinterpret_cast<void**>(&vol))) && vol) {
                                if (toggleMute) {
                                    BOOL muted = FALSE;
                                    if (SUCCEEDED(vol->GetMute(&muted))) {
                                        vol->SetMute(!muted, nullptr);
                                    }
                                } else {
                                    float current = 1.0f;
                                    if (SUCCEEDED(vol->GetMasterVolume(&current))) {
                                        float updated = std::clamp(current + deltaVolume, 0.0f, 1.0f);
                                        vol->SetMasterVolume(updated, nullptr);
                                    }
                                }
                                vol->Release();
                            }
                        }
                        ctrl2->Release();
                    }
                    ctrl->Release();
                }
            }
        }
    }

    if (sessionEnum) sessionEnum->Release();
    if (sessionMgr)  sessionMgr->Release();
    if (device)      device->Release();
    if (enumerator)  enumerator->Release();
}

// ============================================================================
// Worker Thread (0% Idle CPU, Direction-Aware Velocity Dispatch)
// ============================================================================

struct VelocityState {
    ULONGLONG  lastMs     = 0;
    int        lastDir    = 0;
    int        fastStreak = 0;
    ActionKind lastAction = ActionKind::None;
};

// High-resolution scroll delta per physical detent: 1=50 (gentle natural), 2=80, 3=120 (1 notch), 4=160, 5=220
static int ScrollBaseDelta(int baseSpeed) {
    static constexpr int kDeltas[5] = { 50, 80, 120, 160, 220 };
    return kDeltas[std::clamp(baseSpeed, 1, 5) - 1];
}

// Gentle velocity curve: single slow clicks ALWAYS stay at 1.0x; boost only kicks in
// after 3+ consecutive rapid detents in the same direction (never on a single tick).
static float ComputeVelocityScale(
    ULONGLONG nowMs,
    int dir,
    ActionKind action,
    VelocityState& state,
    bool boostEnabled,
    int maxBoost) {
    bool directionChanged = (state.lastDir != 0 && state.lastDir != dir) ||
                            (state.lastAction != ActionKind::None && state.lastAction != action);
    ULONGLONG delta = (state.lastMs == 0 || nowMs < state.lastMs || directionChanged)
                          ? 999
                          : (nowMs - state.lastMs);
    state.lastMs     = nowMs;
    state.lastDir    = dir;
    state.lastAction = action;

    if (directionChanged || delta > 160) {
        state.fastStreak = 0;
    } else if (delta < 95) {
        state.fastStreak = std::min(state.fastStreak + 1, 10);
    }

    if (!boostEnabled || maxBoost <= 1 || state.fastStreak < 3) return 1.0f;
    if (delta < 50 && state.fastStreak >= 5) return static_cast<float>(maxBoost);
    if (delta < 85) return std::min(1.5f, static_cast<float>(maxBoost));
    return 1.0f;
}

static void WorkerThreadProc() {
    HRESULT comHr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    struct RotationClickState {
        ULONGLONG burstStartMs = 0;
        ULONGLONG lastTickMs   = 0;
        int       burstDir     = 0;
        uint32_t  lastResetGen = 0;
        bool      doubleFired  = false;
    };

    VelocityState      scrollVel{};
    VelocityState      cursorVel{};
    RotationClickState rotClick{};
    ULONGLONG lastUndoRedoMs = 0;

    while (true) {
        KnobEvent ev{};
        {
            std::unique_lock<std::mutex> lock(g_queueMutex);
            g_queueCv.wait(lock, [] {
                return !g_eventQueue.empty() || !g_running.load(std::memory_order_acquire);
            });

            if (!g_running.load(std::memory_order_acquire) && g_eventQueue.empty()) {
                break;
            }

            ev = g_eventQueue.front();
            g_eventQueue.pop_front();
        }

        // Discard stale events after any system stall so ghost actions never fire late
        ULONGLONG nowWorkerMs = GetTickCount64();
        if (nowWorkerMs > ev.timestampMs && (nowWorkerMs - ev.timestampMs) > MAX_EVENT_AGE_MS) {
            continue;
        }

        // Instant key-release brake (zero keyboard hook needed): if this was a held-key
        // rotation action and the user already released any required trigger key, drop it.
        if (ev.inputType != KnobInputType::Press &&
            ev.action != ActionKind::SystemVolume &&
            ev.action != ActionKind::SystemMute) {
            bool chordStillHeld = true;
            if ((ev.requiredMods & MOD_BIT_CTRL)  && !(IsKeyDownNow(VK_LCONTROL) || IsKeyDownNow(VK_RCONTROL))) chordStillHeld = false;
            if ((ev.requiredMods & MOD_BIT_SHIFT) && !(IsKeyDownNow(VK_LSHIFT)   || IsKeyDownNow(VK_RSHIFT)))   chordStillHeld = false;
            if ((ev.requiredMods & MOD_BIT_ALT)   && !(IsKeyDownNow(VK_LMENU)    || IsKeyDownNow(VK_RMENU)))    chordStillHeld = false;
            if ((ev.requiredMods & MOD_BIT_WIN)   && !(IsKeyDownNow(VK_LWIN)     || IsKeyDownNow(VK_RWIN)))     chordStillHeld = false;
            if (ev.requiredExtraVk != 0 && !IsKeyDownNow(ev.requiredExtraVk)) chordStillHeld = false;
            if (!chordStillHeld) {
                continue;
            }
        }

        WorkerConfig cfg;
        {
            std::lock_guard<std::mutex> lock(g_settingsMutex);
            cfg = g_settings.cfg;
        }

        int dir = (ev.inputType == KnobInputType::RotateUp) ? 1 : -1;
        if (cfg.invertDirection &&
            (ev.action == ActionKind::VerticalScroll ||
             ev.action == ActionKind::HorizontalScroll ||
             ev.action == ActionKind::PageScroll)) {
            dir = -dir;
        }

        switch (ev.action) {
            case ActionKind::SystemVolume: {
                AdjustSystemMasterAudio(ev.inputType);
                break;
            }

            case ActionKind::SystemMute: {
                AdjustSystemMasterAudio(KnobInputType::Press);
                break;
            }

            case ActionKind::VerticalScroll: {
                if (ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Wheel, nowWorkerMs)) break;
                float scale = ComputeVelocityScale(ev.timestampMs, dir, ev.action, scrollVel,
                                                   cfg.velocityBoost, cfg.maxBoost);
                int delta = static_cast<int>(static_cast<float>(dir * ScrollBaseDelta(cfg.baseSpeed)) * scale);
                SendWithMaskedModifiers(MOD_BIT_NONE, {
                    MakeMouseInput(MOUSEEVENTF_WHEEL, 0, 0, static_cast<DWORD>(delta))
                });
                break;
            }

            case ActionKind::HorizontalScroll: {
                if (ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Wheel, nowWorkerMs)) break;
                float scale = ComputeVelocityScale(ev.timestampMs, dir, ev.action, scrollVel,
                                                   cfg.velocityBoost, cfg.maxBoost);
                int delta = static_cast<int>(static_cast<float>(dir * ScrollBaseDelta(cfg.baseSpeed)) * scale);
                SendWithMaskedModifiers(MOD_BIT_NONE, {
                    MakeMouseInput(MOUSEEVENTF_HWHEEL, 0, 0, static_cast<DWORD>(delta))
                });
                break;
            }

            case ActionKind::PageScroll: {
                WORD vk = (dir > 0) ? VK_PRIOR : VK_NEXT;
                SendWithMaskedModifiers(MOD_BIT_NONE, {
                    MakeKeyInput(vk, false, true),
                    MakeKeyInput(vk, true, true),
                });
                break;
            }

            case ActionKind::SelectScroll: {
                WORD vk = (dir > 0) ? VK_UP : VK_DOWN;
                SendWithMaskedModifiers(MOD_BIT_SHIFT, {
                    MakeKeyInput(vk, false, true),
                    MakeKeyInput(vk, true, true),
                });
                break;
            }

            case ActionKind::CursorVertical: {
                if (IsPhysicalMouseButtonHeld() || ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Cursor, nowWorkerMs)) break;
                float scale = ComputeVelocityScale(ev.timestampMs, dir, ev.action, cursorVel,
                                                   cfg.velocityBoost, cfg.maxBoost);
                LONG dy = static_cast<LONG>(static_cast<float>(-dir * cfg.cursorBasePixels) * scale);
                INPUT moveIn = MakeMouseInput(MOUSEEVENTF_MOVE, 0, dy, 0);
                SendInput(1, &moveIn, sizeof(INPUT));
                break;
            }

            case ActionKind::CursorHorizontal: {
                if (IsPhysicalMouseButtonHeld() || ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Cursor, nowWorkerMs)) break;
                float scale = ComputeVelocityScale(ev.timestampMs, dir, ev.action, cursorVel,
                                                   cfg.velocityBoost, cfg.maxBoost);
                LONG dx = static_cast<LONG>(static_cast<float>(dir * cfg.cursorBasePixels) * scale);
                INPUT moveIn = MakeMouseInput(MOUSEEVENTF_MOVE, dx, 0, 0);
                SendInput(1, &moveIn, sizeof(INPUT));
                break;
            }

            case ActionKind::Zoom: {
                if (ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Wheel, nowWorkerMs)) break;
                int delta = dir * WHEEL_DELTA;
                SendWithMaskedModifiers(MOD_BIT_CTRL, {
                    MakeMouseInput(MOUSEEVENTF_WHEEL, 0, 0, static_cast<DWORD>(delta))
                });
                break;
            }

            case ActionKind::ResetZoom: {
                SendWithMaskedModifiers(MOD_BIT_CTRL, {
                    MakeKeyInput('0', false),
                    MakeKeyInput('0', true),
                });
                break;
            }

            case ActionKind::FontSize: {
                WORD vk = (dir > 0) ? VK_OEM_PLUS : VK_OEM_MINUS;
                SendWithMaskedModifiers(MOD_BIT_CTRL, {
                    MakeKeyInput(vk, false),
                    MakeKeyInput(vk, true),
                });
                break;
            }

            case ActionKind::TimelineScrub: {
                WORD vk = (dir > 0) ? VK_RIGHT : VK_LEFT;
                SendWithMaskedModifiers(MOD_BIT_NONE, {
                    MakeKeyInput(vk, false, true),
                    MakeKeyInput(vk, true, true),
                });
                break;
            }

            case ActionKind::Undo: {
                if (lastUndoRedoMs == 0 ||
                    (ev.timestampMs >= lastUndoRedoMs &&
                     (ev.timestampMs - lastUndoRedoMs) >= static_cast<ULONGLONG>(cfg.undoRedoCooldownMs))) {
                    lastUndoRedoMs = ev.timestampMs;
                    SendWithMaskedModifiers(MOD_BIT_CTRL, {
                        MakeKeyInput('Z', false),
                        MakeKeyInput('Z', true),
                    });
                }
                break;
            }

            case ActionKind::Redo: {
                if (lastUndoRedoMs == 0 ||
                    (ev.timestampMs >= lastUndoRedoMs &&
                     (ev.timestampMs - lastUndoRedoMs) >= static_cast<ULONGLONG>(cfg.undoRedoCooldownMs))) {
                    lastUndoRedoMs = ev.timestampMs;
                    SendWithMaskedModifiers(MOD_BIT_CTRL, {
                        MakeKeyInput('Y', false),
                        MakeKeyInput('Y', true),
                    });
                }
                break;
            }

            case ActionKind::LeftClick: {
                if (IsPhysicalMouseButtonHeld() || ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Click, nowWorkerMs)) break;
                SendWithMaskedModifiers(MOD_BIT_NONE, {
                    MakeMouseInput(MOUSEEVENTF_LEFTDOWN),
                    MakeMouseInput(MOUSEEVENTF_LEFTUP),
                });
                break;
            }

            case ActionKind::RightClick: {
                if (IsPhysicalMouseButtonHeld() || ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Click, nowWorkerMs)) break;
                SendWithMaskedModifiers(MOD_BIT_NONE, {
                    MakeMouseInput(MOUSEEVENTF_RIGHTDOWN),
                    MakeMouseInput(MOUSEEVENTF_RIGHTUP),
                });
                break;
            }

            case ActionKind::MiddleClick: {
                if (IsPhysicalMouseButtonHeld() || ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Click, nowWorkerMs)) break;
                SendWithMaskedModifiers(MOD_BIT_NONE, {
                    MakeMouseInput(MOUSEEVENTF_MIDDLEDOWN),
                    MakeMouseInput(MOUSEEVENTF_MIDDLEUP),
                });
                break;
            }

            case ActionKind::RotationClick: {
                if (IsPhysicalMouseButtonHeld() || ShouldYieldToPhysicalMouse(cfg.prioritizeMouse, MouseYieldScope::Click, nowWorkerMs)) break;

                // Anti-slip duration state machine:
                // - New burst (after quiet pause >= rotationResetGapMs, direction flip, or key release):
                //   fires strictly 1 click immediately (0 ms lag).
                // - All slip ticks below rotationDoubleClickMs are absorbed cleanly.
                // - Sustained Left (CCW, dir < 0) roll >= rotationDoubleClickMs (and within OS double-click window)
                //   fires 1 follow-up Left-click (native Double-click) and hard-locks until quiet pause / key release.
                // - Right (CW, dir > 0) roll is strictly 1-shot Right-click per burst.
                uint32_t resetGen = g_rotClickResetGen.load(std::memory_order_relaxed);
                ULONGLONG sinceLastMs = (rotClick.lastTickMs == 0 || ev.timestampMs < rotClick.lastTickMs)
                                            ? 9999
                                            : (ev.timestampMs - rotClick.lastTickMs);

                // Rebound guard: if the encoder kicks back 1 tick in the opposite direction
                // within 120ms of a burst tick (without key release), drop it as hardware backlash
                // so a Right-Click never gets followed by an accidental Left-Click (or vice versa).
                if (rotClick.lastTickMs != 0 &&
                    rotClick.lastResetGen == resetGen &&
                    rotClick.burstDir != 0 &&
                    rotClick.burstDir != dir &&
                    sinceLastMs < ROT_CLICK_REBOUND_MS) {
                    break;
                }

                bool quietElapsed = (sinceLastMs >= static_cast<ULONGLONG>(cfg.rotationResetGapMs));
                bool newBurst = quietElapsed ||
                                (rotClick.burstDir != dir) ||
                                (rotClick.lastResetGen != resetGen);

                if (newBurst) {
                    rotClick.burstStartMs = ev.timestampMs;
                    rotClick.lastTickMs   = ev.timestampMs;
                    rotClick.burstDir     = dir;
                    rotClick.lastResetGen = resetGen;
                    rotClick.doubleFired  = false;

                    if (dir < 0) {
                        SendWithMaskedModifiers(MOD_BIT_NONE, {
                            MakeMouseInput(MOUSEEVENTF_LEFTDOWN),
                            MakeMouseInput(MOUSEEVENTF_LEFTUP),
                        });
                    } else {
                        SendWithMaskedModifiers(MOD_BIT_NONE, {
                            MakeMouseInput(MOUSEEVENTF_RIGHTDOWN),
                            MakeMouseInput(MOUSEEVENTF_RIGHTUP),
                        });
                    }
                } else {
                    rotClick.lastTickMs = ev.timestampMs;

                    if (dir < 0 && cfg.rotationDoubleClickEnabled && !rotClick.doubleFired) {
                        ULONGLONG heldDuration = (ev.timestampMs >= rotClick.burstStartMs)
                                                     ? (ev.timestampMs - rotClick.burstStartMs)
                                                     : 0;
                        ULONGLONG osDblTime = static_cast<ULONGLONG>(GetDoubleClickTime());
                        ULONGLONG osDblMax  = (osDblTime > 20) ? (osDblTime - 20) : osDblTime;
                        ULONGLONG effectiveMin = static_cast<ULONGLONG>(cfg.rotationDoubleClickMs);
                        if (osDblMax > 180 && effectiveMin >= osDblMax) {
                            effectiveMin = osDblMax - 60;
                        }
                        if (heldDuration >= effectiveMin && heldDuration <= osDblMax) {
                            rotClick.doubleFired = true;
                            SendWithMaskedModifiers(MOD_BIT_NONE, {
                                MakeMouseInput(MOUSEEVENTF_LEFTDOWN),
                                MakeMouseInput(MOUSEEVENTF_LEFTUP),
                            });
                        }
                    }
                }
                break;
            }

            case ActionKind::PerAppVolume: {
                float step = (static_cast<float>(cfg.perAppStepPercent) / 100.0f) * static_cast<float>(dir);
                AdjustForegroundAppAudio(false, step);
                break;
            }

            case ActionKind::PerAppMute: {
                AdjustForegroundAppAudio(true, 0.0f);
                break;
            }

            case ActionKind::None:
                break;
        }
    }

    if (SUCCEEDED(comHr)) {
        CoUninitialize();
    }
}

// ============================================================================
// Knob-Only RegisterHotKey Engine (ZERO Keyboard Hook, Never Touches Typing)
// ============================================================================

static UINT ToWin32HotKeyMods(uint8_t modMask) {
    UINT mods = 0;
    if (modMask & MOD_BIT_ALT)   mods |= MOD_ALT;
    if (modMask & MOD_BIT_CTRL)  mods |= MOD_CONTROL;
    if (modMask & MOD_BIT_SHIFT) mods |= MOD_SHIFT;
    if (modMask & MOD_BIT_WIN)   mods |= MOD_WIN;
    return mods;
}

static int HotKeyId(int volSlot, uint8_t modMask) {
    return 0x100 + (volSlot * 16) + static_cast<int>(modMask & 0x0F);
}

static void FlushPendingQueue() {
    std::lock_guard<std::mutex> lock(g_queueMutex);
    g_eventQueue.clear();
}

static std::vector<int> g_registeredHotKeyIds;

static void UnregisterAllKnobHotKeys(HWND hwnd) {
    for (int id : g_registeredHotKeyIds) {
        UnregisterHotKey(hwnd, id);
    }
    g_registeredHotKeyIds.clear();
}

// Registers ONLY the exact (modMask, VK_VOLUME_UP/DOWN/MUTE) pairs used by enabled rules.
// Normal typing keys (A-Z, 0-9, Ctrl+C, Ctrl+V, Alt+Tab, etc.) are NEVER hooked or registered.
static bool RegisterEnabledKnobHotKeys(HWND hwnd) {
    UnregisterAllKnobHotKeys(hwnd);

    bool rotateModUsed[16] = {};
    bool pressModUsed[16]  = {};

    // Always register bare (modMask=0) volume/mute hotkeys so stray twin-pulses arriving
    // while SendWithMaskedModifiers temporarily releases Shift/Ctrl/Alt/Win are cleanly
    // dropped instead of leaking into Windows system volume or mute toggle.
    rotateModUsed[0] = true;
    pressModUsed[0]  = true;

    {
        std::lock_guard<std::mutex> lock(g_settingsMutex);
        for (const auto& rule : g_settings.rotateRules) {
            rotateModUsed[rule.chord.modMask & 0x0F] = true;
        }
        for (const auto& rule : g_settings.pressRules) {
            pressModUsed[rule.chord.modMask & 0x0F] = true;
        }
    }

    int registeredCount = 0;
    for (uint8_t modMask = 0; modMask < 16; modMask++) {
        UINT winMods = ToWin32HotKeyMods(modMask);
        if (rotateModUsed[modMask]) {
            int idUp   = HotKeyId(0, modMask);
            int idDown = HotKeyId(1, modMask);
            if (RegisterHotKey(hwnd, idUp, winMods, VK_VOLUME_UP)) {
                g_registeredHotKeyIds.push_back(idUp);
                registeredCount++;
            } else {
                Wh_Log(L"[Control Volume Knob] RegisterHotKey failed for mods=0x%02X VK_VOLUME_UP (err=%lu)",
                       modMask, GetLastError());
            }
            if (RegisterHotKey(hwnd, idDown, winMods, VK_VOLUME_DOWN)) {
                g_registeredHotKeyIds.push_back(idDown);
                registeredCount++;
            } else {
                Wh_Log(L"[Control Volume Knob] RegisterHotKey failed for mods=0x%02X VK_VOLUME_DOWN (err=%lu)",
                       modMask, GetLastError());
            }
        }
        if (pressModUsed[modMask]) {
            int idMute = HotKeyId(2, modMask);
            // MOD_NOREPEAT gives native OS-level single-shot press protection
            if (RegisterHotKey(hwnd, idMute, winMods | MOD_NOREPEAT, VK_VOLUME_MUTE)) {
                g_registeredHotKeyIds.push_back(idMute);
                registeredCount++;
            } else {
                Wh_Log(L"[Control Volume Knob] RegisterHotKey failed for mods=0x%02X VK_VOLUME_MUTE (err=%lu)",
                       modMask, GetLastError());
            }
        }
    }

    Wh_Log(L"[Control Volume Knob] Registered %d knob-only hotkeys (zero keyboard hook).", registeredCount);
    return true;
}

// Evaluates held extra keys ONLY when a registered volume knob WM_HOTKEY arrives.
static ActionKind MatchBindingOnKnobHotKey(
    bool isPress,
    uint8_t modMask,
    ULONGLONG nowMs,
    uint16_t& outMatchedExtraVk,
    int& outExtraCount,
    bool& outDebug) {
    outMatchedExtraVk = 0;
    outExtraCount     = 0;

    bool pauseInFullscreen = true;
    ActionKind matched = ActionKind::None;
    uint16_t heldExtraVk = 0;

    {
        std::lock_guard<std::mutex> lock(g_settingsMutex);
        outDebug          = g_settings.cfg.checkVirtualKeyCode;
        pauseInFullscreen = g_settings.cfg.pauseInFullscreen;

        // Check bound extra keys first, then guard against any other held typing/shortcut key
        // (e.g. Ctrl+V, Ctrl+C, Ctrl+/, Alt+Tab, Shift+W) so brushing the knob never misfires.
        for (uint16_t vk : g_settings.watchedExtraVks) {
            if (IsKeyDownNow(vk)) {
                outExtraCount++;
                heldExtraVk = vk;
            }
        }

        if (outExtraCount <= 1) {
            for (uint16_t vk : g_settings.unwatchedGuardVks) {
                if (IsKeyDownNow(vk)) {
                    outExtraCount++;
                    if (outExtraCount > 1 || heldExtraVk == 0) {
                        break;
                    }
                }
            }
        }

        const auto& rules = isPress ? g_settings.pressRules : g_settings.rotateRules;
        for (const auto& rule : rules) {
            if (rule.chord.modMask != modMask) continue;

            if (rule.chord.extraVk != 0) {
                if (outExtraCount != 1 || heldExtraVk != rule.chord.extraVk) continue;
            } else {
                if (outExtraCount != 0) continue;
            }

            matched           = rule.action;
            outMatchedExtraVk = rule.chord.extraVk;
            break;
        }
    }

    if (matched == ActionKind::None) {
        return ActionKind::None;
    }

    if (IsBlockedBySafetyGatesCached(pauseInFullscreen, nowMs)) {
        return ActionKind::None;
    }

    return matched;
}

// Message-only window procedure: receives ONLY registered knob WM_HOTKEY events and
// passive read-only physical mouse WM_INPUT (zero WH_KEYBOARD_LL, zero WH_MOUSE_LL).
static LRESULT CALLBACK KnobMessageWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_HOTKEY) {
        const int id = static_cast<int>(wParam);
        if (id >= 0x100 && id < 0x100 + 48) {
            const int     volSlot = (id - 0x100) / 16;
            const uint8_t modMask = static_cast<uint8_t>((id - 0x100) % 16);
            const bool    isPress = (volSlot == 2);
            const ULONGLONG nowMs = GetTickCount64();

            // Collision guard: if SendWithMaskedModifiers just released a held modifier (or a
            // modifier-knob tick fired <65ms ago), any mods=0x00 pulse is a hardware twin-pulse
            // hitting our synthetic modifier release -> drop it so Volume/Mute NEVER misfires.
            if (modMask == 0) {
                const bool maskingNow = g_maskingModifiers.load(std::memory_order_acquire);
                const ULONGLONG lastMask = g_lastMaskEndMs.load(std::memory_order_relaxed);
                const ULONGLONG lastMod  = g_lastModKnobMs.load(std::memory_order_relaxed);
                if (maskingNow ||
                    IsRecentTimestamp(lastMask, nowMs, MASK_COLLISION_GUARD_MS) ||
                    IsRecentTimestamp(lastMod, nowMs, MASK_COLLISION_GUARD_MS)) {
                    return 0;
                }
            } else {
                g_lastModKnobMs.store(nowMs, std::memory_order_relaxed);
            }

            uint16_t matchedExtraVk = 0;
            int      extraCount     = 0;
            bool     debug          = false;
            ActionKind action = MatchBindingOnKnobHotKey(
                isPress, modMask, nowMs, matchedExtraVk, extraCount, debug);

            if (debug) {
                const UINT vk = HIWORD(lParam);
                Wh_Log(L"[Control Volume Knob] WM_HOTKEY vk=0x%02X mods=0x%02X extra=0x%02X(%d) action=%d",
                       vk, modMask, matchedExtraVk, extraCount, static_cast<int>(action));
            }

            // If no custom action matched (e.g. bare knob turned while P+Knob is enabled, or
            // fullscreen pause / shortcut guard active), pass through to native system audio.
            if (action == ActionKind::None) {
                action = isPress ? ActionKind::SystemMute : ActionKind::SystemVolume;
            } else if (action != ActionKind::RotationClick) {
                g_rotClickResetGen.fetch_add(1, std::memory_order_relaxed);
            }

            KnobInputType inputType = KnobInputType::Press;
            if (volSlot == 0) inputType = KnobInputType::RotateUp;
            if (volSlot == 1) inputType = KnobInputType::RotateDown;

            // Message-thread hardware debounce (owned solely by KnobMessageWndProc):
            // 1) Drop accidental shaft wobble for 70ms after pressing the knob button.
            // 2) Coalesce 1-29ms same-direction encoder twin-pulses into 1 crisp detent.
            // 3) Drop <40ms opposite-direction mechanical contact-bounce glitches.
            static ULONGLONG  s_lastPressMs  = 0;
            static ULONGLONG  s_lastRotMs    = 0;
            static int        s_lastRotSlot  = -1;
            static ActionKind s_lastRotAct   = ActionKind::None;

            if (isPress) {
                s_lastPressMs = nowMs;
            } else {
                if (IsRecentTimestamp(s_lastPressMs, nowMs, PRESS_ROTATE_GUARD_MS)) {
                    return 0;
                }
                if (action != ActionKind::RotationClick && s_lastRotMs != 0 && nowMs >= s_lastRotMs) {
                    ULONGLONG dt = nowMs - s_lastRotMs;
                    if (s_lastRotSlot == volSlot && s_lastRotAct == action && dt < DETENT_COALESCE_MS) {
                        return 0;
                    }
                    if (s_lastRotSlot != -1 && s_lastRotSlot != volSlot && dt < ENCODER_GLITCH_MS) {
                        return 0;
                    }
                }
                s_lastRotMs   = nowMs;
                s_lastRotSlot = volSlot;
                s_lastRotAct  = action;
            }

            {
                std::lock_guard<std::mutex> lock(g_queueMutex);
                if (g_eventQueue.size() >= MAX_PENDING_EVENTS) {
                    g_eventQueue.pop_front();
                }
                g_eventQueue.push_back(KnobEvent{inputType, action, modMask, matchedExtraVk, nowMs});
            }
            g_queueCv.notify_one();
        }
        return 0;
    }

    if (msg == WM_INPUT) {
        if (g_prioritizeMouseFast.load(std::memory_order_relaxed)) {
            RAWINPUT raw{};
            UINT size = sizeof(raw);
            if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT,
                                &raw, &size, sizeof(RAWINPUTHEADER)) != static_cast<UINT>(-1)) {
                // hDevice == nullptr means synthetic SendInput (our own knob output) -> ignore
                if (raw.header.dwType == RIM_TYPEMOUSE && raw.header.hDevice != nullptr) {
                    const RAWMOUSE& m = raw.data.mouse;
                    const bool isWheel  = (m.usButtonFlags & (RI_MOUSE_WHEEL | RI_MOUSE_HWHEEL)) != 0;
                    const bool isButton = (m.usButtonFlags & (
                                              RI_MOUSE_LEFT_BUTTON_DOWN   | RI_MOUSE_LEFT_BUTTON_UP   |
                                              RI_MOUSE_RIGHT_BUTTON_DOWN  | RI_MOUSE_RIGHT_BUTTON_UP  |
                                              RI_MOUSE_MIDDLE_BUTTON_DOWN | RI_MOUSE_MIDDLE_BUTTON_UP |
                                              RI_MOUSE_BUTTON_4_DOWN      | RI_MOUSE_BUTTON_4_UP      |
                                              RI_MOUSE_BUTTON_5_DOWN      | RI_MOUSE_BUTTON_5_UP)) != 0;
                    const bool isMove   = (m.lLastX > 1 || m.lLastX < -1 || m.lLastY > 1 || m.lLastY < -1);

                    if (isWheel || isButton || isMove) {
                        ULONGLONG now = GetTickCount64();
                        if (isMove)   g_lastPhysicalMouseMoveMs.store(now, std::memory_order_relaxed);
                        if (isWheel)  g_lastPhysicalMouseWheelMs.store(now, std::memory_order_relaxed);
                        if (isButton) g_lastPhysicalMouseButtonMs.store(now, std::memory_order_relaxed);
                    }
                }
            }
        }
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    if (msg == WM_APP_RELOAD_HOTKEYS) {
        RegisterEnabledKnobHotKeys(hwnd);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static void MessageThreadProc() {
    g_msgThreadId.store(GetCurrentThreadId(), std::memory_order_release);

    MSG msg{};
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

    constexpr PCWSTR kMsgWndClass = L"ControlVolumeKnobMessageWindow";
    WNDCLASSW wc{};
    wc.lpfnWndProc   = KnobMessageWndProc;
    wc.hInstance     = GetModuleHandleW(nullptr);
    wc.lpszClassName = kMsgWndClass;
    ATOM classAtom   = RegisterClassW(&wc);

    HWND wnd = nullptr;
    bool rawRegistered = false;
    if (classAtom) {
        wnd = CreateWindowExW(0, kMsgWndClass, L"", 0, 0, 0, 0, 0,
                              HWND_MESSAGE, nullptr, wc.hInstance, nullptr);
        if (wnd) {
            g_msgWnd.store(wnd, std::memory_order_release);
            RegisterEnabledKnobHotKeys(wnd);

            // Passive read-only Raw Input registration for physical mouse priority
            RAWINPUTDEVICE rid{};
            rid.usUsagePage = 0x01; // Generic Desktop Controls
            rid.usUsage     = 0x02; // Mouse
            rid.dwFlags     = RIDEV_INPUTSINK;
            rid.hwndTarget  = wnd;
            rawRegistered   = RegisterRawInputDevices(&rid, 1, sizeof(rid)) != FALSE;
        }
    }

    g_msgInitOk.store(wnd != nullptr, std::memory_order_release);
    if (g_msgReadyEvent) {
        SetEvent(g_msgReadyEvent);
    }

    if (wnd) {
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        UnregisterAllKnobHotKeys(wnd);
        g_msgWnd.store(nullptr, std::memory_order_release);
    } else {
        Wh_Log(L"[Control Volume Knob] Failed to create message window (err=%lu)", GetLastError());
    }

    if (rawRegistered) {
        RAWINPUTDEVICE ridRemove{};
        ridRemove.usUsagePage = 0x01;
        ridRemove.usUsage     = 0x02;
        ridRemove.dwFlags     = RIDEV_REMOVE;
        ridRemove.hwndTarget  = nullptr;
        RegisterRawInputDevices(&ridRemove, 1, sizeof(ridRemove));
    }
    if (wnd) {
        DestroyWindow(wnd);
    }
    if (classAtom) {
        UnregisterClassW(kMsgWndClass, wc.hInstance);
    }
}

// ============================================================================
// Tool Mod Lifecycle Callbacks
// ============================================================================

void WhTool_ModUninit();

BOOL WhTool_ModInit() {
    Wh_Log(L"[Control Volume Knob] Initializing Tool Mod (zero keyboard hook)...");
    LoadSettings();

    g_maskingModifiers.store(false, std::memory_order_relaxed);
    g_lastMaskEndMs.store(0, std::memory_order_relaxed);
    g_lastModKnobMs.store(0, std::memory_order_relaxed);
    g_lastPhysicalMouseMoveMs.store(0, std::memory_order_relaxed);
    g_lastPhysicalMouseWheelMs.store(0, std::memory_order_relaxed);
    g_lastPhysicalMouseButtonMs.store(0, std::memory_order_relaxed);
    g_msgWnd.store(nullptr, std::memory_order_relaxed);
    g_msgInitOk.store(false, std::memory_order_relaxed);
    FlushPendingQueue();

    g_msgReadyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_running.store(true, std::memory_order_release);

    g_workerThread = std::thread(WorkerThreadProc);
    g_msgThread    = std::thread(MessageThreadProc);

    if (g_msgReadyEvent) {
        WaitForSingleObject(g_msgReadyEvent, 2000);
    }

    if (!g_msgInitOk.load(std::memory_order_acquire)) {
        WhTool_ModUninit();
        return FALSE;
    }

    return TRUE;
}

void WhTool_ModSettingsChanged() {
    LoadSettings();
}

void WhTool_ModUninit() {
    Wh_Log(L"[Control Volume Knob] Uninitializing Tool Mod...");
    g_running.store(false, std::memory_order_release);

    DWORD msgTid = g_msgThreadId.load(std::memory_order_acquire);
    if (msgTid != 0) {
        PostThreadMessageW(msgTid, WM_QUIT, 0, 0);
    }
    if (g_msgThread.joinable()) {
        g_msgThread.join();
    }

    if (g_msgReadyEvent) {
        CloseHandle(g_msgReadyEvent);
        g_msgReadyEvent = nullptr;
    }

    FlushPendingQueue();
    g_queueCv.notify_all();
    if (g_workerThread.joinable()) {
        g_workerThread.join();
    }
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR commandLine[MAX_PATH + 2 +
                      (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) -
                      1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
