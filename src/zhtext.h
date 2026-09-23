/* zhtext.h - 界面文案（UTF-8，统一由 UTF8->UTF-16 转换后交给 GDI）*/
#ifndef ZHTEXT_H
#define ZHTEXT_H

/* 标题 / 按钮 */
#define TXT_APP_TITLE    "Ecliptica HUD"
#define TXT_APP_SUB      "战斗统计"
#define TXT_BTN_TOP      "置顶"
#define TXT_BTN_BIGGER   "放大"
#define TXT_BTN_SMALLER  "缩小"
#define TXT_BTN_OPAQUE   "变浓"
#define TXT_BTN_FADED    "变淡"
#define TXT_BTN_WIN_LONG "窗长"
#define TXT_BTN_WIN_SHORT "窗短"
#define TXT_BTN_LOG      "日志"
#define TXT_BTN_CLOSE    "✕"

/* 按钮提示 */
#define TXT_TIP_TOP      "切换窗口置顶"
#define TXT_TIP_BIGGER   "放大界面"
#define TXT_TIP_SMALLER  "缩小界面"
#define TXT_TIP_OPAQUE   "提高不透明度"
#define TXT_TIP_FADED    "降低不透明度"
#define TXT_TIP_WIN_LONG "加长 DPS 统计窗口"
#define TXT_TIP_WIN_SHORT "缩短 DPS 统计窗口"
#define TXT_TIP_LOG      "显示/隐藏事件日志"
#define TXT_TIP_CLOSE    "关闭 HUD（Ctrl+Alt+Q）"
#define TXT_TIP_PREV_RUN   "上一局"
#define TXT_TIP_NEXT_RUN   "下一局"
#define TXT_TIP_PREV_FIGHT "上一场 Boss 战"
#define TXT_TIP_NEXT_FIGHT "下一场 Boss 战"
#define TXT_TIP_LOG_UP     "向上翻看事件日志"
#define TXT_TIP_LOG_DOWN   "回到最新事件"
#define TXT_TIP_FILT_ALL   "显示全部事件"
#define TXT_TIP_FILT_DMG   "只看你受到的伤害"
#define TXT_TIP_FILT_TGT   "只看 Boss 目标切换"
#define TXT_TIP_FILT_BOSS  "只看阶段与 Boss 战"

/* 表头 */
#define TXT_COL_STAGE    "阶段"
#define TXT_COL_RUN      "本局"
#define TXT_COL_FIGHT    "本场"

/* 统计行 */
#define TXT_ROW_DMG      "伤害"
#define TXT_ROW_DPS      "DPS"
#define TXT_ROW_TAKEN    "承伤"
#define TXT_ROW_HITS     "受击"
#define TXT_ROW_MAXHIT   "最大受击"
#define TXT_ROW_AVGHIT   "平均受击"
#define TXT_ROW_TPS      "承伤/秒"
#define TXT_ROW_DEATHS   "死亡"
#define TXT_ROW_TOKENS   "印记"

/* 信息区 */
#define TXT_STAGE_NO     "阶段 %d"
#define TXT_NO_STAGE     "等待开始"
#define TXT_CLASS_LABEL  "职业"
#define TXT_KILLS        "击倒 %d"
#define TXT_TARGETS      "切换 %d"
#define TXT_TOKENS_X     "印记 %d/%d"
#define TXT_PROGRESS_LBL "进度"

/* Boss 行 */
#define TXT_FIGHT_LBL    "本场 %s"
#define TXT_NO_FIGHT     "当前没有 Boss 战"
#define TXT_DURATION     "时长 %s"
#define TXT_TARGET_LBL   "目标 %s"
#define TXT_TARGET_FOR   "目标 %s %s"
#define TXT_TARGET_OF    "%s → %s  %s"
#define TXT_TARGET_NONE  "目标 —"

/* 伤害来源 */
#define TXT_BREAKDOWN    "伤害来源"
#define TXT_BD_FIGHT     "（本场）"
#define TXT_BD_STAGE     "（本阶段）"
#define TXT_BD_RUN       "（本局）"
#define TXT_BD_NONE      "暂无受到伤害的记录"

/* 历史翻页 */
#define TXT_RUN_PAGE     "本局 %d/%d"
#define TXT_FIGHT_PAGE   "本场 %d/%d"
#define TXT_LIVE         "实时"
#define TXT_HISTORY      "历史"

/* 事件日志 */
#define TXT_EVENT_LOG    "事件日志"
#define TXT_LOG_EMPTY    "暂无事件"
#define TXT_FILTER_ALL   "全部"
#define TXT_FILTER_DMG   "承伤"
#define TXT_FILTER_TGT   "目标"
#define TXT_FILTER_BOSS   "阶段/Boss"
#define TXT_SCROLL_HINT  "滚轮翻看"

/* 状态栏 */
#define TXT_LOG_MISSING  "未找到 VRChat 日志"
#define TXT_LOG_FILE_MISSING "打不开 --log 指定的文件"
#define TXT_WAIT_JOIN    "等待进入 Ecliptica"
#define TXT_IDLE_WORLD   "已在 Ecliptica，等待开局"
#define TXT_RUNNING      "本局进行中"
#define TXT_INTERMISSION "间歇期"
#define TXT_DEMO         "演示模式"
#define TXT_LOG_SRC      "日志 %s"

/* 日志行模板 */
#define TXT_EV_WORLD_IN  "进入世界：%s"
#define TXT_EV_WORLD_OUT "离开世界"
#define TXT_EV_STAGE     "阶段 %d：%s"
#define TXT_EV_INTERM    "进入间歇期"
#define TXT_EV_LOBBY     "返回大厅"
#define TXT_EV_BOSS      "Boss 战：%s"
#define TXT_EV_BOSS_DOWN "Boss 击杀：%s"
#define TXT_EV_DEALT     "造成伤害 %s"
#define TXT_EV_TAKEN     "承伤 %s（%s · %s）"
#define TXT_EV_TAKEN_1   "承伤 %s（%s）"
#define TXT_EV_DEATH     "你已阵亡"
#define TXT_EV_TOKEN     "发现印记（概率 %s%%）"
#define TXT_EV_TOKEN_GOT "拾取印记"
#define TXT_EV_TARGET    "目标切换 %s → %s"
#define TXT_EV_RUN_END   "本局结束：%s"

#define TXT_RESULT_WON   "通关"
#define TXT_RESULT_LOST  "失败"
#define TXT_RESULT_LOBBY "回大厅"
#define TXT_RESULT_LEFT  "离开"
#define TXT_RESULT_OPEN  "进行中"

#endif
