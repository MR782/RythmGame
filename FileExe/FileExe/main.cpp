#include<stdio.h>
//#include<iostream>
#include<fstream>
//#include <algorithm>
#include<string>
#include <sstream>
#include<vector>

//------------------------------------------------
//列挙体定義
//-------------------------------------------------
enum Rane {
	A,
	S,
	D
};

enum Kind {
	Tap,
	Hold
};

//--------------------------------------------------
//構造体
//--------------------------------------------------

struct NotesData {
	Rane rane;
	Kind kind;
	int syousetu;
	int haku;
};

//-----------------------------------------------------
//変数宣言
//-----------------------------------------------------

std::ifstream file;
int bpm;
std::vector<NotesData> n_datas;

//-----------------------------------------------------
//関数定義
//-----------------------------------------------------

bool ReadLine(std::string& line_txt) {
	//1行読み込む
	bool rtv = false;
	while (std::getline(file, line_txt)) {
		//整合性チェック
		//行内に空白以外の文字が無い
		if (std::string::npos == line_txt.find_first_not_of(" 　")) continue;
		//最初の文字が/の場合コメントとみなす
		if ('/' == line_txt.at(0)) continue;
		//ヘッダー名とデータの境目である[ > ]が含まれていない
		if (std::string::npos == line_txt.find(">")) continue;
		//どれも当てはまらないなら有効な行となる
		rtv = true;
		//1行でも見つけたらループ終了
		break;
	}
	return rtv;
}


bool execute(std::string& header_str, std::string& data_str) {
	//トークン削除
	std::string::size_type t;
	while ((t = data_str.find_first_of("(,);")) != std::string::npos) {
		// (),;を空白に置き換える
		data_str[t] = ' ';
	}
	std::stringstream ss;
	ss << data_str;

	//-----------------------------------------------------
	//読み込みたい項目があればここに追加
	//BPM
	if (header_str == "BPM") {
		ss >> bpm;
	}
	//ノーツデータ
	else if (header_str == "Notes") {
		//データを読み込み
		int kind, rane;
		NotesData n;
		ss >> rane >> kind >> n.syousetu >> n.haku;
		n.rane = Rane(rane);
		n.kind = Kind(kind);
		//作成予定リストに入れる
		n_datas.push_back(n);
	}
	//else if (header_str == "end") this->kill();
	else {
		return false;
	}
	return true;
}

void set_data(std::string filepath) {
	file.open(filepath);
	//ファイルが無いなら例外を投げる
	if (file.fail())throw"読み取るファイルが無いじゃねえか";

	std::string header;//指令
	std::string data;//データ
	std::string line;//１行分のデータ
	while (ReadLine(line)) {
		//行を解読
		std::string::size_type t = line.find(">");// > が見つかるまでの文字数をとる
		header = line.substr(0, t);//最初からヘッダーとデータ情報の区切りまでの文字
		data = line.substr(t + 1);//ヘッダーとの区切りから最後までの文字
		//ヘッダー名に応じた処理を行う
		bool next = execute(header, data);
		//ファイルの終わりならループを抜ける
		if (file.eof()) break;
	}
}

int main(void) {
	n_datas.clear();
	set_data("./data/a.txt");

	//動作確認用---------------------------------------------------
	//BPM
	printf("BPM : %d \n", bpm);

	//ノーツの数をとる
	int size = (int)n_datas.size();
	printf("作成予定のノーツは %d 個です \n", size);
	//ノーツのデータ確認
	for (auto itr = n_datas.begin(); itr != n_datas.end(); itr++) {
		printf("Rane : %d , Kind : %d , Syousetsu : %d , Haku : %d \n",
			(*itr).rane, (*itr).kind, (*itr).syousetu, (*itr).haku);
	}
	//終了
}