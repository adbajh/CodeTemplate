/* 参考 https://oi-wiki.org/string/trie/ */
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

/***** 字典树 *****/

struct Trie {
    int nxt[100000][26], cnt;
    bool exists[100000];
    Trie() {
        memset(nxt,0,sizeof(nxt));
        memset(exists,0,sizeof(exists));
        cnt = 0;
    }
    void insert(char *str, int len) {
        int pos = 0;
        for (int i = 0; i < len; i++) {
            int child = str[i] - 'a';
            if (!nxt[pos][child]) nxt[pos][child] = ++cnt;
            pos = nxt[pos][child];
        }
        exists[pos] = true;
    }
    bool find(char *str, int len) {
        int pos = 0;
        for (int i = 0; i < len; i++) {
            int child = str[i] - 'a';
            if (!nxt[pos][child]) return false;
            pos = nxt[pos][child];
        }
        return exists[pos];
    }
};