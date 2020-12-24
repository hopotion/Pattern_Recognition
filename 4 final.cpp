#include <header.h>
using namespace std;

int main()
{
    int A[81][9];                       //основная матрица
    int A1[81][9];                      //матрица-копия для проверки того что вычеркивание закончилось
    int A2[81];                         //матрица, задающая соседство по блоку
    int A3[81][9];                      //матрица-копия для работы в одном объекте
    int A4[81][9];                      //буферная матрица для проверки отсутсвия элементов в объекте
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
    show(A);
    int B[81];
    for (int i = 0; i <= 80; i++) {
        B[i] = 0;
    }
    char z = 'y';
    while (z != 'n') {              //ввод начальной разметки
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
    }
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
            getchar();
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
        getchar();
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
    }
    cout << endl << endl << "Finished";
    return 0;
}
