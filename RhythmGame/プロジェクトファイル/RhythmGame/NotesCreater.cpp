#include "NotesCreater.h"
#include"Necessary.h"
#include<fstream>
#include"GameScene.h"
#include"Necessary.h"
#include"Define.h"
#include"PushNote.h"
#include"HoldNote.h"
#include<iostream>

void NotesCreater::initialize()
{
	this->filename["monoceros"] = "monoceros.txt";
	this->filename["fancie"] = "tenga.txt";
	//vectorに要素追加
	for (auto itr = this->filename.begin(); itr != this->filename.end(); itr++) {
		NotesCreater::MusicalScore ms;
		ms.name = (*itr).first;//名前
		ms.notes = create_score("./data/txt/" + this->filename[ms.name]);//ファイルを呼んでデータを入れる
		//vectorに格納
		this->musical_score_datas.push_back(ms);
	}
}

void NotesCreater::finalize()
{
	this->filename.clear();
	for (auto itr = this->musical_score_datas.begin(); itr != this->musical_score_datas.end(); itr++) {
		(*itr).notes.clear();
	}
	this->musical_score_datas.clear();
}

std::vector<NotesCreater::NotesData> NotesCreater::create_score(std::string name)
{
	//テキストファイルからデータを受け取りNotesDataのvectorに入れていく
	std::ifstream file(name);
	//ファイルがないなら例外処理を流す
	if (file.fail()) throw("txt file is not found");
	//データを格納する
	std::vector<NotesData> notes_data;
	//ファイルから読み込んだデータをvectorに登録する
	while (!file.eof()) {
		NotesData n_data;
		int kind;
		int rane;
		float p_timing;
		//ファイルからデータをとってくる
		file >> kind >> rane >> p_timing;
		NotesKind n_kind = NotesKind(kind);
		JudgeKey j_key = JudgeKey(rane);
		//値を格納
		n_data.j_key = j_key;
		n_data.kind = n_kind;
		n_data.p_timing = p_timing;
		//vectorに格納
		notes_data.push_back(n_data);
	}
	file.close();

	return notes_data;
}

int NotesCreater::get_all_notes_num(std::string name)
{
	int note_num = 0;
	for (auto itr : musical_score_datas) {
		if (itr.name == name) {
			int cnt = 0;
			for (auto itr2 : itr.notes) {
				cnt++;
			}
			note_num = cnt;
		}
	}
	return note_num;
}

std::vector<std::unique_ptr<Notes>> NotesCreater::get_notes_data(std::string name)
{
	std::vector<std::unique_ptr<Notes>> notes_data;
	notes_data.clear();//配列の中身を空にしておく
	for (auto itr = this->musical_score_datas.begin(); itr != this->musical_score_datas.end(); itr++) {
		if ((*itr).name == name) {
			for (auto itr2 = (*itr).notes.begin(); itr2 != (*itr).notes.end(); itr2++) {
				std::unique_ptr<Notes> note = nullptr;
				//種類によって生成するオブジェクトを変える
				switch ((*itr2).kind)
				{
				case NotesKind::Hold:
					note = std::make_unique<HoldNotes>();
					break;
				case NotesKind::Push:
					note = std::make_unique<PushNotes>();
					break;
				}
				//メモリ確保できなかったら例外を投げる
				if(note == nullptr) throw"NotesCreater note is null_ptr";
				//データ初期化
				note->initialize();
				note->set_contents((*itr2).p_timing, (*itr2).j_key);
				//メモリの所有権移動
				notes_data.push_back(std::move(note));
			}
			break;
		}
	}
	return notes_data;
}