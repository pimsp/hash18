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

ifstream *f_solution;

int R, C, F, N, B, T;
ride_t rides[MAXRIDES];

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

	ll score = 0LL;

	REP(i, F) {
		int n;
		*f_solution >> n;
		// trace the route.

		int travelTime = 0;

		ii location(0, 0);
		int time = 0;
		REP(dummy, n) {
			int j;
			*f_solution >> j;

			time += NYdist(location, rides[j].fr);
			if (time <= rides[j].time.x) time = rides[j].time.x;

			// get a bonus!
			if (time <= rides[j].time.y) {
				if (time == rides[j].time.x) {
					score += B;
				}
				score += NYdist(rides[j].fr, rides[j].to);
				travelTime += NYdist(rides[j].fr, rides[j].to);
			}

			location = rides[j].to;
			time += NYdist(rides[j].fr, rides[j].to);
		}
		
		cerr << travelTime << "\t" << (T - travelTime) << endl;
	}

	cout << score << endl;
}

int main(int argc, char **argv)
{
	assert(argc >= 2);
	srand(time(NULL));
	f_solution = new ifstream(argv[1]);
	run();
	return 0;
}
