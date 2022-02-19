#include "generator.h"
#include <algorithm>
#include <iostream>
int Factorial(int n)
{
	int f = 1;
	for (int b = 2; b <= n; b++)
	{
		f *= b;
	}
	return f;

}
void Generator::pushx(){
	/*for(const auto&i : x){
		std::cout << i << " ";
	}
	std::cout<<std::endl;*/

	for (int  i = 0; i < n; i++)
	{
		x[i]++;
	}

	result.push_back(x);

	for (int i = 0; i < n; i++)
	{
		x[i]--;
	}

}

Generator::Generator(int m,int n,int k){
	this->n = n;
	//this->k = k ;
	this->k = k-1;
	this->m = m-n;
	x.resize(n);
	
}
bool Generator::next(){
	int j = n - 1;
	int s = 0;
	while (x[j] == k ||  x[j]+1 >m || s == 0){
		s+=x[j];
		j--;
		if(j < 0)
			return false;
	}
	x[j]++;
	s--;
	for(int i = n-1; j < i; i--){
		int c = std::min(k,s);
		s-=c;
		x[i] = c;
	}
	return true;
}
void Generator::GenerateAll() {
	if (m>n*k)
		return;
	int i ;
	for(i = n -1; i>0 && m - (n - 1 - i)*k > k;i--){//смотрим чтобы остаток из общей суммы больше чем k 
		// m - сумма которая необходима 
		// (n-1-i)*к - сумма тех слагаемых что мы уже поставили
		// к - максимальное значение слагаемого 
		x[i] = k;
	}
	x[i] = m - (n - 1 - i)*k;// после того как все места под к заняты ,мы ставим то сколько осталось до суммы m
	i--;
	while (i>=0){
		x[i] = 0;
		i--;
	}
	pushx();
	while(next()&&getCount() <1000000)pushx();// проверка по переполнению памяти ,по хорошему нужно убрать
											  // next() возвращяет след элемент и смотрит является ли он конечным


}
std::vector<int>& Generator::GetResult(int idx) {
	
   return result[idx];
}
int Generator::getCount(){
	return result.size();
}
void Generator::GenerateRecursive(){
	recursiveNext(0,m);
}
void Generator::recursiveNext(int i,int s){
	//std::cout<<x[i-1]<< " ("<<i<<", " <<s<<")"<<std::endl;
	if (i == n-1){
		if(s>k){// мы смотрим сумма больше k то откидываем этот вариант
			//std::cout <<"TUPI40k!"<<std::endl;
			return;
		}
		//если нет то ставим то что осталось
		x[i] = s;

		pushx();//возвращяем итоговую послед

		return;
	}	
	if(s==0){// то мы больше 0 поставить не можем и все заполняем нулями
		for(int j =i;j<n;j++){
			x[j] = 0;
		}
		pushx();
		return;
	}
	if(s < 0){
		return;
	}

	for(int j=0;j<=std::min(k,s);j++){//рассматриваем остальные варианты

		x[i] = j;//ставим j 
		
		recursiveNext(i+1,s-j);// ставим остальные числа (сумма оставшихся равна s-j)
	}
}