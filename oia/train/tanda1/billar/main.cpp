#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x;
  int y;
  Point(int nx, int ny): x(nx), y(ny) {}
  Point(){}
};

#define CMP(u, v) if(u != v) return u < v
// ps = midpoint of coordinates of subsegments. rs are indices in ps

vector<bool> broken(vector<Point> ps, vector<int> rs) {
  vector<vector<int>> conn(ps.size(), vector<int>());
  vector<int> iot(ps.size());
  iota(iot.begin(), iot.end(), 0);

  vector<int> ord_x;
  copy_if(iot.begin(), iot.end(), back_inserter(ord_x), [&](int n){return ps[n].x % 2 == 1;});
  sort(ord_x.begin(), ord_x.end(), [&](int a, int b){
    CMP(ps[a].x, ps[b].x);
    CMP(ps[a].y, ps[b].y);
    return false;
  });

  for(int i = 0; i < ord_x.size(); i += 2) {
    conn[ord_x[i]].push_back(ord_x[i + 1]);
    conn[ord_x[i + 1]].push_back(ord_x[i]);
  }

  vector<int> ord_y;
  copy_if(iot.begin(), iot.end(), back_inserter(ord_y), [&](int n){return ps[n].y % 2 == 1;});
  sort(ord_y.begin(), ord_y.end(), [&](int a, int b){
    CMP(ps[a].y, ps[b].y);
    CMP(ps[a].x, ps[b].x);
    return false;
  });

  for(int i = 0; i < ord_y.size(); i += 2) {
    conn[ord_y[i]].push_back(ord_y[i + 1]);
    conn[ord_y[i + 1]].push_back(ord_y[i]);
  }

  vector<bool> visited(ps.size(), false);
  for(auto r: rs) {
    int t = r;
    while(!visited[t]) {
      visited[t] = true;
      if(visited[conn[t][0]] && conn[t].size() >= 2){
        t = conn[t][1];
      } else {
        t = conn[t][0];
      }

    }
  }

  return visited;
}

template<typename T>
void dbg(vector<T> ns) {
  for(auto n : ns) {
    cerr << n << " ";
  } cerr << endl;
}

tuple<vector<Point>, vector<int>, vector<bool>, vector<pair<Point, Point>>> breaker(vector<pair<Point, Point>> ls) {
  vector<Point> ps;
  vector<int> indices;
  vector<bool> tilt;
  vector<pair<Point, Point>> orig;
  for(int k = 0; k < ls.size(); ++k) {
    auto l = ls[k];
    int dx = l.first.x - l.second.x;
    int dy = l.first.y - l.second.y;
    int d = max(abs(dx), abs(dy));
    for(int i = 1; i < 2 * d; i += 2) {
      // ofs << "did " << i << endl;
      int nx = 2 * l.first.x - (dx / d) * i;
      int ny = 2 * l.first.y - (dy / d) * i;
      ps.emplace_back(nx, ny);
      indices.emplace_back(k);
      tilt.push_back(l.first.x > l.second.x);
      orig.emplace_back(
        Point((nx + dx / d) / 2, (ny + dy / d) / 2),
        Point((nx - dx / d) / 2, (ny - dy / d) / 2)
      );
    }
  }

  return make_tuple(ps, indices, tilt, orig);
}

bool coll(Point a, Point b) {
  if(abs(a.x - b.x) != 0 && abs(a.x - b.x) != 2) return false;
  if(abs(a.y - b.y) != 0 && abs(a.y - b.y) != 2) return false;
  return true;
}

pair<Point, Point> to_original(Point a, Point b, bool tilt) {
  if(a.x == b.x && a.y == b.y) {
    if(tilt) {
      return {Point(a.x / 2, a.y / 2), Point((a.x + 1) / 2, (a.y + 1) / 2)};
    } else {
      return {Point((a.x + 1) / 2, a.y / 2), Point(a.x / 2, (a.y + 1) / 2)};
    }
  } else {
    Point out_a;
    Point out_b;
    if(a.x < b.x) {
      out_a.x = a.x / 2;
      out_b.x = (b.x + 1) / 2;
    } else {
      out_a.x = (a.x + 1) / 2;
      out_b.x = b.x / 2;
    }

    if(a.y < b.y) {
      out_a.y = a.y / 2;
      out_b.y = (b.y + 1) / 2;
    } else {
      out_a.y = (a.y + 1) / 2;
      out_b.y = b.y / 2;
    }

    return {out_a, out_b};
  }
}

