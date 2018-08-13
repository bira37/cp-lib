#include <bits/stdc++.h>
using namespace std;

///////////////////////////AUXILIARY VARIABLES////////////////////////////////////////////////
struct Chameleon{
  int id, place;
  Chameleon() {}
  Chameleon(int id, int place) : id(id), place(place) {}
  bool operator==(const Chameleon b) const{
    return id == b.id && place == b.place;
  }
};

int N,S,C,H,U;
Chameleon nearest; //nearest chameleon to beginning
vector< vector< Chameleon > > board; //periodic board
vector<int> chameleons; //position of each chameleon
vector<char> stripe; //periodic stripe pattern
vector<char> hand; //letters in hand
vector<char> bag; //letters in bag
vector< vector<int> > nxt, position;

///////////////////////////GAME FUNCTIONS AND VARIABLES//////////////////////////////////////

void build_game(){
  scanf("%d%d%d%d%d", &N, &S, &C, &H, &U);
  //cin >> N >> S >> C >> H >> U;
  stripe.resize(N);
  hand.resize(H);
  bag.resize(S);
  for(int i=0; i<N; i++) scanf(" %c", &stripe[i]);
  nxt.resize(N, vector<int>(C));
  position.resize(C, vector<int>());
  for(int i=0; i<stripe.size(); i++){
    position[stripe[i]-'A'].push_back(i);
  }
  for(int i=0; i<N; i++){
    //for each position process letter
    for(int l = 0; l < C; l++){
      int idx = upper_bound(position[l].begin(), position[l].end(), i) - position[l].begin();
      if(idx == position[l].size()){
        nxt[i][l] = (N - i) + position[l][0];
      }
      else nxt[i][l] = position[l][idx] - i;
    }
  }
  for(int i=0; i<H; i++){
    scanf(" %c", &hand[i]);
  }
  for(int i=0; i<S; i++){
    scanf(" %c", &bag[i]);
  }
  reverse(bag.begin(), bag.end());
  chameleons.resize(U);
  board.resize(N);
  for(int i=0; i<U; i++){
    chameleons[i] = i;
    board[i].push_back(Chameleon(i, i));
  }
  nearest = Chameleon(0,0);
}

struct Game {
  int N,S,C,H,U;
  Chameleon nearest; //nearest chameleon to beginning
  vector< vector< Chameleon > > board; //periodic board
  vector<int> chameleons; //position of each chameleon
  vector<char> stripe; //periodic stripe pattern
  vector<char> hand; //letters in hand
  vector<char> bag; //letters in bag
  vector<string> instructions;
  Game() {}
  Game(int N, int S, int C, int H, int U, Chameleon nearest, vector< vector< Chameleon > > board, vector<int> chameleons, vector<char> stripe, vector<char> hand, vector<char> bag) : N(N), S(S), C(C), H(H), U(U), nearest(nearest), board(board), chameleons(chameleons), stripe(stripe), hand(hand), bag(bag) {}
  
  void delete_from_board(int board_id, Chameleon cham){
    int id;
    for(int i=0; i<board[board_id].size(); i++){
      if(board[board_id][i] == cham) id = i;
    }
    board[board_id].erase(board[board_id].begin() + id);
  }

  void update_hand(char letter){
    int id;
    for(int i=0; i<H; i++){
      if(letter == hand[i]) id = i;
    }
    hand.erase(hand.begin() + id);
    hand.push_back(bag.back());
    bag.pop_back();
  }  

  Chameleon update_nearest(){ //returns nearest chameleon to beginning
    int distance, cham;
    distance = chameleons[0];
    cham = 0;
    for(int i=1; i<U; i++){
      if(distance > chameleons[i]){
        distance = chameleons[i];
        cham = i;
      }
    }
    return Chameleon(cham, distance);
  }

