// Initializes the internal data structure
// adds: (task,priority) to user
// edit: priority of (taskId) // lookup fast taskId
// remove: remove taskId // lookup fast TaskId
// execTop() removes task with highest priority and taskId, return userId // lookup fast priority and task id

// We dont need to lookup for user
// We need to keep track of order

// One map for <priority, taskId> -> user
// One unordered map for <taskId> -> priority, to emulate a wildcard search

class TaskManager {
    map<pair<int, int>, int> taskToUser;
    unordered_map<int, int> taskToPriority;
public:
    // O(n log n) for n tasks
    TaskManager(vector<vector<int>>& tasks) {
        for(const vector<int>& task : tasks) {
            int userId = task[0];
            int taskId = task[1];
            int priority = task[2];

            taskToPriority[taskId] = priority;
            taskToUser[make_pair(priority, taskId)] = userId;
        }
    }

    // O(log n), if container has n tasks
    void add(int userId, int taskId, int priority) {
        taskToPriority[taskId] = priority;
        taskToUser[make_pair(priority, taskId)] = userId;
    }

    // O(log n), if container has n tasks
    void edit(int taskId, int newPriority) {
        int priority = taskToPriority[taskId];
        int userId = taskToUser[make_pair(priority, taskId)];

        // Remove current register
        auto it = taskToUser.find(make_pair(priority, taskId));
        taskToUser.erase(it);

        // Add new register
        taskToPriority[taskId] = newPriority;
        taskToUser[make_pair(newPriority, taskId)] = userId;
    }

    // O(log n), if container has n tasks
    void rmv(int taskId) {
        int priority = taskToPriority[taskId];

        auto itTaskToPriority = taskToPriority.find(taskId);
        taskToPriority.erase(itTaskToPriority);

        auto itTaskToUser = taskToUser.find(make_pair(priority, taskId));
        taskToUser.erase(itTaskToUser);
    }

    // O(log n), if container has n tasks
    int execTop() {
        if(taskToUser.size()==0) {
            return -1;
        }

        auto itTaskToUser = taskToUser.end();

        // We move it to the last register
        --itTaskToUser;

        auto [priority, taskId] = itTaskToUser->first;
        int userId = itTaskToUser->second;


        // Removing the register
        taskToUser.erase(itTaskToUser);

        auto itTaskToPriority = taskToPriority.find(taskId);
        taskToPriority.erase(itTaskToPriority);

        return userId;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */
