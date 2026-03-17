#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Sorting.h"
#include "Visualizer.h"

#include <fstream>
#include <chrono>
#include <algorithm>
#include <System.IOUtils.hpp>

using namespace std;

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
	MemoResults->Clear();
	MemoResults->Lines->Add("Здесь будет информация о сортировке");
}

// Проверка корректности ввода
bool TForm1::validateInput()
{
    if(editSize->Text.IsEmpty()) return false;
    if(editMin->Text.IsEmpty()) return false;
    if(editMax->Text.IsEmpty()) return false;

    int size = StrToInt(editSize->Text);
    return size > 0;
}

// Генерация массива
void __fastcall TForm1::btnGenerateClick(TObject *Sender)
{
    if(!validateInput())
    {
        ShowMessage("Ошибка ввода данных!");
        return;
    }

    originalArray.clear();

    int size   = StrToInt(editSize->Text);
    int minVal = StrToInt(editMin->Text);
    int maxVal = StrToInt(editMax->Text);

    for(int i = 0; i < size; i++)
        originalArray.push_back(minVal + rand() % (maxVal - minVal + 1));

    currentFileName = "generated";

	Visualizer::drawArray(this, originalArray, -1, originalArray.size());
}

// Сортировка выбранным алгоритмом
void __fastcall TForm1::btnSortSelectedClick(TObject *Sender)
{
    if(originalArray.empty()) return;

    sortedArray = originalArray;

    bool animate = cbAnimation->Checked && sortedArray.size() <= 100;
    int delay = 101 - trackSpeed->Position;

    auto start = chrono::high_resolution_clock::now();

    switch(cbAlgorithms->ItemIndex)
    {
        case 0: Sorting::bubbleSort(sortedArray, this, animate, delay); break;
        case 1: Sorting::insertionSort(sortedArray, this, animate, delay); break;
        case 2: Sorting::selectionSort(sortedArray, this, animate, delay); break;
        case 3: Sorting::shellSort(sortedArray, this, animate, delay); break;
        case 4: Sorting::quickSort(sortedArray, 0, sortedArray.size()-1); break;
    }

    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();

	MemoResults->Lines->Add(
        cbAlgorithms->Text + " : " + FloatToStr(time) + " ms"
	);
	// оставляем отсортированный массив весь зеленым
	Visualizer::drawArray(this, sortedArray, -1, 0);
    ShowMessage("Массив отсортирован!");

	/* автосохранение в Output
	saveToOutputFolder(cbAlgorithms->Text); */
}

// Сортировка всеми (без анимации)
void __fastcall TForm1::btnSortAllClick(TObject *Sender)
{
    if(originalArray.empty()) return;

	MemoResults->Clear();

    for(int i = 0; i < 5; i++)
    {
        vector<int> temp = originalArray;

        auto start = chrono::high_resolution_clock::now();

        switch(i)
        {
            case 0: Sorting::bubbleSort(temp, this, false, 0); break;
            case 1: Sorting::insertionSort(temp, this, false, 0); break;
            case 2: Sorting::selectionSort(temp, this, false, 0); break;
            case 3: Sorting::shellSort(temp, this, false, 0); break;
            case 4: Sorting::quickSort(temp, 0, temp.size()-1); break;
        }

        auto end = chrono::high_resolution_clock::now();
        double time = chrono::duration<double, milli>(end - start).count();

        String sortName = cbAlgorithms->Items->Strings[i];

        MemoResults->Lines->Add(
            sortName + " : " + FloatToStr(time) + " ms"
        );

		sortedArray = temp;
		/* автосохранение
		saveToOutputFolder(sortName); */
	}
}


// сохранение в папку Output
void TForm1::saveToOutputFolder(String sortName)
{
    // Проверяем, есть ли отсортированный массив
    if (sortedArray.empty())
    {
        ShowMessage("Сначала нужно выполнить сортировку!");
        return; // ничего не сохраняем
    }

    // Путь к папке рядом с exe
    String outputFolder = ExtractFilePath(Application->ExeName) + "output\\";

    // Если папки нет — создаём
    if (!DirectoryExists(outputFolder))
    {
        CreateDir(outputFolder);
    }

    // Если файл загружался — берём его имя,
    // если нет — пишем "generated"
    String baseName;

    if (currentFileName != "")
        baseName = currentFileName;
    else
        baseName = "generated";

    // Формируем имена файлов
    String sortedFileName =
        outputFolder + baseName + "_" + sortName + "_sorted.txt";

    String resultFileName =
        outputFolder + baseName + "_" + sortName + "_result.txt";

	// Сохраняем отсортированный массив
    ofstream fileSorted(AnsiString(sortedFileName).c_str());

    for (int i = 0; i < sortedArray.size(); i++)
    {
        fileSorted << sortedArray[i] << " ";
    }

    fileSorted.close();

	// Сохраняем результаты из Memo
    ofstream fileResult(AnsiString(resultFileName).c_str());
    fileResult << AnsiString(MemoResults->Lines->Text).c_str();
    fileResult.close();

	ShowMessage("Файлы сохранены в папку output");
}

// Загрузка массива
void __fastcall TForm1::btnLoadClick(TObject *Sender)
{
	if(OpenDialog1->Execute())
	{
		ifstream file(OpenDialog1->FileName.c_str());
		originalArray.clear();

		int value;
		while(file >> value)
			originalArray.push_back(value);

		file.close();

		// Сохраняем имя файла без расширения
		currentFileName =
			ChangeFileExt(
				ExtractFileName(OpenDialog1->FileName),
				""
			);

		Visualizer::drawArray(this, originalArray, -1, originalArray.size());
    }
}

// save sorted
void __fastcall TForm1::btnSaveSortedClick(TObject *Sender)
{
    if (sortedArray.empty())
    {
        ShowMessage("Нет отсортированного массива!");
        return;
    }

    String sortName = cbAlgorithms->Text;
    saveToOutputFolder(sortName);
}
// save results
void __fastcall TForm1::btnSaveResultsClick(TObject *Sender)
{
    if (MemoResults->Lines->Count == 0)
    {
        ShowMessage("Нет результатов для сохранения!");
        return;
    }

    String sortName = cbAlgorithms->Text;
	saveToOutputFolder(sortName);
}
__fastcall TForm1::~TForm1()
{
}


