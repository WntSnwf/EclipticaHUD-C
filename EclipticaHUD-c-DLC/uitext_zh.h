/* uitext_zh.h - 界面文案：简体中文 */
#ifndef UITEXT_ZH_H
#define UITEXT_ZH_H

/* 数据文件里本语言说明行的前缀（"zh: 弱点取决于…"）。
 * 不带前缀的说明行三种语言都会显示。 */
#define TXT_LANG_TAG      "zh"

/* 标题 / 副标题 */
#define TXT_SUBTITLE      "弱点 / 抗性速查"

/* Boss 行 */
#define TXT_BOSS_LBL      "当前 Boss"

/* 主体区 */
#define TXT_WAITING       "等待 Boss 战…"
#define TXT_NO_DATA       "数据表里没有这只 Boss"
#define TXT_NO_DATA_HINT  "可在 Weakness&Resistance.txt 里补一段"

/* 倍率后的强弱标记（数值型）*/
#define TXT_MARK_WEAK     "▲ 弱"
#define TXT_MARK_RESIST   "▼ 抗"
/* 数据文件只写 1+x / 1-x 时的取值文字 */
#define TXT_VAL_WEAK      "弱"
#define TXT_VAL_RESIST    "抗"

/* 七个属性在面板上的显示名（数据文件里的键见 res.c，两种都认）*/
#define TXT_ELEM_DISPLAY  { "物", "火", "冰", "电", "光", "暗", "毒" }

/* 底部状态栏 */
#define TXT_ST_FORCED     "固定 Boss（--boss）"
#define TXT_ST_DEMO       "演示模式"
#define TXT_ST_NO_TABLE   "找不到 Weakness&Resistance.txt"
#define TXT_ST_NO_LOG     "未找到 VRChat 日志"
#define TXT_ST_LOCKED     "已锁定当前 Boss"
#define TXT_ST_WAITING    "等待 Boss 战"

/* ---- test_dlc.exe --log 探针的输出标签（控制台诊断用）---- */
#define TXT_P_LOG         "日志文件   :"
#define TXT_P_FIGHTING    "正在打的   :"
#define TXT_P_DISPLAY     "显示名     :"
#define TXT_P_PHASE       "形态号     :"
#define TXT_P_QUERY       "查询键     :"
#define TXT_P_ENTRY       "查到条目   :"
#define TXT_P_NOTE        "说明       :"
#define TXT_P_NONE        "(没有 Boss 战)"
#define TXT_P_MISSING     "(数据表里没有这只 Boss)"
#define TXT_P_NOMULT      "（未给倍率）"
#define TXT_P_OPENFAIL    "打不开日志: %s"
#define TXT_P_LOADED      "已加载 %s：%d 个 Boss 段落"

/* 帮助 */
#define TXT_EXE_NAME      "hr-dlc.exe"
#define TXT_HELP_TITLE    "Ecliptica HUD DLC - 帮助"
#define TXT_HELP_BODY \
    "Ecliptica HUD DLC - Boss 弱点 / 抗性面板\n" \
    "\n" \
    "  " TXT_EXE_NAME "                 跟随 VRChat 实时日志\n" \
    "  " TXT_EXE_NAME " --log FILE      只看指定日志文件\n" \
    "  " TXT_EXE_NAME " --boss NAME     固定显示某只 Boss（内部名，如 FlyLord）\n" \
    "  " TXT_EXE_NAME " --demo          轮播演示，不需要日志\n" \
    "  " TXT_EXE_NAME " --help          显示本帮助\n" \
    "\n" \
    "数据来自 exe 同目录的 Weakness&Resistance.txt。\n" \
    "拖动面板移动；点 ✕ 关闭；Ctrl+Alt+W 退出。\n"

#endif
