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
ii center;

int bestScore = 0, bestCutoff = -1;
vi bestSol[MAXCARS];

inline static int NYdist(ii a, ii b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

ll calculate_score()
{
	ll score = 0LL;
	REP(i, F) {
		// trace the route.
		ii location(0, 0);
		int time = 0;
		for (int j : carrides[i]) {
			time += NYdist(location, rides[j].fr);
			if (time <= rides[j].time.x) time = rides[j].time.x;

			// get a bonus!
			if (time <= rides[j].time.y) {
				if (time == rides[j].time.x) {
					score += B;
				}
				score += NYdist(rides[j].fr, rides[j].to);
			}

			location = rides[j].to;
			time += NYdist(rides[j].fr, rides[j].to);
		}
	}

	return score;
}

void run()
{
	ll totX, totY;
	scanf("%d %d %d %d %d %d", &R, &C, &F, &N, &B, &T);
	REP(i, N) {
		scanf("%d %d %d %d %d %d", &rides[i].fr.x, &rides[i].fr.y, &rides[i].to.x, &rides[i].to.y, &rides[i].time.x, &rides[i].time.y);
		rides[i].d = NYdist(rides[i].fr, rides[i].to);
		rides[i].time.y -= rides[i].d;
		rides[i].idx = i;
		totX += rides[i].fr.x;
		totY += rides[i].fr.y;
	}
	center.x = (int)(totX / N);
	center.y = (int)(totY / N);

	sort(rides, rides + N, [] (ride_t a, ride_t b) -> bool {
		return a.time < b.time;
	});

	for (int cutoff = 5000; cutoff < 7000; cutoff += 5) {
		REP(j, F) carrides[j].clear();

		vi carUse(F, 0);
		vii carPos(F, ii());
		REP(i, N) {

			if (NYdist(center, rides[i].to) >= cutoff) continue;

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

		int sc = calculate_score();
		if (sc > bestScore) {
			bestScore = sc;
			bestCutoff = cutoff;
			REP(j, F) {
				bestSol[j] = carrides[j];	
			}
		}

		cerr << cutoff << ": " << calculate_score() << endl;
	}

	for (int MM = 100; MM--; ) {
		REP(j, F) carrides[j].clear();

		vi carUse(F, 0);
		vii carPos(F, ii());
		REP(i, N) {

			if (rides[i].d >= bestCutoff) continue;

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

		int sc = calculate_score();
		cerr << MM << ": " << sc << endl;
		if (sc > bestScore) {
			bestScore = sc;
			REP(j, F) {
				bestSol[j] = carrides[j];	
			}
		}
	}

	REP(j, F) {
		carrides[j] = bestSol[j];	
	}
	cerr << "BIG SOLUTION: " << calculate_score() << endl;
	REP(i, F) {
		printf("%d", (int) bestSol[i].size());
		for (int j : bestSol[i]) printf(" %d", rides[j].idx);
		printf("\n");
	}
}

int main()
{
	srand(time(NULL));
	run();
	return 0;
}
