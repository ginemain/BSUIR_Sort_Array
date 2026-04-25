#include "Visualizer.h"
#include "Unit1.h"

void Visualizer::drawArray(TForm* form, int* arr, int size, int activeIndex, int sortedStart)
{
    // получаем форму
    TForm1* f = dynamic_cast<TForm1*>(form);
    if(f == nullptr) return;

    // получаем Canvas дл€ рисовани€
    TCanvas* canvas = f->paintBox->Canvas;
    if(canvas == nullptr) return;

    int width = f->paintBox->Width;
    int height = f->paintBox->Height;

    // очищаем область рисовани€
    canvas->Brush->Color = clWhite;
    canvas->FillRect(TRect(0, 0, width, height));

    // если массив пустой Ч ничего не рисуем
    if(arr == nullptr || size == 0) return;

    int n = size;
    int barWidth = width / n;
    if(barWidth < 1) barWidth = 1;

    // находим максимальный элемент (дл€ масштабировани€)
    int maxVal = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] > maxVal) maxVal = arr[i];
    }
    if(maxVal == 0) maxVal = 1;

    for(int i = 0; i < n; i++)
    {
        // вычисл€ем высоту столбца
        int barHeight = (double)arr[i] / maxVal * (height - 10);
        if(barHeight < 1) barHeight = 1;

        // выбор цвета
        if(i == activeIndex)
		{
            canvas->Brush->Color = clRed;
        }
        else if(i >= sortedStart)
        {
            canvas->Brush->Color = (TColor)RGB(100, 220, 120);
        }
        else
        {
            canvas->Brush->Color = clBlue;
        }

        // рисуем пр€моугольник
        canvas->Rectangle(
            i * barWidth,
            height - barHeight,
            (i + 1) * barWidth,
            height
        );
    }
}
