#include <string>
#include <random>
#include "randbit.h"

namespace randbit{

std::string rand_binary_bit(int bit){
	std::random_device rng;
	std::string ret="1";
	for(int i=0;i<bit-1;i++){
		ret+=std::to_string(rng()%2);
	}
	return ret;
}

}
