
// Fear is freedom! Subjugation is liberation! Contradiction is truth!

struct Trie {
  vector<int*> trie{new int[alpha]()};
  vector<int> fail{0};
  vector<int> cnt_word{0};
  vector<string> stor;
  void Add(string& s){
    stor.push_back(s);
    int cur = 0;
    for(char c: s){
      if(!trie[cur][c - 'a']){
        trie[cur][c - 'a'] = trie.size();
        trie.push_back(new int[alpha]());
        fail.push_back(0);
        cnt_word.push_back(0);
      }
      cur = trie[cur][c - 'a'];
    }
    cnt_word[cur]++;
  }
  void Build(){
    queue<int> q; q.push(0);
    while(!q.empty()){
      int u = q.front(); q.pop();
      for(int i = 0; i < alpha; i++){
        int v = trie[u][i];
        if(!v) continue;
        q.push(v);
        if(!u) continue;
        fail[v] = fail[u];
        while(fail[v] && !trie[fail[v]][i]) fail[v] = fail[fail[v]];
        fail[v] = trie[fail[v]][i];
        cnt_word[v] += cnt_word[fail[v]];
      }
    }
  }
  Long Query(string& s){
    Long ret = 0;
    int cur = 0;
    for(char c: s){
      while(cur && !trie[cur][c - 'a']) cur = fail[cur];
      cur = trie[cur][c - 'a'];
      ret += cnt_word[cur];
    }
    return ret;
  }
};

vector<Trie> aho;

void add(string& s){
  Trie nu; nu.Add(s);
  while(!aho.empty() && nu.stor.size() == aho.back().stor.size()){
    for(string& s: aho.back().stor) nu.Add(s);
    aho.pop_back();
  }
  aho.push_back(nu);
  aho.back().Build();
}
