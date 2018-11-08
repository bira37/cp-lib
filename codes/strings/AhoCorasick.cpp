map<char, int> *nxt;
int *slinks;
vector<int> *dlinks;

void aho_build(const vector<string>& words) {
    int len_words = 1;
    for(const string& w : words) {
        len_words += w.size();
    }
    nxt = new map<char, int>[len_words];
    dlinks = new vector<int>[len_words];
    int root = 0, fre = 1;
    for(int i = 0; i < words.size(); i++) {
        const string& w = words[i];
        int cur = root;
        for(const char& c : w) {
            if(nxt[cur].count(c)==0) {
                nxt[cur][c] = fre++;
            }
            cur = nxt[cur][c];
        }
        dlinks[cur].push_back(i);
    }

    slinks = new int[len_words];
    slinks[0] = -1;
    queue<int> q;
    for(const pair<char, int>& ch : nxt[root]) {
        slinks[ch.second] = root;
        q.push(ch.second);
    }
    while(!q.empty()) {
        const int cur = q.front();
        q.pop();
        for(const pair<char, int>& ch : nxt[cur]) {
            int sl = slinks[cur];
            while(sl != root && nxt[sl].count(ch.first) == 0)
                sl = slinks[sl];
            if(nxt[sl].count(ch.first) != 0)
                sl = nxt[sl][ch.first];
            slinks[ch.second] = sl;
            copy(dlinks[sl].begin(), dlinks[sl].end(), back_inserter(dlinks[ch.second]));
            q.push(ch.second);
        }
    }
}
vector< vector<int> > aho_matches(const vector<string>& words, const string& text) {
    int root = 0;
    int cur = root;
    vector< vector<int> > matches(text.size());
    // vector< vector<int> > matches(words.size());
    for(int i = 0; i < text.size(); i++) {
        while(cur != root && nxt[cur].count(text[i]) == 0)
            cur = slinks[cur];
        if(nxt[cur].count(text[i]) != 0)
            cur = nxt[cur][text[i]];

        // returns matching words per position in text
        for(int w_id : dlinks[cur]) {
            matches[i-words[w_id].size()+1].push_back(w_id);
        }

        // // returns matching positions per word
        // for(int w_id : dlinks[cur]) {
        //     matches[w_id].push_back(i-words[w_id].size()+1);
        // }
    }
    return matches;
}

int32_t main() {
    vector<string> words;
    words.push_back("he");
    words.push_back("hers");
    words.push_back("his");
    words.push_back("she");
    string text = "heishers sheishis hihershe!";
    aho_build(words);
    vector< vector<int> > matches = aho_matches(words, text);

    for(int i = 0; i < matches.size(); i++) {
        cout << i;
        for(int id : matches[i]) {
            cout << " " << words[id];
        }
        cout << endl;
    }
    // for(int i = 0; i < matches.size(); i++) {
    //     cout << words[i];
    //     for(int p : matches[i]) {
    //         cout << " " << p;
    //     }
    //     cout << endl;
    // }
}
