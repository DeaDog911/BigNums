#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>


void print_num(unsigned char num[], int sign) {
	int i = 0;
	while (num[i] != 100) {
        if (sign && num[0] != 0 && i == 0) {
            printf("-");
        }
        if (num[i] >= 0 && num[i] <= 9) {
            printf("%d", num[i]);
        }else {
            printf("%c", 55 + num[i]);
        }
		i++;
	}
}

void copy(unsigned char * num1, unsigned char num2[]) {
    int i = 0;
    while (num2[i] != 100) {
        num1[i] = num2[i];
        i++;
    }
    num1[i] = 100;
}

int get_last_index(unsigned char num[]) {
    int i = 0;
    while (num[i] != 100) {
        i++;
    }
    return i;
}

void normalize(unsigned char * num) {
    int len = get_last_index(num);
    if (len > 0) {
        if (num[0] == 0) {}
        else if (num[0] == 0) {
            for (int i = 0; i < len; i++) {
                num[i] = num[i+1];
            }
        }
    }
}

void reverse(unsigned char * res) {
    unsigned char res2[1000];
    int i = 0, j = 0;
    while (res[i] != 100) i++;
    while (res[i-1] == 0) i--;
    i--;
    while (i >= 0) {
        res2[j] = res[i];
        i--;
        j++;
    }
    res2[j] = 100;
    i = 0;
    while(res2[i] != 100) {
        res[i] = res2[i];
        i++;
    }
    res[i] = 100;
    if (res[0] == 100) {
        res[0] = 0;
        res[1] = 100;
    }
}

int cmp(unsigned char num1[], unsigned char num2[]) {
    int size_num1 = get_last_index(num1);
    int size_num2 = get_last_index(num2);
    int r = -1;
    if (size_num1 > size_num2) r = 1;
    else if(size_num1 < size_num2) r = -1;
    else {
        int i = 0;
        while (num1[i] == num2[i] && r == -1) {
            if (num1[i] == 100) r = 0;
            i++;
        }
        if (r == -1) {
            if (num1[i] > num2[i]) r = 1;
            else if (num1[i] < num2[i]) r = -1;
        }
    }
    return r;
}



void subtract(unsigned char num1_0[], unsigned char num2[], unsigned char * res) {
    unsigned char num1[1000];
    copy(num1, num1_0);

    if (cmp(num1, num2) == 0){
        res[0] = 0;
        res[1] = 100;
        return;
    }
    res[0] = 100;
    int num1_end = get_last_index(num1);
    int num2_end = get_last_index(num2);
    int t, i = 0;
    unsigned char n1, n2;
    while(num1_end > 0 || num2_end > 0) {
        num1_end--;
        num2_end--;
        if (num1_end >= 0) {
            n1 = num1[num1_end];
        }else {
            n1 = 0;
        }
        if(num2_end >= 0) {
            n2 = num2[num2_end];
        }else {
            n2 = 0;
        }
        t = n1 - n2;
        int a = 0;
        if (t < 0) {
            int j = num1_end - 1;
            while (j >= 0) {
                if (num1[j] > 0) {
                    num1[j] = num1[j] - 1;
                    a = 1;
                    break;
                }else {
                    num1[j] = 9;
                }
                j--;
            }
            if (a) {
                res[i] = 10 + n1 - n2;
            }
        }else {
            res[i] = t;
        }
        i++;
    }
    res[i] = 100;
    reverse(res);
}

void sum(unsigned char num0[], unsigned char num2[], unsigned char * res) {
    int num1_end = get_last_index(num0);
    unsigned char num1[1000];
    for (int i = 0; i < num1_end; i++) {
        num1[i] = num0[i];
    }
    res[0] = 100;
    num1[num1_end] = 100;
    int num2_end = get_last_index(num2);
    int t = 0, i = 0;
    while (num1_end > 0 || num2_end > 0 || t > 0) {
        num1_end--;
        num2_end--;
        unsigned char n1, n2;

        if (num1_end >= 0) {
            n1 = num1[num1_end];
        } else {
            n1 = 0;
        }
        if (num2_end >= 0) {
            n2 = num2[num2_end];
        } else {
            n2 = 0;
        }
        if (n1 + n2 >= 0 || t > 0) {
            res[i] = (t + n1 + n2) % 10;
            if (res[i] == t) t = 0;
            t = (t + n1 + n2) / (10);
            i++;
        }
    }
    res[i] = 100;
    reverse(res);
}

