#!/bin/zsh

# ANSI escape codes for text formatting
RESET='\e[0m'
BOLD='\e[1m'
DIM='\e[2m'
UNDERLINE='\e[4m'
BLINK='\e[5m'
INVERT='\e[7m'
HIDDEN='\e[8m'

# ANSI escape codes for text colors
BLACK='\e[30m'
RED='\e[31m'
GREEN='\e[32m'
YELLOW='\e[33m'
BLUE='\e[34m'
MAGENTA='\e[35m'
CYAN='\e[36m'
WHITE='\e[37m'

# ANSI escape codes for background colors
BG_BLACK='\e[40m'
BG_RED='\e[41m'
BG_GREEN='\e[42m'
BG_YELLOW='\e[43m'
BG_BLUE='\e[44m'
BG_MAGENTA='\e[45m'
BG_CYAN='\e[46m'
BG_WHITE='\e[47m'

diffing () {
    if [ "$#" -lt 1 ]; then
        echo "Error: diffing function expects minimum 1 arguments."
		echo "1: file name, 2-6: nm options"
        exit 1
    fi
    local file_name=$1
    local option_1=$2
    local option_2=$3
    local option_3=$4
    local option_4=$5
    local option_5=$6

	./ft_nm $file_name $option_1 $option_2 $option_3 $option_4 $option_5 > ft_nm.out
	nm $file_name $option_1 $option_2 $option_3 $option_4 $option_5  > nm.out
	diff ft_nm.out nm.out > /dev/null 2>&1

	if [ $? -ne 0 ]; then
		SUCCESS="FALSE"
		echo "${RED}"
		echo "[!] A test has failed."
		if [[ "$file_name" == "" ]]; then
			file_name="a.out"
		fi
		file $file_name
		echo -n "${RESET}"
	fi
}

print_result () {
	if [ "$#" -ne 1 ]; then
        echo "Error: print_result function expects exactly 1 arguments."
		echo "1: test message"
        exit 1
    fi
	local test_message=$1

	if [[ "$SUCCESS" == "TRUE" ]]; then
		echo "${GREEN}${BOLD}[SUCCESS] ${test_message}.${RESET}"
	else
		echo "${RED}${BOLD}[FAILED] ${test_message}.${RESET}"
	fi
	SUCCESS="TRUE"
}

check_makefile_error () {
	local makefile_status=$?
	if [ "$#" -ne 1 ]; then
        echo "Error: print_result function expects exactly 1 arguments."
		echo "1: make command"
        exit 1
    fi
	local make_command=$1

	if [ $makefile_status -ne 0 ]; then
		echo "${RED}${BOLD}[ERROR] Makefile command: '${make_command}'.${RESET}"
		exit 1
	fi
}

help () {
	echo "${}${UNDERLINE}How this tester works ?${RESET}"
	echo -n ${}
	echo "It simply test your ft_nm output against the real nm."
	echo "The tester will compile your ft_nm project and use the generated object files and binaries to test."
        echo "To compile 32 bits objects you need glibc-devel.i686 installed."
	echo "You must have a 'X32' variable in your Makefile so when its equal to '1' (make X32=1) it generates a 32 bit binary."
	echo "You must also have a 'ft_nm.so' rule to compile a shared object (make ft_nm.so)."
	echo "If a test fails, the tester will do a 'file' of the tested binary | object | shared object (ex: file objfile.o)."
	echo "Also, if  you didn't implement the options you will need to comment out this part of the test."
	echo "Ready ? Go !"
	echo ${RESET}
}

echo -e "${BOLD}${MAGENTA}[ TEST MY NM ! ]${RESET}"

help

SUCCESS="TRUE"

# [SETUP] Creating the directories
echo "${YELLOW}${BOLD}[SETUP] Setting up the tester.${RESET}"

rm -r testers > /dev/null 2>&1
mkdir -p testers/binaries/{x64,x32}
mkdir -p testers/objects/{x64,x32}
mkdir -p testers/shared-objects/{x64,x32}

# [SETUP] Shared object x64
make fclean > /dev/null 2>&1
check_makefile_error "make fclean"
make ft_nm.so > /dev/null 2>&1
check_makefile_error "make ft_nm.so"
cp ft_nm.so testers/shared-objects/x64

# [SETUP] Shared object x32
make fclean > /dev/null 2>&1
check_makefile_error "make fclean"
make ft_nm.so X32=1 > /dev/null 2>&1
check_makefile_error "make ft_nm.so X32=1"
cp ft_nm.so testers/shared-objects/x32

