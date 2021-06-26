#include<iostream>
#include<stdio.h>
#include<vector>
#include<set>

typedef struct danhsachdinhke{
    int sodinhke = 0;
    std::set<int> dinhke;
} danhsachdinhke;

int main(){
    int n, i, j, count;
    std::cin >> n;
    std::vector<danhsachdinhke> Tree(n+1);
    count = n;

    for (i = 0; i < n; i++){
        int a, b; std::cin >> a >> b;
        Tree[a].sodinhke++;
        Tree[a].dinhke.insert(b);
        Tree[b].sodinhke++;
        Tree[b].dinhke.insert(a);
    }

    std::set<int> dinhbac1;
    for (i = 1; i < n+1; i++){
        if (Tree[i].sodinhke == 1){
            dinhbac1.insert(i);
        }
    }

    while(count-1){
        i = *dinhbac1.begin();
        dinhbac1.erase(i);
        j = *Tree[i].dinhke.begin();
        
        printf("%d ", j);
        
        Tree[j].sodinhke--;
        Tree[j].dinhke.erase(i);

        if (Tree[j].sodinhke == 1 && j != 0){
            dinhbac1.insert(j);
        }
        count--;
    } 

    return 0;
}