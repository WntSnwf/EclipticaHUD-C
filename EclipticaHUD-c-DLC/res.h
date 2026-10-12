/* res.h - 弱点 / 抗性表
 *
 * 解析数据文件 Weakness&Resistance.txt，并按「Boss 内部名 + 形态号」查询。
 * 数据文件格式（每个 Boss 一段，段之间用 --- 分隔）：
 *
 *     Beelzebub                 <- 段落名（这里用的是显示名）
 *     Physical: 1x              <- 元素: 倍率x
 *     Fire: 1.25x
 *     ...
 *     ---
 *
 * 也支持两种非数值写法：
 *     Fire: 1+x (weak)          <- 只说明"弱"，没有具体倍率
 *     Fire: 1-x (resist)        <- 只说明"抗"
 *     Others: 0.75x             <- 其余元素统一倍率
 * 以及整段只有说明、没有数值表的情况（例如 NaN / Jim C. Bringer(P1)）。
 */
#ifndef RES_H
#define RES_H

#include <stdbool.h>

/* 七个元素，顺序与数据文件一致 */
typedef enum {
    ELEM_PHYSICAL = 0,
    ELEM_FIRE,
    ELEM_FROST,
    ELEM_ELECTRIC,
    ELEM_LUMINOUS,
    ELEM_SHADOW,
    ELEM_POISON,
    ELEM_COUNT
} Elem;

typedef enum {
    VAL_NONE = 0,   /* 该段没有这一项 */
    VAL_NUM,        /* 具体倍率 */
    VAL_WEAK,       /* "1+x (weak)"：弱，倍率未给出 */
    VAL_RESIST      /* "1-x (resist)"：抗，倍率未给出 */
} ValKind;

typedef struct {
    ValKind kind;
    double  mult;
} ElemVal;

#define RES_MAX_BOSSES 160
#define RES_NOTE_LINES 8      /* 一个段落的说明最多保留几行 */
#define RES_NOTE_LEN   160

typedef struct {
    char    name[64];            /* 数据文件里的段落名（查询键），如 "Beelzebub" */
    ElemVal v[ELEM_COUNT];
    bool    has_others;          /* 出现 "Others: Nx" */
    double  others;
    bool    is_note;             /* 整段只有说明文字，没有数值 */
    /* 说明文字**按数据文件里的原始行**逐行保留（不合并成一段再重排）：
     * NaN 那五行是五句独立的话，合并后再按宽度折行会把 "Fire mode: …"
     * 和 "Frost mode: …" 挤进同一行，读起来是糊的。*/
    int     n_note;
    char    note[RES_NOTE_LINES][RES_NOTE_LEN];
} BossRes;

typedef struct {
    BossRes b[RES_MAX_BOSSES];
    int     n;
    int     bad_lines;           /* 无法识别而被忽略的行数（诊断用） */
} ResTable;

/* 元素**显示名**（面板上显示的中文）：物 / 火 / 冰 / 电 / 光 / 暗 / 毒。
 * 注意：数据文件里仍然用英文键（Physical、Fire …），显示名与解析键是分开的；
 * 数据文件里也可以直接写中文（物/火/冰/电/光/圣/暗/毒），两者都认。*/
const char* res_elem_name(int elem);

/* 元素在数据文件里的规范英文键："Physical" … "Poison" */
const char* res_elem_key(int elem);

/* 读取数据文件；成功返回 true。失败时 t 被清空。 */
bool res_load(ResTable* t, const char* path);

/* Boss 内部名 -> 数据文件里用的显示名（未收录则原样返回）。
 * 与本体程序 names.c 的 Boss 映射表保持一致。 */
const char* res_boss_display(const char* internal);

/* 去掉 "(Clone)" 与 "PhaseN" 后缀，取出基础名（"YukiPhase2" -> "Yuki"） */
void res_boss_base(const char* name, char* out, int cap);

/* 形态号："Yuki" -> 1，"YukiPhase3" -> 3 */
int res_boss_phase(const char* name);

/* 查询：内部名 + 形态号。先试 "<显示名>(P<形态>)"，再试 "<显示名>"。
 * 找不到返回 NULL。 */
const BossRes* res_find(const ResTable* t, const char* internal, int phase);

/* 判断一个数值是"弱"还是"抗"：>1 弱，<1 抗，==1 中性 */
int res_verdict(double mult);    /* +1 弱 / -1 抗 / 0 中性 */

#endif
