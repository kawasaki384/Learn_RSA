#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int p;
int q;
//n =p*q
int n;
//Φ(n)
int phi_n;

//1<e<nであり、phi_nと互いにそな数、phi_nの約数ではない小さな素数
int e;

int d;

//乱数生成の初期化
void init(){
	srand(time(NULL));
}

_Bool is_it_primenum(int num){
	int c = 0;
	for(int i = 1;i <= (int)sqrt((double)num);i++){
		if(num % i == 0)
			c++;
	}

	if(c == 1 && num != 1)
		return 1;
	else
		return 0;
}

//2数は互いに素であるか？
_Bool are_they_relatively_prime(int a,int b){
	int c = 0;
	int d = 0;
	while(b != 0){
		d = a % b;
		c = (a-d)/b;
		a = b;
		b = d;
	}

	if(a == 1)
		return 1;
	else
		return 0;
}

//ランダムな素数を生成してp,qに代入する。
void get_random_primenum(){
	int p_tmp = 0;
	while(is_it_primenum(p_tmp) == 0){
		//1024～2048の中からの素数を生成
		p_tmp = 1024 + rand() % 1025;
	}

	int q_tmp = 0;

	while(is_it_primenum(q_tmp) == 0 || p_tmp == q_tmp){
		//1024～2048の中から素数を生成
		q_tmp = 1024 + rand() % 1025;
	}

	p = p_tmp;
	q = q_tmp;

	n = p*q;
	phi_n = (p-1)*(q-1);

	return;
}

//eを生成する
void get_e(){
	int e_tmp = 0;
	
	while(is_it_primenum(e_tmp) == 0 || 1 > e_tmp || e_tmp > phi_n 
			|| are_they_relatively_prime(e_tmp,phi_n) == 0){
		//256～512の中から素数を生成
		e_tmp = 256 + rand() % 257;
	}
	e = e_tmp;

	return;
}

void calcurate_d(){
	int d_tmp = 0;
	int i;
	for(i = 0; (phi_n * i + 1) % e != 0; i++);
	d_tmp = (i * phi_n + 1) / e;
	d = d_tmp;
	return;
}

#define uint128_t __uint128_t

uint128_t modpow(uint128_t b,uint128_t e,uint128_t m){
	uint128_t result = 1;

	while(e > 0){
		if((e & 1) == 1) result = (result * b) % m;
		e >>= 1;
		b = (b*b) % m;
	}
	return result;
}

int main(){
	init();
	get_random_primenum();
	get_e();
	calcurate_d();
	//平文
	char M[] = "HelloWorld";

	uint128_t c[sizeof(M)/sizeof(char)-1];
       	for(int i = 0; i < sizeof(M)/sizeof(char)-1;i++){
		printf("p=%d q=%d phi_n=%d e=%d \n",p,q,phi_n,e);
		c[i] = modpow((uint128_t)M[i],(uint128_t)e,(uint128_t)n);
		printf("暗号C=%d \n",c[i]);
		printf("復号しました。 M=%c \n",modpow(c[i],(uint128_t)d,(uint128_t)n));
		get_random_primenum();
		get_e();
		calcurate_d();
	}
}
