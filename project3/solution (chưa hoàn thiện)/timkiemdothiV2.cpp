#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<string>
#include<set>
//#include<map>


using namespace std;

typedef struct WordNode {
    string word;
    vector<struct WordNode*> LinkedWords;
} WN;


class WordGraph {
public:

    vector<WN> NodeList;
    set<string> RootList;

    WordGraph(){
        ifstream sgb ("sgb-words.txt");
        string word;
        while(true){
            if(!(sgb >> word)){
                break;
            }
            addNewWord(word);
        }
    }

    WN* findWord(string w){
        int s = 0, e = (int)NodeList.size()-1;
        while (s <= e){
            int m = s+(e-s)/2;
            int a = NodeList[m].word.compare(w);
            if (a == 0){
                return &NodeList[m];
            }
            if (a < 0){
                e = m-1;
            } else {
                s = m+1;
            }
        }
      
        cout << "404" << endl;
        return NULL;
    }

    int countConnectedComponent(){
        int count = 0;
        vector<string> queue;
        set<string> isVisited;

        
    }

private:

    bool isConnected(string w1, string w2){
        int dif = 0;
        if (w1.length() != 5 || w2.length() != 5){
            cout << "error" << endl;
            return false;
        }
        for (int i = 0; i < 5; i++){
            if (w1[i] != w2[i]){
                dif++;
                if (dif > 1){
                    return false;
                }
            }
        }
        return true;
    }
    
    void addNewWord(string w){
        WN* pNew = new WN;
        pNew->word = w;
        int index = 0;
        for (int i = 0; i < (int)NodeList.size(); i++){
            if (isConnected(pNew->word, NodeList[i].word)){
                pNew->LinkedWords.push_back(&NodeList[i]);
                NodeList[i].LinkedWords.push_back(pNew);
            }
            if (pNew->word.compare(NodeList[i].word) < 0){
                index = i+1;
            }
        }
        NodeList.insert(NodeList.begin()+index, *pNew);
    }
};


int main(){
    ofstream output("output.txt");

    WordGraph G;

    string w; cout << "input: "; cin >> w;
    WN* x = G.findWord(w);
    for (auto i : x->LinkedWords){
        output << i->word << endl;
    }

    return 0;
}