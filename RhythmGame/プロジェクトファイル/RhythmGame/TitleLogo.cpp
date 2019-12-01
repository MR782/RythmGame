#include "TitleLogo.h"
#include"ScreenSystem.h"
#include"Define.h"

void TitleLogo::initialize()
{
	this->anime = std::make_unique<Animation>();
	if (this->anime == nullptr) throw "TitleLogo anime is null_ptr";//ƒƒ‚ƒŠŠm•Û‚Å‚«‚Ä‚¢‚È‚¢‚È‚ç—áŠO‚ð“Š‚°‚é
	this->anime->set("title_logo");
	this->position = Vector2((ScreenData::width / 2.0f) - (logo_width / 2.0f), (ScreenData::height / 3.0f));
}

void TitleLogo::finalize()
{
	this->anime.reset();
}

void TitleLogo::update()
{
}
