#include "EditDistance.h"

#include <vector>
#include <algorithm>

/*
 * 두 문자열 사이의 Levenshtein 편집 거리를 계산한다.
 * 허용 연산: 삽입, 삭제, 치환
 */
int EditDistance::calculate(const std::string& a, const std::string& b)
{
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(b.size());

    // dp[i][j]:
    // a의 앞 i개의 문자와 b의 앞 j개 문자를 
    // 서로 같게 만들기 위해 필요한 최소 편집 횟수
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    // b가 빈 문자열일 경우:
    // a의 모든 문자를 삭제해야 하므로 편집 횟수는 i
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = i;
    }

    // a가 빈 문자열인 경우: 
    // b의 모든 문자를 삽입해야 하므로 편집 횟수는 j
    for (int j = 0; j <= m; ++j) {
        dp[0][j] = j;
    }

    // a와 b의 각 문자를 하나씩 비교한다.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // 현재 비교하는 문자가 같다면 
            // 추가적인 편집이 필요하지 않다.
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                // 현재 문자가 다르면 다음 세 가지 연산 중 
                // 가장 적은 비용이 드는 방법을 선택한다. 
                // dp[i - 1][j] : a의 문자 하나 삭제 
                // dp[i][j - 1] : b의 문자 하나 삽입 
                // dp[i - 1][j - 1] : 문자 하나 치환
                dp[i][j] = 1 + std::min({
                    dp[i - 1][j],     // 삭제
                    dp[i][j - 1],     // 삽입
                    dp[i - 1][j - 1]  // 치환
                    });
            }
        }
    }
    // 전체 문자열 a와 b 사이의 최소 편집 횟수
    return dp[n][m];
}