#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

inline size_t leftChildIndex(size_t parentIndex) {
    return 2 * parentIndex + 1;
}

inline size_t rightChildIndex(size_t parentIndex) {
    return 2 * parentIndex + 2;
}

struct Worker {
    size_t number;
    long long next_free_time;
    
    Worker(size_t _number) {
        number = _number;
        next_free_time = 0;
    }
};

class Workers {
private:
    
    
    vector<Worker*> workers;
    
    size_t first_worker(size_t p1, size_t p2) {
        if (workers[p1]->next_free_time < workers[p2]->next_free_time) {
            return p1;
        }
        if (workers[p1]->next_free_time > workers[p2]->next_free_time) {
            return p2;
        }
        if (workers[p1]->number < workers[p2]->number) {
            return p1;
        }
        return p2;
    }
    
    void shiftDown() {
        
        size_t p = 0;
        
        do {
            size_t lc = leftChildIndex(p);
            size_t rc = rightChildIndex(p);
            lc = (lc < workers.size()) ? lc : p;
            rc = (rc < workers.size()) ? rc : p;
            size_t c = first_worker(lc, rc);
            
            if (first_worker(p, c) != p) {
                std::swap(workers[p], workers[c]);
                p = c;
            } else {
                p = 0;
            }
            
        } while (p > 0);
    }
    
public:
    Workers(size_t num_workers) {
        workers.resize(num_workers);
        for(size_t i = 0; i < num_workers; i++) {
            workers[i] = new Worker(i);
        }
    };
    
    Worker* addJob(size_t time) {
        Worker *w = workers[0];
        w->next_free_time += time;
        shiftDown();
        return w;
    }
};

class JobQueue {
private:
    int num_workers_;
    vector<size_t> jobs_;
    
    vector<size_t> assigned_workers_;
    vector<size_t> start_times_;
    
    void WriteResponse() const {
        for (size_t i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }
    
    void ReadData() {
        size_t m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(size_t i = 0; i < m; ++i)
            cin >> jobs_[i];
    }
    
    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        
        Workers workers(num_workers_);
        
        for (size_t i = 0; i < jobs_.size(); ++i) {
            size_t duration = jobs_[i];
            Worker *w = workers.addJob(duration);
            assigned_workers_[i] = w->number;
            start_times_[i] = (w->next_free_time - duration);
        }
    }
    
public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}


