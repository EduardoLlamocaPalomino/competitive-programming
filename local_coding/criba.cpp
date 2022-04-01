int min_p[N], pmax[N], func[N];
vector<int> prim;

void sieve(){
  func[1] = 1;
  for(int i = 2; i < N; i++){
    if(!min_p[i]){
      min_p[i] = i;
      prim.push_back(i);
      func[i] = ; // valor para i = p
      pmax[i] = i;
    }
    for(int j = 0; j < sz(prim) && i * prim[j] < N; j++){
      min_p[i * prim[j]] = prim[j];
      if(min_p[i] > prim[j]){
        func[i * prim[j]] = func[i] * func[prim[j]];
        pmax[i * prim[j]] = prim[j];
      }
      else{
        if(pmax[i] == i) func[i * prim[j]] = ; // llenar para i * prim[j] = p ** k
        else func[i * prim[j]] = func[i/pmax[i]] * func[pmax[i] * prim[j]];
        pmax[i * prim[j]] = pmax[i] * prim[j];
        break;
      }
    }
  }
}
