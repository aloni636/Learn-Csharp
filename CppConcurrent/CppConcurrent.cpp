// core
#include <random>
#include <chrono>
#include <thread>  // Requires C++ 17
#include <span>  // Requires C++ 20
#include <functional>  // For passing functions as parameters (used in benchmark function for passing callables)

// fmt
#include <fmt/core.h>
#include <fmt/ranges.h>  // Must be included to be able to fmt::print vectors and other containers
#include <fmt/chrono.h>  // Must be included for duration and point in time printing
#include <locale>  // Configure locale for fmt

namespace chrono = std::chrono;

//  Concept                 C++ Tool                      Use                                              
// ----------------------- ----------------------------- ------------------------------------------------- 
//  Basic thread            std::thread                   Run a function in parallel                       
//  Safe shared access      std::mutex, std::lock_guard   Prevent concurrent data access bugs              
//  Task signaling          std::condition_variable       Wake threads when new work is available          
//  Cancellation / status   std::atomic<bool>             Shared flag between threads, safe to read/write  

class RandomSampler {
public:
    RandomSampler(int min_range, int max_range, unsigned int seed)
        : rng(seed), dist(min_range, max_range) {
    }

    RandomSampler(int min_range = 0, int max_range = 9)
        : RandomSampler(min_range, max_range, std::random_device{}()) {
    }

    int operator()() { return dist(rng); }  // functor pattern; see: https://stackoverflow.com/a/2349878

private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
};

std::vector<int> sequential(const std::vector<int> &vec) {
    std::vector<int> hist(10);

    for (int i = 0; i < vec.size(); i++) { hist[vec[i]]++; }
    return hist;
}

// split vec into N chunks -> compute partial_hist for each one concurrently -> combine back to hist
std::vector<int> thread_partitioning(const std::vector<int>& vec) {
    std::vector<int> hist(10);

    auto threads_count = std::thread::hardware_concurrency();
    fmt::println("Partitioning work across {} threads...", threads_count);
    size_t chunk_size = vec.size() / threads_count;
    std::vector<std::thread> threads;
    // reserve is used instead of sized initialization (i.e. std::vector<std::thread> threads(threads_count)) because it initializes empty threads unnecessarily
    threads.reserve(threads_count);
    std::vector<std::vector<int>> partial_hists(threads_count, hist);

    // partitioning all threads throughout vec and launching them
    for (auto i = 0; i < threads_count; i++) {
        auto &partial_hist = partial_hists[i];
        
        // chunk range is left-closed, right-open interval [begin, end)
        size_t begin = i * chunk_size;
        size_t end = (i == threads_count - 1) ? vec.size() : (i + 1) * chunk_size;  // last chunk size is till end of vec
        
        threads.emplace_back([begin, end, &partial_hist, &vec]() {  // get launched immediately
            for (auto i = begin; i < end; i++) { partial_hist[vec[i]]++; }
        });
    }

    // waiting for all threads to finish
    for (auto &thread : threads) { 
        // each .join() call is blocking, so the call for the first thread will block the main thread
        // all other .join() call will block the main thread for much less time because they 
        // were given extra breathing room while I waited for the previous threads
        thread.join();
    }

    // combining all parital_hists together back into hist
    for (auto& partial_hist : partial_hists) {
        for (size_t i = 0; i < partial_hist.size(); i++) {
            hist[i] += partial_hist[i];
        }
    }
    return hist;
}

void benchmark(const std::string& benchmark_name, const std::function<std::vector<int>(std::vector<int>)> &fn, const std::vector<int>& vec) {
    auto start = chrono::steady_clock::now();
    auto hist = fn(vec);
    auto end = chrono::steady_clock::now();
    fmt::println("[{}] Computed histogram in {}", benchmark_name, chrono::duration_cast<chrono::milliseconds>(end - start));

    fmt::print("element   count\n{:->8}  {:->5}\n", "", "");
    for (size_t i = 0; i < hist.size(); ++i) {
        fmt::print("{:<8}  {:L}\n", i, hist[i]);
    }
    fmt::println("");  // adds a new line for a reasonable formatting when sequentially calling benchmark()
}


int main()
{
    // (Global) locale configuration for comma separated numeric printing with fmt
    std::locale::global(std::locale("en_US.UTF-8"));  // See: https://hackingcpp.com/cpp/libs/fmt.html

    fmt::print("Allocating 10^7 random elements... ");
    RandomSampler rng{};
    std::vector<int> vec((int)pow(10, 7));
    for (int i = 0; i < vec.size(); i++) { vec[i] = rng(); }
    fmt::println("done\n");
    
    benchmark("sequential", sequential, vec);
    benchmark("thread_partitioning", thread_partitioning, vec);
    return 0;
}

