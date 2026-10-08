/* zhtext_ja.h - 画面テキスト：日本語
 *
 * 上部のボタンは 7 個で 1 つあたり論理 60px しかないため、
 * ラベルは全角 2〜3 文字に抑えている。長い説明はツールチップ（TXT_TIP_*）へ。 */
#ifndef ZHTEXT_JA_H
#define ZHTEXT_JA_H

/* 画面フォント：第一候補。無ければ hud.c が代替を選ぶ */
#define TXT_FONT_FACE    L"Meiryo UI"

/* イベントログのフィルタ幅（論理 px）：下の 4 ラベルが収まること。
 * 日本語はラテン文字より 1 文字が広いので中国語版より広く取る
 * （「ターゲット」5 文字・「ステージ/ボス」6 文字＋記号）。 */
#define TXT_CHIP_W       { 46, 46, 72, 92 }

/* タイトル / ボタン */
#define TXT_APP_TITLE    "Ecliptica HUD"
#define TXT_APP_SUB      "戦闘統計"
#define TXT_BTN_TOP      "最前面"
#define TXT_BTN_BIGGER   "拡大"
#define TXT_BTN_SMALLER  "縮小"
#define TXT_BTN_OPAQUE   "濃く"
#define TXT_BTN_FADED    "薄く"
#define TXT_BTN_PIERCE   "透過"
#define TXT_BTN_LOG      "ログ"
#define TXT_BTN_CLOSE    "✕"

/* ボタンの説明 */
#define TXT_TIP_TOP      "常に最前面に表示する／解除する"
#define TXT_TIP_BIGGER   "画面を拡大"
#define TXT_TIP_SMALLER  "画面を縮小"
#define TXT_TIP_OPAQUE   "不透明度を上げる"
#define TXT_TIP_FADED    "不透明度を下げる"
#define TXT_TIP_PIERCE   "マウス透過の切り替え（Ctrl+Alt+T）。オンにするとクリックは下のウィンドウへ抜けます"
#define TXT_TIP_LOG      "イベントログの表示／非表示"
#define TXT_TIP_CLOSE    "HUD を閉じる（Ctrl+Alt+Q）"
#define TXT_TIP_PREV_RUN   "前の周回"
#define TXT_TIP_NEXT_RUN   "次の周回"
#define TXT_TIP_PREV_FIGHT "前のボス戦"
#define TXT_TIP_NEXT_FIGHT "次のボス戦"
#define TXT_TIP_LOG_UP     "イベントログを遡る"
#define TXT_TIP_LOG_DOWN   "最新のイベントに戻る"
#define TXT_TIP_FILT_ALL   "すべてのイベントを表示"
#define TXT_TIP_FILT_DMG   "受けたダメージだけ"
#define TXT_TIP_FILT_TGT   "ボスのターゲット切替だけ"
#define TXT_TIP_FILT_BOSS  "ステージとボス戦だけ"

/* 列見出し */
#define TXT_COL_STAGE    "ステージ"
#define TXT_COL_RUN      "周回"
#define TXT_COL_FIGHT    "戦闘"

/* 統計行 */
#define TXT_ROW_DMG      "与ダメージ"
#define TXT_ROW_DPS      "DPS"
#define TXT_ROW_TAKEN    "被ダメージ"
#define TXT_ROW_HITS     "被弾"
#define TXT_ROW_MAXHIT   "最大被弾"
#define TXT_ROW_AVGHIT   "平均被弾"
#define TXT_ROW_TPS      "被ダメ/秒"
#define TXT_ROW_TOKENS   "トークン"

/* 情報エリア */
#define TXT_STAGE_NO     "ステージ %d"
#define TXT_NO_STAGE     "開始待ち"
#define TXT_CLASS_LABEL  "クラス"
#define TXT_KILLS        "撃破 %d"
#define TXT_TARGETS      "切替 %d"
#define TXT_TOKENS_X     "トークン %d/%d"
#define TXT_PROGRESS_LBL "進行度"

/* ボス行 */
#define TXT_FIGHT_LBL    "戦闘 %s"
#define TXT_NO_FIGHT     "ボス戦は行われていません"
#define TXT_DURATION     "経過 %s"
#define TXT_TARGET_LBL   "ターゲット %s"
#define TXT_TARGET_FOR   "ターゲット %s %s"
#define TXT_TARGET_OF    "%s → %s  %s"
/* ターゲット行を分割描画するときの前半：オブジェクト名 + 矢印 */
#define TXT_TARGET_OF_LBL "%s → "
#define TXT_TARGET_NONE  "ターゲット —"

/* 被ダメージ内訳 */
#define TXT_BREAKDOWN    "被ダメージ内訳"
#define TXT_BD_FIGHT     "（この戦闘）"
#define TXT_BD_STAGE     "（このステージ）"
#define TXT_BD_RUN       "（この周回）"
#define TXT_BD_NONE      "まだダメージを受けていません"

/* 履歴送り */
#define TXT_RUN_PAGE     "周回 %d/%d"
#define TXT_FIGHT_PAGE   "戦闘 %d/%d"
#define TXT_LIVE         "リアルタイム"
#define TXT_HISTORY      "履歴"

/* イベントログ */
#define TXT_EVENT_LOG    "イベントログ"
#define TXT_LOG_EMPTY    "イベントなし"
#define TXT_FILTER_ALL   "すべて"
#define TXT_FILTER_DMG   "被ダメ"
#define TXT_FILTER_TGT   "ターゲット"
#define TXT_FILTER_BOSS  "ステージ/ボス"
#define TXT_SCROLL_HINT  "ホイールで送る"

/* ステータスバー */
#define TXT_PIERCE_BADGE "マウス透過中 · Ctrl+Alt+T で解除"
#define TXT_LOG_MISSING  "VRChat のログが見つかりません"
#define TXT_LOG_FILE_MISSING "--log で指定したファイルを開けません"
#define TXT_WAIT_JOIN    "Ecliptica への入室待ち"
#define TXT_IDLE_WORLD   "Ecliptica 内・開始待ち"
#define TXT_RUNNING      "周回中"
#define TXT_INTERMISSION "インターバル"
#define TXT_DEMO         "デモモード"
#define TXT_LOG_SRC      "ログ %s"

/* イベントログの行テンプレート */
#define TXT_EV_WORLD_IN  "ワールドに入室：%s"
#define TXT_EV_WORLD_OUT "ワールドから退出"
#define TXT_EV_STAGE     "ステージ %d：%s"
#define TXT_EV_INTERM    "インターバルに入りました"
#define TXT_EV_LOBBY     "ロビーに戻りました"
#define TXT_EV_BOSS      "ボス戦：%s"
#define TXT_EV_BOSS_DOWN "ボス撃破：%s"
#define TXT_EV_DEALT     "与ダメージ %s"
#define TXT_EV_TAKEN     "被ダメージ %s（%s · %s）"
#define TXT_EV_TAKEN_1   "被ダメージ %s（%s）"
#define TXT_EV_DEATH     "戦闘不能"
#define TXT_EV_TOKEN     "トークン出現（確率 %s%%）"
#define TXT_EV_TOKEN_GOT "トークンを取得"
#define TXT_EV_TARGET    "ターゲット切替 %s → %s"
#define TXT_EV_RUN_END   "周回終了：%s"

#define TXT_RESULT_WON   "クリア"
#define TXT_RESULT_LOST  "失敗"
#define TXT_RESULT_LOBBY "ロビー"
#define TXT_RESULT_LEFT  "退出"
#define TXT_RESULT_OPEN  "進行中"

#endif