# [SETUP] make x64 {Binaries x64, Binaries x64 stripped, Object files x64}
make fclean > /dev/null 2>&1
check_makefile_error "make fclean"
make > /dev/null 2>&1
check_makefile_error "make"
cp objs/srcs/*.o testers/objects/x64
cp ft_nm testers/binaries/x64
cp ft_nm testers/binaries/x64/ft_nm-strip
strip testers/binaries/x64/ft_nm-strip

# [SETUP] make x32 {Binaries x32, Binaries x32 stripped, Object files x32}
make fclean > /dev/null 2>&1
check_makefile_error "make fclean"
make X32=1 > /dev/null 2>&1
check_makefile_error "make X32=1"
cp objs/srcs/*.o testers/objects/x32
cp ft_nm testers/binaries/x32
cp ft_nm testers/binaries/x32/ft_nm-strip
strip testers/binaries/x32/ft_nm-strip


# [TEST] nm without arguments & without a.out
./ft_nm 2>&1 | grep -qi "no such file"
if [ $? -ne 0 ]; then
	echo "${RED}${BOLD}[FAILED] nm without arguments & without a.out in the cwd.${RESET}"
	echo "${YELLOW}[!] Its maybe a false positive because I am searching for 'no such file' in your ft_nm output.${RESET}"
else
	echo "${GREEN}${BOLD}[SUCCESS] nm without arguments & without a.out.${RESET}"
fi

# [TEST] nm without arguments & with a.out
cp ft_nm a.out
diffing "" ""
rm a.out
print_result "nm without arguments & with a.out in the cwd"

# [TEST] x64 binary
diffing "testers/binaries/x64/ft_nm" ""
print_result "x64 binary"

# [TEST] x64 binary stripped
./ft_nm "testers/binaries/x64/ft_nm-strip" 2>&1 | grep -qi "no symbols"
if [ $? -ne 0 ]; then
	echo "${RED}${BOLD}[FAILED] x64 binary stripped.${RESET}"
	echo "${YELLOW}[!] The output must have something like 'no symbols' in your ft_nm output.${RESET}"
else
	echo "${GREEN}${BOLD}[SUCCESS] x64 binary stripped.${RESET}"
fi

# [TEST] x64 object files
for FILE in testers/objects/x64/*; do
	diffing "$FILE" ""
done
print_result "x64 object files"

# [TEST] x32 binary
diffing "testers/binaries/x32/ft_nm" ""
print_result "x32 binary"

# [TEST] x32 binary stripped
./ft_nm "testers/binaries/x32/ft_nm-strip" 2>&1 | grep -qi "no symbols"
if [ $? -ne 0 ]; then
	echo "${RED}${BOLD}[FAILED] x32 binary stripped.${RESET}"
	echo "${YELLOW}[!] The output must have something like 'no symbols' in your ft_nm output.${RESET}"
else
	echo "${GREEN}${BOLD}[SUCCESS] x32 binary stripped.${RESET}"
fi

# [TEST] x32 object files
for FILE in testers/objects/x32/*; do
	diffing "$FILE" ""
done
print_result "x32 object files"

# [TEST] x64 shared object
diffing "testers/shared-objects/x64/ft_nm.so" ""
print_result "x64 shared object"

# [TEST] x32 shared object
diffing "testers/shared-objects/x32/ft_nm.so" ""
print_result "x32 shared object"

# [TEST] x64 binary with option -a
diffing "testers/binaries/x64/ft_nm" "-a"
print_result "x64 binary with option -a"

# [TEST] x64 binarywith  option -g
diffing "testers/binaries/x64/ft_nm" "-g"
print_result "x64 binary with option -g"

# [TEST] x64 binary with option -u
diffing "testers/binaries/x64/ft_nm" "-u"
print_result "x64 binary with option -u"

# [TEST] x64 binary with option -r
diffing "testers/binaries/x64/ft_nm" "-r"
print_result "x64 binary with option -r"

# [TEST] x64 binary with option -p
diffing "testers/binaries/x64/ft_nm" "-p"
print_result "x64 binary with option -p"


# [TEST] x32 binary with option -a
diffing "testers/binaries/x32/ft_nm" "-a"
print_result "x32 binary with option -a"

# [TEST] x32 binarywith  option -g
diffing "testers/binaries/x32/ft_nm" "-g"
print_result "x32 binary with option -g"

# [TEST] x32 binary with option -u
diffing "testers/binaries/x32/ft_nm" "-u"
print_result "x32 binary with option -u"

# [TEST] x32 binary with option -r
diffing "testers/binaries/x32/ft_nm" "-r"
print_result "x32 binary with option -r"

# [TEST] x32 binary with option -p
diffing "testers/binaries/x32/ft_nm" "-p"
print_result "x32 binary with option -p"

# [TEST] x32 binary with option -a -g
diffing "testers/binaries/x32/ft_nm" "-a" "-g"
print_result "x32 binary with option -a -g"

# [TEST] x32 binary with option -r -u
diffing "testers/binaries/x32/ft_nm" "-r" "-u"
print_result "x32 binary with option -r -u"

# [TEST] x64 binary with option -p -r g
diffing "testers/binaries/x64/ft_nm" "-p" "-r" -"g"
print_result "x64 binary with option -p -r -g"

# [TEST] x64 binary with option -p -r -g -a
diffing "testers/binaries/x64/ft_nm" "-p" "-r" "-g" "-a"
print_result "x64 binary with option -p -r -g -a"

# [CLEANUP]
make clean > /dev/null 2>&1
rm ft_nm.out nm.out
