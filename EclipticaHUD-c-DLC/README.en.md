# Ecliptica HUD DLC — Boss Weakness / Resistance

A **small standalone add-on** to the [main program](../README.en.md): it follows the same
VRChat log, works out **which boss is currently being fought**, and then shows that boss's
**weaknesses / resistances** from `Weakness&Resistance.txt` as a small always-on-top panel.

> **This is a separate program.** It neither modifies nor depends on the main
> `ecliptica-hud-c.exe`. You can run both at once; each reads the same log and they
> do not interfere with each other.

![Panel preview](dlc_preview.png)

---

## Contents

- [What it does](#what-it-does)
- [Building](#building)
- [Usage](#usage)
- [Data file format](#data-file-format)
- [How it works](#how-it-works)
- [Tests and verification](#tests-and-verification)
- [Known limitations](#known-limitations)
- [License](#license)

---

## What it does

The question asked most often during a boss fight is "does my damage type actually hurt this
thing?". This panel puts the answer in the corner of your screen:

```
Boss       Beelzebub
Physical      1x
Fire       1.25x  ▲ WEAK
Frost      0.75x  ▼ RES
Electric      1x
Luminous    0.5x  ▼ RES
Shadow      1.5x  ▲ WEAK
Poison      0.5x  ▼ RES
```

The seven elements are shown as **localized words**, chosen at build time: the English build shows
**Physical**, **Fire**, **Frost**, **Electric**, **Luminous**, **Shadow**, **Poison**; the Chinese
build shows the single characters **物** / **火** / **冰** / **电** / **光** / **暗** / **毒**;
the Japanese build shows **物理** / **火** / **氷** / **電気** / **光** / **闇** / **毒**.

- **▲ WEAK** (multiplier > 1) is marked in a warm colour, **▼ RES** (multiplier < 1) in a cold one,
  and `1x` in neutral grey
- The panel is always-on-top, semi-transparent and never steals focus; drag it wherever you like
- Change boss and the panel follows immediately (the boss row flashes as it switches)
- Position and opacity are stored in `hr-dlc.ini` and reused on the next launch

## Building

You need MinGW-w64 (or MSVC). No third-party dependencies.

**MinGW-w64**

```bat
mingw32-make
```

**MSVC** (inside `x64 Native Tools Command Prompt for VS 2022`, in this folder)

```bat
build.bat
```

Output: `hr-dlc.exe` (GUI subsystem, no console window).

One aside: because the exe name contains a `-`, typing `hr-dlc` in some shells is taken as an
option, so `.\hr-dlc.exe` is the safe form.

### Multilingual builds

The interface text exists in three languages — **Simplified Chinese / English / Japanese**. One
shared source tree is built once per language, selected at build time, producing three executables:

| Language | MinGW-w64 | MSVC | Output |
|---|---|---|---|
| Chinese (default) | `mingw32-make` | `build.bat` | `hr-dlc.exe` |
| English | `mingw32-make LANG=en` | `build.bat en` | `hr-dlc-en.exe` |
| Japanese | `mingw32-make LANG=ja` | `build.bat ja` | `hr-dlc-ja.exe` |

```bat
mingw32-make                  :: Chinese (default) -> hr-dlc.exe
mingw32-make LANG=en          :: English           -> hr-dlc-en.exe
mingw32-make LANG=ja          :: Japanese          -> hr-dlc-ja.exe

build.bat                     :: MSVC: Chinese
build.bat en                  :: MSVC: English
build.bat ja                  :: MSVC: Japanese
```

The helper binaries carry the same suffix (`test_dlc-en.exe`, `preview_dlc-en.exe`, and so on).

The interface text lives in `uitext_zh.h` / `uitext_en.h` / `uitext_ja.h`, and `uitext.h` dispatches
to the right table on `UI_LANG_EN` / `UI_LANG_JA`. **Adding a string means adding it to all three
files**; otherwise the other languages fail to build with an undefined symbol.

## Usage

```bat
hr-dlc.exe                       :: locate the VRChat log automatically and follow it
hr-dlc.exe --log "D:\...\output_log.txt"   :: watch one specific file
hr-dlc.exe --boss FlyLord        :: no log, pin one boss (for debugging)
hr-dlc.exe --table "D:\...\Weakness&Resistance.txt"   :: use this resistance table
hr-dlc.exe --demo                :: built-in rotating demo, no log needed
hr-dlc.exe --help
```

| Argument | Meaning |
|---|---|
| (none) | Locates the log automatically, **scans it from the start** to establish the current boss, then keeps following |
| `--log <file>` | Use only this file; retries every 2 seconds if it cannot be opened, and never falls back to auto-location |
| `--boss <name>` | Ignore the log and pin this one. Three spellings work: `FlyLord`, `YukiPhase2` (the object name from the log) and `Jim C. Bringer(P2)` (the key used in the data table) |
| `--table <file>` | Use this resistance table. By default it is located automatically (see [Data file format](#data-file-format)) |
| `--demo` | Cycles through a few representative bosses, to check that the panel itself works |
| `--help`, `-h` | Show help |

Controls:

| Action | Meaning |
|---|---|
| Drag the panel | Move the window; the position is remembered automatically |
| Click `✕` at the top right | Close |
| `Ctrl+Alt+W` | Global quit (works regardless of which window has focus) |
| Right-click the tray icon | Menu: reload the resistance table / quit |
| Double-click the tray icon | Bring the panel to the front |

> The panel is a `WS_EX_TOOLWINDOW` tool window, so **it never appears in the taskbar or in
> Alt+Tab**. There is a tray icon in the notification area (same design as the main program, but
> with a teal dot); after editing `Weakness&Resistance.txt` you do not need to restart — right-click the tray icon
> and choose "Reload the resistance table". The process is still visible in Task Manager under
> the **Details** tab as `hr-dlc.exe`.
>
> **Cannot find the icon on first run? It is almost certainly collapsed into `^`.** Windows 10/11
> **hides newly added notification-area icons by default**, while the program keeps running.
> Click **`^`** at the right end of the taskbar to expand the overflow and **drag the icon onto the
> taskbar** to pin it; or use Settings → Personalization → Taskbar → Notification area.
> The colours tell the two programs apart: **main HUD = blue dot, DLC = teal dot**.
>
> **If the tray icon does not appear**: `tray.log` next to the exe records the return value and
> error code of `Shell_NotifyIcon`. `NIM_ADD ret=0 lastErr=5` (access denied) means the folder
> carries a Windows **low-integrity** label and such a process may not talk to the taskbar —
> copy the whole folder to a normal location (e.g. the Desktop) and run it from there.

Log discovery follows the same order as the main program:

1. the most recently written `output_log*.txt` under `%USERPROFILE%\AppData\LocalLow\VRChat\VRChat\`
2. if that directory is missing, fall back to `%LOCALAPPDATA%\..\LocalLow\...`
3. then fall back to the exe's own directory / the current directory

When VRChat starts a new session (a newer log file appears in the directory) the panel switches
over automatically.

## Data file format

The data comes from **`Weakness&Resistance.txt`** (UTF-8). At startup the panel looks for it in the
order below and **uses the first one it finds**, so it usually finds the file wherever you put it:

| # | Location | When this applies |
|---|---|---|
| 1 | the path given to `--table <file>` | you want it somewhere specific |
| 2 | `<exe folder>\Weakness&Resistance.txt` | **the standard layout** (recommended) |
| 3 | `<exe folder>\EclipticaHUD-c-DLC\Weakness&Resistance.txt` | the exe sits in the repository root |
| 4 | `<exe folder>\..\Weakness&Resistance.txt` | the exe sits in a subfolder such as `bin\` |
| 5 | `<exe folder>\..\EclipticaHUD-c-DLC\Weakness&Resistance.txt` | as above, table in the DLC subfolder |
| 6 | `<working directory>\Weakness&Resistance.txt` | started from somewhere else |
| 7 | `<working directory>\EclipticaHUD-c-DLC\Weakness&Resistance.txt` | as above |

Two notes:

- **`--table` disables the fallback.** If the path you gave is wrong, the panel says "not found"
  rather than quietly using a different file — otherwise you would think your edit had taken
  effect.
- When nothing is found, **the panel tells you which folder to put the file in** and mentions
  `--table`:

  ```
  Resistance table not found
  Put Weakness&Resistance.txt in:
    D:\...\EclipticaHUD-c-DLC
  or point --table at it
  ```

**The easiest option** is to keep the exe and `Weakness&Resistance.txt` in the same folder
(case 2).

One block per boss, blocks separated by `---`:

```
Beelzebub
Physical: 1x
Fire: 1.25x
Frost: 0.75x
Electric: 1x
Luminous: 0.5x
Shadow: 1.5x
Poison: 0.5x
---
```

Accepted forms:

| Form | Meaning |
|---|---|
| `Fire: 1.25x` | An explicit multiplier; `>1` shows as "weak", `<1` shows as "resist" |
| `Fire: 0.7-x (resist)` | **Multiplier + direction + verdict**: the base is `0.7`, `-x` means **lower than 0.7**, verdict "resist"; the panel shows `<0.7x ▼RES` |
| `Fire: 1.25+x (weak)` | Same but the other way: **higher than 1.25** → `>1.25x ▲WEAK` |
| `Fire: 1+x (weak)` | Says weak without a usable multiplier; the panel shows `WEAK ▲` (the `1` is the neutral baseline, so printing it would be misleading) |
| `Fire: 1-x (resist)` | Says resist without a usable multiplier; the panel shows `RES ▼` |
| `Others: 0.75x` | Every element not listed separately uses this multiplier (e.g. `Jim C. Bringer(P3)`); `其余` works too |
| A plain sentence | When a block has no table at all, the text is shown as a note (e.g. `NaN`, `Jim C. Bringer(P2)`) |

About the `±x` direction:

- `N-x` means **below N**, `N+x` means **above N** (`x` is an increment that is not given).
  The panel marks it with `<` / `>`, so it never reads as "exactly N".
  Example: `Despair(P1)` has `Electric: 0.7x` (exactly 0.7) while `Despair(P2)` has
  `Electric: 0.7-x (resist)` (**below** 0.7, i.e. phase 2 resists it more). The panel shows
  `0.7x` versus `<0.7x`, so the two are distinguishable at a glance.
- When the base is exactly `1`, only the direction is shown (`WEAK` / `RES`); writing `>1x` would be
  more confusing than helpful.
- An explicit verdict word wins: `1.25-x (resist)` shows `<1.25x ▼RES`.

A few tolerance rules:

- **Both colons are accepted**: `Fire: 1x` and `Fire：1x` (the full-width colon a Chinese IME produces) are equivalent.
- **Element names**: English, Chinese and Japanese keys are all accepted (see the table below).
- **Note lines can be long**: a single line may be up to 1024 bytes. Anything wider than the buffer is
  truncated **on a character boundary** with a trailing `…`, so no multi-byte character is ever split
  (a half character would make the whole line render blank). The longest real line is 388 bytes of
  Japanese and is shown in full.

**Note text is displayed line by line, exactly as written in the data file.** It is never merged
into one paragraph and re-wrapped. The `NaN` block is five sentences in the file, and five entries
on the panel:

```
The weakness depends on the mode it
  takes.
Fire mode: weakness is fire
Frost mode: weakness is frost
Electric mode: weakness is electric
Shadow & Luminous mode: no weakness
```

A line only wraps when **that line by itself** is wider than the panel; the wrapped continuation is
indented so it cannot be mistaken for a new line. The first English sentence above happens to be
long enough to wrap, which is why it occupies two rendered lines. The Chinese and Japanese builds
show the same block with one sentence per line, because those sentences are narrower — **wrapping
depends on the text length, not on the language.**

**The note text lives in the data file**, so you write whatever you want shown — the panel does not
translate it, it only displays it as-is (Chinese and English are both fine).

### Language tags on note lines

One file can carry all three languages while the numbers stay shared. A note line may start with a
language prefix:

```
NaN
zh: 弱点取决于它当前所处的模式。
en: The weakness depends on the mode it takes.
ja: 弱点は現在のモードによって決まります。
```

- The prefixes are `zh:` / `en:` / `ja:` (lowercase); a space after the colon is optional.
- Each build keeps only its own language's lines, **plus any line without a prefix** — untagged
  lines are shown by all three builds.
- The numbers themselves carry no prefix and are shared by all three builds.

### Inline comments

A `#` at the end of a line starts a comment, and comments are never displayed. Use it to keep the
original wording next to a translation for reference:

```
NaN
弱点取决于它当前所处的模式。      # The weakness depends on the mode it takes.
火模式：弱点是火                  # Fire mode: weakness is fire
冰模式：弱点是冰                  # Frost mode: weakness is frost
电模式：弱点是电                  # Electric mode: weakness is electric
暗与光模式：没有弱点              # Shadow & Luminous mode: no weakness
---
```

Rule: a `#` starts a comment only at the start of a line or after whitespace; a `#` glued to text,
like `标签#不是注释`, is literal content. A line that is nothing but a comment is skipped and does
not leave a blank line on the panel.

### Element keys and names

The seven canonical element keys are `Physical` / `Fire` / `Frost` / `Electric` / `Luminous` /
`Shadow` / `Poison`, and they are case-insensitive. **Chinese and Japanese keys can be written
directly as well**, and all three key sets are accepted by all three builds — the set of accepted
aliases is identical in every build; only the displayed name depends on the build:

| Keys accepted in the data file | English panel | Chinese panel | Japanese panel |
|---|---|---|---|
| `Physical` / `物` / `物理` | Physical | 物 | 物理 |
| `Fire` / `火` / `火焰` | Fire | 火 | 火 |
| `Frost` / `冰` / `冰霜` | Frost | 冰 | 氷 |
| `Electric` / `电` / `雷` | Electric | 电 | 電気 |
| `Luminous` / `光` / `圣` | Luminous | 光 | 光 |
| `Shadow` / `暗` / `暗影` | Shadow | 暗 | 闇 |
| `Poison` / `毒` / `毒素` | Poison | 毒 | 毒 |

In other words, **the English (and Chinese, and Japanese) spelling in the data file is just a
key**: each build renders its own language's name on the panel, and the two never affect each
other. Boss names (`Beelzebub`, `Jim C. Bringer` and the like) are proper nouns, so the panel uses
the spelling from the data table in every build.

**Parsing rules** (worth knowing before you add a block):

- A line without a colon is treated as a new boss block name if it is **at the start of the file,
  immediately after a `---`, or the current block already has numbers**; otherwise it is note text
  for the current block. So **keeping the `---` between blocks is recommended**.
- A line with a colon that is not an element name or `Others` (for example `Fire mode: weakness is
  fire`) is always treated as note text.
- The block name is the key used for lookups. A boss with phases is written as `name(P2)`.

### About phases

In the log, different phases of the same boss are different object names, for example `Yuki` /
`YukiPhase2` and `JimBringer` / `JimBringerPhase3`. The panel looks them up like this:

1. map the internal name to a display name (`FlyLord → Beelzebub`; the mapping table is in `res.c`)
2. try `DisplayName(P<phase number>)` first, e.g. `Yuki(P2)`
3. if that misses, fall back to `DisplayName` without a phase
4. if both miss → the panel shows "No entry for this boss"

So phase-specific entries such as `Yuki(P1)` / `Yuki(P2)` hit exactly, while a single `Corus` entry
covers all of its phases.

The three phases of `Jim C. Bringer` are written three different ways in the table, and each one
happens to stand for a category:

| Entry | Content | On the panel |
|---|---|---|
| `Jim C. Bringer(P1)` | `No weaknesses and resistances.` | single-line note |
| `Jim C. Bringer(P2)` | `All damage blocked.` | single-line note |
| `Jim C. Bringer(P3)` | `Physical: 1x` + `Others: 0.75x` | number table + Others |

If a phase genuinely has no entry in the table (a new boss that has not been added yet, say), the
panel says so honestly — "No entry for this boss" — and hints at where to add one.

## How it works

```
VRChat output_log.txt
        │  logtail.c   locate + initial scan + keep following
        ▼
   current boss (internal name + phase number)
        │  res.c       display-name mapping -> table lookup
        ▼
   weakness / resistance entry
        │  dlcui.c     layout computation + GDI double-buffered drawing
        ▼
   layered topmost window (dlc.c)
```

- **Only three things are recognized**: the `now fighting boss:` line that starts a fight, the
  `Boss X dead` kill line, and the "this fight is over" signals — `now in intermission` /
  `now in lobby` / `now in stage:` / entering or leaving the room. The main program does full
  parsing; this one stays deliberately minimal so the two never affect each other.
- The log is **scanned from the start** before following: the HUD is often launched mid-fight, and
  watching only new lines would leave it with no idea which boss is up. It scans plain text lines,
  so even a few MB of log takes only tens of milliseconds.
- The layout (title row / boss row / element table / status bar) is computed once by
  `dlcui_layout()`, and **drawing and hit-testing share the same rectangles**, so a button can
  never end up unclickable.
- The window is `WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE` and never
  steals focus from VRChat. It is DPI aware, and the layout is identical from 60% to 200% scaling.

## Tests and verification

```bat
mingw32-make test        :: logic tests (212 checks)
mingw32-make preview     :: render one panel preview offscreen, no monitor needed
```

With the suffix form the helpers follow the language you built, e.g. `mingw32-make LANG=en test`
builds and runs `test_dlc-en.exe`.

`test_dlc.c` covers: data-table parsing (numeric / symbolic / `Others` / note-only),
the boss display-name mapping (18 entries), base-name and phase-number extraction, and the return
values for every kind of lookup miss.

`preview_dlc.exe` can render any state without a monitor, which makes it easy to check the
typography:

```bat
preview_dlc.exe "Weakness&Resistance.txt" FlyLord 100 out.bmp
preview_dlc.exe "Weakness&Resistance.txt" -       100 waiting.bmp    :: no boss fight
preview_dlc.exe "Weakness&Resistance.txt" YukiPhase2 100 yuki2.bmp  :: the phase comes from the name
```

The states actually covered:

![Eight states](dlc_states.png)

|  | Left | Middle | Right |
|---|---|---|---|
| **Top** | plain number block (Beelzebub) | multi-line note (NaN) | number table (Jim P1) |
| **Middle** | long note (Jim P2) | `Others:` block (Jim P3) | multiplier + verdict (Despair P2) |
| **Bottom** | no boss fight | boss missing from the table | (empty) |

| State | Result |
|---|---|
| plain number block (Beelzebub) | 7 elements + weak/resist markers + correct colours |
| `Others:` block (Jim P3) | Physical 1x, the rest 0.75x ▼RES via Others |
| symbolic block (Yuki P2) | Fire shows "WEAK ▲", Frost/Electric show "RES ▼" |
| multi-line note (NaN) | **displayed line by line as in the data file**; only over-wide lines wrap |
| single-line note (Jim P1 / P2) | one line of source is one line on the panel |
| no boss fight | shows "Boss —" and "Waiting for a boss fight…" |
| boss missing from the table | says "No entry for this boss" |

Apart from the **boss name** (a proper noun, spelled as in the data table), every piece of text on
the panel is localized at build time: the title, the status bar, the seven element names, and the
note text you wrote in the data file.

`test_dlc-en.exe --log <log>` verifies the "recognize the boss from a real log" chain without
opening a window, printing which boss was recognized, the entry it found, and the verdict for each
element. **Its output follows the language you built**, so an English build prints English labels:

```
===== caught the moment QueenBug entered the fight =====
Log file   : 2026-10-12_19-00-00
Now fighting: QueenBug
Display name: Vesra
Phase      : 1
Lookup key : Vesra(P1)  /  Vesra
Entry      : Vesra
  Physical           1.00x   -
  Fire               1.50x   WEAK
  ...
```

In the Chinese and Japanese builds each line also prints the data-file key next to the panel name
(e.g. `物 Physical  1.50x  弱`), so you can see at a glance what to write in the table. In the
English build the two are the same word, so it is printed once.

A few cases measured against a real log:

| Boss in the log | Display name | Result |
|---|---|---|
| `Pandora` | Pandora | 7 numeric entries, Fire 1.5 weak / Frost 0.3 resist … |
| `QueenBug` | Vesra | name mapping applied, Vesra block found |
| `ConeHeadPhase2` | Cone Head | `Cone Head(P2)` misses first → falls back to `Cone Head` |
| `Nan` | NaN | note-only, 7 entries show `—` plus the note text |

## Known limitations

- **Windows** only (Win32 + GDI).
- The resistance data **comes entirely from that txt file**; the game itself does not output these
  numbers, so whether they are right depends on whether you maintain the file. The panel only does
  the "look up + display" part.
- The interface text is localized per build (Chinese / English / Japanese), and so are the seven
  element names, which means the panel names can differ from the keys you wrote in the data file
  (see [Element keys and names](#element-keys-and-names)). Boss names stay exactly as written in
  the data table in all three builds.
- Data-file parsing is **convention-driven**: keep the `---` between blocks, and spell the seven
  element names as listed above. A typo will not crash anything, but it shows up as "no entry for
  this boss" or as a missing row.
- Only one boss is shown at a time; if several bosses exist in the world at once, the panel shows
  the one from the last `now fighting boss` line in the log.

## License

Same as the main project: **MIT License** (see [../LICENSE](../LICENSE)).
