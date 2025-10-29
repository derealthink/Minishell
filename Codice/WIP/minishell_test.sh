#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
TOTAL=0
PASSED=0
FAILED=0

# Minishell path
MINISHELL="./minishell"

# Check if minishell exists
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: minishell not found at $MINISHELL${NC}"
    exit 1
fi

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local check_exit_code="${3:-1}"  # 1 = check exit code, 0 = don't check
    
    TOTAL=$((TOTAL + 1))
    
    echo -n "Test $TOTAL: $test_name... "
    
    # Run in bash
    bash_output=$(echo "$command" 2>&1 | bash 2>&1)
    bash_exit=$?
    
    # Run in minishell
    minishell_output=$(echo "$command" 2>&1 | $MINISHELL 2>&1)
    minishell_exit=$?
    
    # Compare outputs
    if [ "$check_exit_code" -eq 1 ]; then
        if [ "$bash_output" == "$minishell_output" ] && [ "$bash_exit" -eq "$minishell_exit" ]; then
            echo -e "${GREEN}✓ PASSED${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            FAILED=$((FAILED + 1))
            echo "  Expected output: $bash_output (exit: $bash_exit)"
            echo "  Got output:      $minishell_output (exit: $minishell_exit)"
        fi
    else
        if [ "$bash_output" == "$minishell_output" ]; then
            echo -e "${GREEN}✓ PASSED${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            FAILED=$((FAILED + 1))
            echo "  Expected: $bash_output"
            echo "  Got:      $minishell_output"
        fi
    fi
}

# Interactive tests
run_interactive_test() {
    local test_name="$1"
    echo -e "\n${YELLOW}=== Interactive Test: $test_name ===${NC}"
    echo "Press Enter to start, then test manually..."
    read
    $MINISHELL
}

echo -e "${YELLOW}=== MINISHELL TEST SUITE ===${NC}\n"

# Create test files
echo "test content" > test_input.txt
echo "line1" > test_file.txt
echo "line2" >> test_file.txt

# ============================================================================
# BASIC COMMANDS
# ============================================================================
echo -e "\n${YELLOW}--- Basic Commands ---${NC}"

run_test "ls" "ls"
run_test "pwd" "pwd"
run_test "echo hello" "echo hello"
run_test "echo with quotes" "echo \"hello world\""
run_test "whoami" "whoami"
run_test "uname -a" "uname -a"

# ============================================================================
# BUILT-INS: ECHO
# ============================================================================
echo -e "\n${YELLOW}--- Echo Built-in ---${NC}"

run_test "echo test" "echo test"
run_test "echo -n test" "echo -n test"
run_test "echo -n -n test" "echo -n -n test"
run_test "echo empty quotes" "echo \"\""
run_test "echo single quotes" "echo 'hello'"
run_test "echo mixed quotes" "echo 'hello \"world\"'"

# ============================================================================
# BUILT-INS: CD & PWD
# ============================================================================
echo -e "\n${YELLOW}--- CD & PWD Built-ins ---${NC}"

run_test "cd .. then pwd" "cd ..; pwd"
run_test "cd /tmp then pwd" "cd /tmp; pwd"
run_test "cd invalid dir" "cd nonexistent_directory_xyz" 0

# ============================================================================
# BUILT-INS: EXPORT & ENV
# ============================================================================
echo -e "\n${YELLOW}--- Export & Env ---${NC}"

run_test "export and print" "export TEST=value; env | grep TEST"
run_test "export with spaces" "export VAR=\"hello world\"; echo \$VAR"
run_test "overwrite var" "export VAR=123; export VAR=456; echo \$VAR"

# ============================================================================
# ENVIRONMENT VARIABLES
# ============================================================================
echo -e "\n${YELLOW}--- Environment Variables ---${NC}"

run_test "echo \$USER" "echo \$USER"
run_test "echo \$HOME" "echo \$HOME"
run_test "echo nonexistent var" "echo \$NONEXISTENT"
run_test "echo in double quotes" "echo \"\$USER\""
run_test "echo in single quotes" "echo '\$USER'"

# ============================================================================
# PIPES
# ============================================================================
echo -e "\n${YELLOW}--- Pipes ---${NC}"

run_test "simple pipe" "echo hello | cat"
run_test "pipe with grep" "echo -e \"hello\nworld\" | grep hello"
run_test "double pipe" "echo test | cat | cat"
run_test "pipe with sort" "printf 'b\na\n' | sort"
run_test "ls | wc -l" "ls | wc -l" 0
run_test "grep in chain" "cat test_file.txt | grep line | wc -l"

# ============================================================================
# REDIRECTIONS
# ============================================================================
echo -e "\n${YELLOW}--- Redirections ---${NC}"

run_test "output redirect" "echo test > test_out.txt; cat test_out.txt"
run_test "append redirect" "echo line1 > test_out.txt; echo line2 >> test_out.txt; cat test_out.txt"
run_test "input redirect" "cat < test_input.txt"
run_test "input and output" "cat < test_input.txt > test_out.txt; cat test_out.txt"
run_test "pipe with redirect" "echo hi | cat > test_out.txt; cat test_out.txt"
run_test "redirect and pipe" "cat < test_input.txt | grep test"

# ============================================================================
# QUOTES
# ============================================================================
echo -e "\n${YELLOW}--- Quotes ---${NC}"

run_test "double quotes" "echo \"hello world\""
run_test "single quotes" "echo 'hello world'"
run_test "mixed quotes 1" "echo \"hello'world\""
run_test "mixed quotes 2" "echo 'hello\"world'"
run_test "empty double quotes" "echo \"\""
run_test "empty single quotes" "echo ''"

# ============================================================================
# EDGE CASES
# ============================================================================
echo -e "\n${YELLOW}--- Edge Cases ---${NC}"

run_test "multiple spaces" "echo    hello    world"
run_test "command not found" "nonexistent_command_xyz" 0
run_test "empty command" "" 0
run_test "pipe at end (invalid)" "echo hi |" 0
run_test "redirect no file" "echo hi >" 0

# ============================================================================
# RELATIVE/ABSOLUTE PATHS
# ============================================================================
echo -e "\n${YELLOW}--- Paths ---${NC}"

run_test "absolute path echo" "/bin/echo hello"
run_test "absolute path ls" "/bin/ls > /dev/null" 0
run_test "relative path command" "./$MINISHELL -c 'echo ok'" 0

# ============================================================================
# SUMMARY
# ============================================================================
echo -e "\n${YELLOW}==================================${NC}"
echo -e "${YELLOW}TEST SUMMARY${NC}"
echo -e "${YELLOW}==================================${NC}"
echo -e "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed!${NC}"
else
    echo -e "\n${RED}❌ Some tests failed${NC}"
fi

# Cleanup
rm -f test_input.txt test_file.txt test_out.txt

# Interactive tests prompt
echo -e "\n${YELLOW}Do you want to run interactive tests? (signals, heredoc, etc.) [y/N]${NC}"
read -r response
if [[ "$response" =~ ^[Yy]$ ]]; then
    echo -e "\n${YELLOW}=== Interactive Tests ===${NC}"
    echo "Test Ctrl+C, Ctrl+D manually"
    echo "Test heredoc: cat << EOF"
    echo "Press Enter to start minishell..."
    read
    $MINISHELL
fi

exit 0

