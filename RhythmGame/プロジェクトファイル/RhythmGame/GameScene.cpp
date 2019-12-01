#include "GameScene.h"
#include"Necessary.h"
#include"Audio.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"SceneManager.h"
#include"Define.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

//�J�E���^
float Counter::game_cnt;
int Counter::perfect_cnt;
int Counter::good_cnt;
int Counter::miss_cnt;
int Counter::notes_num;
int Counter::combo_cnt;
//���f��
std::vector<std::unique_ptr<Notes>> Model::notes;
JudgeLine* Model::judge_line;
std::vector<std::unique_ptr<JudgeResultUI>> Model::judge_results;

Game::Game() :Scene()
{
	this->game_ui = nullptr;
	this->notes_creater = nullptr;
	this->result_creater = nullptr;
	this->start_time.QuadPart = 0;
	this->now_time.QuadPart = 0;
}

void Game::initialize()
{
	//���\�[�X�ǂݍ���
	Audio::load("game");
	//�f�[�^�폜
	Model::notes.clear();
	//�������m�� - �������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	//���胉�C��------------------------------------------------------------------
	Model::judge_line = new JudgeLine();
	MemoryFunction::check_mem(Model::judge_line);
	//UI�̏�����
	this->game_ui = new GameUI();
	MemoryFunction::check_mem(this->game_ui);
	//�m�[�c�̐������u----------------------------------------------------------------
	notes_creater = new NotesCreater();
	MemoryFunction::check_mem(notes_creater);
	//���茋�ʂ̐������u--------------------------------------------------------------
	result_creater = new JudgeResultCreater();
	//�I�u�W�F�N�g�̏�����
	Model::judge_line->initialize();//���胉�C���̏�����
	this->notes_creater->initialize();
	this->game_ui->initialize();//UI�̏�����
	//�I���y�Ȃɂ���ēǂݍ��ރf�[�^��ς���
	set_musical_score();
	if (Model::notes.empty())throw("��������m�[�c������ۂł�");

	//�J�E���^�̏�����-----------------------------------------------------------------
	this->start_time.QuadPart = (LONGLONG)GetNowHiPerformanceCount();//�J�n���Ԃ��擾
	this->now_time.QuadPart = 0;//���Ԃ̍X�V
	Counter::game_cnt = 0;
	Counter::perfect_cnt = 0;
	Counter::good_cnt = 0;
	Counter::miss_cnt = 0;
	Counter::combo_cnt = 0;
	Necessary::set_score(0);//�X�R�A�̏�����
	//�摜���Z�b�g
	this->back_graph_handle = GraphicResource::get_handle("game_back")[0];

	start_music();
}

void Game::finalize()
{
	Model::judge_line->finalize();
	this->notes_creater->finalize();
	this->game_ui->finalize();
	//�������J��
	Model::judge_results.clear();
	Model::notes.clear();
	delete Model::judge_line;
	delete this->notes_creater;
	delete this->result_creater;
	delete this->game_ui;
}

void Game::update()
{
	//�Q�[���J�E���^�̍X�V
	this->now_time.QuadPart = (LONGLONG)GetNowHiPerformanceCount();//���Ԃ̍X�V
	//�}�C�N���b����~���b�ɕϊ����ăt���[���ɕϊ�
	Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) / 1000) / 16.666666667f;//�t���[���P�ʂɕϊ�
	//�m�[�c�̍X�V����
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		if ((*itr) != nullptr) {
			(*itr)->update();
		}
	}
	//�m�[�c�̍폜����
	delete_notes();
	//���茋��
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->update();
	}
	//���茋�ʂ���������UI�̍폜����
	delete_judge_resultUI();
	//���胉�C���̍X�V����
	Model::judge_line->update();
	//UI�̍X�V����
	this->game_ui->update();

	//�Ȃ��I��������t�F�[�h�A�E�g�J�n----------------------
	if (Audio::check_play("monoceros") == false && Audio::check_play("fancie") == false) {
		Necessary::set_fade_ioFlag(true);
	}
	//�Ó]����������
	if (ScreenFunction::check_brend_max()) {
		//�t�F�[�h�C�����s���悤�w�����o��
		Necessary::set_fade_ioFlag(false);
		//�V�[����؂�ւ���
		scene_manager->change_scene(SceneData::result);
	}
}

