#pragma once
#include"Notes.h"
#include"JudgeResultCreater.h"

//レーンごとのノーツ処理

class NotesController : public Object{
private:
	//判定結果の生成装置
	JudgeResultCreater* result_creater;

	std::map<std::string, std::vector<std::unique_ptr<Notes>>> rane_data;
	//ノーツの削除
	bool delete_notes(std::vector<std::unique_ptr<Notes>>& rane);
	//Update,Drawを呼ぶ
	void callUpdate(std::vector<std::unique_ptr<Notes>>& rane);
	void callDraw(std::vector<std::unique_ptr<Notes>>& rane);

	//スコアを追加する
	void add_score(JudgeResult jr);
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_brend = false)override;
};