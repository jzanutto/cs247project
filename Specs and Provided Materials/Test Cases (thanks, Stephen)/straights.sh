for i in {50..61}
do
    # valgrind --leak-check=full --track-origins=yes ../.././straights $i < $i.in > memcheck.dump
	# bash ../../difftool.sh ../.././straights .././straights $i < $i.in > $i.out &

    diff --suppress-common-lines <(.././straights $i < $i.in) <(../.././straights $i < $i.in) > $1.out

done