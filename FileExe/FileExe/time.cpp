#include<time.h>
#include <windows.h>
#include<stdio.h>

int main(void) {
	LARGE_INTEGER start;
	LARGE_INTEGER now;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);//1�b������̃J�E���g�����L�q
	QueryPerformanceCounter(&start);//�X�^�[�g���Ԃ��L�q(initialize()�ɋL�q)
	int i = 0;
	while (i < 100000){
		i++;
		QueryPerformanceCounter(&now);//���݂̎���(update()�ɋL�q)
		//���~���b�o��
		double time = static_cast<double>(now.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart; // / 16.666666667f;//update()�ɋL�q
		
		//�\��
		printf("�o��(ms) : %lf[ms]  --(^��^)---\n", time);//
	}
	return 0;
}