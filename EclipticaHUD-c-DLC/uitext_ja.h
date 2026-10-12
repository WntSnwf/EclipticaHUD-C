/* uitext_ja.h - 画面テキスト：日本語 */
#ifndef UITEXT_JA_H
#define UITEXT_JA_H

/* この言語専用の説明行の接頭辞（"ja: すべてのダメージを無効化。"）。
 * 接頭辞の無い説明行はどの言語版でも表示されます。 */
#define TXT_LANG_TAG      "ja"

/* タイトル / サブタイトル */
#define TXT_SUBTITLE      "弱点 / 耐性"

/* ボス行 */
#define TXT_BOSS_LBL      "現在のボス"

/* 本文 */
#define TXT_WAITING       "ボス戦を待っています…"
#define TXT_NO_DATA       "データ表にこのボスがありません"
#define TXT_NO_DATA_HINT  "Weakness&Resistance.txt に追記してください"
/* 耐性表そのものが読めなかった場合（「表にこのボスがいない」とは別物）*/
#define TXT_NO_TABLE_BODY "耐性表が見つかりません"
#define TXT_NO_TABLE_PUT  "Weakness&Resistance.txt を次に置いてください："
#define TXT_NO_TABLE_OR   "または --table でパスを指定"

/* 弱点 / 耐性のマーク（数値あり）*/
#define TXT_MARK_WEAK     "▲ 弱点"
#define TXT_MARK_RESIST   "▼ 耐性"
/* データファイルが 1+x / 1-x しか書いていない場合 */
#define TXT_VAL_WEAK      "弱点"
#define TXT_VAL_RESIST    "耐性"

/* 画面に出す 7 属性の表示名（データファイルは英語キーも中文キーも可）*/
#define TXT_ELEM_DISPLAY  { "物理", "火", "氷", "電気", "光", "闇", "毒" }

/* ステータスバー */
#define TXT_ST_FORCED     "ボス固定（--boss）"
#define TXT_ST_DEMO       "デモモード"
#define TXT_ST_NO_TABLE   "Weakness&Resistance.txt が見つかりません"
#define TXT_ST_NO_LOG     "VRChat のログが見つかりません"
#define TXT_ST_LOCKED     "ボスを追跡中"
#define TXT_ST_WAITING    "ボス戦待ち"

/* ---- test_dlc-ja.exe --log の出力ラベル（コンソール診断用）---- */
#define TXT_P_LOG         "ログファイル :"
#define TXT_P_FIGHTING    "交戦中のボス :"
#define TXT_P_DISPLAY     "表示名       :"
#define TXT_P_PHASE       "形態         :"
#define TXT_P_QUERY       "検索キー     :"
#define TXT_P_ENTRY       "該当項目     :"
#define TXT_P_NOTE        "説明         :"
#define TXT_P_NONE        "(ボス戦なし)"
#define TXT_P_MISSING     "(データ表にこのボスがありません)"
#define TXT_P_NOMULT      "（倍率の記載なし）"
#define TXT_P_OPENFAIL    "ログを開けません: %s"
#define TXT_P_LOADED      "%s を読み込みました：ボス %d 件"

/* ヘルプ */
#define TXT_EXE_NAME      "hr-dlc-ja.exe"
#define TXT_HELP_TITLE    "Ecliptica HUD DLC - ヘルプ"
#define TXT_HELP_BODY \
    "Ecliptica HUD DLC - ボスの弱点 / 耐性パネル\n" \
    "\n" \
    "  " TXT_EXE_NAME "                 VRChat のログを追跡\n" \
    "  " TXT_EXE_NAME " --log FILE      このログファイルだけを見る\n" \
    "  " TXT_EXE_NAME " --boss NAME     ボスを固定（内部名。例: FlyLord）\n" \
    "  " TXT_EXE_NAME " --table FILE    耐性表を指定（既定は exe と同じ階層などを自動検索）\n" \
    "  " TXT_EXE_NAME " --demo          ログ不要のデモ表示\n" \
    "  " TXT_EXE_NAME " --help          このヘルプを表示\n" \
    "\n" \
    "データは exe と同じフォルダの Weakness&Resistance.txt から読みます。\n" \
    "ドラッグで移動、✕ で閉じる、Ctrl+Alt+W で終了。\n"

#endif
