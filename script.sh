g++ -std=c++17 -O2 $1
echo "A Example";
./a.out < ./inputs/a_example.in > outputs/a.out;
echo "B Should be easy";
./a.out < ./inputs/b_should_be_easy.in > outputs/b.out;
echo "C No hurry"
./a.out < ./inputs/c_no_hurry.in > outputs/c.out;
echo "D Metropolis"
./a.out < ./inputs/d_metropolis.in > outputs/d.out;
echo "E High Bonus"
./a.out < ./inputs/e_high_bonus.in > outputs/e.out;

