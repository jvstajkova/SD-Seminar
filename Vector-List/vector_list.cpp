#include<iostream>
#include<vector>
#include<list>

using namespace std;

int main() {

vector<int> v;
v.push_back(3);
v.push_back(4);
v.push_back(5);



for (int i=0; i<3; i++) {
cout<<v[i]<<endl;
} // 3, 4, 5


list<int> l;
l.push_back(13);
l.push_back(14);
l.push_back(15);

list<int>::iterator  first = l.begin(); // ako napishem --l.end(), vmesto begin, trqbva da izvede 15; pishem s -- predi end, zashtoto
                                        // end sochi kum poslednata kutiika, koqto vsushtnost e prazna 
                                        //ako anpishem ++l.begin() ;  vzima vtoriq element, t.e. 14
cout<< *first <<endl; //* e predefiniran za nego ; izvejda 13
 
system("pause");
return 0;
}