void multi(unsigned char num0[], unsigned char num2[], unsigned char * res0) {
    unsigned char num1[1000];
    for (int i = 0; i < 1000; i++ ){
        num1[i] = num0[i];
    }
    if(num2[0] == 0 || num1[0] == 0) {
        res0[0] = 0;
        res0[1] = 100;
        return;
    }
    res0[0] = 100;
    int num1_end;
    int num2_end = get_last_index(num2);
    unsigned char res[1000];
    res[0] = 100;
    int t = 0, i, k = 0;
    num2_end--;

    while (num2_end >= 0) {
        i = 0;
        num1_end = get_last_index(num1);
        num1_end--;
        for (int l = k; l > 0; l--) {
            res[i] = 0;
            i++;
        }
        while (num1_end >= 0 || t > 0) {
            unsigned char n1 = num1[num1_end];
            unsigned char n2 = num2[num2_end];
            if (num1_end < 0) n1 = 0;
            if (num2_end < 0) n2 = 0;

            unsigned char r = (t + n1 * n2) % 10;
            res[i] = r;
            t = (t + n1 * n2) / 10;
            i++;
            num1_end--;
        }
        k++;
        num2_end--;
        res[i] = 100;
        reverse(res);
        sum(res0, res, res0);
        res[0] = 100;
    }
}

void divide(unsigned char num0[], unsigned char num2[], unsigned char * res, unsigned char * rem) {
    unsigned char num1[1000];
    unsigned char error[] = {150, 100};
    for(int i = 0; i < 1000; i++) {
        num1[i] = num0[i];
    }
    unsigned char null[] = {0, 100};
    copy(rem, null);
    if (cmp(num1, num2) == -1) {
        copy(res, null);
        copy(rem, num1);
        return;
    }
    if (cmp(num2, null) == 0) {
        printf("\nНа ноль делить нельзя!!!");
        copy(res, error);
        return;
    }
    if (cmp(num1, null) == 0) {
        copy(res, null);
        return;
    }

    int num2_length = get_last_index(num2);
    unsigned char num1_sub[1000];

    copy(num1_sub, num1);
    num1_sub[num2_length] = 100;

    unsigned char res0[1000];
    unsigned char res_temp[1000]; // результат умноженя числа 2 на цифру общего результата

    if (cmp(num1_sub, num2) == -1) {
        num1_sub[num2_length] = num1[num2_length];
        num1_sub[num2_length+1] = 100;
    }

    int num1_next_digit = get_last_index(num1_sub);
    int i = 0;
    int res_digit = 1;
    for (; res_digit < 10; res_digit++) {
        res0[0] = res_digit;
        res0[1] = 100;

        multi(num2, res0, res_temp);
        subtract(num1_sub, res_temp, rem);

        if (cmp(rem, num2) == -1)
        {
            copy(num1_sub, rem);
            int num1_sub_length = get_last_index(num1_sub);
            res[i] = res_digit;
            res[i + 1] = 100;
            i++;
            res_digit = -1;
            if (num1[num1_next_digit] == 100) {
                break;
            }
            num1_sub[num1_sub_length] = num1[num1_next_digit];
            num1_sub[num1_sub_length + 1] = 100;
            num1_next_digit++;
        }else {

        }
    }
}

void input_num(unsigned char * num, int * sign, int num_number) {
    *sign = 0;
    if (num_number < 3) {
        printf("Введите число %d:\n", num_number);
    }else {
        printf("Введите систему счисления :\n");
    }
    int i = 0, len = 0;
    int is_null = 0;
    while (1) {
        int key = getch();
        if (key >= '0' && key <= '9') {
            if (i == 0 && key == '0') {
                is_null = 1;
                printf("%c", key);
                num[i] = key - '0';
                i++;
                len++;
            }
            else if (!is_null && (key != '0' || (i > 0 && key == '0'))) {
                printf("%c", key);
                num[i] = key - '0';
                i++;
                len++;
            }
        }
        else if (key == '-' && num_number < 3 && len == 0) {
            if(!(*sign)) {
                *sign = 1;
                len++;
                printf("-");
            }
        }
        else if (key == 8) {
            printf("\b \b");
            if (is_null) {
                is_null = 0;
            }
            if (i > 0)
                i--;
            if (len > 0) {
                len--;
            }
            if (len == 0) {
                *sign = 0;
            }
        } else if (key == 13) {
            break;
        }
    }
    num[i] = 100;
    printf("\n");
}

