#include <iostream>
#include <hayai/hayai.hpp>

/*
Текст задания:

Измерить в прямом и обычном (с кешем) режиме производительность чтения из файла максимального размера
случайно расположенных блоков. Для чтения создать вручную файл размером несколько гигабайт, желательно
больше размера оперативной памяти. Сравнить результаты на механическом жёстком диске, USB Flash диске и,
по возможности, SSD на высокопроизводительном интерфейсе (PCI-E).
*/

int main()
{
    std::cout << "Start..." << std::endl;

    hayai::ConsoleOutputter consoleOutputter;
    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();

    return 0;
}
