#include <random>
#include <fmt/core.h>
#include <fmt/ranges.h>  // Must be included to be able to fmt::print vectors and other containers
#include <fmt/chrono.h>  // Must be included for duration and point in time printing
#include <locale>  // Configure locale for fmt
#include <chrono>

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

int main()
{
    // (Global) locale configuration for comma separated numeric printing with fmt
    std::locale::global(std::locale("en_US.UTF-8"));  // See: https://hackingcpp.com/cpp/libs/fmt.html

    fmt::print("Allocating 10^7 random elements... ");
    RandomSampler rng{};
    std::vector<int> vec((int)pow(10, 7));
    for (int i = 0; i < vec.size(); i++) { vec[i] = rng(); }
    fmt::println("done");

    std::vector<int> hist(10);
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < vec.size(); i++) { hist[vec[i]]++; }
    auto end = chrono::steady_clock::now();
    
    fmt::println("Computed histogram in {}", chrono::duration_cast<chrono::milliseconds>(end - start));
    fmt::print("element   count\n{:->8}  {:->5}\n", "", "");
    for (size_t i = 0; i < hist.size(); ++i) {
        fmt::print("{:<8}  {:L}\n", i, hist[i]);
    }
}

