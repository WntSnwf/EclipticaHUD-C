# Ecliptica HUD（C 语言实现）

![Platform](https://img.shields.io/badge/platform-Windows%2010%2F11%20x64-0078D6)
![Language](https://img.shields.io/badge/language-C11-555555)
![Dependencies](https://img.shields.io/badge/dependencies-none-brightgreen)
![License](https://img.shields.io/badge/license-MIT-green)

VRChat 世界 **Ecliptica** 的战斗统计覆盖层：跟随 VRChat 日志，实时解析战斗事件，
以半透明置顶面板显示**阶段 / 本局 / 本场 Boss 战**三级统计、Boss 目标、DPS、承伤
与事件日志。

全部数据来自 VRChat 自己写的 `output_log`：**不注入、不修改游戏、不需要 OSC**。
纯 C + Win32/GDI 实现，只链接 `user32` / `gdi32`，无任何第三方依赖。

![界面预览](hud_preview.png)

---

## 目录

- [特性](#特性)
- [快速开始](#快速开始)
- [命令行参数](#命令行参数)
- [界面操作](#界面操作)
- [配置文件](#配置文件)
- [日志解析规则](#日志解析规则)
- [世界识别](#世界识别)
- [工作原理](#工作原理)
- [目录结构](#目录结构)
- [测试与验证](#测试与验证)
- [兼容性与限制](#兼容性与限制)
- [致谢](#致谢)
- [许可证](#许可证)

> 📖 **只想上手使用？** 请看 [使用说明.md](使用说明.md) —— 逐块讲解界面、
> 每项设置怎么改（含 **DPS 统计时间的调整方式**）、常见问题排查。
> 本 README 偏项目介绍与开发。

---

## 特性

### 三级统计

| 层级 | 含义 |
|---|---|
| **阶段 Stage** | 当前关卡（`now in stage:` 之后累计）|
| **本局 Run** | 一次进入 Ecliptica 世界到离开 |
| **本场 Fight** | 一次 Boss 战（同一 Boss 的 `Phase2/Phase3` 视为续战并合并）|

每级都给出：伤害、DPS、承伤、受击次数、最大受击、平均受击、承伤/秒、死亡、印记。
DPS 使用可切换的滑动窗口：**3 / 5 / 10 / 30 / 60 / 120 秒**。

多形态 Boss（例如 `JimBringer → JimBringerPhase2 → JimBringerPhase3`）有两个坑，
程序都做了处理：

- **击杀行会迟到。** 真实日志里三阶段 19:12:21 就开战了，`Boss JimBringerPhase2 dead`
  直到 19:12:22 才出现。若只比较基础名，这一行会把刚开始的三阶段当场结束掉，
  界面就变成「当前没有 Boss 战」。程序要求**对象名完全一致**或**形态号一致**才结算。
- **各形态的对象名不同。** 一阶段叫 `JimBringer`、二阶段叫 `JimBringerPhase2`，
  基础名都是同一个。目标查询**先精确匹配对象名**，再退回基础名（并取最近一次变化的那条），
  否则二阶段会一直显示一阶段遗留的目标。

### 目标（仇恨）追踪

解析 `ownership of X transferred to Y`，**覆盖所有敌方单位**（Boss、杂兵、召唤物、
道具）。每个对象各自记住上一次的归属，**只有该对象的目标玩家真的换了才计一次**，
因此同一条 `ownership` 反复上报不会重复计数（`(Clone)` 后缀会归并到同一对象，
`Phase2/Phase3` 则视为各自独立的对象）。

- 本局汇总显示累计切换次数
- Boss 行优先显示当前 Boss 的目标玩家与持续时间；取不到时回落到最近一次切换，
  并带上对象名（`Ice Squid → zukkiii 00:12`）
- 事件日志记录 `目标切换 <对象> → <玩家>`

> **注意：目标追踪依赖日志里是否出现 `ownership` 行。**
> 官方世界会输出；若某个世界不输出，「目标」显示 `—`、切换次数恒为 0。
> 这是日志里没有这份数据，不是解析或去重的问题——
> 详见 [世界识别](#世界识别)。

### 其他

- **伤害来源分布**：按 `攻击者 · 招式` 聚合本场 / 本阶段 / 本局的承伤与次数
- **事件日志**：512 条环形缓冲，按类型着色，四个过滤器（全部 / 承伤 / 目标 / 阶段·Boss），
  支持点击切换、右键循环、▲▼ 翻看
- **历史回看**：底部箭头翻看历史局与历史 Boss 战，右侧徽标区分「实时 / 历史」
- **覆盖层交互**：拖动移动、7 个顶部按钮（含**鼠标穿透**）、关闭按钮、悬停提示、
  `Ctrl+Alt+Q` 退出、`Ctrl+Alt+T` 切换鼠标穿透
- **高 DPI 感知**：任意缩放下版式一致，不会因系统位图拉伸而发虚
- **演示模式**：`--demo` 内置模拟日志，无需 VRChat 即可查看完整界面

---

## 快速开始

### 环境要求

- Windows 10 / 11（x64）
- **二选一**：
  - [MinGW-w64](https://www.mingw-w64.org/)（gcc 8 及以上）
  - Visual Studio 2015 及以上（MSVC）

### 构建

**MinGW-w64**

```bat
mingw32-make
```

**MSVC**（在 `x64 Native Tools Command Prompt for VS 2022` 中）

```bat
build.bat
```

产物为 `ecliptica-hud-c.exe`（GUI 子系统，无控制台窗口）。

### 运行

```bat
ecliptica-hud-c.exe
```

直接双击即可：程序会去 `%USERPROFILE%\AppData\LocalLow\VRChat\VRChat\` 找**最新写入**
的 `output_log*.txt` 并开始跟随。想先看界面效果：

```bat
ecliptica-hud-c.exe --demo
```

详细操作（界面每一块的含义、每项设置怎么改、常见问题排查）见 **[使用说明.md](使用说明.md)**。

---

## 命令行参数

| 参数 | 说明 |
|---|---|
| （无） | 自动定位 VRChat 日志，从**末尾附近**开始跟随（最多回退 64 KB 作预热；小于 64 KB 的文件几乎整份都会读）|
| `--demo` | 演示模式，内置按真实日志格式生成的模拟事件 |
| `--log <文件>` | 回放指定日志**并继续跟随新增内容**。该参数是独占的：文件打不开时不会退回自动定位，而是提示「打不开 --log 指定的文件」并每 2 秒重试 |
| `--from-start` | 从头读完整份日志（默认只从末尾附近开始）|
| `--tail` | 把起始位置改回「末尾附近」（默认行为）。⚠️ 写在 `--log` **后面**会让回放只读该文件最后 64 KB |
| `--help`、`-h`、`/?` | 弹出帮助 |

> **参数大小写不敏感**，且 `--name` 与 `-name` 等价（`--demo` / `--Demo` / `-demo` 都能用）。
> 认不出来的参数（例如 `--xyz`、漏了文件名的 `--log`）会**弹出帮助**而不是被静默忽略。
> 详细用法与实测对比见 [使用说明.md](使用说明.md#6-进阶用法)。

### 日志定位顺序

1. `--log` 指定的文件
2. **VRChat 日志目录** `%USERPROFILE%\AppData\LocalLow\VRChat\VRChat\` 下
   `output_log*.txt` 中**最后写入时间最新**的一个。
   现行版本 VRChat 只写带时间戳的 `output_log_YYYY-MM-DD_HH-MM-SS.txt`（每次会话一个文件），
   旧版本写 `output_log.txt`，同一个通配即可覆盖。
   `USERPROFILE` 不可用时回退到 `%LOCALAPPDATA%\..\LocalLow\...`。
3. 仅当第 2 步一个都没找到时，才退回 exe 同目录 / 当前目录 / exe 上级目录中最新的
   `output_log*.txt`（方便把 exe 丢到日志旁边离线回放）

VRChat 开新会话时（目录里出现更新的文件）会自动切换跟随，并把当前局收尾。

---

## 界面操作

| 位置 | 操作 |
|---|---|
| 面板空白处 | 按住拖动移动窗口 |
| 顶部按钮 | 置顶 / 放大 / 缩小 / 变浓 / 变淡 / **穿透** / 日志 |
| 右上 ✕ | 关闭 |
| 事件日志标题栏 | 点击「全部 / 承伤 / 目标 / 阶段·Boss」切换过滤器；▲▼ 翻看 |
| 面板任意处右键 | 循环切换事件日志过滤器 |
| 底部箭头 | 翻看历史局（◀ ▶ 左侧）与历史 Boss 战（◀ ▶ 中间）|
| `Ctrl+Alt+T` | 全局切换**鼠标穿透**（任意窗口焦点下都有效）|
| `Ctrl+Alt+Q` | 全局退出（任意窗口焦点下都有效）|

> 覆盖层刻意保留 `WS_EX_NOACTIVATE`，**不会抢 VRChat 的焦点**，所以退出请用
> `Ctrl+Alt+Q` 或点 ✕；`Esc` 只在窗口恰好获得焦点时生效。

### 鼠标穿透

点顶部 **穿透** 按钮（或按 `Ctrl+Alt+T`）后，HUD 变得**对鼠标完全透明**：
点击、拖动、滚轮全部落到它下面的窗口上，可以正常操作 VRChat 或桌面，
HUD 仍然照常显示。

实现是给分层窗口加上 `WS_EX_TRANSPARENT`，并让 `WM_NCHITTEST` 返回
`HTTRANSPARENT` 双保险。

> ⚠️ 穿透开启后窗口**收不到任何鼠标消息**，所以没法再点按钮关掉它。
> 程序在标题栏常驻显示 `鼠标穿透中 · Ctrl+Alt+T 恢复`，
> 按 `Ctrl+Alt+T` 即可恢复。该状态会记进 `config.ini`，下次启动沿用。

---

## 配置文件

配置文件为 UTF-8 的 `config.ini`，退出时写回。它的位置按下面的顺序决定：

1. **便携模式** —— exe 同目录已存在**可写**的 `config.ini` 时直接用它。
   想让配置跟着程序走（U 盘、绿色版），把 `config.ini` 放在 exe 旁边即可。
2. **按用户（默认）** —— `%APPDATA%\EclipticaHUD-C\config.ini`
   （取不到 `%APPDATA%` 时退回 `%LOCALAPPDATA%`），目录会自动创建。

> **为什么不默认放在 exe 旁边**：exe 若装在 `C:\Program Files` 这类目录，普通用户
> 根本写不进去（x64 进程没有 UAC 虚拟化），设置会静默丢失；而放在共享可写目录时，
> 同一台电脑上的**不同 Windows 用户会互相覆盖**窗口位置等设置。
>
> 目录名带 `-C` 是为了和上游 Rust 版的 `%APPDATA%\EclipticaHUD\`
> （存放 `pos.txt` / `scale.txt` / `top.txt` / `logpos.txt`）分开，
> 彻底避免两份程序将来撞文件名。

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

| 键 | 取值 | 说明 |
|---|---|---|
| `always_on_top` | 0 / 1 | 窗口置顶 |
| `alpha` | 40 – 255 | 整体不透明度 |
| `scale` | 60 – 200 | 界面缩放百分比 |
| `stat_window` | 3 / 5 / 10 / 30 / 60 / 120 | DPS 统计窗口（秒）|
| `show_event_log` | 0 / 1 | 是否显示事件日志面板 |
| `click_through` | 0 / 1 | 鼠标穿透（等价于点顶部「穿透」按钮）|
| `win_x` / `win_y` | 整数 | 窗口位置，`-1` 表示自动居中偏上 |
| `ev_filter` | 0 – 3 | 事件日志过滤器（全部 / 承伤 / 目标 / 阶段·Boss）|
| `world_names` | 字符串 | 追加的 Ecliptica 系世界名，`\|` 或 `,` 分隔 |

> 顶部按钮里没有「DPS 统计窗口」了，需要改 `stat_window` 请直接编辑 `config.ini`
> （退出时会写回，所以先关掉 HUD 再改）。

---

## 日志解析规则

解析器对 VRChat 日志的**消息体**做前缀匹配（VRChat 日志为无 BOM 的 UTF-8，
含中文世界名与中日文玩家名）。所有句式均取自真实 `output_log`：

| 事件 | 日志句式 |
|---|---|
| 进入世界 | `[Behaviour] Entering Room: <世界名>` |
| 离开世界 | `[Behaviour] OnLeftRoom` / `VRCApplication: HandleApplicationQuit` |
| 阶段开始 | `ECLIPTICA - now in stage: Stage_ProtoColony on phase: 0.1228879 as class: Nekomancer` |
| 间歇期 | `ECLIPTICA - now in intermission` |
| 大厅 | `ECLIPTICA - now in lobby` |
| Boss 战开始 | `ECLIPTICA - now fighting boss: Amaziah(Clone) on phase: 0.4321299` |
| Boss 击杀 | `Boss FlyLord dead, personal damage dealt:` |
| 击杀结算 | `STRIKE DMG: 4793` / `NON-STRIKE DMG: 615` |
| 造成伤害 | `Dealing 74 STRIKE damage` / `Dealing 38 NON-STRIKE damage` |
| 受到伤害 | `damage has been taken: 43, from source: (Peltapod) attack_Slam` |
| 目标（仇恨）切换 | `ownership of Amaziah transferred to OtherPlayer` |
| 死亡 | `Local controller dead, switching off.` |
| 印记 | `spawn token, True, 55` + `ECLIPTICA saving SESSION ID 11508` |
| 敌人工池 | `Initializing Enemy POOL ID17 as ENEMY ID 87` / `Retiring Enemy POOL ID19` |

### 三个容易踩的坑

**死亡连刷。** 一次死亡会在日志里连刷几十行 `Local controller dead, switching off.`
（实测 8 秒内 34 行），中间还会混进 `ECLIPTICA saving SESSION ID` 之类的无关行。
程序要求「上次死亡之后必须再次出现活着的证据（造成伤害 / 受到伤害 / 换阶段 / 开 Boss 战 /
出现印记）」，并叠加 3 秒静默期，因此一次死亡只计一次。

**多形态 Boss 的击杀行会迟到。** 实测 `JimBringerPhase3` 在 19:12:21 开战，
`Boss JimBringerPhase2 dead` 直到 19:12:22 才出现。程序结算击杀时要求对象名完全一致
或形态号一致，否则这一行会把刚开始的三阶段误判为结束（界面回到「当前没有 Boss 战」）。
同理，查目标时先精确匹配对象名——`JimBringer` / `JimBringerPhase2` / `JimBringerPhase3`
是三个不同对象，否则二阶段会显示一阶段遗留的目标。

**名称映射。** 内置参考实现的显示名映射，例如
Boss：`FlyLord → Beelzebub`、`AntKing → Khepri`、`Obisidus → Irides`、`ManalyteAncient → Abaddon`；
阶段：`ProtoColony → Proto Colony`、`VRCHub → VRChat Hub`；
进度阶段：`0.43 → Antumbral`；
伤害来源：`(Khepri) attack_Claws2 → Khepri · Claws 2`、`NukeHitbox (BIG) → Nuke (big)`。

---

## 世界识别

官方世界名是 `Ecliptica …`。程序**不靠房间名硬编码**，两层保证：

1. **世界别名表** —— 内置官方名 `ecliptica`；如需按房间名识别其它同系世界，
   可在 `config.ini` 的 `world_names` 里自行登记（`|` 或 `,` 分隔），命中即立刻开局。
2. **惰性开局** —— 只要出现任意 `ECLIPTICA …` 系战斗日志就自动补开一局。
   因此即使房间名不在别名表里，甚至 HUD 从日志尾部才开始跟随、完全没看到房间行，
   也能正常工作。

### 目标追踪的可用性

**目标（仇恨）追踪依赖日志里是否出现 `ownership of X transferred to Y`。**
官方世界会输出该行；若某个世界不输出它，「目标」会显示 `—`、切换次数恒为 0，
其余统计仍然完全正常。程序无法凭空推断日志里不存在的数据。

---

## 工作原理

```
VRChat output_log.txt
        │  vlog.c   定位 + 增量跟随（日志轮换自动重开）
        ▼
     parse.c      日志行 → 战斗事件（无状态前缀匹配）
        ▼
     stats.c      阶段 / 本局 / 本场三级模型 + 滑动 DPS 窗口 + 历史
        │            ├─ evlog.c   事件日志环形缓冲
        │            └─ evtext.c  事件 → 可读文本
        ▼  stats_view()  汇总成只读快照
     hud.c        版式计算 + GDI 双缓冲绘制
        ▼
     overlay.c    分层透明窗口 / 消息循环 / 交互
```

### 渲染与缩放

内存 DC 使用 `MM_ANISOTROPIC` 映射，把 **460×620 的逻辑坐标**等比放大到窗口像素，
再乘系统 DPI 系数。因此字体、间距、按钮在 60%–200% 任意缩放下都是**同一套版式**，
不会出现文字错位；`BitBlt` 前把映射复位为 `MM_TEXT`，避免源矩形被二次缩放。

### 版式

各区块矩形全部由 `hud_layout()` 一次算出，**绘制与命中测试共用同一份矩形**，
从结构上杜绝「面板互相压盖」：

```
标题行(26) → 按钮行(27) → 阶段/进度(42) → 本场 Boss(22)
→ 三级统计表(表头 18 + 9×19) → 伤害来源(自适应) → [事件日志(可选 142)]
→ 历史翻页条(26) → 底部状态栏(22)
```

事件日志关闭时释放的高度会自动分配给「伤害来源」列表（最多 14 行）。

---

## 目录结构

```
src/
├── main.c     入口：命令行解析、配置加载/保存、世界别名注册
├── overlay.c  覆盖层窗口：分层透明、置顶、DPI、消息循环、日志轮询接线
├── hud.c      HUD 版式计算 + GDI 双缓冲绘制 + 命中测试
├── cfg.c      config.ini 读写（UTF-8）
├── vlog.c     日志定位与增量跟随（VRChat 目录优先、日志轮换重开）
├── parse.c    日志行 → 战斗事件
├── names.c    Boss/阶段/进度阶段名称映射、来源美化、世界名识别
├── stats.c    统计模型：三级统计 + 滑动 DPS 窗口 + 历史 + 目标追踪
├── evlog.c    事件日志环形缓冲
├── evtext.c   事件 → 事件日志文本（overlay 与 preview 共用）
├── format.c   数值/时间格式化（不依赖 Windows，可单元测试）
├── zhtext.h   中文界面文案
└── compat.h   编译器兼容垫片（MSVC / MinGW）
test_core.c    逻辑测试 + 日志回放摘要工具
preview.c      离屏界面预览工具
使用说明.md     面向使用者的操作手册（界面详解 / 设置改法 / FAQ）
testdata/      回归夹具（alt_world.log：房间名与官方不同的一种日志样本）
```

---

## 测试与验证

### 单元测试

```bat
mingw32-make test
```

覆盖解析器、名称映射、世界识别、格式化、三级统计、DPS 窗口、阶段切换、Boss 续战、
目标追踪、死亡连刷、跨世界与事件日志，共 **160 项检查**。

### 日志回放摘要

```bat
test_core.exe <日志文件>
```

打印事件数、目标切换采纳数、各局统计，便于用真实日志校准：

```
lines=1552  events=415  accepted=375
ownership: parse 0 -> keep 0 (per-object, target really changed)
runs=1  in_run=0  stage_no=1  targets_total=0
all runs: deaths=1  kills=1  targets=0
```

### 离屏界面预览

```bat
mingw32-make preview
preview.exe <日志> <缩放%> <是否带日志面板 0/1> <输出.bmp> [只回放前 N 行]
```

把日志回放成统计状态再渲染成图片，**没有显示器也能检查排版**，改界面时可直接对比。

### 已验证项目

| 项目 | 结果 |
|---|---|
| 构建 | MinGW-w64 8.1.0，`-Wall -Wextra` **零警告零错误** |
| 单元测试 | **180 项检查全部通过** |
| 真实日志回放 | 单份 53834 行日志解析出 **9359 个事件** |
| 自动定位 | 无参数启动即跟随 VRChat 目录下 mtime 最新的 `output_log_*.txt` |
| 会话轮换 | 运行中新建更新的日志文件后自动切换跟随 |
| 死亡去抖 | 8 秒内 34 行死亡日志 → 计为 **1 次** |
| 目标追踪 | 单份日志 1544 条 `ownership` → 逐对象去重后采纳 **1342** 条 |
| 世界识别 | 房间名与官方不同时不误判；登记 `world_names` 后进房即开局，未登记则靠 `ECLIPTICA` 日志惰性开局 |
| 界面 | 100% / 150% 缩放离屏渲染版式一致；DPI 感知下实机显示正常 |
| 交互 | 过滤器按钮点击切换、点击按钮不误触发拖动、`WM_CLOSE` 优雅退出并写回配置 |
| 鼠标穿透 | 实机验证：点「穿透」后 `GWL_EXSTYLE` 置上 `WS_EX_TRANSPARENT`、`WM_NCHITTEST` 返回 `HTTRANSPARENT`、`WindowFromPoint` 在窗口中心命中**下层窗口**；按 `Ctrl+Alt+T` 全部恢复，窗口位置不受影响 |
| 多用户 | 配置路径解析经四种场景验证：无 exe 旁配置 → 按用户目录；exe 旁可写配置 → 便携模式；exe 旁只读配置（模拟 Program Files）→ 自动回落到按用户目录；存读往返一致 |

---

## 兼容性与限制

### 多用户 / 多账户

程序内部**没有任何硬编码的用户路径**，所有用户相关位置都由环境变量解析，
因此同一台电脑上的不同 Windows 用户**互不干扰**：

| 数据 | 位置 | 是否按用户隔离 |
|---|---|---|
| VRChat 日志 | `%USERPROFILE%\AppData\LocalLow\VRChat\VRChat\` | ✅ 运行时由 `USERPROFILE` 解析 |
| 本程序配置（窗口位置 / 缩放 / 透明度 / 过滤器…） | `%APPDATA%\EclipticaHUD-C\config.ini` | ✅ 按用户 |
| 界面 DPI / 屏幕尺寸 | 运行时查询 | ✅ 按会话 |

- 不同用户（含"快速用户切换"同时登录）各自跟随各自的日志、各自保存各自的位置。
- 便携模式下（`config.ini` 放在 exe 旁边）配置是共享的——这是有意为之的绿色版行为；
  若要多人各用各的，把 exe 旁边的 `config.ini` 删掉即可回到按用户模式。
- 同一用户开两个实例：两个窗口会重叠，第二个实例的 `Ctrl+Alt+Q` 注册会失败
  （不影响点 ✕ 关闭），退出时后关闭的那个写入配置。

### 其它

- 仅支持 **Windows**（Win32 + GDI），未做跨平台适配。
- 日志只记录**你自己**造成的伤害，因此无法显示其他玩家的 DPS。
- **目标（仇恨）追踪依赖日志输出 `ownership` 行**；没有该行时「目标」显示 `—`。
  日志里没有这份数据，程序无法凭空推断。
- 依赖 VRChat 日志格式；世界更新若改变输出句式，需同步调整 `src/parse.c`。
- 未实现 SteamVR 覆盖层与 Discord Rich Presence。
- 覆盖层为不抢焦点的工具窗口，退出快捷键固定为 `Ctrl+Alt+Q`。

---

## 致谢

- **[EclipticaHUD](https://github.com/RealWhyKnot/EclipticaHUD)** —— Rust 参考实现。
  本项目的日志格式知识、Boss / 阶段 / 进度阶段名称映射均以其为准，特此致谢。
- Ecliptica 世界作者与社区玩家。

---

## 许可证

[MIT](LICENSE)
