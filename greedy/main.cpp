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

	vi carUse(F, 0);
	vii carPos(F, ii());
	REP(i, N) {
		vi opts;
		int bestWait = 1e9;
		REP(j, F) {
			// check if we can match this car with this ride.
			int ddd = NYdist(carPos[j], rides[i].fr);
			int tAtStart = carUse[j] + ddd;
			int wait = max(ddd, rides[i].time.x - carUse[j]);
			if (tAtStart <= rides[i].time.y) {
				if (wait < bestWait) {
					bestWait = wait;
					opts.clear();
				}
				if (wait == bestWait) opts.pb(j);
			}
		}
		if (opts.empty()) continue;

		int pick = opts[rand() % opts.size()];

		carrides[pick].pb(i);
		carUse[pick] = max(rides[i].time.x, carUse[pick] + NYdist(carPos[pick], rides[i].fr)) + rides[i].d;
		carPos[pick] = rides[i].to;
	}

	REP(i, F) {
		printf("%d", (int) carrides[i].size());
		for (int j : carrides[i]) printf(" %d", rides[j].idx);
		printf("\n");
	}
}

int main()
{
	srand(time(NULL));
	run();
	return 0;
}
