#include "ArquivoDialogo.h"

std::string DialogoDeAberturaDeArquivo()
{
#ifdef OS_Windows
		OPENFILENAME DialogoDeAberturaDeArquivo;

		ZeroMemory(&DialogoDeAberturaDeArquivo, sizeof(DialogoDeAberturaDeArquivo));

		DialogoDeAberturaDeArquivo.lStructSize = sizeof(DialogoDeAberturaDeArquivo);
		DialogoDeAberturaDeArquivo.hwndOwner = 0;
		DialogoDeAberturaDeArquivo.lpstrDefExt = 0;
		DialogoDeAberturaDeArquivo.lpstrFile = new TCHAR[512];
		DialogoDeAberturaDeArquivo.lpstrFile[0] = '\0';
		DialogoDeAberturaDeArquivo.nMaxFile = 512;
		DialogoDeAberturaDeArquivo.lpstrFilter = NULL;
		DialogoDeAberturaDeArquivo.nFilterIndex = 1;
		DialogoDeAberturaDeArquivo.lpstrInitialDir = NULL;
		DialogoDeAberturaDeArquivo.lpstrTitle = L"Selecione um arquivo de texto";
		DialogoDeAberturaDeArquivo.Flags = 0;

		GetOpenFileName(&DialogoDeAberturaDeArquivo);

		std::wstring wstring = DialogoDeAberturaDeArquivo.lpstrFile;
		std::string stringConvertida(wstring.begin(), wstring.end());

#else
	nfdchar_t* outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("txt", NULL, &outPath);
	std::string stringConvertida;
	if (result == NFD_OKAY)
	{
		stringConvertida = std::string(outPath);
		puts("Sucesso");
		puts(outPath);
	}
	else if (result == NFD_CANCEL)
	{
		puts("Nenhum Arquivo Selecionado");
	}
	else
	{
		printf("Janela Fechada ou o dialogo de abertura foi fechado inesperadamente");
		//printf("Erro: %s\n", NFD_GetError());
	}

#endif
	return stringConvertida;
}
