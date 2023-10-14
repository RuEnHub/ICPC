// ВАЖНОСТЬ: низкая
//функция эйлера на массиве
void phi(int n) {
    long long phi[n+1];
    for (int i=1; i<=n; i++)
        phi[i] = i;
    for (int p=2; p<=n; p++) {
        if (phi[p] == p) {
            phi[p] = p-1;
            for (int i = 2*p; i<=n; i += p) {
            	phi[i] = (phi[i]/p) * (p-1);
            }
        }
    }
    for (int i=1; i<=n; i++)
    	cout << "Totient of " << i << " is " << phi[i] << endl;
}

// ВАЖНОСТЬ: высокая
// z-функция и префикс функция
vector<int> z_function (string s) {
    int n = (int) s.length();
    vector<int> z (n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min (r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    return z;
}
// переодичность строки
for (int i = 1; i<sz(str); ++i) {
    if (z[i] + i == sz(str)) {
        cout << i;
        return;
    }
}
cout << sz(str);

vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

// ВАЖНОСТЬ: низкая
// суффиксный массив
vector<int> suffix_array (string s) {
    //s.push_back(0);  // добавляем нулевой символ в конец строки
    int n = (int) s.size(),
        cnt = 0,  // вспомогательная переменная: счётчик для сортировки 
        cls = 0;  // количество классов эквивалентности
    vector<int> c(n), p(n);
    
    map< int, vector<int> > t;
    for (int i = 0; i < n; i++)
        t[s[i]].push_back(i);
    
    // «нулевой» этап
    for (auto &x : t) {
        for (int u : x.second)
            c[u] = cls, p[cnt++] = u;
        cls++;
    }
    
    // пока все суффиксы не стали уникальными
    for (int l = 1; cls < n; l++) {
        vector< vector<int> > a(cls);  // массив для сортировки подсчётом
        vector<int> _c(n);  // новые классы эквивалентности
        int d = (1<<l)/2;
        int _cls = cnt = 0;  // новое количество классов
        
        for (int i = 0; i < n; i++) {
            int k = (p[i]-d+n)%n;
            a[c[k]].push_back(k);
        }
        
        for (int i = 0; i < cls; i++) {
            for (size_t j = 0; j < a[i].size(); j++) {
                // если суффикс начинает новый класс эквивалентности
                if (j == 0 || c[(a[i][j]+d)%n] != c[(a[i][j-1]+d)%n])
                    _cls++;
                _c[a[i][j]] = _cls-1;
                p[cnt++] = a[i][j];
            }
        }
        
        c = _c;
        cls = _cls;
    }
    
    return vector<int>(p.begin()+1, p.end());
}


// ВАЖНОСТЬ: высокая
// расширенный алгоритм Евклида
ll extendedGCD(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll gcd = extendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}
gcd = extendedGCD(a, b, x, y);


// ВАЖНОСТЬ: высокая
// Построение выпуклой оболочки обходом Грэхэма
struct pt {
	double x, y;
};
bool cmp (pt a, pt b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool cw (pt a, pt b, pt c) {
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}
bool ccw (pt a, pt b, pt c) {
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}
void convex_hull (vector<pt> & a) {
	if (a.size() == 1)  return;
	sort (a.begin(), a.end(), &cmp);
	pt p1 = a[0],  p2 = a.back();
	vector<pt> up, down;
	up.push_back (p1);
	down.push_back (p1);
	for (size_t i=1; i<a.size(); ++i) {
		if (i==a.size()-1 || cw (p1, a[i], p2)) {
			while (up.size()>=2 && !cw (up[up.size()-2], up[up.size()-1], a[i]))
				up.pop_back();
			up.push_back (a[i]);
		}
		if (i==a.size()-1 || ccw (p1, a[i], p2)) {
			while (down.size()>=2 && !ccw (down[down.size()-2], down[down.size()-1], a[i]))
				down.pop_back();
			down.push_back (a[i]);
		}
	}
	a.clear();
	for (size_t i=0; i<up.size(); ++i)
		a.push_back (up[i]);
	for (size_t i=down.size()-2; i>0; --i)
		a.push_back (down[i]);
}

// ВАЖНОСТЬ: высокая
// Алгоритм Манакера
vector<ll> Manaker(string s) {
    int n = s.size();
    vector<ll> d1(n), d2(n), res(2*n-1);
    // нечетные палиндромы
    int l=0, r=-1;
    for (int i=0; i<n; ++i) {
        int k = i>r ? 1 : min (d1[l+r-i], r-i+1);
        while (i+k < n && i-k >= 0 && s[i+k] == s[i-k]) ++k;
        d1[i] = k;
        res[2*i] = k;
        if (i+k-1 > r) l = i-k+1,  r = i+k-1;
    }
    // четные палиндромы
    l=0, r=-1;
    for (int i=0; i<n; ++i) {
        int k = i>r ? 0 : min (d2[l+r-i+1], r-i+1);
        while (i+k < n && i-k-1 >= 0 && s[i+k] == s[i-k-1]) ++k;
        d2[i] = k;
        res[2*i+1] = k;
        if (i+k-1 > r) l = i-k,  r = i+k-1;
    }
    return res;
}