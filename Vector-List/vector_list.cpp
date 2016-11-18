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

  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) { // vmesto vector<int>::iterator moje da napishem auto
    cout<< *it<<endl;
  }

list<int> l;
l.push_back(13);
l.push_back(14);
l.push_back(15);

list<int>::iterator  first = l.begin(); // ako napishem --l.end(), vmesto begin, trqbva da izvede 15; pishem s -- predi end, zashtoto
                                        // end sochi kum poslednata kutiika, koqto vsushtnost e prazna 
                                        //ako anpishem ++l.begin() ;  vzima vtoriq element, t.e. 14
cout<< *first <<endl; //* e predefiniran za nego ; izvejda 13
 
  
  for(list<int>::iterator it=l.begin(); it != l.end(); ++it) {  //vmesto list<int>::iterator moje da napishem samo auto
    cout<< *it<<endl;
  }
  // shte izvede chuislata 13, 14, 15
  
  for (int n : l) {   //gledai tozi spisuk otdqsno, koito trqbva da sudurja iteratori,
                      //...zapisvai iteratora v promenlivata n i mi dai dostup do promenlivata n
    //dostupvame danni v tozi spisuk
    //raboti za list, vector, nqma da raboti za stek i za opashka
    //obhojda elementite posledovatelno 
    cout<< n << endl;
  }
  
  auto n=7; // auto slaga samo podhodqsht tip na promenlivata //minimum sus c++ 11
  cout<< n <<endl;
  
system("pause");
return 0;
}
