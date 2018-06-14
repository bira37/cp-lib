struct tnode {
  tnode *adj[SIZE_NODE];
  tnode(){
    for(int i=0; i<SIZE_NODE; i++) adj[i] =  NULL;
  }
};

struct Trie{

  tnode *t;
  
  void init(){
    t = new tnode();
  }
  
  void add(){
    tnode *cur = t;
    
  }
  
  int query(){
    tnode *cur = t;
  }
  
  void remove(){
    tnode *cur = t;
  } 

} trie;
