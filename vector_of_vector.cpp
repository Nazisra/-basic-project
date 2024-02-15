#include <bits/stdc++.h>
using namespace std;

void printfvec(vector<int> &v)
{

   cout << "size is " << v.size() << endl;
   for (int i = 0; i < v.size(); i++)
   {
      cout << v[i] << " ";
   }                                                                    /*3
                                                                       2
                                                                       11 23                           input formet
                                                                       
                                                                       3
                                                                       1 2 3

                                                                       3
                                                                        7 6 4*/

   cout << endl;
}

int main()
{

   vector<vector<int>> v;
   cout << "how many vector you want : ";
   int n;
   cin >> n;

   for (int i = 0; i < n; i++)
   {
      int x;
      cout << endl
           << "size of the aray or vector : "; // vector er man nibo sob index er jonno
      cin >> x;
      vector<int> temp;

      for (int j = 0; j < x; j++)
      {

         int k;
         cin >> k;
         temp.push_back(k);
      }

      v.push_back(temp); // 2 number er sob element er last a add hobe eta
   }
   v[1].push_back(100);
   v.push_back(vector<int>());
   v[2].insert(v[2].begin()+1,40);



  cout<<v[1].front()<<endl;
  cout<<v[1].back()<<endl;
  


   for (int s = 0; s < v.size(); s++)
   {

      printfvec(v[s]);
   }
}