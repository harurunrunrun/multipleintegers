#include <string>
#include <vector>

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
}