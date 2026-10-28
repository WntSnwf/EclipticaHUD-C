/* names.h - 内部名 -> 显示名（Boss / 阶段 / 进度阶段 / 伤害来源美化）*/
#ifndef NAMES_H
#define NAMES_H

#include <stdbool.h>

/* Boss 内部名 -> 显示名（未收录则原样返回） */
const char* boss_display(const char* internal);

/* Boss 完整显示名：先做基础名映射，再按需附上 (P2) 之类的形态后缀 */
void boss_label(const char* internal, char* out, int cap);

/* 阶段内部名 -> 显示名（未收录则原样返回） */
const char* stage_display(const char* internal);

/* 进度 0..1 -> 阶段名（Primal / Penumbral / Antumbral / Umbral / Eclipse / Eye of the Eclipse）*/
const char* phase_display(double progress);

/* "attack_Claws2" / "(Khepri) attack_Claws2" -> 可读文本，写入 out */
void source_display(const char* source, char* who, int who_cap, char* attack, int atk_cap);

/* 规范化 Boss 基础名：去掉 "(Clone)" 与 Phase 形态后缀
 *   "Amaziah(Clone)" -> "Amaziah"，"YukiPhase2" -> "Yuki" */
void boss_base(const char* name, char* out, int cap);

/* 阶段序号： "Yuki" -> 1, "YukiPhase2" -> 2 */
int boss_phase_no(const char* name);

/* 是否为玩家召唤物（Neko1 / Neko2 …），用于区分敌人与召唤物 */
int is_player_summon(const char* name);

/* ---- 过长的玩家名 ----
 * 按 UTF-8 字符数统计（不是字节数）。
 * names_shorten()：字符数 <= 10 原样写入；否则只留前 5 个字符再加一个 "…"。
 * 必须按字符边界截：日志里出现过 14 个日文/中文字符的玩家名（42 字节），
 * 而 Event.cls 只有 32 字节，按字节硬截会切在多字节字符中间，产生非法
 * UTF-8 —— 目标栏和事件日志会显示成乱码方块，长度也失控。 */
int  names_utf8_len(const char* s);
void names_shorten(const char* src, char* dst, int cap);

/* 额外的 Ecliptica 系世界名别名 */

/* ---- Ecliptica 系世界识别 ----
 * 内置别名只有官方世界名 "ecliptica"。若要按房间名识别其它同系世界，
 * 可用 names_set_world_aliases() 登记（对应 config.ini 的 world_names，
 * 用 | 或 , 分隔）；即使完全没登记，只要日志里出现 ECLIPTICA 系事件，
 * 统计层也会惰性开局。 */
void names_set_world_aliases(const char* extra);
bool names_is_ecl_world(const char* room_name);

#endif
