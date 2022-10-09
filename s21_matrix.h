#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define BAD_Matrix 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;
//создание матрици
int s21_create_matrix(int rows, int columns, matrix_t *result);
// удаление матрици
void s21_remove_matrix(matrix_t *A);
// сравнения матрици
int s21_eq_matrix(matrix_t *A, matrix_t *B);
//сложение матрици
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// вычитание матрици
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// умножение на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// умножение мартици на матрицу
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// транспортирование, переворот матрици
int s21_transpose(matrix_t *A, matrix_t *result);
// Минор матрицы и матрица алгебраических дополнени
int s21_calc_complements(matrix_t *A, matrix_t *result);
// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);
// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//Функции поддержки
matrix_t funk_minor(int m, int im, int jm, matrix_t *arr);
double fukc_determinant(int m, matrix_t *arr);

#endif  // _SRC_S21_MATRIX_H_