#include "algebra.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b) {
    // 检查矩阵a和b的行数和列数是否相等
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0); // 返回一个空矩阵表示错误
    }

    Matrix result; // 定义结果矩阵
    result.rows = a.rows;
    result.cols = a.cols;

    // 执行矩阵加法
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result; // 返回结果矩阵
}

Matrix sub_matrix(Matrix a, Matrix b) {
    // 检查矩阵a和b的行数和列数是否相等
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0); // 返回一个空矩阵表示错误
    }

    Matrix result; // 定义结果矩阵
    result.rows = a.rows;
    result.cols = a.cols;

    // 执行矩阵减法
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }

    return result; // 返回结果矩阵
}

Matrix mul_matrix(Matrix a, Matrix b) {
    // 检查矩阵a的列数是否等于矩阵b的行数
    if (a.cols != b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0); // 返回一个空矩阵表示错误
    }

    Matrix result; // 定义结果矩阵
    result.rows = a.rows;
    result.cols = b.cols;

    // 初始化结果矩阵的所有元素为0
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            result.data[i][j] = 0.0;
        }
    }

    // 执行矩阵乘法
    for (int i = 0; i < result.rows; ++i) { // 遍历a的行
        for (int j = 0; j < result.cols; ++j) { // 遍历b的列
            for (int k = 0; k < a.cols; ++k) { // 遍历a的列/b的行
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result; // 返回结果矩阵
}

Matrix scale_matrix(Matrix a, double k) {
    Matrix result; // 定义结果矩阵
    result.rows = a.rows;
    result.cols = a.cols;

    // 将矩阵a中的每个元素与标量k相乘
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }

    return result; // 返回结果矩阵
}

Matrix transpose_matrix(Matrix a) {
    Matrix result; // 定义结果矩阵
    result.rows = a.cols; // 转置后，行变成原矩阵的列数
    result.cols = a.rows; // 转置后，列变成原矩阵的行数

    // 执行矩阵转置操作
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[j][i] = a.data[i][j]; // 交换行列索引
        }
    }

    return result; // 返回转置后的矩阵
}

double det_matrix(Matrix a) {
    // 检查是否为方阵
    if (a.rows != a.cols || a.rows == 0) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    
    // 基础情况：1x1矩阵
    if (a.rows == 1) {
        return a.data[0][0];
    }

    // 基础情况：2x2矩阵
    if (a.rows == 2) {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    // 基础情况：3x3矩阵
    else if (a.rows == 3) {
        return a.data[0][0] * (a.data[1][1] * a.data[2][2] - a.data[1][2] * a.data[2][1])
             - a.data[0][1] * (a.data[1][0] * a.data[2][2] - a.data[1][2] * a.data[2][0])
             + a.data[0][2] * (a.data[1][0] * a.data[2][1] - a.data[1][1] * a.data[2][0]);
    }
    // 对于更大的方阵，使用递归的Laplace展开
    else {
        double det = 0.0;
        for (int j = 0; j < a.cols; ++j) {
            Matrix submatrix;
            submatrix.rows = a.rows - 1;
            submatrix.cols = a.cols - 1;
            
            // 创建子矩阵
            for (int i = 1; i < a.rows; ++i) {
                for (int k = 0, l = 0; k < a.cols; ++k) {
                    if (k != j) {
                        submatrix.data[i-1][l++] = a.data[i][k];
                    }
                }
            }
            
            det += pow(-1, j) * a.data[0][j] * det_matrix(submatrix);
        }
        return det;
    }
}

Matrix create_submatrix(Matrix a, int exclude_row, int exclude_col) {
    Matrix submatrix;
    submatrix.rows = a.rows - 1;
    submatrix.cols = a.cols - 1;
    
    // 复制数据到子矩阵，跳过指定的行和列
    for (int i = 0, rowIndex = 0; i < a.rows; ++i, ++rowIndex) {
        if (i == exclude_row) {
            --rowIndex; // 如果是被排除的行，则不增加行索引
            continue;
        }
        for (int j = 0, colIndex = 0; j < a.cols; ++j, ++colIndex) {
            if (j == exclude_col) {
                --colIndex; // 如果是被排除的列，则不增加列索引
                continue;
            }
            submatrix.data[rowIndex][colIndex] = a.data[i][j];
        }
    }

    return submatrix;
}

// 构建伴随矩阵
Matrix adjoint_matrix(Matrix a) {
    Matrix adj;
    adj.rows = a.rows;
    adj.cols = a.cols;

    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            Matrix submatrix = create_submatrix(a, i, j); // 创建缺少第i行第j列的子矩阵
            adj.data[j][i] = pow(-1, i + j) * det_matrix(submatrix); // 注意行列式计算需要根据实际情况调整
        }
    }

    return adj;
}
Matrix inv_matrix(Matrix a) {
    // 检查是否为方阵
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    
    // 计算行列式，检查是否为零
    double determinant = det_matrix(a);
    if (-1e-6< determinant < 1e-6) {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    
    // 计算伴随矩阵
    Matrix adj = adjoint_matrix(a);

    // 根据伴随矩阵计算逆矩阵
    Matrix inv = scale_matrix(adj, fabs(1.0 / determinant));

    return inv;
}

// 辅助函数，用于交换两行
void swap_rows(Matrix *mat, int row1, int row2) {
    for (int col = 0; col < mat->cols; ++col) {
        double temp = mat->data[row1][col];
        mat->data[row1][col] = mat->data[row2][col];
        mat->data[row2][col] = temp;
    }
}

int rank_matrix(Matrix a) {
    int m = a.rows;
    int n = a.cols;
    int rank = (m < n) ? m : n;

    // 复制矩阵，避免修改原矩阵
    Matrix temp = create_matrix(m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            temp.data[i][j] = a.data[i][j];
        }
    }

    // 高斯消元法转换为上三角矩阵
    for (int col = 0; col < rank; ++col) {
        // 寻找非零元素作为主元
        int pivotRow = col;
        while (pivotRow < m && fabs(temp.data[pivotRow][col]) < 1e-6) {
            ++pivotRow;
        }
        if (pivotRow == m) { // 如果找不到非零元素，说明该列及之后的列都为零向量
            rank--;
            continue;
        }
        if (pivotRow != col) { // 交换行
            swap_rows(&temp, col, pivotRow);
        }
        
        // 使用主元消去下方元素
        for (int row = col + 1; row < m; ++row) {
            double factor = temp.data[row][col] / temp.data[col][col];
            for (int k = col; k < n; ++k) {
                temp.data[row][k] -= factor * temp.data[col][k];
            }
        }
    }

    return rank;
}

double trace_matrix(Matrix a) {
    // 检查是否为方阵
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    
    double trace = 0.0;
    // 计算对角线元素之和
    for (int i = 0; i < a.rows; ++i) {
        trace += a.data[i][i];
    }
    
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}