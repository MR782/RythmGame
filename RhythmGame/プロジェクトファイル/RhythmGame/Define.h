#pragma once

//ノーツの大きさ
const int note_height = 16;
const int note_width = 64;

//判定ラインの画像の大きさ
const int judge_line_width = 256;
const int judge_line_height = 16;

//ゲームシーンのUI画像の大きさ
const int ui_graph_width = 110;
const int ui_graph_height = 45;

//ゲームシーン関連
const int buttonNum = 4;//判定ボタンの数
const int judge_resultNum = 3;//判定結果の数
const int theoretical_value = 100000;//理論値(APで大体この数値に近づく)
const int judgeUI_active_cnt = 60;//判定結果を描画するUIの生存フレーム数

//タイトル関連
const int titleLabel_width = 256;//画像の大きさ(ドット単位)
const int blend_speed = 5;//点滅スピード

const int logo_width = 512;//画像の大きさ(ドット単位)
const int logo_height = 128;//画像の大きさ(ドット単位)

//楽曲選択シーン関連
const int  select_cursol_height = 64;//画像の大きさ(ドット単位)
const int select_cursol_width  = 64;//画像の大きさ(ドット単位)
const int jacket_width = 320;//画像の大きさ(ドット単位)
const int jacket_height =480;//画像の大きさ(ドット単位)
const int cursolNum = 2;//カーソルの数

//リザルト関連
const int rankS_border = 90000;
const int rankA_border = 70000;
const int rankB_border = 50000;
const int rankC_border = 0;

const int rank_graph_size = 128;//画像の大きさ(ドット単位)
const int result_width = 512;//画像の大きさ(ドット単位)
const int result_heights = 128;//画像の大きさ(ドット単位)
const int result_guide_width = 128;//画像の大きさ(ドット単位)
const int result_guide_height = 64;//画像の大きさ(ドット単位)
const int fullcombo_graph_width = 256;//画像の大きさ(ドット単位)
const int fullcombo_graph_height = 64;//画像の大きさ(ドット単位)
