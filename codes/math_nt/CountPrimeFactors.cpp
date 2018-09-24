namespace NT{
  
  int CountPrimeFactors(int x){
    
    int ans = 0;
    for(int i=2; i*i*i <= x; i++){
      while(x%i == 0){
        ans++;
        x/=i;
      }
    }
    
    if(PrimalityTest(x, 10)) ans++;
    else if((int)sqrt(x)*(int)sqrt(x) == x && PrimalityTest((int)sqrt(x), 10)) ans+=2;
    else if(x != 1) ans+=2;
    
    return ans;
    
  }
  
}