int main() {
  ofstream ofs("billar.out");
  ifstream ifs("billar.in");
  int n;
  ifs >> n;
  vector<pair<Point, Point>> ls;
  for(int i = 0; i < n; ++i) {
    ls.emplace_back();
    ifs >> ls.back().first.x >> ls.back().first.y;
  }
  for(int i = 0; i < n; ++i) {
    int ne = i == (n - 1) ? 0 : (i + 1);
    ls[i].second = ls[ne].first;
  }
  /*for(auto pa : ls) {
    ofs << pa.first.x << " " << pa.first.y << " " << pa.second.x << " " << pa.second.y << endl;
  }*/
  // ls.emplace_back();
  // cin >> ls.back().first.x >> ls.back().first.y >> ls.back().second.x >> ls.back().second.y;
  Point pa;
  Point pb;
  ifs >> pa.x >> pa.y;
  ifs >> pb.x >> pb.y;
  // ofs << pa.x << " " << pa.y << " " << pb.x << " " << pb.y << endl;
  ls.emplace_back(Point(pa.x, pa.y), Point(pa.x, pb.y));
  ls.emplace_back(Point(pa.x, pb.y), Point(pb.x, pb.y));
  ls.emplace_back(Point(pb.x, pb.y), Point(pb.x, pa.y));
  ls.emplace_back(Point(pb.x, pa.y), Point(pa.x, pa.y));

  vector<Point> ps;
  vector<int> indices;
  vector<bool> tilt;
  // tie(ps, indices, tilt) = breaker(ls);
  auto t = breaker(ls);
  ps = get<0>(t);
  indices = get<1>(t);
  tilt = get<2>(t);
  vector<pair<Point, Point>> orig = get<3>(t);
  vector<int> rect;
  for(int i = 0; i < indices.size(); ++i) {
    // ofs << i << " " << indices[i] << endl;
    if(indices[i] >= ls.size() - 4) {
      rect.push_back(i);
    }
  }
  vector<bool> reach = broken(ps, rect);

  // vector<pair<int, int>> maximals{{0, 0}};
  // for(int i = 0; i < 
  // dbg(reach);
  vector<bool> reach_wall;
  for(int i = 0; i < reach.size(); ++i) {
    if(indices[i] < ls.size() - 4) {
      reach_wall.push_back(reach[i]);
    }
  }
  // dbg(reach_wall);

  vector<pair<int, int>> maximals;
  for(int i = 0; i < reach_wall.size(); ++i) if(reach_wall[i]) {
    if(maximals.empty() || !coll(ps[maximals.back().second], ps[i])) {
      maximals.emplace_back(i, i);
    } else {
      maximals.back().second = i;
    }
  }

  if(coll(ps[maximals[0].first], ps[maximals.back().second])) {
    maximals[0].first = maximals.back().first;
    maximals.pop_back();
  }

  for(auto p : maximals) {
    //ofs << p.first.x / 2 << " " << p.first.y / 2 << " " << (p.second.x + 1) / 2 << " " << (p.second.y + 1) / 2 << endl;
    //auto pa = to_original(ps[p.first], ps[p.second], tilt[p.first]);
    pair<Point, Point> pa = {orig[p.first].first, orig[p.second].second};
    ofs << pa.first.x << " " << pa.first.y << " " << pa.second.x << " " << pa.second.y << endl;
  }
  /*
  int n;
  cin >> n;
  vector<pair<Point, Point>> ls(n);
  vector<Point> vs;
  for(int i = 0; i < n; ++i) {
    vs.emplace_back();
    cin >> vs.back().x >> vs.back().y;
  }
  for(int i = 0; i < n - 1; ++i) {
    ls[i].first = vs[i];
    ls[i].second = vs[i + 1];
  }
  ls[n - 1].first = vs[n - 1];
  ls[n - 1].second = vs[0];

  for(auto p : breaker(ls).first) {
    ofs
    << p.x << " " << p.y << endl;
  }
  */

  /*
  int n;
  cin >> n;
  vector<Point> ps;
  for(int i = 0; i < n; ++i) {
    ps.emplace_back();
    cin >> ps.back().x >> ps.back().y;
  }

  int k;
  cin >> k;
  vector<int> ks;
  for(int i = 0; i < k; ++i) {
    ks.emplace_back();
    cin >> ks.back();
  }

  dbg(broken(ps, ks));
  */
}


