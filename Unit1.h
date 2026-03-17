#ifndef Unit1H
#define Unit1H
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>

#include <vector>
using namespace std;

#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Forms.hpp>

// Главная форма приложения
class TForm1 : public TForm
{
public:
	__fastcall TForm1(TComponent* Owner);
	__fastcall ~TForm1();

__published: // Компоненты формы

    // Кнопки
    TButton *btnGenerate;       // Генерация массива
    TButton *btnSortSelected;   // Сортировка выбранным алгоритмом
    TButton *btnSortAll;        // Сортировка всеми алгоритмами
    TButton *btnSaveSorted;     // Сохранить отсортированный массив
    TButton *btnSaveResults;    // Сохранить результаты времени
    TButton *btnLoad;           // Загрузка массива из файла

    // Выпадающий список алгоритмов
    TComboBox *cbAlgorithms;

    // Поля ввода
    TEdit *editSize;   // Размер массива
    TEdit *editMin;    // Минимальное значение
    TEdit *editMax;
	TMemo *MemoResults;

    // Скорость анимации
    TTrackBar *trackSpeed;

    // Включение анимации
    TCheckBox *cbAnimation;

    // Область визуализации
    TPaintBox *paintBox;
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;

    // Обработчики событий кнопок
    void __fastcall btnGenerateClick(TObject *Sender);
    void __fastcall btnSortSelectedClick(TObject *Sender);
    void __fastcall btnSortAllClick(TObject *Sender);
    void __fastcall btnSaveSortedClick(TObject *Sender);
	void __fastcall btnSaveResultsClick(TObject *Sender);
	void __fastcall btnLoadClick(TObject *Sender);

private:

	// Исходный массив
    vector<int> originalArray;

    // Отсортированный массив
    vector<int> sortedArray;

    // Имя исходного файла (без расширения)
    String currentFileName;

    // Проверка корректности ввода
    bool validateInput();

    // Сохранение результатов в папку output
	void saveToOutputFolder(String sortName);
};

extern PACKAGE TForm1 *Form1;

#endif
