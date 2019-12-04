#pragma once
#include"Notes.h"
#include"JudgeResultCreater.h"

//���[�����Ƃ̃m�[�c����

class NotesController : public Object{
private:
	//���茋�ʂ̐������u
	JudgeResultCreater* result_creater;

	std::map<std::string, std::vector<std::unique_ptr<Notes>>> rane_data;
	//�m�[�c�̍폜
	bool delete_notes(std::vector<std::unique_ptr<Notes>>& rane);
	//Update,Draw���Ă�
	void callUpdate(std::vector<std::unique_ptr<Notes>>& rane);
	void callDraw(std::vector<std::unique_ptr<Notes>>& rane);

	//�X�R�A��ǉ�����
	void add_score(JudgeResult jr);
public:
	void initialize()override;
	void finalize()override;
	void update()override;
	void draw(bool a_brend = false)override;
};