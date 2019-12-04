#include<time.h>
#include <windows.h>
#include<stdio.h>

int main(void) {
	LARGE_INTEGER start;
	LARGE_INTEGER now;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);//1秒あたりのカウント数を記述
	QueryPerformanceCounter(&start);//スタート時間を記述(initialize()に記述)
	int i = 0;
	while (i < 100000){
		i++;
		QueryPerformanceCounter(&now);//現在の時間(update()に記述)
		//何ミリ秒経過
		double time = static_cast<double>(now.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart; // / 16.666666667f;//update()に記述
		
		//表示
		printf("経過(ms) : %lf[ms]  --(^ω^)---\n", time);//
	}
	return 0;
}