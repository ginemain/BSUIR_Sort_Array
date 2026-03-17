#include "Visualizer.h"
#include "Unit1.h"
#include <algorithm>

using namespace std;

// функция отрисовки массива
// activeIndex - элемент, который сейчас изменяется
// sortedStart - с какого индекса начинается уже отсортированная часть справа
void Visualizer::drawArray(TForm* form, vector<int>& arr, int activeIndex, int sortedStart)
{
    // получаем форму
    TForm1* f = dynamic_cast<TForm1*>(form);

    // получаем Canvas для рисования
    TCanvas* canvas = f->paintBox->Canvas;

    int width = f->paintBox->Width;
    int height = f->paintBox->Height;

    // очищаем область рисования
    canvas->Brush->Color = clWhite;
    canvas->FillRect(TRect(0, 0, width, height));

    // если массив пустой — ничего не рисуем
    if(arr.empty()) return;

    int n = arr.size();

    // ширина одного столбца
    int barWidth = width / n;

    // находим максимальный элемент (для масштабирования)
    int maxVal = *max_element(arr.begin(), arr.end());

    for(int i = 0; i < n; i++)
    {
        // вычисляем высоту столбца
        int barHeight = (double)arr[i] / maxVal * (height - 10);

		// ВЫБОР ЦВЕТА

        // если элемент сейчас активный (сравнивается / меняется)
        if(i == activeIndex)
        {
            canvas->Brush->Color = clRed;
        }
        // если элемент уже находится в отсортированной части справа
        else if(i >= sortedStart)
        {
			canvas->Brush->Color = (TColor)RGB(100, 220, 120); // зеленым делаем
        }
        // обычные элементы
        else
        {
            canvas->Brush->Color = clBlue;
        }

        // рисуем прямоугольник
        canvas->Rectangle(
            i * barWidth,
            height - barHeight,
            (i + 1) * barWidth,
            height
        );
    }
}
