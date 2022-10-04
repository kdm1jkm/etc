#include <iostream>
#include <string>

std::string words[] = {"aespa", "baekjoon", "cau", "debug", "edge", "firefox", "golang", "haegang", "iu", "java", "kotlin", "lol", "mips", "null", "os", "python", "query", "roka", "solvedac", "tod", "unix", "virus", "whale", "xcode", "yahoo", "zebra"};

int main()
{
    std::string input;
    std::cin >> input;

    auto iter = input.begin();

    std::string result;

    while (iter < input.end())
    {
        char c = *iter;
        auto &word = words[c - 'a'];

        int remainLen = input.end() - iter;
        int wordLen = word.length();
        if (remainLen < wordLen)
        {
            puts("ERROR!");
            return 0;
        }

        for (auto &key : word)
        {
            if (key != *iter)
            {
                puts("ERROR!");
                return 0;
            }

            iter++;
        }
        result.push_back(c);
    }

    std::cout << "It's HG!\n"
              << result;

    return 0;
}