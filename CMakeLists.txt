cmake_minimum_required (VERSION 3.8)

project ("DynamicProgramming")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable (Binomial "binomial/binomial.cc")

add_executable (BoxStacking "box_stacking/box_stacking.cc")

add_executable (Buffalgo "buffalgo/buffalgo.cc")

add_executable (CatalanNumber "catalan_number/catalan_number.cc")

add_executable (CoinExchange "coin_exchange/coin_exchange.cc")

add_executable (EditDistance "edit_distance/edit_distance.cc")

add_executable (Factorial "factorial/factorial.cc")

add_executable (Fibonacci "fibonacci/fibonacci.cc")

add_executable (FindSubsequence "find_subsequence/find_subsequence.cc")

add_executable (FindSubsequenceSum "find_subsequence_sum/find_subsequence_sum.cc")

add_executable (KnapSack "knapsack/knapsack.cc")

add_executable (KnapSackZeroOne "knapsack_zero_one/knapsack_zero_one.cc")

add_executable (LogicalExpression "logical_expression/logical_expression.cc")

add_executable (LongestCommonSubsequence "longest_common_subsequence/longest_common_subsequence.cc")

add_executable (LongestCommonSubstring "longest_common_substring/longest_common_substring.cc")

add_executable (LongestIncreasingSubsequence "longest_increasing_subsequence/longest_increasing_subsequence.cc")

add_executable (LongestPalindromeSubsequence "longest_palindrome_subsequence/longest_palindrome_subsequence.cc")

add_executable (LongestPalindromeSubstring "longest_palindrome_substring/longest_palindrome_substring.cc")

add_executable (MatrixChainMuliplication "matrix_chain_multiplication/matrix_chain_multiplication.cc")

add_executable (MaxAllOneSquareSubmatrix "max_all_one_square_submatrix/max_all_one_square_submatrix.cc")

add_executable (MaxProfitPath "max_profit_path/max_profit_path.cc")

add_executable (MaxSubarray "max_subarray/max_subarray.cc")

add_executable (MaxSubmatrix "max_submatrix/max_submatrix.cc")

add_executable (MaxSumWithNoContiguousElements "max_sum_with_no_contiguous_elements/max_sum_with_no_contiguous_elements.cc")

add_executable (MinJumps "min_jumps/min_jumps.cc")

add_executable (NumberPartition "number_partition/number_partition.cc")

add_executable (OptimalBinarySearchTree "optimal_binary_search_tree/optimal_binary_search_tree.cc")

add_executable (Tiling_2xN "tiling_2_by_n/tiling_2_by_n.cc")

add_executable (WildcardMatching "wildcard_matching/wildcard_matching.cc")
