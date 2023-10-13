#include "pch.h"

#include "MainWindow.xaml.h"

#include "WinUIEx.h"

#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;

namespace winrt::ProPractice::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        ExtendsContentIntoTitleBar(true);
        SetTitleBar(AppTitleBar());
        WinUIEx::SetIcon(*this, L"Assets/Square44x44Logo.scale-200.ico");
        WinUIEx::CenterOnScreen(*this);
    }

    bool MainWindow::AreNavigationMenuItemsEnabled()
    {
        return _areNavigationMenuItemsEnabled;
    }

    void MainWindow::AreNavigationMenuItemsEnabled(bool value)
    {
        if (_areNavigationMenuItemsEnabled != value)
        {
            _areNavigationMenuItemsEnabled = value;
            _propertyChanged(*this, Data::PropertyChangedEventArgs{ L"AreNavigationMenuItemsEnabled" });
        }
    }

    void MainWindow::NavView_SelectionChanged(IInspectable const& sender, NavigationViewSelectionChangedEventArgs const& args)
    {
        const auto selectedItem = unbox_value<IFrameworkElement>(args.SelectedItem());
        const TypeName pageTypeName { L"ProPractice." + unbox_value<hstring>(selectedItem.Tag()) + L"Page", TypeKind::Metadata };
        // ReSharper disable once CppExpressionWithoutSideEffects
        ContentFrame().Navigate(pageTypeName, *this);
    }

    winrt::event_token MainWindow::PropertyChanged(Data::PropertyChangedEventHandler const& handler)
    {
        return _propertyChanged.add(handler);
    }

    void MainWindow::PropertyChanged(winrt::event_token const& token) noexcept
    {
        _propertyChanged.remove(token);
    }
}
