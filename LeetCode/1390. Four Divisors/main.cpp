class Solution {
public:
    // Time: O(n*sqrt(m)), n=nums.size(), m=max{nums[i]}
    // Space: O(1), but this bound is very loose
    int sumFourDivisors(vector<int>& nums) {
        int fourDivSum = 0;
        vector<int> primes(4);
        vector<int> exps(4);
        for(int num: nums) {
            // We factor the number
            primes.clear();
            exps.clear();

            for(int i=2; i*i<=num && num>1 && primes.size() <= 2; ++i) {
                // Here i must be a prime, due to the way we are factoring
                if(num % i == 0) {
                    primes.push_back(i);
                    int exp = 0;

                    do {
                        num /= i;
                        exp++;
                    } while(num % i == 0);

                    exps.push_back(exp);
                }
            }

            // Here what remained of num is a prime
            if(num > 1) {
                primes.push_back(num);
                exps.push_back(1);
            }

            // Now we check the divisors
            // num = p³
            if(primes.size() == 1 && exps[0]==3) {
                int p = primes[0];
                fourDivSum += 1 + p + p*p + p*p*p;
            }
            // num = p¹q¹
            else if(primes.size() == 2 && exps[0]==1 && exps[1]==1) {
                int p = primes[0];
                int q = primes[1];
                fourDivSum += 1 + p + q + p*q;
            }
        }

        return fourDivSum;
    }
};
