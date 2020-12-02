#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

double ComputeMedian(vector<long>& p_data)
{
  size_t size = p_data.size();

  if (size == 0) return 0;
  else
  {
    sort(p_data.begin(), p_data.end());
    if (size % 2 == 0) return (p_data[size / 2 - 1] + p_data[size / 2]) / 2;
    else               return p_data[size / 2];
  }
}

int main()
{
    long x_min(2e30), x_max(-2e30);
    long y_median;
    int N;
    long l_result(0);
    cin >> N; cin.ignore();
    vector<long> ordinates(N, 0);
    
    for (auto i = 0; i < N; i++) 
    {
        long X;
        cin >> X >> ordinates[i]; cin.ignore();
        
        x_min = X < x_min ? X : x_min;
        x_max = X > x_max ? X : x_max;
    }
    
    y_median = ComputeMedian(ordinates);

    l_result += x_max - x_min;
    for( auto it = ordinates.begin(); it != ordinates.end(); ++it)
    {
        l_result += abs(*it - y_median);
    }
    
    cout << l_result << endl;
}