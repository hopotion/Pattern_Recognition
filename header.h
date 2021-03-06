#include <iostream>
#include <stdio.h>
void fill(int A[81][9], int i, int j);              //функция заполнения начальной разметкой
void show(int A[81][9]);                            //функция вывода
bool check(int A[81][9]);                           //функция проверки на допустимость (проверка если все метки в объекте вычеркнуты)
void clear(int A[81][9], int B[81], int A2[81]);    //функция вычеркивания
void update(int A[81][9], int B[81]);               //функция обновления матрицы-указателя однозначно заполненых ячеек
void solution(int A[81][9], int d);                 //функция выбора метки при поиске разметки
void copy(int A[81][9], int A3[81][9]);             //функция копирования разметки
void roleback(int A[81][9], int A3[81][9]);         //функция отката в случае неудачи при поиске разметки

void fill(int A[81][9], int i, int j)           //функция заполнения начальной разметкой
{
    for (int k = 0; k <= 8; k++) {
        if (A[i][k] != j) {
            A[i][k] = 0;
        }
    }
}

void show(int A[81][9])                         //функция вывода
{
    for (int i = 0; i <= 80; i++) {
        for (int j = 0; j <= 8; j++) {
            if (A[i][j] != 0) {
                cout << A[i][j];
            }
            else {
                cout << "-";
            }
        }
        cout << "   ";
        if ((i + 1) % 3 == 0) {
            cout << "|   ";
        }
        if ((i + 1) % 9 == 0) {
            cout << endl;
        }
        if ((i + 1) % 27 == 0) {
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
}

bool check(int A[81][9])                        //функция проверки на недопустимость имеющейся разметки
{
    int f = 0;
    for (int i = 0; i <= 80; i++) {
        for (int j = 0; j <= 8; j++) {
            if (A[i][j] == 0) {
                f++;
            }  
        }
        if (f == 9) {
            return false;
        }
        else {
            f = 0;
        }
    }
    return true;
}

void update(int A[81][9], int B[81])            //функция обновления матрицы-указателя однозначно заполненых ячеек
{
    int f = 0;
    for (int n = 0; n <= 80; n++) {
        for (int m = 0; m <= 8; m++) {
            if (A[n][m] == 0) {
                f++;
            }
        }
        B[n] = 0;
        if (f == 8 && B[n] == 0) {
            B[n] = 1;
        }
        f = 0;
    }
}

void clear(int A[81][9], int B[81], int A2[81]) //функция вычеркивания
{
    for (int n = 0; n <= 80; n++) {
        if (B[n] == 1) {
            int x;
            int m = 0;
            while (A[n][m] == 0) {
                m++;
            }
            x = A[n][m];
            for (int k = n - 9; k >= 0; k -= 9) {               //соседство по столбцу сверху
                int s = 0;
                while (A[k][s] != x && s < 9) {
                    s++;
                }
                if (s < 9) {
                    A[k][s] = 0;
                }
            }
            for (int k = n + 9; k <= 80; k += 9) {              //соседство по столбцу снизу
                int s = 0;
                while (A[k][s] != x && s < 9) {
                    s++;
                }
                if (s < 9) {
                    A[k][s] = 0;
                }
            }
            for (int k = n - 1; k >= n - (n % 9); k--) {        //соседство по ряду слева
                int s = 0;
                while (A[k][s] != x && s < 9) {
                    s++;
                }
                if (s < 9) {
                    A[k][s] = 0;
                }
            }
            for (int k = n + 1; k <= n + 8 - (n % 9); k++) {    //соседство по ряду справа
                int s = 0;
                while (A[k][s] != x && s < 9) {
                    s++;
                }
                if (s < 9) {
                    A[k][s] = 0;
                }
            }
            for (int k = 0; k <= 80; k++) {                     //соседство по блоку
                if (A2[k] == A2[n] && k != n) {
                    int s = 0;
                    while (A[k][s] != x && s < 9) {
                        s++;
                    }
                    if (s < 9) {
                        A[k][s] = 0;
                    }
                }
            }
        }
    }
}

void solution(int A[81][9], int d)    //функция выбора метки для поиска разметки
{
    for (int j = 0; j <= 8; j++) {
        if (A[d][j] != 0) {
            for (int k = j + 1; k <= 8; k++) {
                A[d][k] = 0;
            }
        }
    }
}

void copy(int A[81][9], int A3[81][9])          //функция копирования матриц
{
    for (int i = 0; i <= 80; i++) {
        for (int j = 0; j <= 8; j++) {
            A3[i][j] = A[i][j];
        }
    }
}

void roleback(int A[81][9], int A3[81][9])      //функция отката
{
    for (int i = 0; i <= 80; i++) {
        for (int j = 0; j <= 8; j++) {
            A[i][j] = A3[i][j];
        }
    }
}
