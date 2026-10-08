# Ecliptica HUD User Guide

> This document is only about **how to use it**: what every number means, how to change each
> setting, and how to troubleshoot problems. For the project introduction, build instructions,
> code structure and verification results see [README.en.md](README.en.md).

> 🌐 **Language 言語 语言**：
> [简体中文](使用说明.md) · [English](USAGE.en.md) · [日本語](USAGE.ja.md)
>
> The UI itself also ships in three languages, one executable each:
> `ecliptica-hud-c.exe` (Chinese), `ecliptica-hud-c-en.exe` (English),
> `ecliptica-hud-c-ja.exe` (Japanese). Button names in this document use the
> English build; the other builds differ only in wording — layout and
> behaviour are identical.

---

## Contents

- [1. Get started in three minutes](#1-get-started-in-three-minutes)
- [2. What every part of the interface means](#2-what-every-part-of-the-interface-means)
- [3. How to change settings](#3-how-to-change-settings)
  - [3.1 What the interface buttons change directly](#31-what-the-interface-buttons-change-directly)
  - [3.2 config.ini only: the DPS window](#32-configini-only-the-dps-window)
  - [3.3 All configuration keys at a glance](#33-all-configuration-keys-at-a-glance)
- [4. Keyboard shortcuts](#4-keyboard-shortcuts)
- [5. FAQ](#5-faq)
- [6. Advanced usage](#6-advanced-usage)
- [7. Uninstalling](#7-uninstalling)

---

## 1. Get started in three minutes

### Step 1: Put the files somewhere

Put `ecliptica-hud-c.exe` in **any** directory you like (the desktop, a folder on drive D,
anywhere). No installation, no administrator rights, and it does not write to the registry.

Use `ecliptica-hud-c-en.exe` for the English build or `ecliptica-hud-c-ja.exe` for the
Japanese one; the three builds differ only in interface language and everything below is
identical.

### Step 2: Launch it

```bat
ecliptica-hud-c.exe
```

Double-clicking works too. Once started, it goes looking for the VRChat log here:

```
C:\Users\<your user name>\AppData\LocalLow\VRChat\VRChat\
```

and picks the `output_log*.txt` with the **newest last-write time** in that directory to
follow.

### Step 3: Confirm that it is working

Look at the **status bar in the bottom-left corner** of the panel; it always tells you the
current state:

| Status bar text | Meaning | What to do |
|---|---|---|
| `No VRChat log found` | There is no log in that directory | Make sure VRChat has been started at least once |
| `Waiting to enter Ecliptica` | The log is connected, but you are not in the world | Just enter the world; nothing else needed |
| `In Ecliptica, waiting for a run` | You are in the world, but no fight has started | Nothing needed |
| `Run in progress · <boss name>` | A boss fight is running | Nothing needed |
| `Run in progress · Intermission 3` | The break after the 3rd stage | Nothing needed |
| `Demo mode` | You started it with `--demo` | Nothing needed |
| `Cannot open the file given to --log` | The log path you gave does not exist | Check the path |

The **bottom-right corner** shows which log file it is reading, for example
`output_log_2026-09-24_18-20-39.txt`. As long as there is a file name there and the
bottom-left does not say "No VRChat log found", it is connected.

### The panel did not show up?

- It is a **borderless, semi-transparent window**, so it may be hidden behind other windows —
  press `Alt+Tab` to look for it, or check the horizontally centred spot about a quarter of
  the way down from the top of the screen (the default position on first start).
- The position is remembered, so next time it appears where you left it.

---

## 2. What every part of the interface means

```
┌──────────────────────────────────────────────────────┐
│ ● Ecliptica HUD  Combat Stats [Click-through · …]  ✕ │ ← Title bar
├──────────────────────────────────────────────────────┤
│ [Top][Big][Small][Opaque][Fade][Thru][Log]           │ ← Button row
├──────────────────────────────────────────────────────┤
│ Stage 3 · Proto Colony              Class Nekomancer │ ← Stage / Class
│ ▓▓▓░░░░░░░  Primal 25% Kills 2 Switches 7 Tokens 1/3 │ ← Progress / summary
├──────────────────────────────────────────────────────┤
│ Fight Beelzebub (P2)  Time 01:19   Target xxx 00:07  │ ← Fight boss row
├──────────────────────────────────────────────────────┤
│             Stage         Run       Fight            │ ← Header
│ Damage        5,802      77,408       6,058          │
│ DPS            22.1        17.5        22.2          │
│ …                                                    │
├──────────────────────────────────────────────────────┤
│ Damage sources (fight)                               │
│ enemy · Kick Project                  29  x1         │
├──────────────────────────────────────────────────────┤
│ Event log [All][Taken][Target][Stage/Boss]       ▲ ▼ │
│ 22:09:50  Left world                                 │
├──────────────────────────────────────────────────────┤
│ ◀ ▶ Run 3/5          ◀ ▶ Fight 2/4          LIVE     │ ← History bar
├──────────────────────────────────────────────────────┤
│ Run in progress · Amaziah           output_log_….txt │ ← Status bar
└──────────────────────────────────────────────────────┘
```

### Title bar

- Normally it just shows the title.
- **A gold `Click-through · Ctrl+Alt+T`** means click-through is on (see
  section 4).
- The `✕` at the top right closes it.

### Button row (7 buttons)

See [3.1](#31-what-the-interface-buttons-change-directly).

### Stage / Class / Progress

- **Stage N · name**: which stage you are in and what it is called.
- **Class**: your class for this run.
- **Progress bar**: the stage progress percentage, also showing the **stage name** that goes
  with it (Primal / Penumbral / Antumbral / Umbral / Eclipse / Eye of the Eclipse).
- **Kills N**: the number of bosses killed this run.
- **Switches N**: the total number of target (ownership) switches of enemy units this run.
- **Tokens N/M**: N tokens picked up in this stage / M spawned in total this stage.

### The Fight boss row

`Fight <boss name> (Pn)` — `(P2)` means this is the boss's second form. Phase 2 and phase 3 of
the same boss count as **the same continued fight**, with the data merged and the statistics
never interrupted.

On the right:

- `Time mm:ss` — how long this fight has been running.
- `Target <player> mm:ss` — **which player the boss is currently locked onto, and for how
  long**. The player name is drawn in **gold** so it stands out more than the duration beside
  it; one glance tells you who is being focused right now.
- If it shows `Target —`, there is no target information in the log (see
  [Q3](#q3-why-does-the-target-column-always-show-a-dash)).

**Over-long player names are shortened.** Any name longer than **10 characters** shows only
its **first 5 characters plus `…`**:

| Name in the log | Displayed as | Characters |
|---|---|---|
| `SRETR00` | `SRETR00` | 7, as is |
| `Millianna_` | `Millianna_` | 10, as is (the boundary) |
| `ひなた_hinatan` | `ひなた_h…` | 11 → shortened |
| `てぃな xplaTina` | `てぃな x…` | 12 → shortened |
| `蒼凪 みなと／Minato` | `蒼凪 みな…` | 13 → shortened |
| `三松许今年也超爱你明年也保证` | `三松许今年…` | 14 → shortened |

The limit counts **characters**, not bytes, and only cuts on character boundaries — so you
never get half a Chinese character or a garbage box. The `Target switch <object> → <player>`
entries in the event log use the same rule.

> Internally the statistics still keep the full name; shortening only affects the display.

### The three-tier table (the important one)

What the three columns cover:

| Column | Scope |
|---|---|
| **Stage** | Only the current small level |
| **Run** | From entering the world to leaving it, including every stage and every boss fight |
| **Fight** | Only the current boss fight (adds killed during stages do not count) |

What the eight rows mean:

| Row | Meaning |
|---|---|
| **Damage** | Total damage you dealt |
| **DPS** | Damage per second over the recent window, see [3.2](#32-configini-only-the-dps-window) |
| **Taken** | Total damage you took |
| **Hits** | The **number of times** you were hit |
| **Max Hit** | The largest single hit you took |
| **Avg Hit** | Taken ÷ number of hits |
| **Taken/s** | Damage taken per second over the recent window |
| **Tokens** | The number of tokens picked up |

> The table has **no "Deaths" row**: death counts are not part of the statistics. A death only
> leaves one "You died" entry in the event log (see
> [Q4](#q4-why-arent-deaths-counted-in-the-stats)).

**Why are some cells 0 or `—`?**

- `0` is a real 0 (you took no hits in this fight, for instance).
- `—` means **that tier has no such concept**. For example "Fight tokens" is always `—`,
  because tokens are settled per stage and do not belong to a particular boss fight.
- The Stage column is also all `0` as long as you have not entered any stage yet.

### Damage sources

It splits damage taken by **`who · with which move`**. Each line has the format:

```
enemy · hit                                1  x20      ← 1 point per hit, 20 hits
NX-Obsidian · Punch                       26  x2       ← 26 points per hit, 2 hits
The Gravetender · Roar                    16  x1       ← a single hit of 16 points
```

The red number on the right is the **per-hit damage**, and the `xN` right after it is the
**number of hits**. To get the total, multiply the two (20, 52 and 16 in the examples above).

> **Why per-hit instead of a running total?** A running total next to `xN` is easily read as
> "N points landed N times". The classic example is a damage-over-time effect whose
> `from source:` is empty in the log, displayed as `enemy · hit`: it totals 20 points over
> 20 hits, so showing the total would make it `20 x20`, which looks like 20 points every
> time. With the per-hit value it is `1 x20` and can no longer be misread.

The list is ordered by **first appearance**, not by damage.

The heading changes with the current state:

| Heading | Description |
|---|---|
| `Damage sources (fight)` | Only the current boss fight |
| `Damage sources (stage)` | Damage taken in the current stage (the default when not in a boss fight) |
| `Damage sources (run)` | The whole run's damage taken (the default once a run has ended) |

When you are not in combat and there is no current stage, the whole-run summary is shown
automatically.

### Event log

Entries are in **reverse chronological order** (newest at the top) and the time in front of
each entry is the time from the log.

- Four filter buttons: **All / Taken / Target / Stage/Boss** — click one to switch.
- Right-clicking **anywhere** on the panel also cycles the filter (while click-through is
  off).
- `▲` scrolls back to older events, `▼` returns to the newest.
- At most **512 entries** are kept; older records are pushed out.

### History bar / status bar

- **The ◀ ▶ on the left**: page through **past runs** (`Run 3/5` = run 3 of 5).
- **The ◀ ▶ in the middle**: page through **past boss fights** (`Fight 2/4`).
- The capsule on the right shows **`LIVE`** (viewing the current run) or **`HISTORY`**
  (viewing a past run).
- While browsing history, the three-tier table above switches as a whole to that run's final
  data.

---

## 3. How to change settings

### 3.1 What the interface buttons change directly

The 7 buttons in the button row **take effect on click and are remembered automatically**:

| Button | Effect | Range | Change per click |
|---|---|---|---|
| **Top** | Whether the window is always on top (highlighted when on) | on / off | — |
| **Big** | Scale the whole interface up | 60% – 200% | +10% |
| **Small** | Scale the whole interface down | 60% – 200% | −10% |
| **Opaque** | Raise opacity | 40 – 255 | +15 |
| **Fade** | Lower opacity | 40 – 255 | −15 |
| **Thru** | Mouse click-through toggle (highlighted when on) | on / off | — |
| **Log** | Show / hide the event log panel (highlighted when on) | on / off | — |

> Once a button reaches its limit it stops changing and never goes out of range.
> While the mouse rests on a button, **the right-hand side of the bottom status bar** shows
> that button's description.

Also:

- **Dragging**: hold the left button on an empty part of the panel and drag to move the
  window; the position is remembered automatically.
- **Filtering the event log**: click the four buttons in the event log panel's title bar.

### 3.2 config.ini only: the DPS window

**This is the most frequently asked-about setting and there is no interface button for it** —
the top button slot was taken by **Thru**, so the DPS window can only be changed in the
configuration file.

#### Why you would change it

DPS is a **sliding-window** value, not "total damage ÷ total time". The longer the window the
steadier the number, the shorter the window the better it reflects the current burst. The
default is **10 seconds**.

#### Steps

> ⚠️ **Step 1 is not optional.** On exit the program writes the whole in-memory configuration
> back to `config.ini`. If you edit the file while the HUD is running, your changes are
> overwritten on exit.

1. **Quit the HUD completely** (click `✕`, or press `Ctrl+Alt+Q`).
2. Find `config.ini` (see the explanation below for its location).
3. Open it in **Notepad** and find this line:

   ```ini
   stat_window=10
   ```

4. Change it to the value you want; only these six are allowed:

   | Value | Good for |
   |---|---|
   | `3` | Watching instant burst; the number jumps around very fast |
   | `5` | A short window, leaning towards burst |
   | `10` | **The default**, fairly balanced |
   | `30` | Steady output |
   | `60` | Close to the average over a whole fight |
   | `120` | The long view; only long fights show any movement |

   > Any other number (such as `15`) is automatically treated as `10`.

5. Save the file.
6. Start `ecliptica-hud-c.exe` again.

#### Where is config.ini?

There are two possibilities, checked in order:

1. **There is a `config.ini` next to the exe** → that one is used (portable mode). Good for a
   portable copy: keep the exe and config.ini together and copy the whole folder, settings
   and all.
2. **Otherwise** → it lives in the per-user directory:

   ```
   C:\Users\<your user name>\AppData\Roaming\EclipticaHUD-C\config.ini
   ```

   To open it quickly: press `Win+R`, paste the line below and hit Enter:

   ```
   %APPDATA%\EclipticaHUD-C
   ```

   > It defaults to here so that: ① an ordinary user can still write to it when the program
   > is installed under `C:\Program Files`; ② **different Windows users on the same machine
   > each keep their own copy** instead of overwriting one another.

   > Be careful not to confuse it with the upstream Rust version EclipticaHUD's
   > `%APPDATA%\EclipticaHUD\`; this program uses the directory with the `-C` in it.

#### How DPS is actually calculated

Once you understand this, you know why it sometimes differs from what you work out in your
head:

```
DPS = damage dealt in the last N seconds ÷ the time actually counted
```

where "the time actually counted" = `min(N seconds, how long this unit has been running)`.

- Two seconds into a fight the denominator is 2 seconds rather than 10, so **the numbers jump
  around a lot at the start** and only become worth reading once they settle.
- The three DPS columns use **the same window length** but are **calculated separately**: the
  Stage column only counts this stage's damage, the Fight column only counts this boss
  fight's damage.
- When there is no recognisable log event for a long time (standing around doing nothing,
  say), the time base does not advance and DPS and Time **freeze** until the next event.

### 3.3 All configuration keys at a glance

The file itself looks like this:

```ini
# Ecliptica HUD (C) config - UTF-8
always_on_top=1
alpha=210
scale=100
stat_window=10
show_event_log=0
click_through=0
win_x=538
win_y=71
ev_filter=0
# world_names: extra Ecliptica-family world names, separated by | or ,
world_names=
```

| Key | Default | Values | Description | How to change it |
|---|---|---|---|---|
| `always_on_top` | `1` | 0 / 1 | Whether the window stays on top | Use the **Top** button |
| `alpha` | `210` | 40 – 255 | Opacity, higher is more opaque | Use the **Opaque/Fade** buttons |
| `scale` | `100` | 60 – 200 | Interface scale in percent | Use the **Big/Small** buttons |
| `stat_window` | `10` | 3 / 5 / 10 / 30 / 60 / 120 | **DPS window (seconds)** | **File only**, see 3.2 |
| `show_event_log` | `0` | 0 / 1 | Whether the event log panel is shown | Use the **Log** button |
| `click_through` | `0` | 0 / 1 | Mouse click-through | Use the **Thru** button or `Ctrl+Alt+T` |
| `win_x` / `win_y` | automatic | integers | Window position, `-1` = auto-centred | Drag the window |
| `ev_filter` | `0` | 0 / 1 / 2 / 3 | Log filter: All / Taken / Target / Stage/Boss | Click the log panel's filter buttons |
| `world_names` | empty | string | Extra world names to recognise, separated by `\|` or `,` | See [6. Advanced usage](#6-advanced-usage) |

Most entries can be changed with the interface buttons; **only `stat_window` requires editing
the file by hand**.

---

## 4. Keyboard shortcuts

| Shortcut | Effect |
|---|---|
| `Ctrl+Alt+T` | **Toggle mouse click-through** (global; no need to focus the window first) |
| `Ctrl+Alt+Q` | **Quit the program** (global) |

### About mouse click-through

After clicking the **Thru** button or pressing `Ctrl+Alt+T`, the HUD becomes **completely
transparent to the mouse**: clicks, drags and the wheel all land on the window below, so you
can play or use the desktop as usual while the HUD keeps showing its data.

**With it on, the window receives no mouse messages, so the buttons cannot be clicked** —
that is by design. The program permanently shows a gold hint in the title bar:

```
Click-through · Ctrl+Alt+T
```

Press `Ctrl+Alt+T` to turn click-through off. The state is saved to `config.ini` and reused
on the next start.

> When to use it: when the HUD covers something in the game you need to click, or covers
> other software — turning click-through on saves you from moving the window.

---

## 5. FAQ

### Q1. The panel is all zeros — is it broken?

Check the status bar first:

- `No VRChat log found` → the program has not read a log; go to
  [Q5](#q5-the-status-bar-shows-no-vrchat-log-found).
- `Waiting to enter Ecliptica` → you are not in the world; entering it will start things.
- `In Ecliptica, waiting for a run` → you are in the world but no fight has started; that is
  normal.
- `Run in progress` but still zeros → see [Q2](#q2-dps-stays-at-00).

There is one more case: **the HUD starts reading from the tail of the log**. If you start the
HUD after entering the world, it misses the earlier data, but it starts counting
automatically as soon as the first combat log line appears.

### Q2. DPS stays at 0.0?

In order of likelihood:

1. **You dealt no damage in the recent window.** DPS is a sliding-window value; no damage in
   the window means `0.0`. With a 10-second window, stopping for 10 seconds drops it to
   zero — that is correct behaviour, not a bug.
2. **You are not in any stage or fight yet.** Damage is only counted inside a stage or a boss
   fight.
3. **Check that the Damage row has a number.** If Damage has a value while DPS is 0, you
   simply have not dealt damage recently.

For an average over a longer period, increase `stat_window` (see
[3.2](#32-configini-only-the-dps-window)).

### Q3. Why does the Target column always show a dash?

**Target information comes from `ownership of X transferred to Y` lines in the log.** If the
current world's log has no such line at all, the program cannot display a target — that is not
a parsing problem, the data is not in the log and the program cannot infer it.

The official world emits it normally, and the Target column then reads `Target <player name> 00:12`.

**Showing `—` for the first few dozen seconds of a fight is normal**: bosses differ a lot in
how long they take to emit their first `ownership` line after the fight starts:

| Boss | Lag | Boss | Lag |
|---|---|---|---|
| Nan | 2 seconds | DarkMouth | 17 seconds |
| Gravetender | 3 seconds | Kakarot | 18 seconds |
| Steven | 8 seconds | JackedPumpkin | 20 seconds |
| Despair | 13 seconds | **FlyLord (Beelzebub)** | **57 seconds** |

FlyLord opens with INTRO SLAP and a swarm of `Fly` adds, so its target does not appear for
nearly a minute. During that time the program **deliberately shows `—`** instead of padding it
with another enemy's target — otherwise you would see something like the previous stage's
`LavaSac → so-and-so` and take it for FlyLord's target.

Outside a boss fight the Target column still reports the most recent switch together with the
object name (for example `Ice Squid → zukkiii 00:12`), because at that point there is no
"current boss" to speak of.

### Q4. Why aren't deaths counted in the stats?

**Death counts are no longer part of the statistics**, so the three-tier table has no
"Deaths" row and the replay summary no longer prints `deaths=`.

A death does exactly one thing: it writes a "You died" entry to the **event log**.

The reason it still needs a little handling: one death **floods the log with dozens of lines**
of `Local controller dead, switching off.` (34 lines within 8 seconds, measured), with
unrelated lines such as `ECLIPTICA saving SESSION ID` mixed in. The program requires that
"after the previous death, proof of being alive must appear again" (damage dealt / damage
taken / stage change / boss fight started / token spawned), plus a 3-second quiet period, so
that **one death writes only one log entry** — otherwise the log would be flooded with those
dozens of lines.

### Q5. The status bar shows "No VRChat log found"

The program looks for `output_log*.txt` in these places:

1. `C:\Users\<you>\AppData\LocalLow\VRChat\VRChat\` (taking the newest one)
2. If the previous step found nothing: next to the exe / the current directory / the exe's
   parent directory

Troubleshooting:

- Make sure VRChat has **been started at least once** (no start, no log file).
- Open `%USERPROFILE%\AppData\LocalLow\VRChat\VRChat\` and check whether an
  `output_log_xxxx-xx-xx_xx-xx-xx.txt` is there.
- Use `--log` to point at a file directly (see [6. Advanced usage](#6-advanced-usage)).

The program searches again every 2 seconds, so **starting the HUD before VRChat is fine** —
it will connect on its own.

### Q6. The status bar shows "Cannot open the file given to --log"

You used `--log` but the path is wrong. Note:

- **Wrap paths containing spaces in quotes.**
- `--log` is **exclusive**: when the file cannot be opened the program does **not** quietly go
  and read some other log, so that you never look at completely unrelated data. Fix the path
  or drop `--log`.

### Q7. I changed config.ini but nothing happened?

The two most common reasons:

1. **The HUD was still running when you edited it.** On exit the program writes the whole
   in-memory configuration back and overwrites your changes. **You must quit the HUD
   completely, then edit the file, then start it again.**
2. **You edited the wrong file.** Make sure you edited the `config.ini` the program actually
   uses (see [Where is config.ini?](#where-is-configini)). If there happens to be a
   `config.ini` next to the exe, the program prefers that one over the one in `%APPDATA%`.

After editing you can reopen the file to confirm your changes are still there.

### Q8. The interface is too big / too small

Use the **Big / Small** buttons (60% – 200%).

The program is also **DPI aware**: on a display scaled to 125% / 150% it scales up
proportionally instead of being stretched blurry by the system the way some old programs are.
So "it looks too big" may just be the system scaling itself.

### Q9. The buttons stopped responding!

You turned on **mouse click-through**. Check whether the title bar has the gold
`Click-through · Ctrl+Alt+T`. Press `Ctrl+Alt+T` to turn it off.

### Q10. The panel covers something in the game

Two options:

- **Turn on click-through** (the **Thru** button / `Ctrl+Alt+T`); clicks pass through and the
  panel keeps showing.
- **Move it**: drag the panel, or click **Small** a few times.

### Q11. I want to look back at the run I just did

Use the **◀ ▶ on the left** at the bottom to page through past runs and the **◀ ▶ in the
middle** for past boss fights. `Run 3/5` means you are looking at run 3 out of 5 recorded
runs.

The program keeps the last **8 runs**, up to **16 boss fights** and **12 stages** per run.

### Q12. Why can't I see my teammates' DPS?

**Because that data simply is not in the VRChat log.** The log only records damage **you**
dealt and damage you took.

It is not that the program left it out, it is a limitation of the data source — no tool that
only reads the log can do it. (Any tool that can must be injecting or altering packets, which
this project is not.)

### Q13. Does damage to the dummy during an intermission count?

**No.** The only thing to hit during an intermission (the status bar shows
`Run in progress · Intermission N`) is the practice dummy, and the log still spams
`Dealing 30 STRIKE/NON-STRIKE damage`; one measured intermission produced more than 20 lines.
That damage **counts towards no tier of the statistics** and does not appear in the event log
either.

Measured comparison: at the start and at the end of the same intermission, run damage is
`4,965` both times — completely unchanged.

### Q14. Are the stats reset automatically after a wipe?

**Yes.** After a wipe the game sends the whole team back to the starting lobby to begin again,
and once the program notices it will:

1. Close this run as **FAILED** and record it in the history;
2. **Immediately start a new run**, with the three tiers, the stage number and the kill count
   all reset to zero.

There are two criteria for a wipe and either one is enough:

| Criterion | Description |
|---|---|
| **An intermission starts while the boss is alive** | The normal flow is always `Boss X dead` first and `now in intermission` after; if the fight did not end with a kill, you lost |
| **The starting lobby appears again outside the first stage** | At least one stage has already been played and `Stage_Hall of Beginnings` shows up again, which means you were sent back to the start |

So after a wipe you will see the Run numbers reset to zero while the M in the bottom
`Run N/M` goes up by one (the failed run has been stored in the history). To look at the data
from before the wipe, page back with the **◀ on the left** at the bottom.

> Incidentally: the first stage of a normal run **is** the starting lobby, and that case is
> not misdetected as a wipe.

---

## 6. Advanced usage

### 6.1 First, learn to open a command line

The commands below all have to be typed in a **command-line window**. Pick whichever of the
three ways you like:

| Method | Steps | Notes |
|---|---|---|
| **Address bar** (most recommended) | Open the folder containing the exe → click the **address bar** at the top → type `cmd` → Enter | The command line's working directory is that folder, so relative paths are easiest to write |
| Run box | `Win+R` → type `cmd` → Enter, then `cd /d "D:\your path"` | Works anywhere |
| Right-click menu | **Shift + right-click** in the folder → "Open PowerShell window here" | Same capability, slightly different syntax in places |

Three tricks that save a lot of trouble:

- **Drag to fill in a path** — drag a file from Explorer **into the command-line window** and
  the path is filled in automatically, quotes and all.
- **Paths with spaces must be quoted** — `"D:\my hud\log.txt"`. Without quotes it is split
  into two arguments.
- **`Tab` completion** — type the first few characters and press `Tab` to complete the file
  name.

> ⚠️ **A relative path is relative to the command line's working directory, not to the exe.**
> When you open it with "address bar → cmd" the working directory is exactly the exe's folder,
> which is the least error-prone way. If in doubt, always write an **absolute path**.

### 6.2 Option reference

| Option | Effect | Opens the interface? |
|---|---|---|
| (nothing at all) | Locate the log automatically and follow it live from **near the end** | Yes |
| `--demo` | Demo mode with built-in simulated data | Yes |
| `--log <file>` | Replay the given log file (parse from the start and keep following) | Yes |
| `--tail` | Change the start position to "near the end" (backing up at most 64 KB) | Yes |
| `--from-start` | Change the start position to "read the whole file from the beginning" | Yes |
| `--help`, `-h`, `/?` | Pop up the help window, then exit | **No** |

> ✅ **Case-insensitive, single or double dash.**
> `--demo`, `--Demo`, `--DEMO`, `-demo` are completely equivalent; `--LOG "path"` is equally
> valid.
>
> ✅ **A mistyped option pops up help.** For example `--xyz`, or `--log` with the file name
> missing: the program shows the usage text instead of ignoring it — so you are not left
> puzzling over an interface that "looks normal but behaves wrong".

### 6.3 Every option in detail

#### `--demo` — demo mode

```bat
ecliptica-hud-c.exe --demo
```

It reads no log file at all and plays the built-in simulated events on a loop. Good for:

- Taking a first look at the interface after installing it
- **Screen recording / screenshots** — the picture is stable and reproducible, so a bad take
  can simply be re-run
- Verifying the effect of a configuration change

**How to be sure demo mode is really on:** look in two places — the status bar in the
bottom-left shows `Demo mode`, and the **bottom-right shows no log file name at all** (because
no file is being read).

> If something like `output_log_2026-xx-xx_xx-xx-xx.txt` appears in the bottom-right, demo
> mode **did not take effect** and the program is reading a real log. Check whether the option
> was written as something like `--Demo` (now supported), or was mangled by quotes or an IME.

#### `--log <file>` — replay a given log

```bat
ecliptica-hud-c.exe --log "D:\VRChatLogs\output_log_2026-09-24_18-20-39.txt"
```

It parses from the **beginning** of the file and then **keeps following** new content appended
to it. Good for reviewing a fight.

A few points:

- **A path is required.** Writing `--log` with nothing after it makes the program **pop up
  help** (that is a usage error).
- **Exclusive**: if the file cannot be opened the program does **not** quietly fall back to
  auto-discovery; it reports `Cannot open the file given to --log` and retries every
  2 seconds. This is deliberate — otherwise you would look at completely unrelated data and
  believe it was right.
- The file is opened **read-only**; it is never modified or locked.
- Paths are limited to 260 characters and longer ones are truncated.
- **Absolute paths are strongly recommended**; see the note in
  [6.1](#61-first-learn-to-open-a-command-line).

#### `--from-start` and `--tail` — controlling "where reading starts"

These decide where reading begins when the log file is first opened.

| Command | Effect |
|---|---|
| `ecliptica-hud-c.exe` | Start **near the end** and only look at newly produced content (the default; good for watching while playing) |
| `ecliptica-hud-c.exe --from-start` | Read the whole log from the **beginning**, then keep following |

##### How near is "near the end", exactly

The program **backs up at most 64 KB** and then reads from the next line break onwards:

| Log size | Range actually read |
|---|---|
| **Smaller than 64 KB** | Almost the **whole file** is read (only the first line is skipped) |
| **Larger than 64 KB** | Only the **last 64 KB** is read; anything earlier is skipped |

This "warm-up" is intentional: even if you start the HUD halfway through a fight, the last
64 KB is enough to **rebuild** the current stage, the current boss and the accumulated damage,
instead of starting from a blank slate.

##### When to use `--from-start`

The typical case: **you only remembered to start the HUD after getting into the game** and
want the part of this run you already played to be included too.

> **A note on large logs**: a 5 MB log has more than 50,000 lines and the program reads it
> quickly in a few passes (about one or two seconds). The panel numbers fly around during that
> time, which is normal; they settle once it has caught up.

##### Note: `--tail` applies to `--log` as well

It is not "for auto-discovery only" — written **after** `--log` it changes that replay to
"read only the last 64 KB" too. This is the easiest trap to fall into; see
[6.4](#64-combining-options-and-the-ordering-trap) for details.

#### `--help` / `-h` / `/?` — see the usage

```bat
ecliptica-hud-c.exe --help
```

It pops up a help window and exits as soon as you click OK; it **does not open the HUD**.

**A mistyped option pops up this same help automatically**, for example:

```bat
ecliptica-hud-c.exe --xyz          :: unknown option
ecliptica-hud-c.exe --log          :: --log with the path forgotten
```

This is intentional: such errors used to be **silently ignored**, the program would start
normally and read the real log, and nothing on the interface showed that anything was wrong —
one measured user typed `--Demo` instead of `--demo` and concluded that "demo mode is broken".

### 6.4 Combining options and the ordering trap

| Command line | What actually happens |
|---|---|
| `ecliptica-hud-c.exe` | Follow the newest log live (default) |
| `ecliptica-hud-c.exe --demo` | Demo mode |
| `ecliptica-hud-c.exe --from-start` | Follow live, but first read the current log from the beginning |
| `ecliptica-hud-c.exe --log "D:\log.txt"` | **Replay the file in full from the start** ✅ |
| `ecliptica-hud-c.exe --tail --log "D:\log.txt"` | **Replay the file in full from the start** ✅ |
| `ecliptica-hud-c.exe --log "D:\log.txt" --tail` | ⚠️ Read only the **last 64 KB** of the file, losing most of the history |
| `ecliptica-hud-c.exe --demo --log "D:\log.txt"` | Demo mode; `--log` is ignored |

**The rule: whichever of `--log` and `--tail` is written last wins.**

`--log` by itself implies "start from the beginning", and a `--tail` written after it changes
that behaviour back to "near the end".

> ✅ **To replay a file, put `--log` last, or simply leave out `--tail`.**

##### How big the difference is in practice

Comparing against a **5 MB real log** (53834 lines):

| Command | Runs detected | Current run damage | Stage |
|---|---|---|---|
| `--log BIG` | 5 runs | 77,408 | Stage 6 · VRChat Hub |
| `--log BIG --tail` | 2 runs | 12,610 | Waiting |

That is nearly **6×** apart, and the stage, the kill count and the token count are all wrong
as well.

> Conversely: if the log is **smaller than 64 KB** (a freshly started session, say), the two
> forms look almost identical — because "near the end" effectively means reading from the
> start. **Do not conclude that the order does not matter**; the trap springs once the log
> grows.

##### Other things to watch out for

- **An unknown option pops up help** rather than being silently ignored.
  Note that **dragging a log file onto the exe icon still does nothing** — the argument
  produced by a drop is a file path, not an option starting with `-`/`--`, and the program
  does not treat it as `--log`. To replay by dragging, use the `.bat` approach in
  [6.5](#65-shortcuts-and-batch-files).
- Options are **case-insensitive**; `--demo` / `--Demo` / `-demo` all work.
- Only `--log` / `--tail` / `--from-start`, the three options related to "start position",
  override each other; the others can go in any order.

### 6.5 Shortcuts and batch files

#### A desktop shortcut for demo mode

1. Right-click `ecliptica-hud-c.exe` → **Send to → Desktop (create shortcut)**
2. Right-click the shortcut → **Properties**
3. Change **Target** to (note the single space after the exe path):

   ```
   "D:\your path\ecliptica-hud-c.exe" --demo
   ```

4. OK. From then on, double-clicking it goes straight into demo mode.

#### A "drag to replay" batch file (recommended)

Create `回放日志.bat` in the same folder as the exe, containing:

```bat
@echo off
"%~dp0ecliptica-hud-c.exe" --log "%~1"
```

Usage: **drag a log file onto this .bat** and it replays it.

- `%~dp0` = the directory the .bat itself lives in, so the exe path is always right no matter
  what the working directory is;
- `%~1` = the path of the dropped file (quoted automatically, so spaces are no problem).

#### Always replaying one specific log

```bat
@echo off
start "" "%~dp0ecliptica-hud-c.exe" --log "D:\VRChatLogs\output_log_2026-09-24_18-20-39.txt"
```

### 6.6 Bundled helper tools (build them yourself)

`test_core.exe` and `preview.exe` **are not shipped alongside the released exe**; build them
from source:

```bat
mingw32-make test      :: build and run all logic tests
mingw32-make preview   :: build the off-screen preview tool
```

> With the English / Japanese builds the tools carry the same language suffix as the
> executable: `test_core-en.exe` / `preview-en.exe`, and `test_core-ja.exe` /
> `preview-ja.exe`.

#### `test_core.exe` — see what the log actually parses into

```bat
test_core.exe                               :: no arguments = run all logic tests
test_core.exe "D:\VRChatLogs\output_log.txt" :: with an argument = replay and print a statistics summary
```

The output looks like this:

```
lines=1552  events=415  accepted=375
ownership: parse 0 -> keep 0 (per-object, target really changed)
runs=1  in_run=0  stage_no=1  targets_total=0
all runs: kills=1  targets=0
run: dmg=3188 taken=453 hits=46 tokens=1 fights=1 stages=1
```

How to read it:

| What you see | Meaning |
|---|---|
| `events=0` | There are **no recognisable events** in this log — the wrong file, or the log format changed |
| `lines` large but `events` small | Normal; the vast majority of a log is unrelated system messages |
| `ownership: parse 0` | This log has no target information, and the HUD's Target column shows `—` (see [Q3](#q3-why-does-the-target-column-always-show-a-dash)) |
| `runs=` | How many runs were detected |
| `kills=` / `targets=` | The overall kill count and target-switch count |

When working out "why does the panel have no data", this tool is far more effective than
staring at the HUD and guessing.

#### `preview.exe` — render an interface image without launching the game

```
preview.exe  [log] [scale%] [log panel 0/1] [output.bmp] [replay only the first N lines]
```

| Position | Default | Description |
|---|---|---|
| log | built-in sample | Passing `-` or nothing uses the built-in sample data |
| scale% | `100` | 50 – 300 allowed |
| log panel | `1` | `1` = with the event log panel, `0` = without |
| output file | `hud_preview.bmp` | A 24-bit BMP |
| replay only the first N lines | `0` | `0` = everything; a line number renders a "halfway through the fight" state |

Examples:

```bat
preview.exe
:: built-in data / 100% / with log panel → hud_preview.bmp

preview.exe "D:\VRChatLogs\output_log.txt" 150 1 out.bmp 1970
:: 150% scale, replay only up to line 1970, export out.bmp

preview.exe - 60 0 small.bmp
:: built-in data / 60% / without log panel → small.bmp
```

It is good for making tutorial images, and for checking the layout in a **headless or remote
environment**.

> Note: `preview.exe` only renders an image; it does **not** pop up a window and does not read
> `config.ini`.

### 6.7 Teaching the program about other world names

Out of the box the program only recognises the official world name. If you play another world
with **the same log format**, register its room name in `config.ini`:

```ini
world_names=WorldNameA|WorldNameB
```

Separated by `|` or `,`, with **substring matching** (case-insensitive).

> Even with nothing registered at all, the program starts counting automatically as soon as an
> `ECLIPTICA …` event appears in the log — it just does not start a run the moment you enter
> the room, but waits for the first combat log line.

---

## 7. Uninstalling

1. Close the program and delete `ecliptica-hud-c.exe`.
2. Delete the configuration directory (optional; leaving it does no harm):

   ```
   %APPDATA%\EclipticaHUD-C
   ```

3. If a `config.ini` was created next to the exe, delete that as well.

The program does not write to the registry, install services or touch system files, so
deleting it is a clean uninstall.

---

## Appendix: one-line cheat sheet

| I want to… | How |
|---|---|
| Change the DPS window | Quit the program → edit `stat_window` in `config.ini` → restart |
| Change opacity / scale / always-on-top | Click the top buttons; effective immediately |
| Let mouse clicks pass through the HUD | Click **Thru** or press `Ctrl+Alt+T`; press again to restore |
| Move it | Drag the panel |
| See only damage-taken events | Click **Taken** in the log panel |
| Look back at the last run | ◀ on the left at the bottom |
| See the effect without entering the game | `--demo` |
| Review a log | `--log "path"` (put it last, no `--tail`) |
| Catch up on the part of this run already played | `--from-start` |
| Quit | `Ctrl+Alt+Q` or click `✕` |
