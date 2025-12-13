class Bank {
    vector<long long> accounts;

    bool isValidBankAccount(int account) {
        return (account <= accounts.size()) && (account >= 1);
    }
public:
    Bank(vector<long long>& balance) : accounts(balance) { }
    
    bool transfer(int account1, int account2, long long money) {
        // Checking accounts
        if(!isValidBankAccount(account1) || !isValidBankAccount(account2)) {
            return false;
        }

        int account1Id = account1 - 1;
        int account2Id = account2 - 1;

        // Checking money avaiability
        if(accounts[account1Id] < money) {
            return false;
        }

        // Do the transfer
        accounts[account1Id] -= money;
        accounts[account2Id] += money;

        return true;
    }
    
    bool deposit(int account, long long money) {
        // Checking the account
        if(!isValidBankAccount(account)) {
            return false;
        }

        int accountId = account - 1;

        // Do the deposit
        accounts[accountId] += money;

        return true;
    }
    
    bool withdraw(int account, long long money) {
        // Checking the account
        if(!isValidBankAccount(account)) {
            return false;
        }

        int accountId = account - 1;

        // Checking money avaibility
        if(accounts[accountId] < money) {
            return false;
        }

        // Do the withdraw
        accounts[accountId] -= money;

        return true;
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