  void move(char letter){ //move the nearest chameleon
    //print movement
    instructions.push_back(to_string(nearest.id) + " " + letter + "\n"); 
    
    //update board and hand
    delete_from_board(nearest.place%N, nearest);
    update_hand(letter);
    
    //move the chameleon
    nearest.place+= nxt[nearest.place%N][letter-'A'];
    while(true){
      //check if we can put chameleon there
      bool occupied = false;
      for(Chameleon cham : board[nearest.place%N]){
        if(cham.place == nearest.place){
          occupied = true;
          break;
        }
      }
      if(occupied){
        nearest.place+= nxt[nearest.place%N][letter-'A'];
        continue;
      }
      else break;
    }
    
    //put the chameleon in correct place then update nearest
    board[nearest.place%N].push_back(nearest);
    chameleons[nearest.id] = nearest.place;
    nearest = update_nearest();
  }
  
  /////////////////////////////////MUTABLE FUNCTIONS///////////////////////////////////////
  
  int simulate_move(char letter){ //simulate the movement and return the final place
    Chameleon dummy = nearest;
    dummy.place+= nxt[dummy.place%N][letter-'A'];
    while(true){
      bool occupied = false;
      for(Chameleon cham : board[dummy.place%N]){
        if(cham.place == dummy.place){
          occupied = true;
          break;
        }
      }
      if(occupied){
        dummy.place+= nxt[dummy.place%N][letter-'A'];
        continue;
      }
      else break;
    }
    return dummy.place;
  }

  void greedy(){
    int best_move = -1;
    char chosen_letter = 'Z';
    for(int i=0; i<H; i++){
      int final_place = simulate_move(hand[i]);
      if(final_place > best_move){
        best_move = final_place;
        chosen_letter = hand[i];
      }
    }
    move(chosen_letter);
  }
  
  void allow_masks(int allow_mask){
    int best_move = -1;
    int best_allowed_move = -1;
    char chosen_letter = 'Z';
    char allowed_chosen_letter = 'Z';
    for(int i=0; i<H; i++){
      int final_place = simulate_move(hand[i]);
      if(final_place > best_move){
        best_move = final_place;
        chosen_letter = hand[i];
      }
      if(!(allow_mask & (1LL<<(hand[i] - 'A')))){
        if(final_place > best_allowed_move){
          best_allowed_move = final_place;
          allowed_chosen_letter = hand[i];
        }
      }
    }
    if(allowed_chosen_letter == 'Z') allowed_chosen_letter = chosen_letter;
    move(allowed_chosen_letter);
  }
};

Game create_instance(){
  return Game(N, S, C, H, U, nearest, board, chameleons, stripe, hand, bag);
}

void clone_game(Game & new_game, Game & instance){
  new_game.nearest = instance.nearest;
  new_game.board = instance.board;
  new_game.chameleons = instance.chameleons;
  new_game.hand = instance.hand;
  new_game.bag = instance.bag;
  new_game.instructions = instance.instructions;
}

//////////////////////////////////////////////////////////////////////////////////////////

int32_t main(){
  build_game();
  Game instance = create_instance();
  int gira = 0;
  for(int offset = S-80; instance.bag.size() > 0; offset-=80){
    int near = -1;
    int best_msk = -1;
    Game save;
    clone_game(save, instance);    
    for(int msk = 1; msk < (1<<C); msk++){
      bool allow = false;
      if(__builtin_popcount(msk) == 6){
        gira = (gira+1)%4;
        if(gira == 0) allow = true;
      }
      if(__builtin_popcount(msk) < 7 && !allow) continue;
      clone_game(instance, save);
      while(instance.bag.size() > 0 && instance.bag.size() > offset) instance.allow_masks(msk);
      if(near < instance.nearest.place){
        near = instance.nearest.place;
        best_msk = msk;
      }
    }
    clone_game(instance, save);
    while(instance.bag.size() > 0 && instance.bag.size() > offset) instance.allow_masks(best_msk);
  }
  for(string command : instance.instructions) printf("%c %c\n", command[0], command[2]);
}
