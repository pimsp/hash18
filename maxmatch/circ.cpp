#include<bits/stdc++.h>

using namespace std;
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for (auto i = (a); i != (b); ++i)
#define REP(i,n) rep(i,0,n)

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const ll INF = (1LL << 59);

ostream& operator<<(ostream &out, const ii &pr) { return out << '(' << pr.x << ',' << pr.y << ')'; }

const ll maxRC = 10000, MAXRIDES = 10000;

struct ride_t
{
	// time.x: start time, time.y: end time
	ii fr, to, time;
	ll d; // distance
	ll idx;
};

struct car_t
{
	// time.x: start time, time.y: end time
	ii pos;
	ll time; // distance

	car_t(){
        pos.x = pos.y = time = 0;
	}
};

ll R, C, F, N, B, T;
ride_t rides[MAXRIDES];

const ll MAXN = 10001;
ll a[MAXN + 1][MAXN + 1]; // matrix, 1-based
vi ans(MAXN+1);

ll minimum_assignment(ll n, ll m) { // n rows, m columns
	vi p(MAXN+1), u(n + 1), v(m + 1), way(m + 1);


	for (ll i = 1; i <= n; i++) {
        cout << i << endl;
		p[0] = i;
		ll j0 = 0;
		vi minv(m + 1, INF);
		vector<char> used(m + 1, false);
		do {
			used[j0] = true;
			ll i0 = p[j0], delta = INF, j1;
			for (ll j = 1; j <= m; j++)
				if (!used[j]) {
					ll cur = a[i0][j] - u[i0] - v[j];
					if (cur < minv[j]) minv[j] = cur, way[j] = j0;
					if (minv[j] < delta) delta = minv[j], j1 = j;
				}
			for (ll j = 0; j <= m; j++) {
				if(used[j]) u[p[j]] += delta, v[j] -= delta;
				else minv[j] -= delta;
			}
			j0 = j1;
		} while (p[j0] != 0);
        //cout << i << endl;
		do {
			ll j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
		//cout << i << endl;
	}

	// column j is assigned to row p[j]
	for (ll j = 1; j <= m; ++ j) ans[p[j]] = j;
	return -v[0];
}

ll dist(ii fr, ii to){
    return abs(fr.x - to.x) + abs(fr.y - to.y);
}

vi length(MAXN, -1);

void dfs(int a, int &tot){
    if(length[a] == -3)
        return;
    if(length[a] == -2){
        length[a] = -3;
    }
    tot++;
    dfs(ans[a+1]-1, tot);
    length[a] = tot;
}

void run()
{
	cin >> R >> C >> F >> N >> B >> T;
	REP(i, N) {
	    //cout << i << endl;
		cin >> rides[i].fr.x >> rides[i].fr.y;
		cin >> rides[i].to.x >> rides[i].to.y;
		cin >> rides[i].time.x >> rides[i].time.y;
		rides[i].d = abs(rides[i].fr.x - rides[i].to.x) + abs(rides[i].fr.y - rides[i].to.y);
		rides[i].time.y -= rides[i].d;
		rides[i].idx = i;
	}



	vector<car_t> cars(F);
    vector<vi> cartoride(F);

    ll score = 0;

    REP(j,N){
        cout << j << endl;
        REP(k,N){
            a[j+1][k+1] = (j == k) ? R+C : dist(rides[j].to, rides[k].fr);
        }
    }

    minimum_assignment(N, N);
cout << endl;
    REP(j,N){
        if(length[j] < 0){
            length[j] = -2;
            int nul = 0;
            dfs(j, nul);
            cout << length[j] << endl;
        }
    }


    /*
    REP(j,F){
        cout << cartoride[j].size() << " ";
        for(ll r : cartoride[j])
            cout << rides[r].idx << " ";
        cout << endl;
    }*/
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
