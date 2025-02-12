#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 主函数：根据输入的数字字符串和要删除的数字个数，返回最小数字
    static string getMinNumber(string number, int digitsToRemove)
    {
        int numberLength = static_cast<int>(number.length());

        while (digitsToRemove > 0)
        {
            digitsToRemove--;

            int removalPosition = numberLength - 1; // 默认删除最后一个数字的位置

            // 遍历字符串，查找第一个比后面数字大的数字
            // 该数字就是要删除的数字，因为它使得剩下的数字更小
            for (int i = 0; i < numberLength - 1; i++)
            {
                if (number[i] > number[i + 1])
                {
                    // 找到一个比下一个数字大的数字
                    removalPosition = i; // 记录该数字的删除位置
                    break; // 找到后，跳出循环
                }
            }

            number.erase(removalPosition, 1);
            numberLength--;
        }

        while (number[0] == '0' && !number.empty())
        {
            number.erase(0, 1);
        }

        // 如果删除后字符串为空，返回 "0"
        return number.empty() ? "0" : number;
    }
};

int main()
{
    cout << "请输入一个正整数：";
    string number;
    cin >> number;

    cout << "请输入需要删除的数字个数：";
    int digitsToRemove;
    cin >> digitsToRemove;

    const string result = Solution::getMinNumber(number, digitsToRemove);

    cout << "删除后的最小数字是： " << result << endl;

    return 0;
}
