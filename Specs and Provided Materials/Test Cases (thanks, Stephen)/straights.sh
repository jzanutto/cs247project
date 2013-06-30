for i in {50..60}
do
    # valgrind --leak-check=full --track-origins=yes ../.././program $i < $i.in > memcheck.dump
	bash ../../difftool.sh ../.././program .././straights $i < $i.in

    # diff --suppress-common-lines <(.././straights $i < $i.in) <(../.././program $i < $i.in)
done