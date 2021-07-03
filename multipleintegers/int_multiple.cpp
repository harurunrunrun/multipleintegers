#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include "int_multiple.h"

namespace multipleintegers{

//加算
std::string add(std::string x,std::string y);
//減算
std::string sub(std::string x,std::string y);
//乗算
std::string mul(std::string x,std::string y);
//除算
std::string div(std::string x,std::string y);
//剰余
std::string mod(std::string x,std::string y);
//繰り返し２乗法
std::string pow(std::string x,std::string n,std::string m);
//最大公約数
std::string gcd(std::string x,std::string y);
//最小公倍数
std::string lcm(std::string x,std::string y);
//乗法逆元
std::string inv_mod(std::string a,std::string N);
//拡張ユークリッドの互除法
std::vector<std::string> ext_gcd(std::string x,std::string y);
//k bitの乱数を生成
std::string randbit(int k);
//x桁以上y桁以下の乱数を生成
std::string random_int(int x,int y);
//x以上y以下の範囲の自然数を生成
std::string random_range(std::string x,std::string y);

//a>=bのときtrueを返す関数
bool cmp(std::string a,std::string b);
//商と余りを返す関数
std::vector<std::string> div_and_mod(std::string x,std::string y);
//2進数に変換する関数
std::string bin(std::string x);
//2進数を10進数に変換する関数
std::string convert2to10(std::string x);

/*
**************************************************************
*/


bool cmp(std::string a,std::string b){
  //a>=bを判定
  if(a.at(0)=='-' || b.at(0)=='-')std::cerr<<"Error: cmp detected minus."<<std::endl;
  int a_size = a.size(),b_size = b.size();
  if(a_size<b_size)return false;
  if(a_size>b_size)return true;
  for(int i=0;i<a_size;i++){
    if(a.at(i)<b.at(i))return false;
    if(a.at(i)>b.at(i))return true;
  }
  return true;//equal
}

std::string add(std::string x,std::string y);

std::string sub(std::string x,std::string y){
  if(x.at(0)=='-' && y.at(0)!='-'){
    y.insert(0,"-");
    return add(x,y);
  }
  if(x.at(0)!='-' && y.at(0)=='-'){
    y.erase(0,1);
    return add(x,y);
  }
  
  // 正負が異なるならaddへ

  //cout<<"x: "<<x<<endl;
  //cout<<"y: "<<y<<endl;
  int x_size=x.size(),y_size=y.size();
  int z_size=std::max(x_size,y_size);
  bool flag1=false,flag2=false;//flag1はどちらも-のときtrue,+のときfalse、flag2はx,yを入れ替えたときtrue
  int m=0;
  if(x.at(0)=='-' && y.at(0)=='-'){
    //m++;
    flag1=true;
    //cout<<"flag1 is true"<<endl;
    x.erase(0,1);
    y.erase(0,1);
    x_size--;
    y_size--;
  }
  if(!cmp(x,y)){
    flag2=true;
    std::string tmp=x;
    x=y;
    y=tmp;
    //cout<<"flag2 is true"<<endl;
    int tmp2=x_size;
    x_size=y_size;
    y_size=tmp2;
  }
  //cout<<"abs_x: "<<x<<endl;
  //cout<<"abs_y: "<<y<<endl;
  //cout<<"cmp(x,y): "<<cmp(x,y)<<", cmp(y,x): "<<cmp(y,x)<<endl;
  int dz,cl=0;
  std::string ret="",rz;
  for(int i=1;i<=z_size;i++){
    dz=-cl;
    cl=0;
    if(x_size-i>=m){
      dz+=x.at(x_size-i)-'0';
      //cout<<"x_i: "<<x.at(x_size-i)<<" ";
    }
    if(y_size-i>=m){
      dz-=y.at(y_size-i)-'0';
      //cout<<"y_i: "<<y.at(y_size-i)<<" ";
    }
    if(dz<0){
      cl=(-dz+9)/10;
      dz+=10*cl;
    }
    ret+=std::to_string(abs(dz)%10);
    //cout<<"cl: "<<cl<<endl;
  }
  //cout<<"abs ret: "<<ret<<endl;
  if((flag1 && !flag2) || (!flag1 && flag2))ret+='-';
  reverse(ret.begin(),ret.end());
  //cout<<"ret: "<<ret<<endl;
  std::string ret2;
  bool flag3 = true;
  for(unsigned int i=0;i<ret.size()-1;i++){
    if(ret.at(i)=='-'){
      ret2+=ret.at(i);
    }
    else if(ret.at(i)=='0' && flag3)continue;
    else{
      flag3=false;
      ret2+=ret.at(i);
    }
  }
  ret2+=ret.at(ret.size()-1);
  if(ret2=="-0")return "0";
  return ret2;
}

std::string add(std::string x,std::string y){
  if(x.at(0)=='-' && y.at(0)!='-'){
    x.erase(0,1);
    return sub(y,x);
  }
  if(x.at(0)!='-' && y.at(0)=='-'){
    y.erase(0,1);
    return sub(x,y);
  }
  
  //-の判定を入れる。正負が異なる場合はsubへ
  
  int x_size=x.size(),y_size=y.size();
  int z_size=std::max(x_size,y_size)+1;
  bool flag=false;
  int m=0;
  if(x.at(0)=='-' && y.at(0)=='-'){
    flag=true;
    z_size--;
    m++;
  }
  std::string ret="";
  short dz,cl=0;
  for(int i=1;i<z_size;i++){
    dz=0;
    if(x_size-i>=m){
      dz+=x.at(x_size-i)-'0';
    }
    if(y_size-i>=m){
      dz+=y.at(y_size-i)-'0';
    }
    dz+=cl;
    cl=dz/10;
    dz%=10;
    ret+=std::to_string(dz);
  }
  if(cl!=0)ret+=std::to_string(cl);
  if(flag)ret+='-';
  reverse(ret.begin(),ret.end());
  return ret;
}

std::string mod(std::string x,std::string y){
  if(y=="0"){
    std::cerr<<"Error: division by zero"<<std::endl;
    exit(1);
  }
  //x%y
  if(y.at(0)=='-'){
    std::cerr<<"Error: mod by minus"<<std::endl;
    exit(1);
  }  
  if(x.at(0)=='-'){
    while(x.at(0)=='-'){
      x=add(x,y);
    }
  }
  int x_size=x.size();
	//int y_size=y.size();
  std::vector<short> z(x_size);
  std::string tmp="";
  //前計算
  std::vector<std::string> dy(10);
  std::string sdy=y;
  dy.at(0)="0";
  for(int i=1;i<10;i++){
    dy.at(i)=sdy;
    sdy=add(sdy,y);
  }
  //本計算
  for(int i=0;i<x_size;i++){
    tmp+=x.at(i);
    if(cmp(tmp,y)){
      short j=9;
      while(!cmp(tmp,dy.at(j)))j--;
      z.at(i)=j;
      tmp=sub(tmp,dy.at(j));
    }
    if(tmp=="0")tmp="";
  }
  //cout<<x_size<<" "<<y_size<<" "<<endl;
  if(tmp=="")tmp="0";
  return tmp;
}

std::string div(std::string x,std::string y){
  if(y=="0"){
    std::cerr<<"Error: division by zero"<<std::endl;
    exit(1);
  }
  bool flag1=false,flag2=false;
  if(x.at(0)=='-'){
    flag1=true;
    x.erase(0,1);
  }
  if(y.at(0)=='-'){
    flag2=true;
    y.erase(0,1);
  }
  //cout<<"x: "<<x<<endl;
  //cout<<"y: "<<y<<endl;
  int x_size=x.size();
	//int y_size=y.size();
  std::vector<short> z(x_size);
  std::string tmp="";
  //前計算
  std::vector<std::string> dy(10);
  std::string sdy=y;
  dy.at(0)="0";
  for(int i=1;i<10;i++){
    dy.at(i)=sdy;
    sdy=add(sdy,y);
  }
  //本計算
  for(int i=0;i<x_size;i++){
    tmp+=x.at(i);
    if(cmp(tmp,y)){
      short j=9;
      while(!cmp(tmp,dy.at(j)))j--;
      z.at(i)=j;
      tmp=sub(tmp,dy.at(j));
      //cout<<tmp<<" "<<j<<" "<<dy.at(j)<<endl;
    }
    if(tmp=="0")tmp="";
  }
  std::string ret="";
  if((flag1 && !flag2) || (!flag1 && flag2))ret+="-";
  bool flag3=true;
  for(int i=0;i<x_size-1;i++){
    if(flag3 && z.at(i)==0)continue;
    if(flag3 && z.at(i)!=0){
      flag3=false;
    }
    ret+=std::to_string(z.at(i));
  }
  ret+=std::to_string(z.at(x_size-1));
  if(ret=="-0")return "0";
  return ret;
}

std::vector<std::string> div_and_mod(std::string x,std::string y){
  if(y=="0"){
    std::cerr<<"Error: division by zero"<<std::endl;
    exit(1);
  }
  bool flag1=false,flag2=false;
  if(x.at(0)=='-'){
    flag1=true;
    x.erase(0,1);
  }
  if(y.at(0)=='-'){
    flag2=true;
    y.erase(0,1);
  }
  int x_size=x.size();
	//int y_size=y.size();
  std::vector<short> z(x_size);
  std::string tmp="";
  //前計算
  std::vector<std::string> dy(10);
  std::string sdy=y;
  dy.at(0)="0";
  for(int i=1;i<10;i++){
    dy.at(i)=sdy;
    sdy=add(sdy,y);
  }
  //本計算
  for(int i=0;i<x_size;i++){
    tmp+=x.at(i);
    if(cmp(tmp,y)){
      short j=9;
      while(!cmp(tmp,dy.at(j)))j--;
      z.at(i)=j;
      tmp=sub(tmp,dy.at(j));
      //cout<<tmp<<" "<<j<<" "<<dy.at(j)<<endl;
    }
    if(tmp=="0")tmp="";
  }
  std::string ret="";
  if((flag1 && !flag2 )|| (!flag1 && flag2))ret+="-";
  bool flag3=true;
  for(int i=0;i<x_size-1;i++){
    if(flag3 && z.at(i)==0)continue;
    if(flag3 && z.at(i)!=0){
      flag3=false;
    }
    ret+=std::to_string(z.at(i));
  }
  ret+=std::to_string(z.at(x_size-1));
  if(ret=="-0")ret="0";
  if(tmp=="")tmp="0";
  std::vector<std::string> ret_v(2);
  ret_v.at(0)=ret;
  ret_v.at(1)=tmp;
  return ret_v;
}

std::string mul(std::string x,std::string y){
  if(x=="0" || y=="0")return "0";
  bool flag1=false,flag2=false;
  if(x.at(0)=='-'){
    flag1=true;
    x.erase(0,1);
  }
  if(y.at(0)=='-'){
    flag2=true;
    y.erase(0,1);
  }
  int x_size=x.size(),y_size=y.size();
  int z_size=x_size+y_size;
  std::vector<int> z(z_size);
  for(int i=0;i<y_size;i++){
    for(int j=0;j<x_size;j++){
      z.at(z_size-i-j-1)+=(y.at(y_size-i-1)-'0')*(x.at(x_size-j-1)-'0');
    }
  }
  std::string ret="";
  int cl=0,dz;
  for(int i=0;i<z_size-1;i++){
    dz=z.at(z_size-i-1)+cl;
    ret+=std::to_string(dz%10);
    cl=dz/10;
  }
  if(cl!=0)ret+=std::to_string(cl);
  if((flag1 && !flag2) || (!flag1 && flag2))ret+="-";
  reverse(ret.begin(),ret.end());
  return ret;
}


std::string bin(std::string x){
  std::string ret="";
  //cout<<x<<endl;
  std::vector<std::string> tmp(2);
  tmp.at(0)=x;
  do{
    tmp=div_and_mod(tmp.at(0),"2");
    //cout<<tmp.at(0)<<" "<<tmp.at(1)<<endl;
    ret+=tmp.at(1);
  }while(tmp.at(0)!="0");
  reverse(ret.begin(),ret.end());
  return ret;
}

std::string pow(std::string x,std::string n,std::string m){
  //pow(x,y)%m を求める。
  std::string ans="1";
  std::string bin_n=bin(n);
  //cout<<bin_n<<endl;
  while(bin_n!=""){
    //cout<<"ans: "<<ans<<", x: "<<x<<", bin_n: "<<bin_n<<endl;
    if(bin_n.at(bin_n.size()-1)=='1'){
      ans=mul(ans,x);
      ans=mod(ans,m);
    }
    x=mul(x,x);
    x=mod(x,m);
    bin_n.erase(bin_n.size()-1,1);
  }
  return ans;
}

std::string gcd(std::string x,std::string y){
  if(y.at(0)=='-'){
    std::cerr<<"Error: y must be positive"<<std::endl;
    exit(1);
  }
  if(y=="0")return x;
  return gcd(y,mod(x,y));
}

std::vector<std::string> ext_gcd(std::string x,std::string y){
  if(!cmp(x,y)){
    std::string tmp=x;
    x=y;
    y=tmp;
  }
  std::string a0=x,x0="1",y0="0",a1=y,x1="0",y1="1";
  while(a1!="0"){
    std::string q=div(a0,a1);
    std::string a2=sub(a0,mul(q,a1)),x2=sub(x0,mul(q,x1)),y2=sub(y0,mul(q,y1));
    a0=a1;
    x0=x1;
    y0=y1;
    a1=a2;
    x1=x2;
    y1=y2;
  }
  std::vector<std::string> ret={a0,x0,y0};
  return ret;
}

std::string inv_mod(std::string a,std::string N){
  std::vector<std::string> ret=ext_gcd(a,N);
  if(ret.at(0)!="1"){
    std::cerr<<"Error: inverse element is not find."<<std::endl;
    exit(1);
  }
  return mod(ret.at(2),N);
}

std::string convert2to10(std::string x){
  std::string a="1",ret="0";
  int x_size=x.size();
  for(int i=0;i<x_size;i++){
    if(x.at(x_size-i-1)=='1'){
      ret=add(ret,a);
    }
    a=mul(a,"2");
  }
  return ret;
}

std::string randbit(int k){
  // k bitの乱数を生成します。
  std::random_device rng;
  std::string ret="1";
  for(int i=0;i<k-1;i++){
    ret+=std::to_string(rng()%2);
  }
  return convert2to10(ret);
}

std::string random_int(int x,int y){
  //x桁以上y桁以下の自然数を生成します。
  if(x>y){
    int tmp=x;
    x=y;
    y=tmp;
  }
  std::random_device rng;
  std::string ret=std::to_string(rng()%9+1);
  int t=y-x+1;
  int rand_size=rng()%t+x;
  for(int i=0;i<rand_size-1;i++){
    ret+=std::to_string(rng()%10);
  }
  return ret;
}

std::string lcm(std::string x,std::string y){
  std::string ret=mul(x,y);
  return div(ret,gcd(x,y));
}

std::string random_range(std::string x,std::string y){
  //x以上y以下の範囲の自然数を生成
  int x_size=x.size(),y_size=y.size();
  if(x_size>y_size){
    int tmp=x_size;
    x_size=y_size;
    y_size=tmp;
  }
  std::string ret;
  do{
    ret=random_int(x_size,y_size+1);
  }while(!(cmp(y,ret) && cmp(ret,x)));
  return ret;
}

}