void percent(unsigned char num1[], unsigned char num2[], unsigned char * res) {
    unsigned char rem[1000];
    unsigned char hundred[] = {1, 0, 0, 100};

    unsigned char num1_1[999];
    unsigned char num1_2[3];

    int num1_length = get_last_index(num1);
    int i;
    for (i = 0; i < num1_length-2; i++) {
        num1_1[i] = num1[i];
    }
    num1_1[i] = 100;
    if (i == 0) {
        num1_1[0] = 0;
        num1_1[1] = 100;
    }
    int j;
    for (i = num1_length-2, j = 0; i < num1_length; i++, j++) {
        num1_2[j] = num1[i];
    }
    num1_2[j] = 100;
    normalize(num1_2);

    unsigned char num1_1_res[1000];
    num1_1_res[0] = 100;
    unsigned char num1_2_res[10];
    unsigned char num1_2_2_res[10];

    multi(num1_1, num2, num1_1_res);
    multi(num1_2, num2, num1_2_res);
    divide(num1_2_res, hundred, num1_2_2_res, rem);

    sum(num1_1_res, num1_2_2_res, res);
}

void raise(unsigned char num1_0[], unsigned char num2_0[], unsigned char * res) {
    unsigned char num1[1000];
    for(int i = 0; i < 1000; i++) {
        num1[i] = num1_0[i];
    }
    unsigned char num2[1000];
    for(int i = 0; i < 1000; i++) {
        num2[i] = num2_0[i];
    }
    unsigned char one[] = {1, 100};
    unsigned char null[] = {0, 100};
    if (cmp(num2, one) == 0) {
        copy(res, num1);
    }else if (cmp(num2, null) == 0) {
        copy(res, one);
    }else {
        copy(res, num1);
        while (cmp(num2, one) != 0) {
            multi(res, num1, res);
            subtract(num2, one, num2);
        }
        if(res[0] == 0) {
            res[0] = 150;
            res[1] = 100;
        }
    }
}

void sqr(unsigned char x[], unsigned char * res) {
    unsigned char null[] = {0, 100}; // 100 - конец числа
    //cmp - сравнение чисел
    // если число равно нулю, возвращаем ноль
    if (cmp(x, null) == 0) {
        copy(res, null); // копируем в результат ноль
        return;
    }
    unsigned char S[1000];
    unsigned char two[] = {2, 100};
    unsigned char rem[1000];
    copy(S, x); // s = x
    unsigned char a[1000];
    unsigned char one[] = {1, 100};
    copy(a, one); // a = 1
    unsigned char b[1000];
    copy(b, x); // b = x
    unsigned char sub_res[1000];
    unsigned char sum_res[1000];
    unsigned char b1[1000];
    int cmp_res = cmp(a, b);
    // цикл работает пока числа a и b не равны
    while (cmp_res != 0) {
        // если a > b, то вычитаем из a b, иначе - из b вычитаем a
        if (cmp_res == 1) {
            subtract(a, b, sub_res);
        } else {
            subtract(b, a, sub_res);
        }
        // складываем a и b и записываем результат в sum_res
        sum(a, b, sum_res);
        // делим sum_res на два, а результат записываем в a
        divide(sum_res, two, a, rem);
        //если a равно b выходим из цикла
        if (cmp(a, b) == 0) {
            break;
        }
        copy(b1, b);
        divide(S, a, b, rem);
        // если b не изменился, то выходим из цикла
        if(cmp(b1, b) == 0) {
            break;
        }
        cmp_res = cmp(a, b);
    }
    sum(a, b, sum_res);
    divide(sum_res, two, res, rem);
}

int bnum_to_int(unsigned char num[]) {
    int r = 0;
    int j = 0,k;
    while (num[j] != 100) {
        j++;
    }
    j--;
    k = 0;
    while (j >= 0) {
        r += num[j] * (int) pow(10, k);
        j--; k++;
    }
    return r;
}

void to_ss(unsigned char num1[], unsigned char num2[], unsigned char * res) {
    unsigned char one[] = {1, 100};
    if (cmp(num2, one) == 1) {
        unsigned char div_res[1000];
        copy(div_res, num1);
        unsigned char rem[1000];
        rem[0] = 100;
        int i = 0;
        while (cmp(div_res, num2) >= 0) {
            divide(div_res, num2, div_res, rem);
            res[i] = bnum_to_int(rem);
            i++;
        }
        res[i] = bnum_to_int(div_res);
        res[i + 1] = 100;
        reverse(res);
    }
}


