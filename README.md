[![Lint and test](https://github.com/nkiryanov/s21_matrix/actions/workflows/ci.yaml/badge.svg)](https://github.com/nkiryanov/s21_matrix/actions/workflows/ci.yaml) [![codecov](https://codecov.io/gh/nkiryanov/s21_matrix/branch/main/graph/badge.svg?token=V5LV3KVG84)](https://codecov.io/gh/nkiryanov/s21_matrix)

# s21_matrix

Работа с матрицами в C

### Структура матрицы на языке C:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

### Функции
| Готовность | Название функции | Сигнатура |
| - | ------ |------------------------------------------------------------------------------------|
| 🟢 | Создание | int s21_create_matrix(int rows, int columns, matrix_t *result); |
| 🟢 | Очистка | void s21_remove_matrix(matrix_t *A); |
| 🟢 | Сравнение | int s21_eq_matrix(matrix_t *A, matrix_t *B); |
| 🟢 | Сложение | int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result); |
| 🟢 | Вычитание | int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result); |
| 🟢 | Умножение на число | int s21_mult_number(matrix_t *A, double number, matrix_t *result); |
| 🟢 | Умножение двух матриц | int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result); |
| 🔴 | Транспонирование | int s21_transpose(matrix_t *A, matrix_t *result); |
| 🔴 | Минор и матрица алгебраических дополнений | int s21_calc_complements(matrix_t *A, matrix_t *result); |
| 🔴 | Определитель | int s21_determinant(matrix_t *A, double *result); |
| 🔴 | Обратная матрица | int s21_inverse_matrix(matrix_t *A, matrix_t *result); |


### Дополнительные определения
- Результат сравнения, сравнение должно происходить вплоть до 7 знака после запятой включительно.
    ```c
    #define SUCCESS 1
    #define FAILURE 0
    ```
- Все операции (кроме сравнения матриц) должны возвращать результирующий код:  
    - 0 - OK
    - 1 - Ошибка, некорректная матрица
    - 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)
