all: main test

test:
	echo "0,0" >> test.txt

main: main.c
	gcc main.c -W -o PrisonerProblem

clean:
	rm -f PrisonerProblem
	rm -f test.txt
