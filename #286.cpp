#include <iostream>
#include <vector>
#include <tuple>
using namespace std;


class City{
    public:
        City() { cout <<"contructed city"<<endl; }
        ~City() {}
        //returneaza daca modificarea este mai in stanga de modificarea m
        // mai in dreapta de modificarea  m+1
        // sau intre m si m+1
        int is_between(int pos, int v){
            if(v < get<0>(skyline[pos])) return -1;
            if(v > get<0>(skyline[pos+1])) return 1;
            return 0;
        }
        //returneaza pozitia la care ar trebuie inserata modificarea de nivel in vector
        int get_i(int v){
            
            int i=0,j=skyline.size() - 1;

            while(i<=j){
                int m=(i+j) / 2;
                int status = is_between(m,v);
                if(status == -1) j = m;
                else if(status == 1) i = m + 1;
                else return m + 1;
            }
            
            if(j == 0) return j;
            if(i == skyline.size()) return i;
            return -1;
        }
        //insereaza modificarea 
        int insereaza(int val,int h){
            int m = get_i(val);
            if( m == skyline.size())skyline.push_back(make_pair(val,0));
            else if(get<1>(skyline[m-1]) < h)
                skyline.insert(skyline.begin() + m,make_pair(val, h));
            return m;
        }
        //adauga inceputul si sfarsitul unui bloc
        void adauga(int left,int right,int height){
            if(skyline.size() == 0){
                skyline.push_back(make_pair(left,height));
                skyline.push_back(make_pair(right,0));
            }
            else if(left >= 0 ){

                int m=insereaza(left,height);
                int n = m+1;
                while(get<1>(skyline[n]) < get<1>(skyline[m]) && skyline.size() > n)
                    skyline.erase(skyline.begin() + n);
                if(m == 0)insereaza(right,0); 
                else insereaza(right,get<1>(skyline[m-1]));
            }
        }
        friend ostream &operator<<(ostream &out,
            const City &c){
            for(auto e:c.skyline){
                out <<"("<< get<0>(e) <<",";
                out << get<1>(e) << ") ";
            }
            return out;
        }
    private:
        vector<tuple<int,int> > skyline{};
};


int main()
{
    int left,right,height;
    City cluj;
    /*while(cin >> left >> right >>height){
        cout << left << right << height << endl;
        
    }*/
    cluj.adauga(0, 20, 5);
    cluj.adauga(8, 10, 6);
    cluj.adauga(16, 18, 7);
    cluj.adauga(22,26,4);
    cluj.adauga(24,30,10);
    cout << cluj << endl;
    
    return 0;
}

