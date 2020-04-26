// Example of Generator for Sum of 2 Numbers

#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

typedef long long ll;

using namespace std;

class Generator {
public:
  mt19937_64 rng;
  string filename;
  
  Generator(){
    rng = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
  }
  
  ll rand(ll mod = (ll)(1e18)){
    return rng()%mod + 1LL;
  }
  
  void random_generator(){
    cout << rand() << " " << rand() << endl;
  }
  
  void generate(string type){
    if(type == "general"){
        random_generator();
    } else {    
      cout << "Error: Wrong Test Type" << endl;
      exit(1);
    }
  } 
};

int32_t main(int argc, char *argv[]){
  if(argc < 2){
    cout << "Error: Expected Argument for Test Type" << endl;
    exit(1);
  }
   
  Generator gen = Generator();
  
  gen.generate(argv[1]);
}
