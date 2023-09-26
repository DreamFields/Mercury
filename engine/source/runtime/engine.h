#pragma once

#include <filesystem>
#include <string>
#include <chrono>

namespace Mercury
{
    class MercuryEngine
    {
        friend class MercuryEditor; // 使得编辑器MercuryEditor类可以访问引擎MercuryEngine的私有和保护成员
    public:
        void startEngine(const std::string& config_file_path);
        void shutdownEngine();

        void initialize();
        void clear();

        void run();
        bool tickOneFrame(float delta_time);
        int getFPS() const { return m_fps; }

    protected:
        float calculateDeltaTime();

    protected:
        int m_fps{ 0 };
        std::chrono::steady_clock::time_point m_last_tick_time_point{ std::chrono::steady_clock::now() };

    };



} // namespace Mercury
