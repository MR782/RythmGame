#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>

//ゲームを通して必要なものの定義

//シーン
enum class SceneData {
	title,//タイトルシーン
	game,//ゲームシーン
	result,//リザルトシーン
	m_select//楽曲選択シーン
};

//楽曲リスト
enum class MusicList {
	monoceros,
	fancie,
	MusicNum
};

class Necessary {
private:
	static int score;//スコア
	static int speed;//ノーツの移動する速度
	static SceneData scene;//シーン
	static MusicList m_list;//楽曲リスト
	//false : フェードイン　true : フェードアウト
	static bool fade_ioFlag;
public:
	static void initialize();
	//フラグや値をセットする
	//false : フェードイン　true : フェードアウト
	static void set_fade_ioFlag(bool);
	//スコアをセット
	static void set_score(int);
	//シーンのセット
	static void set_scene(SceneData scene_);
	//楽曲セット
	static void set_music(MusicList list);
	//速度設定
	static void set_speed(int sp);

	//値を受け取る
	static bool get_fade_ioFlag();
	static int get_score();
	static SceneData get_now_scene();
	static MusicList get_music();
	static int get_speed();
};