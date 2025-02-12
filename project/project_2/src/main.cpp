#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 1024; // 最大支持的棋盘大小为 2^10
int board[MAX_SIZE][MAX_SIZE]; // 棋盘
int current_id = 1; // 当前编号，用于标记不同的 L 型骨牌形状

// 在棋盘 (x, y) 的大小为 size 的区域放置 L 型骨牌，特殊方块在 (special_x, special_y)
void coverBoard(int x, int y, int size, int special_x, int special_y) {
    if (size == 2) { // 基础情况：2x2 小棋盘
        // 确定 L 型骨牌的形状，并用相同的编号标记
        if (special_x == x && special_y == y) { // 特殊方块在左上角
            board[x][y + 1] = current_id;
            board[x + 1][y] = current_id;
            board[x + 1][y + 1] = current_id;
        } else if (special_x == x && special_y == y + 1) { // 特殊方块在右上角
            board[x][y] = current_id;
            board[x + 1][y] = current_id;
            board[x + 1][y + 1] = current_id;
        } else if (special_x == x + 1 && special_y == y) { // 特殊方块在左下角
            board[x][y] = current_id;
            board[x][y + 1] = current_id;
            board[x + 1][y + 1] = current_id;
        } else { // 特殊方块在右下角
            board[x][y] = current_id;
            board[x][y + 1] = current_id;
            board[x + 1][y] = current_id;
        }
        current_id++; // 每种形状的 L 型骨牌使用同一个编号
        return;
    }

    int half = size / 2;
    int center_x = x + half;
    int center_y = y + half;

    // 标记四个子棋盘中的特殊方块位置
    int special_quadrant = 0;
    if (special_x < center_x && special_y < center_y) {
        special_quadrant = 0; // 左上子棋盘
    } else if (special_x < center_x && special_y >= center_y) {
        special_quadrant = 1; // 右上子棋盘
    } else if (special_x >= center_x && special_y < center_y) {
        special_quadrant = 2; // 左下子棋盘
    } else {
        special_quadrant = 3; // 右下子棋盘
    }

    // 放置中心的 L 型骨牌，使每个子棋盘都有一个特殊方块
    if (special_quadrant != 0) board[center_x - 1][center_y - 1] = current_id;
    if (special_quadrant != 1) board[center_x - 1][center_y] = current_id;
    if (special_quadrant != 2) board[center_x][center_y - 1] = current_id;
    if (special_quadrant != 3) board[center_x][center_y] = current_id;
    current_id++; // 每种 L 型骨牌用一个编号

    // 递归处理四个子棋盘
    coverBoard(x, y, half,
        special_quadrant == 0 ? special_x : center_x - 1,
        special_quadrant == 0 ? special_y : center_y - 1);

    coverBoard(x, center_y, half,
        special_quadrant == 1 ? special_x : center_x - 1,
        special_quadrant == 1 ? special_y : center_y);

    coverBoard(center_x, y, half,
        special_quadrant == 2 ? special_x : center_x,
        special_quadrant == 2 ? special_y : center_y - 1);

    coverBoard(center_x, center_y, half,
        special_quadrant == 3 ? special_x : center_x,
        special_quadrant == 3 ? special_y : center_y);
}

int main() {
    int k, special_x, special_y;
    cout << "请输入棋盘的大小（2^k）k：";
    cin >> k;
    int size = 1 << k; // 2^k
    cout << "请输入特殊方块的坐标（行 列）：";
    cin >> special_x >> special_y;

    // 特殊方块从 0 开始索引
    special_x--;
    special_y--;

    // 初始化棋盘
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = 0;
        }
    }

    // 开始覆盖棋盘
    coverBoard(0, 0, size, special_x, special_y);

    // 输出棋盘
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}