#include <iostream>
#include <fstream>
#include <array>
#include <optional>
using namespace std;
const size_t MATRIX_SIZE = 3;
using Mat3x3 = array<array<double, MATRIX_SIZE>, MATRIX_SIZE>;

void ReadMatrix(ifstream& file, Mat3x3& matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            file >> matrix[i][j];
        }
    }
    file.close();
}

double CalculateDeterminant(const Mat3x3& matrix)
{
    double x1 = matrix[0][0] * matrix[1][1] * matrix[2][2];
    double x2 = matrix[0][1] * matrix[1][2] * matrix[2][0];
    double x3 = matrix[0][2] * matrix[1][0] * matrix[2][1];
    double x4 = matrix[0][2] * matrix[1][1] * matrix[2][0];
    double x5 = matrix[0][1] * matrix[1][0] * matrix[2][2];
    double x6 = matrix[0][0] * matrix[1][2] * matrix[2][1];
    return x1 + x2 + x3 - x4 - x5 - x6;
}

void CalculateAdjugateMatrix(const Mat3x3& matrix, Mat3x3& adjugateMatrix)
{
    adjugateMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adjugateMatrix[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
    adjugateMatrix[2][0] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    adjugateMatrix[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
    adjugateMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adjugateMatrix[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
    adjugateMatrix[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    adjugateMatrix[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
    adjugateMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}


optional<Mat3x3> InvertMatrix(const Mat3x3& matrix)
{
    double det = CalculateDeterminant(matrix);
    if (det == 0)
        return nullopt;
    Mat3x3 adjugateMatrix;
    CalculateAdjugateMatrix(matrix, adjugateMatrix);
    Mat3x3 inverseMatrix{};
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            inverseMatrix[i][j] = 1 / det * adjugateMatrix[i][j];
        }
    }
    return inverseMatrix;
}

void PrintInverseMatrix(const optional<Mat3x3>& matrix)
{
    Mat3x3 m = matrix.value();
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            cout << floor(m[i][j] * 1000) / 1000 << ' ';
        }
        cout << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect number of command line arguments. The command line should look like: invert.exe <matrix file1>" << endl;
        return 1;
    }
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Error opening a file for reading" << endl;
        return 1;
    }
    Mat3x3 matrix;
    ReadMatrix(input, matrix);
    optional<Mat3x3> inverseMatrix;
    try
    {
        inverseMatrix = InvertMatrix(matrix);
        PrintInverseMatrix(inverseMatrix);
    }
    catch (bad_optional_access)
    {
        cout << "This matrix cannot be inverted, because determinant equals zero" << endl;
        return 0;
    }
}