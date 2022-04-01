
/* Finds the convex hull of a given set of points. This templates requires
 * the struct point defined in point_integer.cpp or in point_double.cpp
 *
 * p - (input) vector of points for which the convex hull will be found.
 * ch - convex hull of `p` in counter-clockwise order.
 * if chull == line returns lines if chull = point returns empty
 */

vector<point> convexHull(vector<point> p) {
  int n = sz(p);
	sort(p.begin(), p.end());
	vector<point> low, up;
	for(int i = 0; i < n; i++){
    while(sz(up) >= 2 && !right(up[sz(up)-2], up.back(), p[i]))
      up.pop_back();
    up.push_back(p[i]);
    while(sz(low) >= 2 && !left(low[sz(low)-2], low.back(), p[i]))
      low.pop_back();
    low.push_back(p[i]);
	}
  vector<point> ch;
	for(int i = 0; i < sz(low) - 1; i++) ch.push_back(low[i]);
	for(int i = sz(up) - 1; i >= 1; i--) ch.push_back(up[i]);
  return ch;
}
