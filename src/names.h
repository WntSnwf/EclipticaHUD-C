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

/* ---- Ecliptica 系世界识别 ----
 * 官方世界名是 "Ecliptica …"，但存在非官方改版（例如 "男生女生向前冲"）：
 * 它们复用同一套 Udon 脚本，战斗日志的 "ECLIPTICA …" 前缀完全一致，
 * 只有房间名不同。内置别名 "ecliptica" 与 "男生女生向前冲"，
 * 可用 names_set_world_aliases() 追加（config.ini 的 world_names，用 | 或 , 分隔）。 */
void names_set_world_aliases(const char* extra);
bool names_is_ecl_world(const char* room_name);

#endif
