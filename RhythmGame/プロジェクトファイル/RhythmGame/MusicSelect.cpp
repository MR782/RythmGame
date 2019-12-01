#include "MusicSelect.h"
#include"./dxlib/DxLib.h"
#include"ScreenFunction.h"
#include"ScreenSystem.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"SceneManager.h"
#include"MemoryFunc.h"

MusicSelect::MusicSelect()
{
	this->ms_ui = nullptr;
	this->back_graph_handle = 0;
}

void MusicSelect::initialize()
{
	//���\�[�X�̓ǂݍ���
	MovieResource::load("m_select");
	//BGM��ǂݍ���
	Audio::load("select");
	//�Đ�
	Audio::play("m_select", false);
	//�������m��
	this->ms_ui = new MusicSelectUI();
	MemoryFunction::check_mem(this->ms_ui);
	//�f�[�^�̏�����
	//�w�i�摜���i�[
	this->back_graph_handle = GraphicResource::get_handle("select_back")[0];
	//�m�[�c�̗����鑬�x������(�����X�s�[�h)
	Necessary::set_speed(5);
	//�I�𒆂̊y�Ȃ�������
	Necessary::set_music(MusicList::monoceros);
	this->ms_ui->initialize();
}

void MusicSelect::finalize()
{
	this->ms_ui->finalize();
	delete this->ms_ui;
	Audio::stop("m_select");
}

void MusicSelect::update()
{
	if (ScreenFunction::check_brend_min()) {
		//UI�̍X�V����
		this->ms_ui->update();
		set_speed();
	}
	//----------------------------------------------------------------------
	//Enter�L�[�������ꂽ��V�[���ݒ�
	scene_change(KeyBoard::key_down(KEY_INPUT_RETURN), SceneData::game);
	//-----------------------------------------------------------------------
}

void MusicSelect::draw()
{
	//�w�i�摜���g�k�`��
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//UI�̕`��
	this->ms_ui->draw();
}

void MusicSelect::set_speed()
{
	//�X�s�[�h��������
	if (KeyBoard::key_down(KEY_INPUT_D) || KeyBoard::key_down(KEY_INPUT_F)) {
		//���ʉ���炷
		Audio::play("cursol");
		//����0�ɂ͂��Ȃ�
		if (Necessary::get_speed() <= 1) return;
		Necessary::set_speed(Necessary::get_speed() - 1);
	}
	//�X�s�[�h���グ��
	if (KeyBoard::key_down(KEY_INPUT_J) || KeyBoard::key_down(KEY_INPUT_K)) {
		//���ʉ���炷
		Audio::play("cursol");
		//�X�s�[�h�����20�Ƃ���
		if (Necessary::get_speed() >= 20) return;
		Necessary::set_speed(Necessary::get_speed() + 1);
	}
}