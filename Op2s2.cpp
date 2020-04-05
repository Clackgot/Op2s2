// Op2s2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <windows.h>
#include "Shop.h"


void cursorVisible(bool cond)
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = cond;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

template<typename type > type getValue(std::string s)
{
    while (true) // Цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        std::cout << s << ": ";
        type a;
        std::cin >> a;
        if (std::cin.fail()) // Если предыдущее извлечение оказалось неудачным,
        {
            //system("cls");
            std::cin.clear(); // То возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // Удаляем значения предыдущего ввода из входного буфера
        }
        else // Eсли всё хорошо, то возвращаем a
            return a;
    }
}

template<typename type > type getValue()
{
    while (true) // Цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        type a;
        std::cin >> a;
        if (std::cin.fail()) // Если предыдущее извлечение оказалось неудачным,
        {
            system("cls");
            std::cin.clear(); // То возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // Удаляем значения предыдущего ввода из входного буфера
        }
        else // Eсли всё хорошо, то возвращаем a
            return a;
    }
}

int drawMain()
{
    int mode = -1;
    do
    {
        system("cls");
        printf("1.Вывести все товары\n");
        printf("2.Вывести продукты\n");
        printf("3.Вывести инструменты\n");
        printf("4.Сортировать инструменты по массе\n");
        printf("5.Сортировать продукты по жирности\n");
        printf("6.Сортировать товары по номеру\n");
        printf("7.Удалить инструменты с массой\n");
        printf("8.Удалить товары с наименованием\n");
        printf("0.Выход\n");
        std::cout << ">>";
        mode = getValue<int>();
    } while (!(mode >= 0 && mode < 9));
    return mode;
}

int main()
{
	setlocale(LC_ALL, "Rus");
    cursorVisible(false);

	auto shop = Shop("Магнит");

	shop.Load();

    int mode = -1;
    
    
    while (mode == -1)
    {
        mode = drawMain();

        switch (mode)
        {
        case 1://Вывести все товары
            system("cls");
            shop.printGoods();
            system("pause");
            mode = -1;
            break;
        case 2://Вывести продукты
            system("cls");
            shop.printFoodGoods();
            system("pause");
            mode = -1;
            break;
        case 3://Вывести инструменты
            system("cls");
            shop.printInstrumentalGoods();
            system("pause");
            mode = -1;
            break;
        case 4://Сортировать инструменты по массе
            shop.SortInstrumentalGoodsByWeight([]()->int {int x = -1; while (!(x > 0 && x < 3))x = getValue<int>("Тип сортировки(0/1)"); return x; }());
            system("pause");
            mode = -1;
            break;
        case 5://Сортировать продукты по жирности
            shop.SortFoodGoodsByFat([]()->int {int x = -1; while (!(x > 0 && x < 3))x = getValue<int>("Тип сортировки(0/1)"); return x; }());
            system("pause");
            mode = -1;
            break;
        case 6://Сортировать товары по номеру
            shop.SortGoodsById([]()->int {int x = -1; while (!(x > 0 && x < 3))x = getValue<int>("Тип сортировки(0/1)"); return x; }());
            system("pause");
            mode = -1;
            break;
        case 7://Удалить инструменты с массой
            shop.RemoveInstrumentalGoodByWeight([]()->float {float x = -1; x = getValue<float>("Масса инструмента"); return x; }());
            system("pause");
            mode = -1;
            break;
        case 8://Удалить товары с наименованием
            shop.RemoveFoodGoodByName([]()->std::string {
                std::string name = "";
                std::cout << "Наименование товара: ";
                while (name == "")
                {
                    std::cin >> name;
                }
                return name;
                }());
            system("pause");
            mode = -1;
            break;
        default:
            break;
        }

    }

	shop.Save();
}

