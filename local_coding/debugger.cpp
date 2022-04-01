
template<typename A, typename B> 
ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> 
ostream& operator<<(ostream& os, const T_container& v) { os << '{'; string sep; for (const T& x : v) os << sep << x, sep = ", "; return os << '}'; }

template<typename... Args> void debug_out(Args... args) { ((cerr << ' ' << args), ...); }
#ifdef NTR_GOD
  #define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
  int __db_level = 0;
  struct Debug_Block {
    Debug_Block() { clog << "{" << endl; ++__db_level; }
    ~Debug_Block() { --__db_level; clog << "}" << endl; }
  };
  #define DB() Debug_Block dbbl##__LINE__
  #define dbg(...) clog << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__), cerr << endl
#else
  #define clog if(0) cerr
  #define DB(...)
  #define dbg(...)
#endif
