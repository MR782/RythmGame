#include "Jacket.h"
#include"ScreenSystem.h"
#include"Define.h"
#include"Necessary.h"

void Jacket::initialize()
{
	this->anime = std::make_unique<Animation>();//�������m��
	if (this->anime == nullptr) throw "Jacket anime is null_ptr";//�������m�ۂł��Ă��Ȃ��Ȃ��O�𓊂���
	this->anime->set("monoceros_jacket");//�����摜���Z�b�g
	//���S�ɃZ�b�g
	this->position = Vector2((ScreenData::width / 2) - (jacket_width / 2), (ScreenData::height / 2) - (jacket_height / 2));
}

void Jacket::finalize()
{
	this->anime.reset();
}

void Jacket::update()
{
	change_jacket();
}

void Jacket::change_jacket()
{
	//��Փx�Ɗy�Ȃɂ���ĉ摜��ς���
	switch (Necessary::get_music())
	{
	case MusicList::monoceros:
		this->anime->set("monoceros_jacket");
		break;
	case MusicList::fancie:
		this->anime->set("fancie_jacket");
		break;
	}
}
