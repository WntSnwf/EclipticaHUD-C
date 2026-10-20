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
#include <wchar.h>

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
    VAL_WEAK,       /* 弱 */
    VAL_RESIST      /* 抗 */
} ValKind;

typedef struct {
    ValKind kind;       /* 用于配色和 ▲/▼ 标记 */
    double  mult;       /* 数值 */
    /* mult 是否有效。数据文件里既有纯数值写法（1.25x），
     * 也有"只给判定"的写法（1+x (weak) / 1-x (resist)），
     * 还有**两者都给**的写法（0.7-x (resist)）—— 最后这种以前会把 0.7 丢掉。*/
    bool    has_mult;
    /* "N±x" 里的未知增量方向：-1 = 比 N 更低，+1 = 比 N 更高，0 = 就是 N。
     * 关键案例：Despair(P2) 的 `Electric: 0.7-x (resist)` 意思是
     * **低于 0.7**（比一阶段的 0.7 更抗），显示成 "0.7x" 会被读成"正好 0.7"。*/
    int     bound;
} ElemVal;

/* 说明文字比较长，而且**按句分行**写（实测 Jim P2 是 4 行、NaN 是 5 行），
 * 所以行数留够。尺寸预算：128 × (8×640 + 其它) ≈ 660 KB，是静态区，不进栈。*/
#define RES_MAX_BOSSES 128
#define RES_NOTE_LINES 8      /* 一个段落的说明最多保留几行 */
#define RES_NOTE_LEN   640

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

/* 读取数据文件；成功返回 true。失败时 t 被清空。
 *
 * res_load  收窄字符路径 —— 只适合纯 ASCII 或"控制台 ANSI 编码"的路径。
 * res_load_w 收宽字符路径 —— **从 exe 目录拼出来的绝对路径必须用它**：
 *   MSVCRT 的 fopen 按 ANSI 代码页解释路径，把 UTF-8 路径喂进去，
 *   只要目录名里有中文就会打不开文件（本程序就踩过这个坑）。 */
bool res_load(ResTable* t, const char* path);
bool res_load_w(ResTable* t, const wchar_t* path);

/* Boss 内部名 -> 数据文件里用的显示名（未收录则原样返回）。
 * 与本体程序 names.c 的 Boss 映射表保持一致。 */
const char* res_boss_display(const char* internal);

/* 去掉 "(Clone)" 与 "PhaseN" 后缀，取出基础名（"YukiPhase2" -> "Yuki"） */
void res_boss_base(const char* name, char* out, int cap);

/* 形态号："Yuki" -> 1，"YukiPhase3" -> 3 */
int res_boss_phase(const char* name);

/* 把用户输入的 Boss 名解析成"基础名 + 形态号"。三种写法都支持：
 *     FlyLord              -> ("FlyLord", 1)
 *     YukiPhase2           -> ("Yuki", 2)           日志里的对象名
 *     Jim C. Bringer(P2)   -> ("Jim C. Bringer", 2) 数据表里的键
 * --boss 和演示模式都必须走这个，否则多形态 Boss 查不到。*/
void res_parse_boss_arg(const char* arg, char* base, int cap, int* phase);

/* 查询：内部名 + 形态号。先试 "<显示名>(P<形态>)"，再试 "<显示名>"。
 * 找不到返回 NULL。 */
const BossRes* res_find(const ResTable* t, const char* internal, int phase);

/* 判断一个数值是"弱"还是"抗"：>1 弱，<1 抗，==1 中性 */
int res_verdict(double mult);    /* +1 弱 / -1 抗 / 0 中性 */

#endif