void print_menu(int operation_code) {
    printf("\nВыберите действие\n");

    printf(operation_code == 1 ? "1. Сложение    <--\n" : "1. Сложение\n");
    printf(operation_code == 2 ? "2. Вычитание    <--\n" : "2. Вычитание\n");
    printf(operation_code == 3 ? "3. Деление    <-- \n" : "3. Деление\n");
    printf(operation_code == 4 ? "4. Умножение    <-- \n" : "4. Умножение\n");
    printf(operation_code == 5 ? "5. Остаток от деления    <-- \n" : "5. Остаток от деления\n");
    printf(operation_code == 6 ? "6. Процент от числа    <-- \n" : "6. Процент от числа\n");
    printf(operation_code == 7 ? "7. Взять корень    <-- \n" : "7. Взять корень\n");
    printf(operation_code == 8 ? "8. Возвести в степень    <-- \n" : "8. Возвести в степень\n");
    printf(operation_code == 9 ? "9. Ввести число 1    <-- \n" : "9. Ввести число 1 \n");
    printf(operation_code == 10 ? "A. Ввести число 2    <-- \n" : "A. Ввести число 2\n");
    printf(operation_code == 11 ? "B. Изменить систему счисления для вывода результата    <-- \n"
    : "B. Изменить систему счисления для вывода результата\n");
    printf(operation_code == 12 ? "C. Выход    <-- \n" : "С. Выход\n");
}

void make_operation(unsigned char * num1, unsigned char * num2, int * sign1, int * sign2, unsigned char * ss, int operation_code) {
    unsigned char res[10000];
    unsigned char rem[10000];
    int sign_res = 0;
    int s = 0;
    int error = 0;
    unsigned char null[] = {0, 100};
    unsigned char one[] = {1, 100};
    unsigned char n36[] = {3, 6, 100};

    res[0] = 100;
    rem[0] = 100;

    if (operation_code >= 1 && operation_code <= 8 && operation_code != 7) {
        if (num1[0] == 100) {
            printf("\n");
            input_num(num1, sign1, 1);
        }
        if (num2[0] == 100) {
            printf("\n");
            input_num(num2, sign2, 2);
        }
    }
    int cmp_res;
    switch (operation_code) {
        case 1: // Сложение
            cmp_res = cmp(num1, num2);
            if (!*sign1 && !*sign2) {
                sum(num1, num2, res);
                sign_res = 0;
            }
            else if (*sign1 && *sign2) {
                sum(num1, num2, res);
                sign_res = 1;
            }
            else if (*sign1 && !*sign2) {
                if (cmp_res == 1) {
                    subtract(num1, num2, res);
                    sign_res = 1;
                }else {
                    subtract(num2, num1, res);
                    sign_res = 0;
                }
            }
            else if (!*sign1 && *sign2) {
                if (cmp_res == 1) {
                    subtract(num1, num2, res);
                    sign_res = 0;
                }else {
                    subtract(num2, num1, res);
                    sign_res = 1;
                }
            }
            break;
        case 2: // Вычитание
            cmp_res = cmp(num1, num2);
            if (!*sign1 && !*sign2) { // + +
                if (cmp_res == 1) {
                    subtract(num1, num2, res);
                    sign_res = 0;
                }else {
                    subtract(num2, num1, res);
                    sign_res = 1;
                }
            }
            else if (*sign1 && *sign2) {
                if (cmp_res == 1) {
                    subtract(num1, num2, res);
                    sign_res = 1;
                }else {
                    subtract(num2, num1, res);
                    sign_res = 0;
                }
            }
            else if (*sign1 && !*sign2) {
                sum(num1, num2, res);
                sign_res = 1;
            }
            else if (!*sign1 && *sign2) {
                sum(num1, num2, res);
                sign_res = 0;
            }
            break;
        case 3: // Деление
            if(cmp(num2, null) != 0) {
                divide(num1, num2, res, rem);
                if (*sign1 == *sign2) {
                    sign_res = 0;
                }else {
                    sign_res = 1;
                }
            }else {
                printf("\nНа ноль делить нельзя!!!");
                error = 1;
            }
            break;
        case 4: // Умножение
            multi(num1, num2, res);
            if (*sign1 == *sign2) {
                sign_res = 0;
            }else {
                sign_res = 1;
            }
            break;
        case 5: // Остаток от деления
            if(cmp(num2, null) != 0) {
                divide(num1, num2, rem, res);
                if (*sign1 == *sign2) {
                    sign_res = 0;
                }else {
                    sign_res = 1;
                }
            }else {
                printf("\nНа ноль делить нельзя!!!");
                error = 1;
            }
            break;
        case 6: // Процент от числа
            if (!*sign2) {
                percent(num1, num2, res);
                sign_res = *sign1;
            }else {
                printf("\nЧисло 2 должно быть неотрицательным");
                error = 1;
            }
            break;
        case 7: // Взять корень
            if (num1[0] == 100) {
                printf("\n");
                input_num(num1, sign1, 1);
            }
            if(!*sign1) {
                sqr(num1, res);
                sign_res = 0;
            }else {
                printf("\nЧисло 1 должно быть неотрицательным");
                error = 1;
            }
            break;
        case 8: // Возвести в степень
            if(!*sign2) {
                if(!*sign1) {
                    sign_res = 0;
                }else {
                    unsigned char two[] = {2, 100};
                    divide(num2, two, res, rem);
                    if (rem[0] == 1) {
                        sign_res = 1;
                    }else {
                        sign_res = 0;
                    }
                }
                raise(num1, num2, res);
            }else {
                printf("\nЧисло 2 должно быть неотрицательным");
                error = 1;
            }
            break;
        case 9:  // Ввести число 1
            printf("\n");
            input_num(num1, sign1,1);
            break;
        case 10: // Ввести число 2
            printf("\n");
            input_num(num2, sign2, 2);
            break;
        case 11: // Ввести сс
            do {
                printf("\nМаксимальная система счисления - 36-ричная\n");
                input_num(ss, &s, 3);
            }while(!(cmp(ss, one) == 1 && cmp(ss, n36) <= 0));
            break;
        case 12: // Выход
            exit(0);
    }
    if (operation_code < 9) {
        if (!error) {
            if (res[0] != 150) {
                to_ss(res, ss, res);
                printf("\nРезультат: ");
                print_num(res, sign_res);
            }else {
                printf("\n Результат слишком большой\n");
            }
        }
        getch();
    }
}

