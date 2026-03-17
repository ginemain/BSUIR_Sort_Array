#ifndef VisualizerH
#define VisualizerH

#include <vector>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>

using namespace std;

class Visualizer
{
public:
    // activeIndex - текущий элемент
    // sortedStart - начало уже отсортированной части справа
    static void drawArray(TForm* form, vector<int>& arr, int activeIndex, int sortedStart);
};

#endif
