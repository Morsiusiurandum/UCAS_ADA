#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
public:
    /**
     * 从文件中读取数据
     * @return 返回读取的数据
     */
    static auto Read_From_File() -> vector<double>
    {
        const string file_name = "input.txt";
        vector<double> nums;

        if (ifstream infile(file_name); infile.is_open())
        {
            int n;
            infile >> n;
            nums.resize(n);
            for (int i = 0; i < n; ++i)
            {
                infile >> nums[i];
            }
            infile.close();
        }
        else
        {
            cerr << "Unable to open file";
        }

        return nums;
    }
    
    /**
     * 将数据写入文件
     * @param nums 要写入的数据
     */
    static auto Write_To_File(const vector<double>& nums) -> void
    {
        const string file_name = "output.txt";

        if (ofstream outfile(file_name); outfile.is_open())
        {
            outfile << Linear_Sln(nums);
            outfile.close();
        }
        else
        {
            cerr << "Unable to open file";
        }
    }

    /**
     * 找到数组中的最大值和最小值
     * @param values 输入的数组
     * @return 返回数组中的最大值和最小值
     */
    static auto Find_Max_Min(const vector<double>& values) -> pair<double, double>
    {
        double max_value = values[0];
        double min_value = values[0];

        for (const double value : values)
        {
            if (value > max_value)
            {
                max_value = value;
            }

            if (value < min_value)
            {
                min_value = value;
            }
        }

        return {max_value, min_value};
    }

    /**
     * 线性时间复杂度的方法
     * @param nums 输入的数组
     * @return 返回数组中的最大间隔
     */
    static auto Linear_Sln(const vector<double>& nums) -> double
    {
        if (nums.size() < 2)
            return 0;

        auto [first, second] = Find_Max_Min(nums);

        if (first == second)
            return 0;

        const double interval = (first - second) / static_cast<double>(nums.size() - 1);

        vector buckets(
            nums.size(),
            make_tuple(second, first, false));

        for (const double num : nums)
        {
            int bucketIndex = static_cast<int>((num - second) / interval);

            if (bucketIndex >= buckets.size())
            {
                bucketIndex--;
            }

            auto& bucket = buckets[bucketIndex];

            if (num >= get<0>(bucket))
            {
                get<0>(bucket) = num;
                get<2>(bucket) = true;
            }
            if (num <= get<1>(bucket))
            {
                get<1>(bucket) = num;
                get<2>(bucket) = true;
            }
        }

        double max_gap = 0;
        double current_max = get<0>(buckets[1]);
        double current_min = get<0>(buckets[0]);

        for (int i = 1; i < buckets.size(); i++)
        {
            if (!get<2>(buckets[i]))
                continue;

            current_max = get<1>(buckets[i]);
            const auto gap = current_max - current_min;
            current_min = get<0>(buckets[i]);

            if (gap > max_gap)
            {
                max_gap = gap;
            }
        }

        return max_gap;
    }

    /**
     * 遍历获得答案的标准方法
     * @param nums 输入的数组
     * @return 返回数组中的最大间隔
     */
    static auto Standard_Sln(vector<double>& nums) -> double
    {
        std::sort(nums.begin(), nums.end());
        double max_gap = 0;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (auto new_gap = abs(nums[i] - nums[i + 1]); new_gap > max_gap)
            {
                max_gap = new_gap;
            }
        }
        return max_gap;
    }
};

int main()
{
    const vector<double> nums = Solution::Read_From_File();
    Solution::Write_To_File(nums);
    return 0;
}
