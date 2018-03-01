g++ -std=c++17 $1
#g++ -std=c++17 -O2 analysis/score.cpp -o calc_score
echo "A Example";
./a.out < inputs/a_example.in > outputs/a.out;
./calc_score outputs/a.out < inputs/a_example.in
echo "B Should be easy";
./a.out < inputs/b_should_be_easy.in > outputs/b.out;
./calc_score outputs/b.out < inputs/b_should_be_easy.in
echo "C No hurry"
./a.out < inputs/c_no_hurry.in > outputs/c.out;
./calc_score outputs/c.out < inputs/c_no_hurry.in
echo "D Metropolis"
./a.out < inputs/d_metropolis.in > outputs/d.out;
./calc_score outputs/d.out < inputs/d_metropolis.in
echo "E High Bonus"
./a.out < inputs/e_high_bonus.in > outputs/e.out;
./calc_score outputs/e.out < inputs/e_high_bonus.in

