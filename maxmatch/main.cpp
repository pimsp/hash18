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

const ll MAXN = 1001;
ll a[MAXN + 1][MAXN + 1]; // matrix, 1-based
vi ans(MAXN+1);

ll minimum_assignment(ll n, ll m) { // n rows, m columns
	vi p(MAXN+1), u(n + 1), v(m + 1), way(m + 1);


	for (ll i = 1; i <= n; i++) {
        //cout << i << endl;
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

    sort(rides, rides + N, [] (ride_t a, ride_t b) -> bool {
                return a.time < b.time;
    });

	vector<car_t> cars(F);
    vector<vi> cartoride(F);

    ll score = 0;

    for(ll i = 0; i < N; i += F){
        //cout << "i: "<< i << endl;
        ll n = F;
        ll m = min(F, N-i);
        REP(j,n){
            //cout << "j1: " << j << endl;
            a[j][0] = a[0][j] = 0;
            REP(k,m){
                //cout << "k: "<< k << endl;
                ll earliesttime = cars[j].time + dist(cars[j].pos, rides[k+i].fr);
                if(earliesttime > rides[k+i].time.y)
                    a[j+1][k+1] = 0;
                else
                    a[j+1][k+1] = -(rides[k+i].d + B * (earliesttime <= rides[k+1].time.x));
                //cout << "k: "<< k << endl;
            }
            rep(k,m,F)
                a[j+1][k+1] = 0;
        }
        //cout << "H" << endl;
        minimum_assignment(n,n);
        //cout << "oi" << endl;
        REP(j,n){
            //cout << "j2: "<< j << endl;
            if(a[j+1][ans[j+1]] < 0){
                // send car j to location k
                ll k = ans[j+1]-1;
                cartoride[j].pb(k+i);
                score += -a[j+1][ans[j+1]];
                ll starttime = max(cars[j].time + dist(cars[j].pos, rides[k+i].fr), rides[k+i].time.y);
                cars[j].pos = rides[k+i].to;
                cars[j].time = starttime + rides[k+i].d;
            }
        }
    }

    REP(j,F){
        cout << cartoride[j].size() << " ";
        for(ll r : cartoride[j])
            cout << rides[j].idx << " ";
        cout << endl;
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
