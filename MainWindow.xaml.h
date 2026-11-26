#pragma once
#include "MainWindow.g.h"
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <chrono>

namespace winrt::MyFpsCounterApp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        int32_t myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        // FPS Counter Members
        uint32_t m_frame_count{ 0 };
        std::chrono::high_resolution_clock::time_point m_last_time;
        Microsoft::UI::Xaml::Media::CompositionTarget::Rendering_revoker m_rendering_revoker;

        // FPS Counter Method
        void OnRendering(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& args);
    };
}

namespace winrt::MyFpsCounterApp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}