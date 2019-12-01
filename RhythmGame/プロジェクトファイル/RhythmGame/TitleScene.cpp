#include "TitleScene.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"ScreenFunction.h"
#include"Mouse.h"
#include"SceneManager.h"
#include"Audio.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

Title::Title()
{
	this->title_ui = nullptr;
	this->back_graph_handle = 0;
}

void Title::initialize()
{
	//�������m��
	this->title_ui = new TitleUI();
	MemoryFunction::check_mem(this->title_ui);
	//���\�[�X�̓ǂݍ���
	MovieResource::load("title");
	Audio::load("title");
	this->back_graph_handle = GraphicResource::get_handle("title_back")[0];//1���̂��ߔz���0���w��
	//�f�[�^�̏�����
	this->title_ui->initialize();
	//�I�[�f�B�I�f�[�^�̓ǂݍ���
	Audio::play("title",false);
	
}

void Title::finalize()
{
	this->title_ui->finalize();
	delete this->title_ui;
	//���\�[�X�f�[�^�̊J��
	Audio::delete_soundData_name("title");
	MovieResource::delete_movie_mem("reaf");
}

void Title::update()
{
	if (ScreenFunction::check_brend_min()) {
		//UI�̍X�V����
		title_ui->update();
	}
	//�V�[���؂�ւ�-----------------------------------------
	scene_change(Mouse::left_click_down(), SceneData::m_select);
}

void Title::draw()
{
	//�w�i���g�k���ĕ`��
	DrawExtendGraph(0, 0, ScreenData::width, ScreenData::height, this->back_graph_handle, FALSE);
	//UI�̕`��
	title_ui->draw();
}
