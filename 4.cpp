#include <iostream>
#include <stdio.h>
void fill(int A[81][9], int i, int j);              //функция заполнения начальной разметкой
void show(int A[81][9]);                            //функция вывода
bool check(int A[81][9]);                           //функция проверки на допустимость (проверка если все метки в объекте вычеркнуты)
void clear(int A[81][9], int B[81], int A2[81]);    //функция вычеркивания
void update(int A[81][9], int B[81]);               //функция обновления матрицы-указателя однозначно заполненых ячеек
void solution(int A[81][9], int d);       //функция выбора метки при поиске разметки
void copy(int A[81][9], int A3[81][9]);             //функция копирования разметки
void roleback(int A[81][9], int A3[81][9]);         //функция отката в случае неудачи при поиске разметки
using namespace std;

int main()
{
    int A[81][9];                       //основная матрица
    int A1[81][9];                      //матрица-копия для проверки того что вычеркивание закончилось
    int A2[81];                         //матрица, задающая соседство по блоку
    int A3[81][9];                      //матрица-копия для работы в одном объекте
    int A4[81][9];                      //буферная матрица для проверки отсутсвия элементов в объекте
    
    int A5[81]{ 8,  1,  0,      0,  3,  0,      0,  2,  7,      
                0,  6,  2,      0,  0,  0,      0,  9,  0,
                0,  7,  0,      0,  0,  0,      0,  0,  0,
            
                0,  0,  0,      6,  0,  0,      1,  0,  0,
                0,  0,  0,      0,  0,  0,      0,  0,  4,
                0,  0,  8,      0,  0,  5,      0,  7,  0,
            
                0,  0,  0,      0,  0,  0,      0,  8,  0,
                0,  0,  0,      0,  1,  0,      7,  5,  0,
                0,  0,  0,      0,  7,  0,      0,  4,  2
    };                                                               //матрица ввода
    
    for (int i = 0; i <= 80; i++) {                                 //заполнение матриц всеми возможными метками
        for (int j = 0; j <= 8; j++) {
            A[i][j] = j + 1;
            A1[i][j] = j + 1;
        }
        int c1 = (i % 9) + 1;
        int c2 = ((i - (i % 9)) / 9) + 1;
        if ((c1 == 1 || c1 == 2 || c1 == 3) && (c2 == 1 || c2 == 2 || c2 == 3)) {           //заполнение матрицы, задающей соседство по блоку
            A2[i] = 1;
        }
        else if ((c1 == 4 || c1 == 5 || c1 == 6) && (c2 == 1 || c2 == 2 || c2 == 3)) {
            A2[i] = 2;
        }
        else if ((c1 == 7 || c1 == 8 || c1 == 9) && (c2 == 1 || c2 == 2 || c2 == 3)) {
            A2[i] = 3;
        }
        else if ((c1 == 1 || c1 == 2 || c1 == 3) && (c2 == 4 || c2 == 5 || c2 == 6)) {
            A2[i] = 4;
        }
        else if ((c1 == 4 || c1 == 5 || c1 == 6) && (c2 == 4 || c2 == 5 || c2 == 6)) {
            A2[i] = 5;
        }
        else if ((c1 == 7 || c1 == 8 || c1 == 9) && (c2 == 4 || c2 == 5 || c2 == 6)) {
            A2[i] = 6;
        }
        else if ((c1 == 1 || c1 == 2 || c1 == 3) && (c2 == 7 || c2 == 8 || c2 == 9)) {
            A2[i] = 7;
        }
        else if ((c1 == 4 || c1 == 5 || c1 == 6) && (c2 == 7 || c2 == 8 || c2 == 9)) {
            A2[i] = 8;
        }
        else if ((c1 == 7 || c1 == 8 || c1 == 9) && (c2 == 7 || c2 == 8 || c2 == 9)) {
            A2[i] = 9;
        }
    }
    for (int i = 0; i <= 80; i++) {
        if (A5[i] != 0) {
            for (int j = 0; j <= 8; j++) {
                if (A5[i] != A[i][j]) {
                    A[i][j] = 0;
                }
            }
        }
    }
    //show(A);
    int B[81];
    for (int i = 0; i <= 80; i++) {
        B[i] = 0;
    }
    //char z = 'y';
    /*while (z != 'n') {              //ввод начальной разметки
        cout << endl;
        int n;
        cout << "Enter position (from 1 to 81) : ";
        cin >> n;
        B[n - 1] = 1;
        int m;
        cout << "Enter value (from 1 to 9) : ";
        cin >> m;
        fill(A, n - 1, m);
        fill(A1, n - 1, m);
        cout << endl << "Continue (y/n)? ";
        cin >> z;
    }*/
    cout << endl << endl;
    show(A);
    cout << endl << endl;
    int h = 0;
    for (int i = 0; i <= 80; i++) {             //проверка на полную заполненность матрицы
        if (B[i] == 1) {
            h++;
        }
    }
    if (h == 81) {
        cout << endl << endl << "Done";
        return 0;
    }
    clear(A, B, A2);                            //вычеркивание для начальной разметки
    show(A);
    if (check(A) == false) {                                            //проверка на недопустимость начальной разметки
        cout << endl << endl << "Error - no solution for given data";
        return 0;
    }
    update(A, B);
    int s = 0;
    while (s != 729) {              //цикл - вычеркивание до тех пор, пока матрица не перестанет меняться
        s = 0;
        for (int i = 0; i <= 80; i++) {         //копирование матриц на каждом шаге
            for (int j = 0; j <= 8; j++) {
                if (A1[i][j] == A[i][j]) {
                    s++;
                }
                else {
                    A1[i][j] = A[i][j];
                }
            }
        }
        if (s == 729) {                         //проверка на неизменность матриц на данном и предыдущем шаге
            cout << endl << endl << "Done";
            //getchar();
            break;
        }
        cout << endl << endl;
        clear(A, B, A2);
        show(A);
        if (check(A) == false) {
            cout << endl << endl << "Error - no solution for given data";
            return 0;
        }
        update(A, B);
    }
    h = 0;
    for (int i = 0; i <= 80; i++) {             //проверка на полную заполненность матрицы
        if (B[i] == 1) {
            h++;
        }
    }
    int d = 0;                                  //указатель на первый по счету объект, в котором не определена метка
    for (int i = 0; i <= 80; i++) {
        if (B[i] == 1) {
            d++;
        }
        else {
            break;
        }
    }
    if (h == 81) {
        cout << endl << endl;
        show(A);
        cout << endl << endl << "Finished";
        return 0;
    }
    else {
        copy(A, A3);                                        //копирование перед запуском поиска разметки
        cout << endl << endl << "Looking for solution...";
        solution(A, d);                                  //выбор первой возможной метки в объекте d
        update(A, B);
        cout << endl << endl;
        show(A);
        cout << endl << endl;
    }
    update(A, B);
    while (h != 81) {                   //цикл - поиск допустимой разметки
        clear(A, B, A2);
        update(A, B);
        //getchar();
        if (check(A) == false) {        //если после вычеркивания с выбраной меткой в объекте d получили недопустимую разметку - сделать откат
            cout << endl << endl << "Bad solution - doing a roleback";
            roleback(A, A3);
            update(A, B);
            for (int i = d; i <= 80; i++) {
                if (B[i] == 0) {
                    for (int j = 0; j <= 8; j++) {
                        if (A[i][j] != 0) {
                            A[i][j] = 0;            //вычеркиваем ту метку, которую только что пробовали
                            break;
                        }
                    }
                    break;
                }
            }
            copy(A, A4);
            update(A4, B);
            clear(A4, B, A2);
            if (check(A4) == false) {                                           //если метка была последней в выбраном объекте - решение не найдено
                cout << endl << endl << "Error - no solution for given data";
                return 0;
            }
            copy(A, A3);                                                    //копирование измененной матрицы А
            cout << endl << endl << "Looking for a different solution...";
            cout << endl << endl;
            solution(A, d);              //выбор следующей возможной метки в объекте d
            update(A, B);
            show(A);
            cout << endl << endl;
            update(A, B);
            h = 0;
            for (int i = 0; i <= 80; i++) {
                if (B[i] == 1) {
                    h++;
                }
            }
            continue;
        }
        update(A, B);
        h = 0;
        for (int i = 0; i <= 80; i++) {
            if (B[i] == 1) {
                h++;
            }
        }
        if (h > 81) {
            cout << endl << endl << "Finished";
            return 0;
        }
        cout << endl << endl;
        show(A);
        cout << endl << endl;
        s = 0;
        for (int i = 0; i <= 80; i++) {
            for (int j = 0; j <= 8; j++) {
                if (A1[i][j] == A[i][j]) {
                    s++;
                }
                else {
                    A1[i][j] = A[i][j];
                }
            }
        }
        if (s == 729) {         //если больше ничего не вычеркивается и зарметка все еще допустимая - берем следующий по счету неоднозначный объект и берем в нем первую возможную метку
            d = 0;
            for (int i = 0; i <= 80; i++) {
                if (B[i] == 1) {
                    d++;
                }
                else {
                    break;
                }
            }
            copy(A, A3);
            solution(A, d);
            update(A, B);
            cout << endl << endl;
            show(A);
            cout << endl << endl;
            continue;
        }
    }
    cout << endl << endl << "Finished";
    return 0;
}



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