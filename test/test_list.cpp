#include "List.h"

#include <../gtest/gtest.h>


#include <sstream>

TEST(TList, create_list)
{
    ASSERT_NO_THROW(TList<int>());
}

TEST(TList, correct_ins_first)
{
    const int size = 4;
    vector<int> expEq;
    TList<int> L;
    for (int i = 0; i < size; i++)
    {
        L.InsFirst(i + 1);
        expEq.push_back(size - i);
    }
    vector<int>res = L.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TList, correct_ins_last)
{
    const int size = 4;
    vector<int> expEq;
    TList<int> L;
    for (int i = 0; i < size; i++)
    {
        L.InsLast(i + 1);
        expEq.push_back(i + 1);
    }
    vector<int>res = L.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TList, correct_ins)
{
    const int size = 4;
    vector<int> expEq;
    TList<int> L;
    for (int i = 0; i < size; i++)
    {
        L.InsLast(i + 1);
    }
    TListIterator<int> iter = L.begin();
    for (int i = 1; i < size / 2 + size % 2; i++)
    {
        ++iter;
    }
    for (int i = 0; i < size; i++)
    {
        L.Ins(iter, i + 1);
        ++iter;
    }
    for (int i = 0; i < size / 2 + size % 2; i++)
    {
        expEq.push_back(i + 1);
    }
    for (int i = 0; i < size; i++)
    {
        expEq.push_back(i + 1);
    }
    for (int i = size / 2 + size % 2; i < size; i++)
    {
        expEq.push_back(i + 1);
    }
    vector<int>res = L.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TList, correct_del_first)
{
    const int size = 4;
    vector<int> expEq;
    TList<int> L;
    L.InsLast(1);
    for (int i = 1; i < size; i++)
    {
        L.InsLast(i + 1);
        expEq.push_back(i + 1);
    }
    L.DelFirst();
    vector<int>res = L.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TList, correct_del_last)
{
    const int size = 4;
    vector<int> expEq;
    TList<int> L;
    for (int i = 0; i < size - 1; i++)
    {
        L.InsLast(i + 1);
        expEq.push_back(i + 1);
    }
    L.InsLast(size);
    L.DelLast();
    vector<int>res = L.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TList, correct_del)
{
    const int size = 8;
    vector<int> expEq;
    TList<int> L;
    for (int i = 0; i < size; i++)
    {
        L.InsLast(i + 1);
    }
    TListIterator<int> iter = L.begin();
    for (int i = 0; i < size / 4 + size % 2; i++)
    {
        ++iter;
    }
    for (int i = 0; i < size / 2; i++)
    {
        TListIterator<int> tmp = iter;
        ++iter;
        L.Del(tmp);
    }
    for (int i = 0; i < size / 4 + size % 2; i++)
    {
        expEq.push_back(i + 1);
    }
    for (int i = size / 2 + size / 4 + size % 2; i < size; i++)
    {
        expEq.push_back(i + 1);
    }
    vector<int>res = L.ElemsModZero(1);
    EXPECT_EQ(expEq, res);
}

TEST(TList, use_iterator)
{
    const int size = 4;
    TList<int> L;
    string expStr = "";
    for (int i = 0; i < size; i++)
    {
        expStr += (i + 1) + '0';
        L.InsLast(i + 1);
    }
    string res = "";
    for (TListIterator<int> iter = L.begin(); !iter.IsEmpty(); ++iter)
    {
        res += *iter + '0';
    }
    EXPECT_EQ(expStr, res);
}

TEST(TList, find_elems_mod_n_equals_0)
{
    const int size = 4;
    int n = 2;
    vector<int> expEq;
    TList<int> L;
    for (int i = 0; i < size; i++)
    {
        L.InsLast(i + 1);
        if ((i + 1) % n == 0)
            expEq.push_back(i + 1);
    }
    vector<int> res;
    res = L.ElemsModZero(n);
    EXPECT_EQ(expEq, res);
}

TEST(TList, can_write_list_to_file)
{
    const int size = 4;
    TList<int> L;
    for (int i = 0; i < size; i++)
        L.InsLast(i + 1);
    L.WriteToFile("ListOI.txt");
    string expList = "1234";
    string List = "";
    ifstream fin("ListOI.txt");
    fin >> List;
    fin.close();
    EXPECT_EQ(expList, List);
}