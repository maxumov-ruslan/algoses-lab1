#pragma once
#include <vector>

class Generator {

    std::vector<std::vector<int> >  result;
    std::vector<int> x;
    int n;
    int k;
    int m;


    // завести набор построенных объектов - vector<vector>
    
    // конструктор с n,k
    void pushx();    
    bool next();
    void recursiveNext(int i,int s);
public:
    Generator(int m,int n,int k);
    void GenerateAll();
    void GenerateRecursive();
    int getCount();
    std::vector<int>& GetResult(int index);
};

int Factorial(int n);
