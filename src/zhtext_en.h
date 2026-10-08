/* zhtext_en.h - UI strings: English
 *
 * Kept deliberately terse: the seven top buttons are only 60 logical pixels
 * wide each, so labels must stay within roughly 7 Latin characters.
 * Anything longer goes into the tooltips (TXT_TIP_*). */
#ifndef ZHTEXT_EN_H
#define ZHTEXT_EN_H

/* UI font: preferred face; hud.c falls back if it is not installed */
#define TXT_FONT_FACE    L"Segoe UI"

/* Event-log filter chip widths (logical px): must fit the four labels below */
#define TXT_CHIP_W       { 32, 44, 48, 66 }

/* Title / buttons */
#define TXT_APP_TITLE    "Ecliptica HUD"
#define TXT_APP_SUB      "Combat Stats"
#define TXT_BTN_TOP      "Top"
#define TXT_BTN_BIGGER   "Big"
#define TXT_BTN_SMALLER  "Small"
#define TXT_BTN_OPAQUE   "Opaque"
#define TXT_BTN_FADED    "Fade"
#define TXT_BTN_PIERCE   "Thru"
#define TXT_BTN_LOG      "Log"
#define TXT_BTN_CLOSE    "✕"

/* Button tooltips */
#define TXT_TIP_TOP      "Toggle always-on-top"
#define TXT_TIP_BIGGER   "Scale the panel up"
#define TXT_TIP_SMALLER  "Scale the panel down"
#define TXT_TIP_OPAQUE   "Increase opacity"
#define TXT_TIP_FADED    "Decrease opacity"
#define TXT_TIP_PIERCE   "Toggle mouse click-through (Ctrl+Alt+T); clicks then reach the window below"
#define TXT_TIP_LOG      "Show / hide the event log"
#define TXT_TIP_CLOSE    "Close the HUD (Ctrl+Alt+Q)"
#define TXT_TIP_PREV_RUN   "Previous run"
#define TXT_TIP_NEXT_RUN   "Next run"
#define TXT_TIP_PREV_FIGHT "Previous boss fight"
#define TXT_TIP_NEXT_FIGHT "Next boss fight"
#define TXT_TIP_LOG_UP     "Scroll back through the event log"
#define TXT_TIP_LOG_DOWN   "Jump to the newest event"
#define TXT_TIP_FILT_ALL   "Show every event"
#define TXT_TIP_FILT_DMG   "Only damage you took"
#define TXT_TIP_FILT_TGT   "Only boss target switches"
#define TXT_TIP_FILT_BOSS  "Only stages and boss fights"

/* Column headers */
#define TXT_COL_STAGE    "Stage"
#define TXT_COL_RUN      "Run"
#define TXT_COL_FIGHT    "Fight"

/* Stat rows */
#define TXT_ROW_DMG      "Damage"
#define TXT_ROW_DPS      "DPS"
#define TXT_ROW_TAKEN    "Taken"
#define TXT_ROW_HITS     "Hits"
#define TXT_ROW_MAXHIT   "Max Hit"
#define TXT_ROW_AVGHIT   "Avg Hit"
#define TXT_ROW_TPS      "Taken/s"
#define TXT_ROW_TOKENS   "Tokens"

/* Info area */
#define TXT_STAGE_NO     "Stage %d"
#define TXT_NO_STAGE     "Waiting"
#define TXT_CLASS_LABEL  "Class"
#define TXT_KILLS        "Kills %d"
#define TXT_TARGETS      "Switches %d"
#define TXT_TOKENS_X     "Tokens %d/%d"
#define TXT_PROGRESS_LBL "Progress"

/* Boss line */
#define TXT_FIGHT_LBL    "Fight %s"
#define TXT_NO_FIGHT     "No boss fight right now"
#define TXT_DURATION     "Time %s"
#define TXT_TARGET_LBL   "Target %s"
#define TXT_TARGET_FOR   "Target %s %s"
#define TXT_TARGET_OF    "%s → %s  %s"
/* Prefix used when the target row is drawn in segments: object + arrow */
#define TXT_TARGET_OF_LBL "%s → "
#define TXT_TARGET_NONE  "Target —"

/* Damage breakdown */
#define TXT_BREAKDOWN    "Damage sources"
#define TXT_BD_FIGHT     " (fight)"
#define TXT_BD_STAGE     " (stage)"
#define TXT_BD_RUN       " (run)"
#define TXT_BD_NONE      "No damage taken yet"

/* History paging */
#define TXT_RUN_PAGE     "Run %d/%d"
#define TXT_FIGHT_PAGE   "Fight %d/%d"
#define TXT_LIVE         "LIVE"
#define TXT_HISTORY      "HISTORY"

/* Event log */
#define TXT_EVENT_LOG    "Event log"
#define TXT_LOG_EMPTY    "No events"
#define TXT_FILTER_ALL   "All"
#define TXT_FILTER_DMG   "Taken"
#define TXT_FILTER_TGT   "Target"
#define TXT_FILTER_BOSS  "Stage/Boss"
#define TXT_SCROLL_HINT  "scroll to browse"

/* Status bar */
#define TXT_PIERCE_BADGE "Click-through · Ctrl+Alt+T"
#define TXT_LOG_MISSING  "No VRChat log found"
#define TXT_LOG_FILE_MISSING "Cannot open the file given to --log"
#define TXT_WAIT_JOIN    "Waiting to enter Ecliptica"
#define TXT_IDLE_WORLD   "In Ecliptica, waiting for a run"
#define TXT_RUNNING      "Run in progress"
#define TXT_INTERMISSION "Intermission"
#define TXT_DEMO         "Demo mode"
#define TXT_LOG_SRC      "Log %s"

/* Event log line templates */
#define TXT_EV_WORLD_IN  "Entered world: %s"
#define TXT_EV_WORLD_OUT "Left world"
#define TXT_EV_STAGE     "Stage %d: %s"
#define TXT_EV_INTERM    "Intermission started"
#define TXT_EV_LOBBY     "Back to lobby"
#define TXT_EV_BOSS      "Boss fight: %s"
#define TXT_EV_BOSS_DOWN "Boss killed: %s"
#define TXT_EV_DEALT     "Dealt %s damage"
#define TXT_EV_TAKEN     "Took %s (%s · %s)"
#define TXT_EV_TAKEN_1   "Took %s (%s)"
#define TXT_EV_DEATH     "You died"
#define TXT_EV_TOKEN     "Token spawned (%s%% chance)"
#define TXT_EV_TOKEN_GOT "Token picked up"
#define TXT_EV_TARGET    "Target switch %s → %s"
#define TXT_EV_RUN_END   "Run ended: %s"

#define TXT_RESULT_WON   "CLEAR"
#define TXT_RESULT_LOST  "FAILED"
#define TXT_RESULT_LOBBY "LOBBY"
#define TXT_RESULT_LEFT  "LEFT"
#define TXT_RESULT_OPEN  "LIVE"

#endif
