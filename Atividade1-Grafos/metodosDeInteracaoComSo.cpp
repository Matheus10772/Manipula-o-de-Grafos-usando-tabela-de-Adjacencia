#include "metodosDeInteracaoComSo.h"

void LimparTela()
{
#ifdef OS_Windows
	setvbuf(stdin, NULL, _IONBF, 0);
	system("cls");
#else
	setbuf(stdin, NULL);
	system("tput reset");
#endif
}

void Pause()
{
#ifdef OS_Windows	
	setvbuf(stdin, NULL, _IONBF, 0);
	printf("\nPressione enter para continuar.\n");
	std::cin.get();
	setvbuf(stdin, NULL, _IONBF, 0);
#else
	setbuf(stdin, NULL);
	printf("\nPressione enter para continuar.\n");
	std::cin.get();
	setbuf(stdin, NULL);
#endif
}
