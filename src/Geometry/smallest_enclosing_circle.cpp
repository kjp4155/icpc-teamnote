typedef pair<double, double> pdd;
double sq(double x){ return x*x; }
pdd operator+(pdd l, pdd r){ return pdd(l.Fi + r.Fi, l.Se + r.Se); }
pdd operator-(pdd l, pdd r){ return pdd(l.Fi - r.Fi, l.Se - r.Se); }
pdd operator*(pdd l, double r){ return pdd(l.Fi * r, l.Se * r); }
double operator^(pdd l, pdd r){ return l.Fi * r.Se - l.Se * r.Fi; }
double size(pdd x){ return hypot(x.Fi, x.Se); }
double size2(pdd x){ return sq(x.Fi) + sq(x.Se); }
pdd r90(pdd v){ return pdd(-v.Se, v.Fi); }
const double EPS = 1e-8;

struct circle{
    circle(pdd O, double r):O(O), r(r){}
    circle(){}
    pdd O;
    double r;
};

int intersect(pdd a, pdd b, pdd u, pdd v, pdd &des){
    if (abs(b^v) < EPS) return 0;
    des = pdd(((a - u) ^ v) / (v^b), ((a - u) ^ b) / (v^b));
    return 1;
}

int get_circle(pdd p0, pdd p1, pdd p2, circle &des){
    pdd a = (p0+p1) * 0.5, b = r90(p0-p1);
    pdd u = (p0+p2) * 0.5, v = r90(p0-p2), R;
    if( !intersect(a, b, u, v, R) ) return 0;
    des = circle(a+b*R.Fi, size(a+b*R.Fi - p0));
    return 1;
}

circle make_circle(vector<pdd> Q){
    if( Q.size() == 0 ) return circle(pdd(0, 0), 0);
    if( Q.size() == 1 ) return circle(Q[0], 0);
    circle res;
    for(int i = 0; i < Q.size(); i++){
        swap(Q.back(), Q[i]);
        res = circle((Q[0]+Q[1]) * 0.5, size(Q[0]-Q[1])/2);
        bool ch = 1; for(pdd c : Q) if( size2(c-res.O) > sq(res.r) + EPS ) ch = 0;
        if( ch ) return res;
        swap(Q.back(), Q[i]);
    }
    get_circle(Q[0], Q[1], Q[2], res);
    return res;
}

circle smallest_circle(vector<pdd> &P, vector<pdd> &Q, int N) {
    circle c = make_circle(Q);
    if( N == 0 || Q.size() >= 3 ) return c;
    for(int i = 0; i < N; i++){
        if( size2(c.O - P[i]) > sq(c.r) ){
            Q.push_back(P[i]);
            c = smallest_circle(P, Q, i);
            Q.pop_back();
        }
    }
    return c;
}
circle smallest_get(vector <pdd> P) {
    vector <pdd> T;
    return smallest_circle(P, T, szz(P));
}
