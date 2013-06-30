#!/bin/bash
 
sandbox="$(mktemp -d)"
hasstdin=false
 
if [ ! -t 0 ]; then
    cat <&0 > "$sandbox/stdin.txt"
    hasstdin=true
fi
 
usage() {
    echo "Usage: $0 prog1 prog2 [ARG]..."
    echo
    echo "Checks that prog1 and prog2 output the same things to stdout and"
    echo "stderr and have the same return code. Any arguments after prog1 and"
    echo "prog2 will be passed directly to the two programs. Anything piped to"
    echo "$0 will also be passed to the two programs."
    echo
    echo "Example:"
    echo
    echo "    $0 ./foo ./bar arg1 arg2 < input.txt"
    echo
    echo "will run"
    echo
    echo "    ./foo arg1 arg2 < input.txt"
    echo "    ./bar arg1 arg2 < input.txt"
    echo
    echo "then report any differences in standard output, standard error and"
    echo "return code."
    exit 1
}
 
run () {
    local srcpath="$1"
    local trialnum="$2"
    shift 2
 
    if [ ! -x "$srcpath" ]; then
        echo "No executable found at $(pwd)/$srcpath"
        echo
        usage
    fi
 
    local execpath="$sandbox/exec"
    cp "$srcpath" "$execpath"
 
    if $hasstdin; then
        $execpath < "$sandbox/stdin.txt" > "$sandbox/stdout.$trialnum.txt" 2> "$sandbox/stderr.$trialnum.txt" $@
        return $?
    else
        $execpath > "$sandbox/stdout.$trialnum.txt" 2> "$sandbox/stderr.$trialnum.txt" $@
    fi
}
 
prog1="$1"
prog2="$2"
shift 2
 
if [ -z "$prog1" ] || [ -z "$prog2" ]; then
    usage
fi
 
run "$prog1" 1 $@
retval1=$?
run "$prog2" 2 $@
retval2=$?
 
retcode=0
if [ "$retval1" -ne "$retval2" ]; then
    retcode=1
    echo -e "\e[00;31mReturn code differs\e[00m"
    echo -e "\e[00;31m-------------------\e[00m"
    echo -e "\t$prog1 returned $retval1"
    echo -e "\t$prog2 returned $retval2"
    echo
fi
 
diff -y "$sandbox/stdout.1.txt" "$sandbox/stdout.2.txt" > "$sandbox/stdout.diff.txt"
if [ "$?" -ne "0" ]; then
    retcode=1
    echo -e "\e[00;31mStandard output differs\e[00m"
    echo -e "\e[00;31m-----------------------\e[00m"
    cat "$sandbox/stdout.diff.txt"
fi
 
diff -y "$sandbox/stderr.1.txt" "$sandbox/stderr.2.txt" > "$sandbox/stderr.diff.txt"
if [ "$?" -ne "0" ]; then
    retcode=1
    echo -e "\e[00;31mStandard error differs\e[00m"
    echo -e "\e[00;31m-----------------------\e[00m"
    cat "$sandbox/stderr.diff.txt"
fi
 
exit $retcode