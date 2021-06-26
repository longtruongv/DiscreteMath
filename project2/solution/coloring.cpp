#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<iomanip>
#include<algorithm> // find()

using namespace std;

//Mau sac sinh ra la khac nhau (co kiem tra), nhung co the RAT GIONG NHAU
string random_mausac(){
    stringstream rgb;
    for (int i = 0; i < 6; i++){
        rgb << hex << rand()%16;
    }
    return rgb.str();
}

int main(){
    srand(time(0));
    int sodinh, socanh, a, b, somausac = 1;

    ifstream dothi; dothi.open("dothi.txt");
    ofstream dothitomau("dothitomau.dot");
    dothi >> sodinh >> socanh;

    set<int> danhsachdinhke[sodinh]; //Danh sach chi luu dinh ke co gia tri nho hon gia tri dinh
    int maudinh[sodinh]; //Danh sach index cho mau sac cua cac dinh (danhsachmausac)
    maudinh[0] = 0;

    dothitomau << "graph dothi \n{\n"; 
    vector<string> danhsachmausac; danhsachmausac.push_back(random_mausac()); //Danh sach mau sac

    //Nhap input, xuat danh sach canh ra output
    for (int i = 0; i < socanh; i++){
        dothi >> a >> b;
        if (a > b){
            danhsachdinhke[a-1].insert(b-1);
        } else {
            danhsachdinhke[b-1].insert(a-1);
        }

        dothitomau << "\t" << a << " -- " << b << ";\n";
    }

    //Xu li mau sac: xet lan luot cac dinh
    for (int i = 1; i < sodinh; i++){
        //Mau sac phu hop cho dinh dang xet
        //0 la co the to duoc, 1 la khong to duoc
        bool mausac[somausac+1] = {0};

        //Xet cac dinh ke: mau sac cua dinh ke tro thanh khong to duoc
        for (int k : danhsachdinhke[i]){
            mausac[maudinh[k]] = 1;
        }

        //Tim mau sac co the to duoc dau tien
        int j = 0;
        while (1){
            if (!mausac[j]){
                maudinh[i] = j;
                break;
            }
            j++;
        }

        //Tao them mau moi neu khong to duoc mau sac duoc tao ra truoc do
        if (j == somausac){
            somausac++;
            string str = random_mausac();
            if (find(danhsachmausac.begin(), danhsachmausac.end(), str) == danhsachmausac.end()){
                danhsachmausac.push_back(str);
            }
        }
    }

    //In ra terminal so mau sac da su dung, danh sach cac mau sac tren
    cout << somausac << endl;
    for(string s : danhsachmausac){
        cout << s << endl;
    }

    //Xuat mau sac dinh ra output   
    for(int i = 0; i < sodinh; i++){
        dothitomau << "\t" << i+1 << " [fillcolor=\"#" << danhsachmausac[maudinh[i]] << "\", style=filled];\n";
    }
    dothitomau << "}";

    return 0;
}