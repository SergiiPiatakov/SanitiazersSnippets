#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>

int main (int argc, char ** argv)
{
    constexpr size_t size {128};
    std::array <char, size> dataA;
    std::array <char, size> dataB;

    std::mutex mutexA;
    std::mutex mutexB;

    const auto equalize = [&](){
        while (true) {
            std::this_thread::sleep_for (std::chrono::microseconds (1) );
            std::lock_guard <std::mutex> guardA (mutexA);
            std::lock_guard <std::mutex> guardB (mutexB);
            for (size_t i = 0; i < size; ++i) {
                if (dataA [i] != dataB [i]) {
                    dataA [i]  = dataB [i];
                }
            }
        }
    };

    const auto modify = [&](){
        while (true) {
            std::this_thread::sleep_for (std::chrono::microseconds (1) );
            std::lock_guard <std::mutex> guardB (mutexB);
            std::lock_guard <std::mutex> guardA (mutexA);
            for (size_t i = 0; i < size; ++i) {
                if (dataA [i] == dataB [i]) {
                    dataB [i]++;
                }
            }
        }
    };

    std::thread threadA (equalize);
    std::thread threadB (modify);

    threadA.join ();
    threadB.join ();

    return EXIT_SUCCESS;
}
