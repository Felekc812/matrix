// gcc tests.c p.c -std=c11 -g3 -fsanitize=address -Wall -Wextra -Werror -c
// -lflag -lm -lrt -lpthread -lsubunit

#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = 0;
  result->matrix = NULL;
  if (A->matrix == NULL || A->matrix == NULL) {
    flag = 1;
  } else if (A->columns != A->rows) {
    flag = 2;
  } else {
    double d = 0.0;
    s21_determinant(A, &d);
    if (d == 0) {
      flag = 2;
    } else {
      matrix_t baff;
      matrix_t baff2;
      s21_calc_complements(A, &baff);
      s21_transpose(&baff, &baff2);
      s21_mult_number(&baff2, (1.0 / d), result);
      s21_remove_matrix(&baff);
      s21_remove_matrix(&baff2);
    }
  }
  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = 0;
  result->matrix = NULL;
  if (A->matrix == NULL || A->matrix == NULL) {
    flag = 1;
  } else if (A->columns != A->rows) {
    flag = 2;
  } else {
    // int i, j;
    s21_create_matrix(A->rows, A->columns, result);
    if (A->columns == 1 && A->columns == 1) {
      result->matrix[0][0] = 1;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          int x = pow(-1, i + j);
          matrix_t minor = funk_minor(A->rows, i, j, A);
          for (int i = 0; i < minor.columns; i++) {
            for (int j = 0; j < minor.rows; j++) {
            }
          }
          result->matrix[i][j] = x * fukc_determinant(A->rows - 1, &minor);
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = 0;
  if (A->matrix == NULL || A->matrix == NULL) {
    flag = 1;
  } else if (A->columns != A->rows) {
    flag = 2;
  } else {
    *result = fukc_determinant(A->rows, A);
  }
  return flag;
}

double fukc_determinant(int m, matrix_t *A) {
  double result = 0.0;
  double piece;
  if (m == 1) {
    result = A->matrix[0][0];
  } else if (m == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    for (int j = 0; j < m; j++) {
      matrix_t minor = funk_minor(m, 0, j, A);
      int sign = pow(-1, j);
      piece = (A->matrix[0][j]) * sign * fukc_determinant(m - 1, &minor);
      result += piece;
      s21_remove_matrix(&minor);
    }
  }
  return result;
}

matrix_t funk_minor(int m, int iA, int jA, matrix_t *A) {
  matrix_t result;
  s21_create_matrix(m - 1, m - 1, &result);
  for (int i = 0; i < m; i++) {
    if (i != iA) {
      for (int j = 0; j < m; j++) {
        if (j != jA) {
          if (i < iA) {
            if (j < jA)
              result.matrix[i][j] = A->matrix[i][j];

            else
              result.matrix[i][j - 1] = A->matrix[i][j];

          } else {
            if (j < jA)
              result.matrix[i - 1][j] = A->matrix[i][j];
            else
              result.matrix[i - 1][j - 1] = A->matrix[i][j];
          }
        }
      }
    }
  }

  return result;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->matrix == NULL || B->matrix == NULL) {
    flag = 1;
    result->matrix = NULL;
  } else {
    if (A->columns != B->rows) {
      result->matrix = NULL;
      flag = 2;
    } else {
      int k = s21_create_matrix(A->rows, B->columns, result);

      if (k == 0) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int k = 0; k < A->columns; k++)
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
      } else {
        flag = 1;
        result->matrix = NULL;
      }
    }
  }
  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (A->matrix == NULL) {
    flag = 1;
    result->matrix = NULL;
  } else {
    int k = s21_create_matrix(A->columns, A->rows, result);
    if (k == 0) {
      for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    } else {
      flag = 1;
      result->matrix = NULL;
    }
  }
  return flag;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = 0;
  if (rows > 0 && columns > 0) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(int *));
    }
  } else {
    result->matrix = NULL;
    flag = 1;
  }
  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if ((A->rows == B->rows) && (A->columns == B->columns) && A->matrix != NULL &&
      B->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        float x = A->matrix[i][j] - B->matrix[i][j];
        if (x > 0.0000001 || x < -0.0000001) {
          flag = FAILURE;
          break;
        }
      }
      if (flag == FAILURE) {
        break;
      }
    }
  } else {
    flag = FAILURE;
  }
  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->matrix == NULL || B->matrix == NULL) {
    flag = 1;
    result->matrix = NULL;
  } else {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      int k = s21_create_matrix(A->rows, A->columns, result);
      if (k == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      flag = 2;
      result->matrix = NULL;
    }
  }
  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;
  if (A->matrix == NULL || B->matrix == NULL) {
    flag = 1;
    result->matrix = NULL;
  } else {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      int k = s21_create_matrix(A->rows, A->columns, result);
      if (k == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    } else {
      flag = 2;
      result->matrix = NULL;
    }
  }
  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = 0;
  if (A->matrix == NULL) {
    flag = 1;
    result->matrix = NULL;
  } else {
    int k = s21_create_matrix(A->rows, A->columns, result);
    if (k == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      flag = 2;
      result->matrix = NULL;
    }
  }
  return flag;
}
