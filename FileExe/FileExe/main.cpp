#include<stdio.h>
//#include<iostream>
#include<fstream>
//#include <algorithm>
#include<string>
#include <sstream>
#include<vector>

//------------------------------------------------
//�񋓑̒�`
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
//�\����
//--------------------------------------------------

struct NotesData {
	Rane rane;
	Kind kind;
	int syousetu;
	int haku;
};

//-----------------------------------------------------
//�ϐ��錾
//-----------------------------------------------------

std::ifstream file;
int bpm;
std::vector<NotesData> n_datas;

//-----------------------------------------------------
//�֐���`
//-----------------------------------------------------

bool ReadLine(std::string& line_txt) {
	//1�s�ǂݍ���
	bool rtv = false;
	while (std::getline(file, line_txt)) {
		//�������`�F�b�N
		//�s���ɋ󔒈ȊO�̕���������
		if (std::string::npos == line_txt.find_first_not_of(" �@")) continue;
		//�ŏ��̕�����/�̏ꍇ�R�����g�Ƃ݂Ȃ�
		if ('/' == line_txt.at(0)) continue;
		//�w�b�_�[���ƃf�[�^�̋��ڂł���[ > ]���܂܂�Ă��Ȃ�
		if (std::string::npos == line_txt.find(">")) continue;
		//�ǂ�����Ă͂܂�Ȃ��Ȃ�L���ȍs�ƂȂ�
		rtv = true;
		//1�s�ł��������烋�[�v�I��
		break;
	}
	return rtv;
}


bool execute(std::string& header_str, std::string& data_str) {
	//�g�[�N���폜
	std::string::size_type t;
	while ((t = data_str.find_first_of("(,);")) != std::string::npos) {
		// (),;���󔒂ɒu��������
		data_str[t] = ' ';
	}
	std::stringstream ss;
	ss << data_str;

	//-----------------------------------------------------
	//�ǂݍ��݂������ڂ�����΂����ɒǉ�
	//BPM
	if (header_str == "BPM") {
		ss >> bpm;
	}
	//�m�[�c�f�[�^
	else if (header_str == "Notes") {
		//�f�[�^��ǂݍ���
		int kind, rane;
		NotesData n;
		ss >> rane >> kind >> n.syousetu >> n.haku;
		n.rane = Rane(rane);
		n.kind = Kind(kind);
		//�쐬�\�胊�X�g�ɓ����
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
	//�t�@�C���������Ȃ��O�𓊂���
	if (file.fail())throw"�ǂݎ��t�@�C������������˂���";

	std::string header;//�w��
	std::string data;//�f�[�^
	std::string line;//�P�s���̃f�[�^
	while (ReadLine(line)) {
		//�s�����
		std::string::size_type t = line.find(">");// > ��������܂ł̕��������Ƃ�
		header = line.substr(0, t);//�ŏ�����w�b�_�[�ƃf�[�^���̋�؂�܂ł̕���
		data = line.substr(t + 1);//�w�b�_�[�Ƃ̋�؂肩��Ō�܂ł̕���
		//�w�b�_�[���ɉ������������s��
		bool next = execute(header, data);
		//�t�@�C���̏I���Ȃ烋�[�v�𔲂���
		if (file.eof()) break;
	}
}

int main(void) {
	n_datas.clear();
	set_data("./data/a.txt");

	//����m�F�p---------------------------------------------------
	//BPM
	printf("BPM : %d \n", bpm);

	//�m�[�c�̐����Ƃ�
	int size = (int)n_datas.size();
	printf("�쐬�\��̃m�[�c�� %d �ł� \n", size);
	//�m�[�c�̃f�[�^�m�F
	for (auto itr = n_datas.begin(); itr != n_datas.end(); itr++) {
		printf("Rane : %d , Kind : %d , Syousetsu : %d , Haku : %d \n",
			(*itr).rane, (*itr).kind, (*itr).syousetu, (*itr).haku);
	}
	//�I��
}