#include <string>
#include <set>
#include <iostream>
using namespace std;

class Trie{
private:
    int cnt = 0;
    Trie* ptr[26] = {nullptr};
public:
    Trie(){
        cnt = 0;
        for(int i=0; i<26; i++) ptr[i] = nullptr;
    }
    void add(const string& word){
        Trie* now = this;
        for( const char& c : word ){
            int idx = c - 'a';
            if( now->ptr[idx] == nullptr ){
                now->ptr[idx] = new Trie();
            }
            now = now->ptr[idx];
        }
        now->cnt++;
    }
    bool search(const string& word, int L, int R){
        cout << "Search: " << word << ", " << L << ", " << R << endl;
        if( L == R && this->is_tail()){
            return true;
        }
        Trie* now = this;

        for(int i=L; i<R; i++){
            char c = word[i];

            if( c != '.' ){
                int idx = c - 'a';
                if( now->ptr[idx] == nullptr ){
                    return false;
                }
                now = now->ptr[idx];
            }
            else{
                for(int k=0; k<26; k++){
                    if( now->ptr[k] == nullptr ) continue;
                    if( now->ptr[k]->search( word, i+1, R ) ){
                        return true;
                    }
                }
                return false;
            }
        }
        return now->cnt > 0;
    }

    bool is_tail(){
        for(int i=0; i<26; i++){
            if( ptr[i] ) return false;
        }
        return true;
    }

};

class WordDictionary {
private:
    Trie* t;
public:
    WordDictionary() {
        t = new Trie();
    }
    
    void addWord(string word) {
        t->add(word);
    }
    
    bool search(string word) {
        return t->search(word, 0, word.size());
    }

};

int main(){
    WordDictionary* obj = new WordDictionary();
    cout << obj->search(".") << endl;
    obj->addWord("a");
    obj->addWord("dad");
    obj->addWord("bad");
    obj->addWord("mad");
    cout << obj->search(".") << endl;
    cout << obj->search("pad") << endl;
    cout << obj->search("bad") << endl;
    cout << obj->search(".ad") << endl;
    cout << obj->search("ba.") << endl;
    cout << obj->search("b..") << endl;
    cout << obj->search("b.") << endl;
    cout << obj->search(".a") << endl;
    cout << obj->search(".a.") << endl;
    return 0;
}