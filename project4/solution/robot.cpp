#include<iostream>
#include<fstream>
#include<climits> //INT_MAX
#include<vector>
#include<map>
#include<set>
#include<utility> //pair


using namespace std;

typedef pair<int, int> Key;
typedef vector<pair<int, int>> Value;

//Ham tim va tra ve vi tri Alarm Clock keu dau tien
int minAlarm(vector<int> dist, vector<bool> isAlarmed, int n){
    int min = INT_MAX, min_idx;
    for (int i = 0; i < n; i++){
        if (!isAlarmed[i] && dist[i] < min){
            min = dist[i];
            min_idx = i;
        }
    }
    return min_idx;
}

//Ham tinh khoang cach ngan nhat giua cac dinh
void calcuDistance(vector<vector<int>> &sD, vector<vector<bool>> e, int n){
    for (int V = 0; V < n; V++){ //xet lan luot cac dinh goc V
        //Mang luu khoang cach ngan nhat tu cac dinh toi V
        vector<int> dist(n, INT_MAX);

        //true neu Alarm Clock da keu tai dinh do
        vector<bool> isAlarmed(n, false);
        dist[V] = 0;

        for (int count = 0; count < n-1; count++){
            int min_idx = minAlarm(dist, isAlarmed, n);
            isAlarmed[min_idx] = true;

            for (int i = 0; i < n; i++){
                if (!isAlarmed[i] && e[min_idx][i] && dist[min_idx] != INT_MAX && dist[min_idx] + sD[min_idx][i] < dist[i]){
                    dist[i] = dist[min_idx] + sD[min_idx][i];
                }
            }
        }

        //Cap nhat shortestDist
        for (int i = 0; i < n; i++){
            sD[V][i] = dist[i];
        }
    }
}

//Dung BFS tim duong di tu trang thai (a, b) toi (c, d)
Value findPath(int a, int b, int c, int d, map<Key, Value> locationStatus){
    //Lich trinh di chuyen
    Value schedule;

    //Cac trang thai da toi
    set<Key> isVisited;

    //Luu trang thai va trang thai cha cua no
    map<Key, Key> previous;

    //Hang doi cac trang thai
    Value queue;

    //true neu tim thay trang thai (c, d)
    bool isFound = false;

    //Xuat phat tu trang thai (a, b)
    Key u = {a, b};
    isVisited.insert(u);
    queue.push_back(u);

    while (!isFound && !queue.empty()){
        queue.erase(queue.begin());

        for (Key x : locationStatus[u]){
            if (isVisited.find(x) != isVisited.end()) continue;

            isVisited.insert(x);
            queue.push_back(x);
            previous.insert({x, u});

            if (x.first == c && x.second == d){
                isFound = true;
                break;
            }
        }

        u = queue.front();
    }

    //Viet lai lich trinh di chuyen
    u = {c, d};
    while (previous.find(u) != previous.end()) {
        schedule.insert(schedule.begin(), u);
        u = previous[u];
    }

    if (u.first != a && u.second != b){
        return Value();
    } else {
        schedule.insert(schedule.begin(), u);
        return schedule;
    }
}

int main(){
    int n, m, r, a, b, c, d;
    ifstream Graph; Graph.open("robotgraph.txt");
    Graph >> n >> m;

    //Mang 2D ghi khoang cach ngan nhat giua 2 dinh
    vector<vector<int>> shortestDist(n, vector<int> (n, -1));
    //Mang 2D ghi cac canh do thi
    vector<vector<bool>> edge(n, vector<bool> (n, false));
    //Mang 2D xet trang thai vi tri 2 robot co hop le
    vector<vector<bool>> isValidLoc(n, vector<bool> (n, false));
    
    //Nhap cac canh
    for (int i = 0; i < m; i++){
        int V1, V2, distance;
        Graph >> V1 >> V2 >> distance;
        shortestDist[V1][V2] = distance;
        shortestDist[V2][V1] = distance;
        edge[V1][V2] = true;
        edge[V2][V1] = true;
    }
    
    Graph >> a >> b >> c >> d >> r;

    //Cap nhat shortestDist
    calcuDistance(shortestDist, edge, n);

    //Map luu trang thai Key va danh sach trang thai co the toi tu Key
    map<Key, Value> locationStatus;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (shortestDist[i][j] > r){
                isValidLoc[i][j] = true;
                locationStatus.insert({{i, j}, Value()});
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (!isValidLoc[i][j]) continue;

            for (int k = 0; k < n; k++){
                //Neu trang thai (i, j) co duong di toi trang thai (k, j)
                if (edge[k][i] && isValidLoc[k][j]){
                    locationStatus[{i, j}].push_back({k, j});
                }

                //Neu trang thai (i, j) co duong di toi trang thai (i, k)
                if (edge[j][k] && isValidLoc[i][k]){
                    locationStatus[{i, j}].push_back({i, k});
                }
            }
        }
    }

    //Tim duong di tu trang thai (a, b) den trang thai (c, d)
    Value Path = findPath(a, b, c, d, locationStatus);

    if (Path.empty()){
        cout << "Khong the!" << endl;
    } else {
        for (auto x : Path){
            cout << x.first << " " << x.second << " " 
            << shortestDist[x.first][x.second] << endl;
        }
    }

    system("pause");
    return 0;
}