void Game::draw()
{
	//�w�i�̊g�k�`��
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//���[���̕`��-------------------------------------------------------------
	const int judge_lineX = (int)Model::judge_line->get_position().x;
	const int judge_lineY = (int)Model::judge_line->get_position().y;
	DrawBox(judge_lineX, 0, judge_lineX + judge_line_width, judge_lineY, GetColor(0, 0, 0), TRUE);
	for (int i = 0; i < buttonNum; i++) {
		DrawLine(judge_lineX + note_width * i, 0,
			judge_lineX + note_width * i,
			judge_lineY + judge_line_height,
			GetColor(255, 255, 255));
	}
	//���胉�C���̕`��---------------------------------------------------------
	Model::judge_line->draw();
	//�m�[�c�̕`�揈��
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		(*itr)->draw();
	}
	//UI�̕`��
	this->game_ui->draw();
	//���茋��
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		(*itr)->draw();
	}
}

void Game::delete_notes()
{
	//�����𖞂�����Notes���폜
	for (auto itr = Model::notes.begin(); itr != Model::notes.end(); itr++) {
		if ((*itr)->get_active() == false) {
			//���肪�s���Ă��Ȃ��m�[�c������Ȃ������x�T��
			const bool continue_flag = ((*itr)->get_result() == JudgeResult::none);
			if (continue_flag) continue;
			add_score((*itr)->get_result());
			//�f�[�^������������vector�ɑ}��
			MemoryFunction::check_mem(result_creater);
			result_creater->create((*itr)->get_result(), (*itr)->get_judge_key());
			Model::notes.erase((itr));//vector����폜
			break;
		}
	}
}

void Game::delete_judge_resultUI()
{
	for (auto itr = Model::judge_results.begin(); itr != Model::judge_results.end(); itr++) {
		//���݂���ׂ��ł͂Ȃ��Ȃ�
		if ((*itr)->is_active() == false) {
			//�z�񂩂�폜
			Model::judge_results.erase(itr);
			break;
		}
	}
}

void Game::set_musical_score()
{
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		Model::notes = this->notes_creater->get_notes_data("monoceros");
		break;
	case MusicList::fancie:
		Model::notes = this->notes_creater->get_notes_data("fancie");
	}
}

void Game::start_music()
{
	//�y�ȑI���Ɋ�Â��ĕς���
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		Audio::play("monoceros");
		Counter::notes_num = notes_creater->get_all_notes_num("monoceros");
		break;
	case MusicList::fancie:
		Audio::play("fancie");
		Counter::notes_num = notes_creater->get_all_notes_num("fancie");
		break;
	default:
		throw "�y�Ȃɖ����Ȓl�������Ă���";
		break;
	}
}

void Game::add_score(JudgeResult jr)
{
	int score = 0;
	//���茋�ʂ�`�悷�邽�߂̃I�u�W�F�N�g��vector�ɒǉ�
	//���茋�ʂ��ǂ����������ŃX�R�A�𑝉�������
	switch (jr)
	{
	case JudgeResult::perfect:
		//��������X�R�A�̒l������
		score = theoretical_value / Counter::notes_num;
		//�J�E���^�㏸
		Counter::perfect_cnt++;
		Counter::combo_cnt++;
		break;
	case JudgeResult::good:
		//��������X�R�A�̒l������
		score = theoretical_value / Counter::notes_num / 2;
		//�J�E���^�㏸
		Counter::good_cnt++;
		Counter::combo_cnt++;
		break;
	case JudgeResult::miss:
		//��������X�R�A�̒l������
		score = 0;
		//�J�E���^�㏸
		Counter::miss_cnt++;
		break;
	}
	//���݃X�R�A�ɉ��Z����
	Necessary::set_score(Necessary::get_score() + score);
}
