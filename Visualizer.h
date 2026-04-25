#ifndef VisualizerH
#define VisualizerH

#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>

class Visualizer
{
public:
    // activeIndex - элемент, который сейчас изменяется
    // sortedStart - с какого индекса начинается уже отсортированная часть справа
    static void drawArray(TForm* form, int* arr, int size, int activeIndex, int sortedStart);
};

#endif