void print_nums(unsigned char * num1, unsigned char * num2, int sign1, int sign2, unsigned char * ss) {
    printf("\nЧисло 1: ");
    if (num1[0] == 100)
        printf("не введено");
    else
        print_num(num1, sign1);
    printf("\nЧисло 2: ");
    if (num2[0] == 100)
        printf("не введено");
    else
        print_num(num2, sign2);
    printf("\nСистема счисления для вывода результата: ");
    print_num(ss, 0);
    printf("\n");
}

int main() {
    system("chcp 65001 > nul");
    unsigned char num1[1000];
    unsigned char num2[1000];

    num1[0] = 100;
    num2[0] = 100;

    int sign1, sign2;
    const int OPERATION_CODE_START = 1;
    const int OPERATION_CODE_END = 12;

    const int ARROWS_CODE = 224;
    const int KEY_UP = 72;
    const int KEY_DOWN = 80;
    const int ENTER = 13;
    const int ESCAPE = 27;
    int operation_code = 1;
    unsigned char ss[1000];
    ss[0] = 1;
    ss[1] = 0;
    ss[2] = 100;
    while (1) {
        system("cls");
        printf("Программа калькулятор\n");
        print_nums(num1, num2, sign1, sign2, ss);
        print_menu(operation_code);
        int btn_code = getch();
        if (btn_code == ARROWS_CODE) {
            btn_code = getch();
            if (btn_code == KEY_UP) {
                if (operation_code > OPERATION_CODE_START) {
                    operation_code--;
                }
                else {
                    operation_code = OPERATION_CODE_END;
                }
            }
            else if (btn_code == KEY_DOWN) {
                if (operation_code < OPERATION_CODE_END) {
                    operation_code++;
                }
                else {
                    operation_code = OPERATION_CODE_START;
                }
            }
        }
        else if (btn_code >= 49 && btn_code <= 57) {
            operation_code = btn_code - 48;
        }
        else if (btn_code >= 97 && btn_code <= 99) {
            operation_code = btn_code - 87;
        }
        else if (btn_code == ENTER) {
            make_operation(num1, num2, &sign1, &sign2, ss, operation_code);
        }
        else if (btn_code == ESCAPE) {
            break;
        }
    }

	return 0;
}
