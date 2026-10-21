/* uitext_en.h - UI strings: English */
#ifndef UITEXT_EN_H
#define UITEXT_EN_H

/* Prefix for note lines meant for this language only ("en: All damage blocked.").
 * Untagged note lines are shown by every language build. */
#define TXT_LANG_TAG      "en"

/* Title / subtitle */
#define TXT_SUBTITLE      "Weakness / Resistance"

/* Boss row */
#define TXT_BOSS_LBL      "Boss"

/* Body */
#define TXT_WAITING       "Waiting for a boss fight…"
#define TXT_NO_DATA       "No entry for this boss"
#define TXT_NO_DATA_HINT  "Add one in Weakness&Resistance.txt"
/* The table itself could not be read at all (different from "no entry for this boss") */
#define TXT_NO_TABLE_BODY "Resistance table not found"
#define TXT_NO_TABLE_PUT  "Put Weakness&Resistance.txt in:"
#define TXT_NO_TABLE_OR   "or point --table at it"

/* Weak / resist markers (numeric entries) */
#define TXT_MARK_WEAK     "▲ WEAK"
#define TXT_MARK_RESIST   "▼ RES"
/* Shown when the data file only says 1+x / 1-x */
#define TXT_VAL_WEAK      "WEAK"
#define TXT_VAL_RESIST    "RES"

/* Element names as shown on the panel (the data file accepts English keys too) */
#define TXT_ELEM_DISPLAY  { "Physical", "Fire", "Frost", "Electric", \
                            "Luminous", "Shadow", "Poison" }

/* Status bar */
#define TXT_ST_FORCED     "Fixed boss (--boss)"
#define TXT_ST_DEMO       "Demo mode"
#define TXT_ST_NO_TABLE   "Weakness&Resistance.txt not found"
#define TXT_ST_NO_LOG     "No VRChat log found"
#define TXT_ST_LOCKED     "Boss locked"
#define TXT_ST_WAITING    "Waiting for a boss fight"

/* ---- test_dlc-en.exe --log probe output labels (console diagnostics) ---- */
#define TXT_P_LOG         "Log file   :"
#define TXT_P_FIGHTING    "Now fighting:"
#define TXT_P_DISPLAY     "Display name:"
#define TXT_P_PHASE       "Phase      :"
#define TXT_P_QUERY       "Lookup key :"
#define TXT_P_ENTRY       "Entry      :"
#define TXT_P_NOTE        "Note       :"
#define TXT_P_NONE        "(no boss fight)"
#define TXT_P_MISSING     "(no entry for this boss)"
#define TXT_P_NOMULT      " (no multiplier given)"
#define TXT_P_OPENFAIL    "Cannot open log: %s"
#define TXT_P_LOADED      "Loaded %s: %d boss entries"

/* Help */
#define TXT_EXE_NAME      "hr-dlc-en.exe"
#define TXT_HELP_TITLE    "Ecliptica HUD DLC - Help"
#define TXT_HELP_BODY \
    "Ecliptica HUD DLC - Boss weakness / resistance panel\n" \
    "\n" \
    "  " TXT_EXE_NAME "                 follow the live VRChat log\n" \
    "  " TXT_EXE_NAME " --log FILE      use only this log file\n" \
    "  " TXT_EXE_NAME " --boss NAME     pin one boss (internal name, e.g. FlyLord)\n" \
    "  " TXT_EXE_NAME " --table FILE    use this resistance table (else auto-detected)\n" \
    "  " TXT_EXE_NAME " --demo          rotating demo, no log needed\n" \
    "  " TXT_EXE_NAME " --help          show this help\n" \
    "\n" \
    "Data comes from Weakness&Resistance.txt next to the exe.\n" \
    "Drag the panel to move it; click X to close; Ctrl+Alt+W to quit.\n" \
    "The program has no taskbar button - use the tray icon (right-click) to quit or reload the table.\n"

/* Tray icon (right-click menu). The panel is WS_EX_TOOLWINDOW so it has no
 * taskbar button; the tray icon is its only place to live. */
#define TXT_TRAY_TIP     "Ecliptica weakness/resistance - right-click for the menu"
#define TXT_TRAY_RELOAD  "Reload the resistance table"
#define TXT_TRAY_QUIT    "Quit"
#define TXT_TRAY_LOADED  "Resistance table reloaded"
#define TXT_TRAY_FAIL    "Could not add the tray icon (see tray.log)"
#define TXT_TRAY_DENIED  "Tray icon denied; run from a normal folder"

#endif
