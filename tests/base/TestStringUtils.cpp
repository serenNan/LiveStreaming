#include "StringUtils.h"
#include "gtest/gtest.h"
using namespace tmms::base;

TEST(TestStringUtils, StartsWith)
{
    EXPECT_TRUE(StringUtils::StartsWith("hello world", "hello"));
    EXPECT_FALSE(StringUtils::StartsWith("hello world", "world"));
    EXPECT_TRUE(StringUtils::StartsWith("hello", ""));
    EXPECT_FALSE(StringUtils::StartsWith("", "hello"));
}

TEST(TestStringUtils, EndsWith)
{
    EXPECT_TRUE(StringUtils::EndsWith("hello world", "world"));
    EXPECT_FALSE(StringUtils::EndsWith("hello world", "hello"));
    EXPECT_TRUE(StringUtils::EndsWith("hello", ""));
    EXPECT_FALSE(StringUtils::EndsWith("", "hello"));
}

TEST(TestStringUtils, FilePath)
{
    EXPECT_EQ(StringUtils::FilePath("/home/user/file.txt"), "/home/user");
    EXPECT_EQ(StringUtils::FilePath("C:\\Users\\file.txt"), "C:\\Users");
    EXPECT_EQ(StringUtils::FilePath("file.txt"), "");
    EXPECT_EQ(StringUtils::FilePath(""), "");
}

TEST(TestStringUtils, FileNameExt)
{
    EXPECT_EQ(StringUtils::FileNameExt("/home/user/file.txt"), "file.txt");
    EXPECT_EQ(StringUtils::FileNameExt("C:\\Users\\file.txt"), "file.txt");
    EXPECT_EQ(StringUtils::FileNameExt("file.txt"), "file.txt");
    EXPECT_EQ(StringUtils::FileNameExt(""), "");
}

TEST(TestStringUtils, FileName)
{
    EXPECT_EQ(StringUtils::FileName("/home/user/file.txt"), "file");
    EXPECT_EQ(StringUtils::FileName("C:\\Users\\file.txt"), "file");
    EXPECT_EQ(StringUtils::FileName("file.txt"), "file");
    EXPECT_EQ(StringUtils::FileName("file"), "file");
    EXPECT_EQ(StringUtils::FileName(""), "");
}

TEST(TestStringUtils, Extension)
{
    EXPECT_EQ(StringUtils::Extension("/home/user/file.txt"), ".txt");
    EXPECT_EQ(StringUtils::Extension("C:\\Users\\file.txt"), ".txt");
    EXPECT_EQ(StringUtils::Extension("file.txt"), ".txt");
    EXPECT_EQ(StringUtils::Extension("file"), "");
    EXPECT_EQ(StringUtils::Extension(""), "");
}

TEST(TestStringUtils, SplitString)
{
    // 正常分割
    std::vector<std::string> result1 = StringUtils::SplitString("a,b,c", ",");
    EXPECT_EQ(result1.size(), 3);
    EXPECT_EQ(result1[0], "a");
    EXPECT_EQ(result1[1], "b");
    EXPECT_EQ(result1[2], "c");

    // 空字符串输入
    std::vector<std::string> result2 = StringUtils::SplitString("", ",");
    EXPECT_EQ(result2.size(), 1);
    EXPECT_EQ(result2[0], "");

    // 空分隔符
    std::vector<std::string> result3 = StringUtils::SplitString("abc", "");
    EXPECT_EQ(result3.size(), 1);
    EXPECT_EQ(result3[0], "abc");

    // 边界条件：分隔符在开头
    std::vector<std::string> result4 = StringUtils::SplitString(",a,b", ",");
    EXPECT_EQ(result4.size(), 3);
    EXPECT_EQ(result4[0], "");
    EXPECT_EQ(result4[1], "a");
    EXPECT_EQ(result4[2], "b");

    // 边界条件：分隔符在结尾
    std::vector<std::string> result5 = StringUtils::SplitString("a,b,", ",");
    EXPECT_EQ(result5.size(), 3);
    EXPECT_EQ(result5[0], "a");
    EXPECT_EQ(result5[1], "b");
    EXPECT_EQ(result5[2], "");

    // 多字符分隔符
    std::vector<std::string> result6 = StringUtils::SplitString("a::b::c", "::");
    EXPECT_EQ(result6.size(), 3);
    EXPECT_EQ(result6[0], "a");
    EXPECT_EQ(result6[1], "b");
    EXPECT_EQ(result6[2], "c");
}

TEST(TestStringUtils, SplitStringWithFSM)
{
    // 测试1：基本分割功能
    std::vector<std::string> result1 = StringUtils::SplitStringWithFSM("a,b,c", ',');
    EXPECT_EQ(result1.size(), 3);
    EXPECT_EQ(result1[0], "a");
    EXPECT_EQ(result1[1], "b");
    EXPECT_EQ(result1[2], "c");

    // 测试2：空字符串
    std::vector<std::string> result2 = StringUtils::SplitStringWithFSM("", ',');
    EXPECT_EQ(result2.size(), 0);

    // 测试3：只有一个分隔符
    std::vector<std::string> result3 = StringUtils::SplitStringWithFSM(",", ',');
    EXPECT_EQ(result3.size(), 0);

    // 测试4：连续的分隔符
    std::vector<std::string> result4 = StringUtils::SplitStringWithFSM("a,,b", ',');
    EXPECT_EQ(result4.size(), 2);
    EXPECT_EQ(result4[0], "a");
    EXPECT_EQ(result4[1], "b");

    // 测试5：分隔符在开头
    std::vector<std::string> result5 = StringUtils::SplitStringWithFSM(",a,b", ',');
    EXPECT_EQ(result5.size(), 2);
    EXPECT_EQ(result5[0], "a");
    EXPECT_EQ(result5[1], "b");

    // 测试6：分隔符在结尾
    std::vector<std::string> result6 = StringUtils::SplitStringWithFSM("a,b,", ',');
    EXPECT_EQ(result6.size(), 2);
    EXPECT_EQ(result6[0], "a");
    EXPECT_EQ(result6[1], "b");

    // 测试7：包含空格的字符串
    std::vector<std::string> result7 = StringUtils::SplitStringWithFSM("hello world,cpp", ',');
    EXPECT_EQ(result7.size(), 2);
    EXPECT_EQ(result7[0], "hello world");
    EXPECT_EQ(result7[1], "cpp");

    // 测试8：长字符串
    std::vector<std::string> result8 =
        StringUtils::SplitStringWithFSM("one,two,three,four,five", ',');
    EXPECT_EQ(result8.size(), 5);
    EXPECT_EQ(result8[0], "one");
    EXPECT_EQ(result8[1], "two");
    EXPECT_EQ(result8[2], "three");
    EXPECT_EQ(result8[3], "four");
    EXPECT_EQ(result8[4], "five");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}