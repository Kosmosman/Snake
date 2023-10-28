//
// Created by Joaquina Daeron on 10/28/23.
//

#ifndef SNAKE_JOINABLE_THREAD_H
#define SNAKE_JOINABLE_THREAD_H

#include <thread>

namespace joaquind {

    class Jthread {
    public:
        Jthread() noexcept = default;

        template<typename Callable, typename ... Args>
        explicit Jthread(Callable &&func, Args &&...args) :
                thread_(std::forward<Callable>(func), std::forward<Args>(args)...) {};

        explicit Jthread(std::thread other) noexcept: thread_{std::move(other)} {};

        Jthread(Jthread &&other) noexcept: thread_{std::move(other.thread_)} {};

        ~Jthread() noexcept {
            if (joinable())
                join();
        }

        Jthread &operator=(const Jthread &other) = delete;

        Jthread &operator=(Jthread &&other) noexcept {
            if (joinable())
                join();
            thread_ = std::move(other.thread_);
            return *this;
        };

        [[nodiscard]] bool joinable() const { return thread_.joinable(); };

        void join() { thread_.join(); };

        void detach() { thread_.detach(); };

        std::thread &operator*() noexcept { return thread_; };

        const std::thread &operator*() const noexcept { return thread_; };

        [[nodiscard]] std::thread::id get_id() const noexcept { return thread_.get_id(); };

    private:
        std::thread thread_;
    };

} // joaquind

#endif //SNAKE_JOINABLE_THREAD_H
