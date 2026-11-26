#include "pch.h"
#include "MainWindow.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <format>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::MyFpsCounterApp::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        m_last_time = std::chrono::high_resolution_clock::now();
        m_rendering_revoker = Microsoft::UI::Xaml::Media::CompositionTarget::Rendering(winrt::auto_revoke, { this, &MainWindow::OnRendering });
    }

    int32_t MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        // Default button click handler - you can remove this if you want
        return 0;
    }

    void MainWindow::OnRendering(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::Foundation::IInspectable const&)
    {
        m_frame_count++;
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - m_last_time);

        if (elapsed_time.count() >= 1)
        {
            double fps = static_cast<double>(m_frame_count) / elapsed_time.count();
            winrt::hstring fps_string = winrt::to_hstring(std::format(L"FPS: {:.2f}", fps));

            DispatcherQueue().TryEnqueue([this, fps_string]()
                {
                    FpsTextBlock().Text(fps_string);
                });

            m_frame_count = 0;
            m_last_time = current_time;
        }
    }
}