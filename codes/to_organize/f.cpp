#include <bits/stdc++.h>

using namespace std;

struct point{
  double x,y,z;
  void operator=(const point & b){
    x = b.x;
    y = b.y;
    z = b.z;
  }
};

point cross(point a, point b){
  point ret;
  ret.x = a.y*b.z - b.y*a.z;
  ret.y = a.z*b.x - a.x*b.z;
  ret.z = a.x*b.y - a.y*b.x;
  return ret;
}

int main(){
  int num;
  cin >> num;
  point v[num];
  for(int i=0; i<num; i++) cin >> v[i].x >> v[i].y >> v[i].z;
  
  point n;
  double mx = 0;
  for(int i=0; i<num; i++){
    point nn = cross(v[i], v[(i+1)%num]);
    if(nn.x*nn.x + nn.y*nn.y + nn.z*nn.z > mx){
      n = nn;
      mx = nn.x*nn.x + nn.y*nn.y + nn.z*nn.z;
    }
  }
  
  point cur;
  cur.x = 0, cur.y = 0, cur.z = 0;
  
  for(int i=0; i<num; i++){
    point res = cross(v[i], v[(i+1)%num]);
    cur.x += res.x;
    cur.y += res.y;
    cur.z += res.z;
  }
  
  double sz = sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
  
  n.x /= 2.*sz;
  n.y /= 2.*sz;
  n.z /= 2.*sz;
  
  double ans = n.x*cur.x + n.y*cur.y + n.z*cur.z;
  
  double area = abs(ans);
  
  cout << fixed << setprecision(9) << area << endl; 
} 
