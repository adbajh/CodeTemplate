#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct BKnode {
    string word;
    map<int,int> child;
};

class BKTree { // 寻找与查询单词距离不超过特定值的单词
public:
    BKTree() {
        cnt = 0;
        for (int i = 0; i < 100000; i++) {
            nodes[i].word = "";
            nodes[i].child.clear();
        }
    }
    void insert(string word) {
        int pos = 0;
        while (1) {
            if (word == nodes[pos].word) return;
            int diff = distance(word, nodes[pos].word);
            auto it = nodes[pos].child.find(diff);
            if (it == nodes[pos].child.end()) {
                nodes[pos].child[diff] = ++cnt;
                nodes[cnt].word = word;
                return;
            }
            pos = it->second;
        }
    }
    void find(const string &word, int max_diff, vector<string> &ans) {
        ans.clear();
        if (nodes[0].word == "") return;
        return find_recursive(0,word,max_diff,ans);
    }
private:
    BKnode nodes[100000];
    int cnt, dp[100][100];
    int distance(string str1, string str2) {
        memset(dp,0x7f,sizeof(dp));
        int x = str1.length();
        int y = str2.length();
        for (int i = 0; i < x; i++) dp[i][0] = i;
        for (int j = 0; j < y; j++) dp[0][j] = j;
        for (int i = 1; i <= x; i++) {
            for (int j = 1; j <= y; j++) {
                dp[i][j] = min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+(str1[i]!=str2[j]));
            }
        }
        return dp[x][y];
    }
    void find_recursive(int idx, const string &word, int max_diff, vector<string> &ans) {
        int dist = distance(word,nodes[idx].word);
        if (dist <= max_diff) ans.push_back(nodes[idx].word);
        for (int i = max(1, dist - max_diff); i <= min(dist + max_diff, 20); i++) {
            auto it = nodes[idx].child.find(i);
            if (it != nodes[idx].child.end()) find_recursive(it->second,word,max_diff,ans);
        }
    }
};
