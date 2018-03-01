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
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

ostream& operator<<(ostream &out, const ii &pr) { return out << '(' << pr.x << ',' << pr.y << ')'; }

const int maxRC = 10000, MAXRIDES = 10000, MAXCARS = 1000;

struct ride_t
{
	// time.x: start time, time.y: end time
	ii fr, to, time;
	int d, idx; // distance
};

int R, C, F, N, B, T;
ride_t rides[MAXRIDES];
vi carrides[MAXCARS];

inline static int NYdist(ii a, ii b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void run()
{
	scanf("%d %d %d %d %d %d", &R, &C, &F, &N, &B, &T);
	REP(i, N) {
		scanf("%d %d %d %d %d %d", &rides[i].fr.x, &rides[i].fr.y, &rides[i].to.x, &rides[i].to.y, &rides[i].time.x, &rides[i].time.y);
		rides[i].d = NYdist(rides[i].fr, rides[i].to);
		rides[i].time.y -= rides[i].d;
		rides[i].idx = i;
	}

	sort(rides, rides + N, [] (ride_t a, ride_t b) -> bool {
		return a.time < b.time;
	});
	
	REP(i, F) {
		int a, M;
		scanf("%d", &M);
		REP(j, M){
			scanf("%d", &a);
			carrides[i].eb(a - 1);
		}
	}
	
	REP(i, F) {
		printf("%d", (int) carrides[i].size());
		for (int j : carrides[i]) printf(" %d", rides[j].idx);
		printf("\n");
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
