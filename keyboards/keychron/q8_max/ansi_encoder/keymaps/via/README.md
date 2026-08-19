# Keychron Q8 Max — HHKB-style custom keymap

Custom `via` keymap for the Keychron Q8 Max (ANSI, knob), replicating HHKB
placements and adding vim-style navigation. Used across a Mac and a Windows
machine through a TESmart Dual USB-C KVM switch — everything lives in
firmware so both machines see the identical keyboard. The physical Mac/Win
side switch stays in **Mac mode** for both machines.

## Base layer changes (Mac layer 0 and Windows layer 1, kept in sync)

| Physical key | Stock | Now |
|---|---|---|
| Caps Lock position (1.75u) | Caps Lock | **tap = Esc, hold = Left Ctrl** (`LCTL_T(KC_ESC)`) |
| Bottom-left corner (1.25u) | Left Ctrl | **tap = Caps Word, double-tap = Caps Lock** (tap dance) |
| Backspace (2u) | Backspace | `\` |
| `\` (top-right of main block) | `\` | Backspace |
| Left spacebar | Space | **tap = Space, hold = NAV layer** (`LT(NAV, KC_SPC)`) |
| Right Fn key | Fn2 (momentary) | **tap = `` ` ``, hold = Fn2** (`LT(FN2, KC_GRV)`) — Shift+tap = `~` |

## Key overrides (all layers, firmware-level)

| Chord | Sends |
|---|---|
| **Right** Shift + `[` / `;` / `'` / `/` | ↑ ← → ↓ (HHKB-style; Left Shift still types `{` `:` `"` `?`) |

## NAV layer (hold left spacebar)

| Key | Sends | Mnemonic |
|---|---|---|
| H / J / K / L | ← ↓ ↑ → | vim |
| U / D | PgUp / PgDn | up/down |
| A / E | Home / End | emacs C-a / C-e |
| W / B | Opt+→ / Opt+← (word jump) | vim w/b |

## Other behavior

- `Shift+Esc` → `~` — **not firmware**: a Karabiner-Elements rule on the Mac
  (Mac-only; on the Windows machine use `Fn2+Esc` for `~`)
- `Fn1` layer: stock Keychron media/brightness row, Bluetooth keys, RGB
- `Fn2` layer: F1–F12 on the number row (hold the right Fn key)
- Tap-hold tuning: `TAPPING_TERM 180`, `PERMISSIVE_HOLD` (`config.h`)
- Dynamic keymap layer count raised 5 → 6 for the NAV layer
  (`keyboards/keychron/q8_max/info.json`)
- Core patch in `quantum/process_keycode/process_key_override.c`: backport of
  mainline's HID report ordering fix — without it macOS drops the replacement
  key of a key override (mod change and key change in one report)

### Tried and removed

- **Space Cadet shifts** (tap = parens): misfires against the Shift+Space
  Korean/English IME toggle. Do not re-add.
- **Ctrl+H/J/K/L → arrows** (key overrides): superseded by the NAV layer on
  the left spacebar; removed to restore native terminal control codes
  (Ctrl+H backspace, Ctrl+K kill-line, Ctrl+L clear).

## Host-side settings that matter

- macOS: **"Use F1, F2, etc. keys as standard function keys" is ON**
  (System Settings → Keyboard → Keyboard Shortcuts → Function Keys).
  Without it macOS turns the Fn2 layer's F1/F2 into brightness keys.
- **Karabiner-Elements runs on the Mac** with two rules: `Shift+Esc → ~` and
  `Shift+Space → Ctrl+Space` (Korean/English input toggle). Both are Mac-only.
  A third rule (`left_control+hjkl → arrows`) was removed 2026-08-19 when the
  equivalent firmware overrides were retired — when debugging "keyboard"
  behavior on the Mac, always check Karabiner first.
- No other OS-level modifier remapping (all other remaps are in firmware).

## Building

```sh
# One-time: Homebrew qmk + keg-only ARM toolchain on PATH
export PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:$PATH"

qmk compile -kb keychron/q8_max/ansi_encoder -km via
```

Built from Keychron's `wireless_playground` fork (the Q8 Max is **not** in
mainline QMK; mainline firmware would break wireless).

## Flashing

1. Keyboard in **Cable** mode, USB connected.
2. Enter DFU: pull the spacebar keycap, hold the reset button ~4 s.
   (Holding Esc while replugging does *not* work — the battery keeps the MCU
   powered, so replugging never reboots it.)
3. `qmk flash -kb keychron/q8_max/ansi_encoder -km via`, or flash the
   prebuilt bin with QMK Toolbox / dfu-util.
4. If base-layer keys act stale afterwards, factory-reset the EEPROM:
   hold `Fn + J + Z` ~4 s (left Fn).

A known-good compiled binary is committed at
`keyboards/keychron/q8_max/firmware/keychron_q8_max_ansi_encoder_via_custom.bin`,
and tagged releases with binaries live at
<https://github.com/yongha-h/qmk_firmware/releases>.

## Maintenance

- Branch `my-keymap` on <https://github.com/yongha-h/qmk_firmware>
  (fork of Keychron/qmk_firmware; remote `origin` = Keychron, `fork` = mine).
- To take Keychron updates: `git fetch origin`, rebase `my-keymap` onto the
  new `wireless_playground` tip, rebuild. A conflict in
  `process_key_override.c` means Keychron merged the mainline fix — drop the
  local patch.
- Release rhythm: commit → tag `q8max-vX.Y` → `gh release create` with the
  fresh `.bin`.
- VIA: the Q8 Max needs its definition side-loaded in usevia.app
  (Settings → Show Design tab → Load draft definition); the JSON is attached
  to release `q8max-v1.0`. Note VIA edits live in EEPROM and *override* the
  compiled keymap defaults until a factory reset.
